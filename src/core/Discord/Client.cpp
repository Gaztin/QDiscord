#include "Client.h"

#include "Discord/Objects/Guild.h"
#include "Discord/Patches/ChannelPatch.h"
#include "Discord/Patches/GuildPatch.h"
#include "Discord/GatewayEvents.h"

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
	
	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
		Channel channel(data);

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

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
		Message message(data);

		promise->resolve(message);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getMessages(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Message> messages;
		for (QJsonValue value : data)
		{
			messages.append(Message(value.toObject()));
		}

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

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Reaction> reactions;
		for (QJsonValue value : data)
		{
			reactions.append(Reaction(value.toObject()));
		}

		promise->resolve(reactions);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getPins(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/pins").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
		QList<Message> pins;
		for (QJsonValue value : data)
		{
			pins.append(Message(value.toObject()));
		}

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

void Client::modifyChannel(snowflake_t channel_id,
		const ChannelPatch& channel_patch)
{
	QString endpoint = QString("/channels/%1").arg(channel_id);
	QJsonObject payload(channel_patch);

	http_service_.patch(token_, endpoint, payload);
}

void Client::modifyGuild(snowflake_t guild_id, const GuildPatch& guild_patch)
{
	QString endpoint = QString("/guilds/%1").arg(guild_id);
	QJsonObject payload(guild_patch);

	http_service_.patch(token_, endpoint, payload);
}

void Client::onGatewayEvent(const QString& name, const QJsonObject& data)
{
	switch (Events::idFromName(name))
	{
		case EventId::READY:
		{
			User user(data["user"].toObject());
			QList<Channel> private_channels;
			QJsonArray private_channels_array =
				data["private_channels"].toArray();
			for (QJsonValue private_channel_value : private_channels_array)
			{
				private_channels.append(Channel(
					private_channel_value.toObject()));
			}

			QList<Guild> guilds;
			QJsonArray guilds_array = data["guilds"].toArray();
			for (QJsonValue guild_value : guilds_array)
			{
				guilds.append(Guild(guild_value.toObject()));
			}

			onReady(user, private_channels, guilds);

			session_id_ = data["session_id"].toString();
		}
		break;

		case EventId::CHANNEL_CREATE:
		{
			Channel new_channel(data);
			onChannelCreate(new_channel);
		}
		break;

		case EventId::CHANNEL_UPDATE:
		{
			Channel updated_channel(data);
			onChannelUpdate(updated_channel);
		}
		break;

		case EventId::CHANNEL_DELETE:
		{
			Channel deleted_channel(data);
			onChannelDelete(deleted_channel);
		}
		break;

		case EventId::CHANNEL_PINS_UPDATE:
		{
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			QDateTime last_pin_timestamp = QDateTime::fromString(
				data["joined_at"].toString(), Qt::ISODate);
			onChannelPinsUpdate(channel_id, last_pin_timestamp);
		}
		break;

		case EventId::GUILD_CREATE:
		{
			Guild guild(data);
			onGuildCreate(guild);
		}
		break;

		case EventId::GUILD_UPDATE:
		{
			Guild guild(data);
			onGuildUpdate(guild);
		}
		break;

		case EventId::GUILD_DELETE:
		{
			snowflake_t guild_id = data["id"].toString().toULongLong();
			bool unavailable = data["unavailable"].toBool();
			onGuildDelete(guild_id, unavailable);
		}
		break;

		case EventId::GUILD_BAN_ADD:
		{
			User banned_user(data);
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			onGuildBanAdd(banned_user, guild_id);
		}
		break;

		case EventId::GUILD_BAN_REMOVE:
		{
			User banned_user(data);
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			onGuildBanRemove(banned_user, guild_id);
		}
		break;

		case EventId::GUILD_EMOJIS_UPDATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			QList<Emoji> emojis;
			QJsonArray emojis_array = data["emojis"].toArray();
			for (QJsonValue emoji_value : emojis_array)
			{
				emojis.append(Emoji(emoji_value.toObject()));
			}

			onGuildEmojisUpdate(guild_id, emojis);
		}
		break;

		case EventId::GUILD_INTEGRATIONS_UPDATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			onGuildIntegrationsUpdate(guild_id);
		}
		break;

		case EventId::GUILD_MEMBER_ADD:
		{
			GuildMember guild_member(data);
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			onGuildMemberAdd(guild_member, guild_id);
		}
		break;

		case EventId::GUILD_MEMBER_REMOVE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			User removed_user(data["user"].toObject());
			onGuildMemberRemove(guild_id, removed_user);
		}
		break;

		case EventId::GUILD_MEMBER_UPDATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			User user(data["user"].toObject());
			QString nick = data["nick"].toString();
			QList<snowflake_t> roles;
			QJsonArray roles_array = data["roles"].toArray();
			for (QJsonValue role_value : roles_array)
			{
				roles.append(role_value.toString().toULongLong());
			}

			onGuildMemberUpdate(guild_id, roles, user, nick);
		}
		break;

		case EventId::GUILD_ROLE_CREATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			QList<GuildMember> members;
			QJsonArray members_array = data["members"].toArray();
			for (QJsonValue member_value : members_array)
			{
				members.append(GuildMember(member_value.toObject()));
			}

			onGuildRoleCreate(guild_id, members);
		}
		break;

		case EventId::GUILD_ROLE_UPDATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			Role role(data["role"].toObject());
			onGuildRoleUpdate(guild_id, role);
		}
		break;

		case EventId::GUILD_ROLE_DELETE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			snowflake_t role_id = data["role_id"].toString().toULongLong();
			onGuildRoleDelete(guild_id, role_id);
		}
		break;

		case EventId::MESSAGE_CREATE:
		{
			Message message(data);
			onMessageCreate(message);
		}
		break;

		case EventId::MESSAGE_UPDATE:
		{
			Message message(data);
			onMessageUpdate(message);
		}
		break;

		case EventId::MESSAGE_DELETE:
		{
			snowflake_t id = data["id"].toString().toULongLong();
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			onMessageDelete(id, channel_id);
		}
		break;

		case EventId::MESSAGE_DELETE_BULK:
		{
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			QList<snowflake_t> ids;
			QJsonArray ids_array = data["ids"].toArray();
			for (QJsonValue id_value : ids_array)
			{
				ids.append(id_value.toString().toULongLong());
			}

			onMessageDeleteBulk(ids, channel_id);
		}
		break;

		case EventId::MESSAGE_REACTION_ADD:
		{
			snowflake_t user_id = data["user_id"].toString().toULongLong();
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			snowflake_t message_id =
				data["message_id"].toString().toULongLong();
			Emoji emoji(data["emoji"].toObject());
			onMessageReactionAdd(user_id, channel_id, message_id, emoji);
		}
		break;

		case EventId::MESSAGE_REACTION_REMOVE:
		{
			snowflake_t user_id = data["user_id"].toString().toULongLong();
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			snowflake_t message_id =
				data["message_id"].toString().toULongLong();
			Emoji emoji(data["emoji"].toObject());
			onMessageReactionRemove(user_id, channel_id, message_id, emoji);
		}
		break;

		case EventId::MESSAGE_REACTION_REMOVE_ALL:
		{
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
			snowflake_t message_id =
				data["message_id"].toString().toULongLong();
			onMessageReactionRemoveAll(channel_id, message_id);
		}
		break;

		case EventId::PRESENCE_UPDATE:
		{
			User user(data["user"].toObject());
			Activity activity(data["game"].toObject());
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			QString status = data["status"].toString();
			QList<snowflake_t> roles;
			QJsonArray roles_array = data["roles"].toArray();
			for (QJsonValue role_value : roles_array)
			{
				roles.append(role_value.toString().toULongLong());
			}

			onPresenceUpdate(user, roles, activity, guild_id, status);
		}
		break;

		case EventId::TYPING_START:
		{
			snowflake_t channel_id = data["channel_id"].toString().toULongLong();
			snowflake_t user_id = data["user_id"].toString().toULongLong();
			int timestamp = data["timestamp"].toInt();
			onTypingStart(channel_id, user_id, timestamp);
		}
		break;

		case EventId::USER_UPDATE:
		{
			User user(data);
			onUserUpdate(user);
		}
		break;

		case EventId::VOICE_STATE_UPDATE:
		{
			VoiceState voice_state(data);
			onVoiceStateUpdate(voice_state);
		}
		break;

		case EventId::VOICE_SERVER_UPDATE:
		{
			QString token = data["token"].toString();
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			QString endpoint = data["endpoint"].toString();
			onVoiceServerUpdate(token, guild_id, endpoint);
		}
		break;

		case EventId::WEBHOOKS_UPDATE:
		{
			snowflake_t guild_id = data["guild_id"].toString().toULongLong();
			snowflake_t channel_id =
				data["channel_id"].toString().toULongLong();
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