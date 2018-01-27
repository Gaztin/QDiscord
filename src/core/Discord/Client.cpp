#include "Client.h"

#include "Discord/Objects/Ban.h"
#include "Discord/Objects/Guild.h"
#include "Discord/Objects/GuildEmbed.h"
#include "Discord/Objects/Integration.h"
#include "Discord/Objects/VoiceRegion.h"
#include "Discord/Patches/ChannelPatch.h"
#include "Discord/Patches/EmojiPatch.h"
#include "Discord/Patches/GuildPatch.h"
#include "Discord/Patches/GuildEmbedPatch.h"
#include "Discord/Patches/GuildMemberPatch.h"
#include "Discord/Patches/IntegrationPatch.h"
#include "Discord/Patches/MessagePatch.h"
#include "Discord/Patches/RolePatch.h"
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

		QJsonObject channel_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		Channel channel(channel_object);

		promise->resolve(channel);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getChannelMessages(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray channel_messages_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Message> messages;
		for (QJsonValue channel_message_value : channel_messages_array)
		{
			messages.append(Message(channel_message_value.toObject()));
		}

		promise->resolve(messages);
	});

	return (*promise);
}

Promise<Message>& Client::getChannelMessage(snowflake_t channel_id,
		snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/messages/%2").arg(channel_id).arg(
		message_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<Message>* promise = new Promise<Message>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject channel_message_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		Message message(channel_message_object);

		promise->resolve(message);
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

		QJsonArray reactions_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Reaction> reactions;
		for (QJsonValue reaction_value : reactions_array)
		{
			reactions.append(Reaction(reaction_value.toObject()));
		}

		promise->resolve(reactions);
	});

	return (*promise);
}

Promise<QList<Invite>>& Client::getChannelInvites(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/invites").arg(channel_id);

	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Invite>>* promise = new Promise<QList<Invite>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray invites_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Invite> invites;
		for (QJsonValue invite_value : invites_array)
		{
			invites.append(Invite(invite_value.toObject()));
		}

		promise->resolve(invites);
	});

	return (*promise);
}

Promise<QList<Message>>& Client::getPinnedMessages(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1/pins").arg(channel_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Message>>* promise = new Promise<QList<Message>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray pinned_messages_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Message> pins;
		for (QJsonValue pinned_message_value : pinned_messages_array)
		{
			pins.append(Message(pinned_message_value.toObject()));
		}

		promise->resolve(pins);
	});

	return (*promise);
}

Promise<QList<Emoji>>& Client::listGuildEmojis(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/emojis").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Emoji>>* promise = new Promise<QList<Emoji>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_emojis_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Emoji> emojis;
		for (QJsonValue guild_emoji_value : guild_emojis_array)
		{
			emojis.append(Emoji(guild_emoji_value.toObject()));
		}

		promise->resolve(emojis);
	});

	return (*promise);
}

Promise<Emoji>& Client::getGuildEmoji(snowflake_t guild_id,
		snowflake_t emoji_id)
{
	QString endpoint = QString("/guilds/%1/emojis/%2").arg(guild_id).arg(
		emoji_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<Emoji>* promise = new Promise<Emoji>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject guild_emoji_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		Emoji emoji(guild_emoji_object);

		promise->resolve(emoji);
	});

	return (*promise);
}

Promise<Guild>& Client::getGuild(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<Guild>* promise = new Promise<Guild>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject guild_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		Guild guild(guild_object);

		promise->resolve(guild);
	});

	return (*promise);
}

Promise<QList<Channel>>& Client::getGuildChannels(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/channels").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Channel>>* promise = new Promise<QList<Channel>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_channels_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Channel> channels;
		for (QJsonValue guild_channel_value : guild_channels_array)
		{
			channels.append(Channel(guild_channel_value.toObject()));
		}

		promise->resolve(channels);
	});

	return (*promise);
}

Promise<GuildMember>& Client::getGuildMember(snowflake_t guild_id,
		snowflake_t user_id)
{
	QString endpoint = QString("/guilds/%1/members/%2").arg(guild_id).arg(
		user_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<GuildMember>* promise = new Promise<GuildMember>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject guild_member_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		GuildMember guild_member(guild_member_object);

		promise->resolve(guild_member);
	});

	return (*promise);
}

Promise<QList<GuildMember>>& Client::listGuildMembers(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/members").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<GuildMember>>* promise = new Promise<QList<GuildMember>>(
		reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_members_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<GuildMember> members;
		for (QJsonValue guild_member_value : guild_members_array)
		{
			members.append(GuildMember(guild_member_value.toObject()));
		}

		promise->resolve(members);
	});

	return (*promise);
}

Promise<QList<Ban>>& Client::getGuildBans(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/bans").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Ban>>* promise = new Promise<QList<Ban>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_bans_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Ban> bans;
		for (QJsonValue guild_ban_value : guild_bans_array)
		{
			bans.append(Ban(guild_ban_value.toObject()));
		}

		promise->resolve(bans);
	});

	return (*promise);
}

Promise<QList<Role>>& Client::getGuildRoles(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/roles").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Role>>* promise = new Promise<QList<Role>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_roles_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Role> roles;
		for (QJsonValue guild_role_value : guild_roles_array)
		{
			roles.append(Role(guild_role_value.toObject()));
		}

		promise->resolve(roles);
	});

	return (*promise);
}

Promise<int>& Client::getGuildPruneCount(snowflake_t guild_id, int days)
{
	QString endpoint = QString("/guilds/%1/prune").arg(guild_id);
	QJsonObject payload;

	payload["days"] = days;

	QNetworkReply* reply = http_service_.get(token_, endpoint, payload);
	Promise<int>* promise = new Promise<int>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		const QJsonObject guild_prune_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		int pruned = guild_prune_object["pruned"].toInt();

		promise->resolve(pruned);
	});

	return (*promise);
}

Promise<QList<VoiceRegion>>& Client::getGuildVoiceRegions(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/regions").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<VoiceRegion>>* promise = new Promise<QList<VoiceRegion>>(
		reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_voice_regions_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<VoiceRegion> voice_regions;
		for (QJsonValue guild_voice_region_value : guild_voice_regions_array)
		{
			voice_regions.append(VoiceRegion(
				guild_voice_region_value.toObject()));
		}

		promise->resolve(voice_regions);
	});

	return (*promise);
}

Promise<QList<Invite>>& Client::getGuildInvites(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/invites").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Invite>>* promise = new Promise<QList<Invite>>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_invites_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Invite> invites;
		for (QJsonValue guild_invite_value : guild_invites_array)
		{
			invites.append(Invite(guild_invite_value.toObject()));
		}

		promise->resolve(invites);
	});

	return (*promise);
}

Promise<QList<Integration>>& Client::getGuildIntegrations(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/integrations").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<QList<Integration>>* promise = new Promise<QList<Integration>>(
		reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonArray guild_integrations_array = QJsonDocument::fromJson(
			reply->readAll()).array();
		QList<Integration> integrations;
		for (QJsonValue guild_integration_value : guild_integrations_array)
		{
			integrations.append(Integration(
				guild_integration_value.toObject()));
		}

		promise->resolve(integrations);
	});

	return (*promise);
}

Promise<GuildEmbed>& Client::getGuildEmbed(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1/embed").arg(guild_id);
	QNetworkReply* reply = http_service_.get(token_, endpoint);
	Promise<GuildEmbed>* promise = new Promise<GuildEmbed>(reply);

	connect(reply, &QNetworkReply::finished, [reply, promise]{
		if (reply->error() != QNetworkReply::NoError)
			return promise->reject();

		QJsonObject guild_embed_object = QJsonDocument::fromJson(
			reply->readAll()).object();
		GuildEmbed guild_embed(guild_embed_object);

		promise->resolve(guild_embed);
	});

	return (*promise);
}

void Client::deleteChannel(snowflake_t channel_id)
{
	QString endpoint = QString("/channels/%1").arg(channel_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteOwnReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji)
{
	QString endpoint = QString(
		"/channels/%1/messages/%2/reactions/%3/@me").arg(channel_id).arg(
			message_id).arg(emoji);

	http_service_.del(token_, endpoint);
}

void Client::deleteUserReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji, snowflake_t user_id)
{
	QString endpoint = QString("/channels/%1/messages/%2/reactions/%3/%4").arg(
		channel_id).arg(message_id).arg(emoji).arg(user_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteAllReactions(snowflake_t channel_id, snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/messages/%2/reactions").arg(
		channel_id).arg(message_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteMessage(snowflake_t channel_id, snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/messages/%2").arg(channel_id).arg(
		message_id);

	http_service_.del(token_, endpoint);
}

void Client::bulkDeleteMessages(snowflake_t channel_id,
		const QList<snowflake_t>& message_ids)
{
	QString endpoint = QString("/channels/%1/messages/bulk-delete").arg(
		channel_id);
	QJsonArray message_ids_array;
	QJsonObject payload;

	for (snowflake_t message_id : message_ids)
		message_ids_array.append(QString::number(message_id));

	payload["messages"] = message_ids_array;

	http_service_.post(token_, endpoint, payload);
}

void Client::deleteChannelPermission(snowflake_t channel_id,
		snowflake_t overwrite_id)
{
	QString endpoint = QString("/channels/%1/permissions/%2").arg(
		channel_id).arg(overwrite_id);

	http_service_.del(token_, endpoint);
}

void Client::deletePinnedChannelMessage(snowflake_t channel_id,
		snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/pins/%2").arg(channel_id).arg(
		message_id);

	http_service_.del(token_, endpoint);
}

void Client::groupDmRemoveRecipient(snowflake_t channel_id,
		snowflake_t user_id)
{
	QString endpoint = QString("/channels/%1/recipients/%2").arg(
		channel_id).arg(user_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteGuildEmoji(snowflake_t guild_id, snowflake_t emoji_id)
{
	QString endpoint = QString("/guilds/%1/emojis/%2").arg(guild_id).arg(
		emoji_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteGuild(snowflake_t guild_id)
{
	QString endpoint = QString("/guilds/%1").arg(guild_id);

	http_service_.del(token_, endpoint);
}

void Client::removeGuildMemberRole(snowflake_t guild_id, snowflake_t user_id,
		snowflake_t role_id)
{
	QString endpoint = QString("/guilds/%1/members/%2/roles/%3").arg(
		guild_id).arg(user_id).arg(role_id);

	http_service_.del(token_, endpoint);
}

void Client::removeGuildMember(snowflake_t guild_id, snowflake_t user_id)
{
	QString endpoint = QString("/guilds/%1/members/%2").arg(guild_id).arg(
		user_id);

	http_service_.del(token_, endpoint);
}

void Client::removeGuildBan(snowflake_t guild_id, snowflake_t user_id)
{
	QString endpoint = QString("/guilds/%1/bans/%2").arg(guild_id).arg(
		user_id);

	http_service_.del(token_, endpoint);
}

void Client::deleteGuildRole(snowflake_t guild_id, snowflake_t role_id)
{
	QString endpoint = QString("/guilds/%1/roles/%2").arg(guild_id).arg(
		role_id);

	http_service_.del(token_, endpoint);
}

void Client::beginGuildPrune(snowflake_t guild_id, int days)
{
	QString endpoint = QString("/guilds/%1/prune").arg(guild_id);
	QJsonObject payload;

	payload["days"] = days;

	http_service_.post(token_, endpoint, payload);
}

void Client::deleteGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id)
{
	QString endpoint = QString("/guilds/%1/integrations/%2").arg(guild_id).arg(
		integration_id);

	http_service_.del(token_, endpoint);
}

void Client::createMessage(snowflake_t channel_id, const QString& content)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QJsonObject payload;

	payload["content"] = content;

	http_service_.post(token_, endpoint, payload);
}

void Client::createReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji)
{
	QString endpoint = QString(
		"/channels/%1/messages/%2/reactions/%3/@me").arg(channel_id).arg(
			message_id).arg(emoji);

	http_service_.put(token_, endpoint, QJsonObject());
}

void Client::createChannelInvite(snowflake_t channel_id, int max_age,
		int max_uses, bool temporary, bool unique)
{
	QString endpoint = QString("/channels/%1/invites").arg(channel_id);
	QJsonObject payload;

	payload["max_age"] = max_age;
	payload["max_uses"] = max_uses;
	payload["temporary"] = temporary;
	payload["unique"] = unique;

	http_service_.post(token_, endpoint, payload);
}

void Client::addPinnedChannelMessage(snowflake_t channel_id,
		snowflake_t message_id)
{
	QString endpoint = QString("/channels/%1/pins/%2").arg(channel_id).arg(
		message_id);

	http_service_.put(token_, endpoint, QJsonObject());
}

void Client::groupDmAddRecipient(snowflake_t channel_id, snowflake_t user_id,
		const QString& access_token, const QString& nick)
{
	QString endpoint = QString("/channels/%1/recipients/%2").arg(
		channel_id).arg(user_id);
	QJsonObject payload;

	payload["access_token"] = access_token;
	payload["nick"] = nick;

	http_service_.put(token_, endpoint, payload);
}

void Client::createGuildEmoji(snowflake_t guild_id, const QString& name,
		const QByteArray& image, const QList<snowflake_t>& role_ids)
{
	QString endpoint = QString("/guilds/%1/emojis").arg(guild_id);
	QJsonObject payload;
	QJsonArray role_ids_array;

	for (snowflake_t role_id : role_ids)
	{
		role_ids_array.append(QString::number(role_id));
	}

	payload["name"] = name;
	payload["image"] = QString(image);
	payload["roles"] = role_ids_array;

	http_service_.post(token_, endpoint, payload);
}

void Client::createGuild(const QString& name, const QString& region,
		const QString& icon, VerificationLevel verification_level,
		DefaultMessageNotificationLevel default_message_notification_level,
		ExplicitContentFilterLevel explicit_content_filter_level,
		const QList<Role>& roles, const QList<Channel>& channels)
{
	QString endpoint("/guilds");
	QJsonObject payload;
	QJsonArray roles_array, channels_array;

	for (const Role& role : roles)
	{
		roles_array.append(QJsonObject(role));
	}
	for (const Channel& channel : channels)
	{
		channels_array.append(QJsonObject(channel));
	}

	payload["name"] = name;
	payload["region"] = region;
	payload["icon"] = icon;
	payload["verification_level"] = static_cast<int>(verification_level);
	payload["default_message_notifications"] = static_cast<int>(
		default_message_notification_level);
	payload["explicit_content_filter"] = static_cast<int>(
		explicit_content_filter_level);
	payload["roles"] = roles_array;
	payload["channels"] = channels_array;

	http_service_.post(token_, endpoint, payload);
}

void Client::createGuildChannel(snowflake_t guild_id, const QString& name,
		ChannelType type, int bitrate, int user_limit,
		const QList<Overwrite>& permission_overwrites, snowflake_t parent_id,
		bool nsfw)
{
	QString endpoint = QString("/guilds/%1/channels").arg(guild_id);
	QJsonObject payload;
	QJsonArray permission_overwrites_array;

	for (const Overwrite& permission_overwrite : permission_overwrites)
	{
		permission_overwrites_array.append(QJsonObject(permission_overwrite));
	}

	payload["name"] = name;
	payload["type"] = static_cast<int>(type);
	payload["bitrate"] = bitrate;
	payload["user_limit"] = user_limit;
	payload["permission_overwrites"] = permission_overwrites_array;
	payload["parent_id"] = QString::number(parent_id);
	payload["nsfw"] = nsfw;

	http_service_.post(token_, endpoint, payload);
}

void Client::addGuildMember(snowflake_t guild_id, snowflake_t user_id,
		const QString& access_token, const QString& nick,
		const QList<snowflake_t>& roles, bool mute, bool deaf)
{
	QString endpoint = QString("/guilds/%1/members/%2").arg(guild_id, user_id);
	QJsonObject payload;
	QJsonArray roles_array;

	for (snowflake_t role : roles)
	{
		roles_array.append(QString::number(role));
	}

	payload["access_token"] = access_token;
	payload["nick"] = nick;
	payload["roles"] = roles_array;
	payload["mute"] = mute;
	payload["deaf"] = deaf;

	http_service_.put(token_, endpoint, payload);
}

void Client::addGuildMemberRole(snowflake_t guild_id, snowflake_t user_id,
		snowflake_t role_id)
{
	QString endpoint = QString("/guilds/%1/members/%2/roles/%3").arg(
		guild_id).arg(user_id).arg(role_id);

	http_service_.put(token_, endpoint, QJsonObject());
}

void Client::createGuildBan(snowflake_t guild_id, snowflake_t user_id,
		int delete_message_days, const QString& reason)
{
	QString endpoint = QString("/guilds/%1/bans/%2").arg(guild_id).arg(
		user_id);
	QJsonObject payload;

	payload["delete-message-days"] = delete_message_days;
	payload["reason"] = reason;

	http_service_.put(token_, endpoint, payload);
}

void Client::createGuildRole(snowflake_t guild_id, const QString& name,
		int permissions, int color, bool hoist, bool mentionable)
{
	QString endpoint = QString("/guilds/%1/roles").arg(guild_id);
	QJsonObject payload;

	payload["name"] = name;
	payload["permissions"] = permissions;
	payload["color"] = color;
	payload["hoist"] = hoist;
	payload["mentionable"] = mentionable;

	http_service_.post(token_, endpoint, payload);
}

void Client::createGuildIntegration(snowflake_t guild_id, const QString& type,
		snowflake_t id)
{
	QString endpoint = QString("/guilds/%1/integrations").arg(guild_id);
	QJsonObject payload;

	payload["type"] = type;
	payload["id"] = QString::number(id);

	http_service_.post(token_, endpoint, payload);
}

void Client::modifyChannel(snowflake_t channel_id,
		const ChannelPatch& channel_patch)
{
	QString endpoint = QString("/channels/%1").arg(channel_id);

	http_service_.patch(token_, endpoint, channel_patch);
}

void Client::editMessage(snowflake_t channel_id, snowflake_t message_id,
		const MessagePatch& message_patch)
{
	QString endpoint = QString("/channels/%1/messages/%2").arg(channel_id).arg(
		message_id);

	http_service_.patch(token_, endpoint, message_patch);
}

void Client::editChannelPermissions(snowflake_t channel_id,
		snowflake_t overwrite_id, int allow, int deny, const QString& type)
{
	QString endpoint = QString("/channels/%1/permissions/%2").arg(
		channel_id).arg(overwrite_id);
	QJsonObject payload;

	payload["allow"] = allow;
	payload["deny"] = deny;
	payload["type"] = type;

	http_service_.put(token_, endpoint, payload);
}

void Client::modifyGuildEmoji(snowflake_t guild_id, snowflake_t emoji_id,
		const EmojiPatch& emoji_patch)
{
	QString endpoint = QString("/guilds/%1/emojis/%2").arg(guild_id).arg(
		emoji_id);

	http_service_.patch(token_, endpoint, emoji_patch);
}

void Client::modifyGuild(snowflake_t guild_id, const GuildPatch& guild_patch)
{
	QString endpoint = QString("/guilds/%1").arg(guild_id);

	http_service_.patch(token_, endpoint, guild_patch);
}

void Client::modifyGuildChannelPositions(snowflake_t guild_id,
		const QList<QPair<snowflake_t, int>>& channel_position_updates)
{
	QString endpoint = QString("/guilds/%1/channels").arg(guild_id);
	QJsonObject payload;
	QJsonArray channel_position_updates_array;
	
	for (const QPair<snowflake_t, int>& channel_position_update :
			channel_position_updates)
	{
		QJsonObject channel_position_update_object;
		channel_position_update_object["id"] = QString::number(
			channel_position_update.first);
		channel_position_update_object["position"] =
			channel_position_update.second;

		channel_position_updates_array.append(channel_position_update_object);
	}

	http_service_.patch(token_, endpoint, payload);
}

void Client::modifyGuildMember(snowflake_t guild_id, snowflake_t user_id,
		const GuildMemberPatch& guild_member_patch)
{
	QString endpoint = QString("/guilds/%1/members/%2").arg(guild_id).arg(
		user_id);

	http_service_.patch(token_, endpoint, guild_member_patch);
}

void Client::modifyCurrentUserNick(snowflake_t guild_id, const QString& nick)
{
	QString endpoint = QString("/guilds/%1/members/@me/nick").arg(guild_id);
	QJsonObject payload;

	payload["nick"] = nick;

	http_service_.patch(token_, endpoint, payload);
}

void Client::modifyGuildRolePositions(snowflake_t guild_id,
		const QList<QPair<snowflake_t, int>>& role_position_updates)
{
	QString endpoint = QString("/guilds/%1/roles").arg(guild_id);
	QJsonObject payload;
	QJsonArray role_position_updates_array;
	
	for (const QPair<snowflake_t, int>& role_position_update :
			role_position_updates)
	{
		QJsonObject role_position_update_object;
		role_position_update_object["id"] = QString::number(
			role_position_update.first);
		role_position_update_object["position"] = role_position_update.second;

		role_position_updates_array.append(role_position_update_object);
	}

	http_service_.patch(token_, endpoint, payload);
}

void Client::modifyGuildRole(snowflake_t guild_id, snowflake_t role_id,
		const RolePatch& role_patch)
{
	QString endpoint = QString("/guilds/%1/roles/%2").arg(guild_id).arg(
		role_id);

	http_service_.patch(token_, endpoint, role_patch);
}

void Client::modifyGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id, const IntegrationPatch& integration_patch)
{
	QString endpoint = QString("/guilds/%1/integrations/%2").arg(guild_id).arg(
		integration_id);

	http_service_.patch(token_, endpoint, integration_patch);
}

void Client::syncGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id)
{
	QString endpoint = QString("/guilds/%1/integrations/%2/sync").arg(
		guild_id).arg(integration_id);

	http_service_.post(token_, endpoint, QJsonObject());
}

void Client::modifyGuildEmbed(snowflake_t guild_id,
		const GuildEmbedPatch& guild_embed_patch)
{
	QString endpoint = QString("/guilds/%1/embed").arg(guild_id);

	http_service_.patch(token_, endpoint, guild_embed_patch);
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