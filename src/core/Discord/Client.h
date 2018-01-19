#pragma once
#include "Discord/Objects/Channel.h"
#include "Discord/Objects/Message.h"
#include "Discord/Objects/Reaction.h"
#include "Discord/Objects/User.h"
#include "Discord/GatewaySocket.h"
#include "Discord/HttpService.h"
#include "Discord/Promise.h"
#include "Discord/Token.h"

#include <QtCore/QObject>
#include <QtCore/QString>

class QDateTime;
class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Channel;
class ChannelPatch;
class Activity;
class Emoji;
class Guild;
class GuildPatch;
class GuildMember;
class GuildMemberPatch;
class Message;
class Role;
class User;
class VoiceState;

class Client : public QObject
{
public:
	Client(const QString& user_agent, QObject* parent = nullptr);

	void login(const Token& token);
	void logout();

	Promise<Channel>& getChannel(snowflake_t channel_id);
	Promise<Message>& getMessage(snowflake_t channel_id,
		snowflake_t message_id);
	Promise<QList<Message>>& getMessages(snowflake_t channel_id);
	Promise<QList<Reaction>>& getReactions(snowflake_t channel_id,
		snowflake_t message_id, const QString& emoji);
	Promise<QList<Message>>& getPins(snowflake_t channel_id);

	void sendMessage(snowflake_t channel_id, const QString& content);
	void addReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji);
	void removeReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji, snowflake_t user_id = 0);
	void removeAllReactions(snowflake_t channel_id, snowflake_t message_id);
	void triggerTypingIndicator(snowflake_t channel_id);

	void modifyChannel(snowflake_t channel_id,
		const ChannelPatch& channel_patch);
	void modifyGuild(snowflake_t guild_id, const GuildPatch& guild_patch);
	void modifyGuildMember(snowflake_t guild_id, snowflake_t user_id,
		const GuildMemberPatch& guild_member_patch);

protected:
	virtual void onReady(const User& user,
		const QList<Channel>& private_channels, const QList<Guild>& guilds) {}
	virtual void onChannelCreate(const Channel& channel) {}
	virtual void onChannelUpdate(const Channel& channel) {}
	virtual void onChannelDelete(const Channel& channel) {}
	virtual void onChannelPinsUpdate(snowflake_t channel_id,
		const QDateTime& last_pin_timestamp) {}
	virtual void onGuildCreate(const Guild& guild) {}
	virtual void onGuildUpdate(const Guild& guild) {}
	virtual void onGuildDelete(snowflake_t guild_id, bool unavailable) {}
	virtual void onGuildBanAdd(const User& user, snowflake_t guild_id) {}
	virtual void onGuildBanRemove(const User& user, snowflake_t guild_id) {}
	virtual void onGuildEmojisUpdate(snowflake_t guild_id,
		const QList<Emoji>& emojis) {}
	virtual void onGuildIntegrationsUpdate(snowflake_t guild_id) {}
	virtual void onGuildMemberAdd(const GuildMember& guild_member,
		snowflake_t guild_id) {}
	virtual void onGuildMemberRemove(snowflake_t guild_id, const User& user) {}
	virtual void onGuildMemberUpdate(snowflake_t guild_id,
		const QList<snowflake_t>& roles, const User& user,
		const QString& nick) {}
	virtual void onGuildRoleCreate(snowflake_t guild_id,
		const QList<GuildMember>& members) {}
	virtual void onGuildRoleUpdate(snowflake_t guild_id, const Role& role) {}
	virtual void onGuildRoleDelete(snowflake_t guild_id,
		snowflake_t role_id) {}
	virtual void onMessageCreate(const Message& message) {}
	virtual void onMessageUpdate(const Message& message) {}
	virtual void onMessageDelete(snowflake_t message_id,
		snowflake_t channel_id) {}
	virtual void onMessageDeleteBulk(const QList<snowflake_t>& ids,
		snowflake_t channel_id) {}
	virtual void onMessageReactionAdd(snowflake_t user_id,
		snowflake_t channel_id, snowflake_t message_id, const Emoji& emoji) {}
	virtual void onMessageReactionRemove(snowflake_t user_id,
		snowflake_t channel_id, snowflake_t message_id, const Emoji& emoji) {}
	virtual void onMessageReactionRemoveAll(snowflake_t channel_id,
		snowflake_t message_id) {}
	virtual void onPresenceUpdate(const User& user,
		const QList<snowflake_t>& roles, const Activity& activity,
		snowflake_t guild_id, const QString& status) {}
	virtual void onTypingStart(snowflake_t channel_id, snowflake_t user_id,
		int timestamp) {}
	virtual void onUserUpdate(const User& user) {}
	virtual void onVoiceStateUpdate(const VoiceState& voice_state) {}
	virtual void onVoiceServerUpdate(const QString& token,
		snowflake_t guild_id, const QString& endpoint) {}
	virtual void onWebhooksUpdate(snowflake_t guild_id,
		snowflake_t channel_id) {}
	virtual void onUnhandledEvent(const QString& name,
		const QJsonObject& data) {}

private slots:
	void onGatewayEvent(const QString& name, const QJsonObject& data);
	void onHttpGetGatewayReply();
	void onHttpGetGatewayBotReply();

private:
	Token token_;
	QString session_id_;

	GatewaySocket gateway_socket_;
	HttpService http_service_;
};

QDISCORD_NAMESPACE_END