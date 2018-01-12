#include "Client.h"

#include "Discord/GatewayEvents.h"
#include "Discord/Serializer.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkReply>

QDISCORD_NAMESPACE_BEGIN

Client::Client(const QString& user_agent, QObject* parent)
	: QObject(parent)
	, token_()
	, session_id_()
	, gateway_socket_(this)
	, http_service_(user_agent, this)
{
	connect(&gateway_socket_, &GatewaySocket::event, this,
		&Client::onGatewayEvent);
}

void Client::login(const Token& token)
{
	token_ = token;

	QString endpoint;
	switch (token.type())
	{
		case Token::Type::BOT:
			endpoint = "/gateway/bot";
		break;

		default:
			endpoint = "/gateway";
		break;
	}

	QNetworkReply* get_gateway_reply = http_service_.get(token, endpoint);

	connect(get_gateway_reply, &QNetworkReply::finished, this,
		&Client::onHttpGetGatewayReply);
}

void Client::logout()
{
	gateway_socket_.disconnectFromGateway();
}

Promise<Channel>& Client::getChannel(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<Channel>* promise = new Promise<Channel>(reply);
	
	connect(reply, &QNetworkReply::finished, [&]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
		Channel channel = Serializer::channel(data);

		promise->resolve(channel);
	});

	return (*promise);
}

Promise<Message>& Client::getMessage(snowflake_t channel_id,
		snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/messages/%2").arg(channel_id).arg(
		message_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<Message>* promise = new Promise<Message>(reply);

	connect(reply, &QNetworkReply::finished, [&]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
		Message message = Serializer::message(data);

		promise->resolve(message);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getMessages(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [&]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Message> messages = Serializer::array<Message>(data);

		promise->resolve(messages);
	});

	return (*promise);
}

Promise<QList<Reaction>>& Client::getReactions(snowflake_t channel_id,
		snowflake_t message_id, const QString& emoji)
{
	QString endpoint = QString("/channels/%1/messages/%2/reactions/%3").arg(
		channel_id).arg(message_id).arg(emoji);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Reaction>>* promise = new Promise<QList<Reaction>>(reply);

	connect(reply, &QNetworkReply::finished, [&]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Reaction> reactions = Serializer::array<Reaction>(data);

		promise->resolve(reactions);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getPins(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/pins").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [&]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Message> pins = Serializer::array<Message>(data);

		promise->resolve(pins);
	});

	return (*promise);
}

void Client::sendMessage(snowflake_t channel_id, const QString& content)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QJsonObject payload;

	payload["content"] = content;

	http_service_.post(token_, endpoint, payload);
}

void Client::addReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji)
{
	QString endpoint = QString(
		"/channels/%1/messages/%2/reactions/%3/@me").arg(channel_id).arg(
			message_id).arg(emoji);

	http_service_.put(token_, endpoint, QJsonObject());
}

void Client::removeReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji, snowflake_t user_id)
{
	QString user_string = (user_id == 0) ? "@me" : QString::number(user_id);
	QString endpoint = QString("/channels/%1/messages/%2/reactions/%3/%4").arg(
		channel_id).arg(message_id).arg(emoji).arg(user_string);

	http_service_.del(token_, endpoint);
}

void Client::removeAllReactions(snowflake_t channel_id, snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/messages/%2/reactions").arg(
		channel_id).arg(message_id);

	http_service_.del(token_, endpoint);
}

void Client::triggerTypingIndicator(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/typing").arg(channel_id);

	http_service_.post(token_, endpoint, QJsonObject());
}

void Client::onGatewayEvent(const QString& name, const QJsonObject& data)
{
	switch (Events::idFromName(name))
	{
		case EventId::READY:
		{
			User user = Serializer::user(data["user"].toObject());
			QList<Channel> private_channels = Serializer::array<Channel>(
				data["private_channels"].toArray());
			QList<Guild> guilds = Serializer::array<Guild>(
				data["guilds"].toArray());
			onReady(user, private_channels, guilds);

			session_id_ = data["session_id"].toString();
		}
		break;

		case EventId::CHANNEL_CREATE:
		{
			Channel new_channel = Serializer::channel(data);
			onChannelCreate(new_channel);
		}
		break;

		case EventId::CHANNEL_UPDATE:
		{
			Channel updated_channel = Serializer::channel(data);
			onChannelUpdate(updated_channel);
		}
		break;

		case EventId::CHANNEL_DELETE:
		{
			Channel deleted_channel = Serializer::channel(data);
			onChannelDelete(deleted_channel);
		}
		break;

		case EventId::CHANNEL_PINS_UPDATE:
		{
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			QDateTime last_pin_timestamp = Serializer::timestamp(
				data["joined_at"]);
			onChannelPinsUpdate(channel_id, last_pin_timestamp);
		}
		break;

		case EventId::GUILD_CREATE:
		{
			Guild guild = Serializer::guild(data);
			onGuildCreate(guild);
		}
		break;

		case EventId::GUILD_UPDATE:
		{
			Guild guild = Serializer::guild(data);
			onGuildUpdate(guild);
		}
		break;

		case EventId::GUILD_DELETE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["id"]);
			bool unavailable = data["unavailable"].toBool();
			onGuildDelete(guild_id, unavailable);
		}
		break;

		case EventId::GUILD_BAN_ADD:
		{
			User banned_user = Serializer::user(data);
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			onGuildBanAdd(banned_user, guild_id);
		}
		break;

		case EventId::GUILD_BAN_REMOVE:
		{
			User banned_user = Serializer::user(data);
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			onGuildBanRemove(banned_user, guild_id);
		}
		break;

		case EventId::GUILD_EMOJIS_UPDATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			QList<Emoji> emojis = Serializer::array<Emoji>(
				data["emojis"].toArray());
			onGuildEmojisUpdate(guild_id, emojis);
		}
		break;

		case EventId::GUILD_INTEGRATIONS_UPDATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			onGuildIntegrationsUpdate(guild_id);
		}
		break;

		case EventId::GUILD_MEMBER_ADD:
		{
			GuildMember guild_member = Serializer::guildMember(data);
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			onGuildMemberAdd(guild_member, guild_id);
		}
		break;

		case EventId::GUILD_MEMBER_REMOVE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			User removed_user = Serializer::user(data["user"].toObject());
			onGuildMemberRemove(guild_id, removed_user);
		}
		break;

		case EventId::GUILD_MEMBER_UPDATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			QList<snowflake_t> roles = Serializer::array<snowflake_t>(
				data["roles"].toArray());
			User user = Serializer::user(data["user"].toObject());
			QString nick = data["nick"].toString();
			onGuildMemberUpdate(guild_id, roles, user, nick);
		}
		break;

		case EventId::GUILD_ROLE_CREATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			QList<GuildMember> members = Serializer::array<GuildMember>(
				data["members"].toArray());
			onGuildRoleCreate(guild_id, members);
		}
		break;

		case EventId::GUILD_ROLE_UPDATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			Role role = Serializer::role(data["role"].toObject());
			onGuildRoleUpdate(guild_id, role);
		}
		break;

		case EventId::GUILD_ROLE_DELETE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			snowflake_t role_id = Serializer::snowflake(data["role_id"]);
			onGuildRoleDelete(guild_id, role_id);
		}
		break;

		case EventId::MESSAGE_CREATE:
		{
			Message message = Serializer::message(data);
			onMessageCreate(message);
		}
		break;

		case EventId::MESSAGE_UPDATE:
		{
			Message message = Serializer::message(data);
			onMessageUpdate(message);
		}
		break;

		case EventId::MESSAGE_DELETE:
		{
			snowflake_t id = Serializer::snowflake(data["id"]);
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			onMessageDelete(id, channel_id);
		}
		break;

		case EventId::MESSAGE_DELETE_BULK:
		{
			QList<snowflake_t> ids = Serializer::array<snowflake_t>(
				data["ids"].toArray());
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			onMessageDeleteBulk(ids, channel_id);
		}
		break;

		case EventId::MESSAGE_REACTION_ADD:
		{
			snowflake_t user_id = Serializer::snowflake(data["user_id"]);
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			snowflake_t message_id = Serializer::snowflake(data["message_id"]);
			Emoji emoji = Serializer::emoji(data["emoji"].toObject());
			onMessageReactionAdd(user_id, channel_id, message_id, emoji);
		}
		break;

		case EventId::MESSAGE_REACTION_REMOVE:
		{
			snowflake_t user_id = Serializer::snowflake(data["user_id"]);
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			snowflake_t message_id = Serializer::snowflake(data["message_id"]);
			Emoji emoji = Serializer::emoji(data["emoji"].toObject());
			onMessageReactionRemove(user_id, channel_id, message_id, emoji);
		}
		break;

		case EventId::MESSAGE_REACTION_REMOVE_ALL:
		{
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			snowflake_t message_id = Serializer::snowflake(data["message_id"]);
			onMessageReactionRemoveAll(channel_id, message_id);
		}
		break;

		case EventId::PRESENCE_UPDATE:
		{
			User user = Serializer::user(data["user"].toObject());
			QList<snowflake_t> roles = Serializer::array<snowflake_t>(
				data["roles"].toArray());
			Activity activity = Serializer::activity(data["game"].toObject());
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			QString status = data["status"].toString();
			onPresenceUpdate(user, roles, activity, guild_id, status);
		}
		break;

		case EventId::TYPING_START:
		{
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			snowflake_t user_id = Serializer::snowflake(data["user_id"]);
			int timestamp = data["timestamp"].toInt();
			onTypingStart(channel_id, user_id, timestamp);
		}
		break;

		case EventId::USER_UPDATE:
		{
			User user = Serializer::user(data);
			onUserUpdate(user);
		}
		break;

		case EventId::VOICE_STATE_UPDATE:
		{
			VoiceState voice_state = Serializer::voiceState(data);
			onVoiceStateUpdate(voice_state);
		}
		break;

		case EventId::VOICE_SERVER_UPDATE:
		{
			QString token = data["token"].toString();
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			QString endpoint = data["endpoint"].toString();
			onVoiceServerUpdate(token, guild_id, endpoint);
		}
		break;

		case EventId::WEBHOOKS_UPDATE:
		{
			snowflake_t guild_id = Serializer::snowflake(data["guild_id"]);
			snowflake_t channel_id = Serializer::snowflake(data["channel_id"]);
			onWebhooksUpdate(guild_id, channel_id);
		}
		break;

		default:
			onUnhandledEvent(name, data);
		break;
	}
}

void Client::onHttpGetGatewayReply()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
	QString url = data["url"].toString();

	gateway_socket_.connectToGateway(url, token_);
}

void Client::onHttpGetGatewayBotReply()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
	QString url = data["url"].toString();
//	int shards = data["shards"].toInt();

	gateway_socket_.connectToGateway(url, token_);
}

QDISCORD_NAMESPACE_END