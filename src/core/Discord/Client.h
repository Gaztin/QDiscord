#pragma once
#include "Discord/Objects/Channel.h"
#include "Discord/Objects/Invite.h"
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

class Activity;
class Ban;
class Channel;
class ChannelPatch;
class ChannelPermissionsPatch;
class Connection;
class Emoji;
class EmojiPatch;
class Guild;
class GuildEmbed;
class GuildEmbedPatch;
class GuildPatch;
class GuildMember;
class GuildMemberPatch;
class Integration;
class IntegrationPatch;
class Message;
class MessagePatch;
class Role;
class RolePatch;
class User;
class UserPatch;
class VoiceRegion;
class VoiceState;
class Webhook;
class WebhookPatch;

class Client : public QObject
{
	Q_OBJECT

public:
	Client(const QString& user_agent, QObject* parent = nullptr);

	void login(const Token& token);
	void logout();

	Promise<Channel>& getChannel(snowflake_t channel_id);
	Promise<QList<Message>>& getChannelMessages(snowflake_t channel_id);
	Promise<Message>& getChannelMessage(snowflake_t channel_id,
		snowflake_t message_id);
	Promise<QList<Reaction>>& getReactions(snowflake_t channel_id,
		snowflake_t message_id, const QString& emoji);
	Promise<QList<Invite>>& getChannelInvites(snowflake_t channel_id);
	Promise<QList<Message>>& getPinnedMessages(snowflake_t channel_id);
	Promise<QList<Emoji>>& listGuildEmojis(snowflake_t guild_id);
	Promise<Emoji>& getGuildEmoji(snowflake_t guild_id, snowflake_t emoji_id);
	Promise<Guild>& getGuild(snowflake_t guild_id);
	Promise<QList<Channel>>& getGuildChannels(snowflake_t guild_id);
	Promise<GuildMember>& getGuildMember(snowflake_t guild_id,
		snowflake_t user_id);
	Promise<QList<GuildMember>>& listGuildMembers(snowflake_t guild_id);
	Promise<QList<Ban>>& getGuildBans(snowflake_t guild_id);
	Promise<QList<Role>>& getGuildRoles(snowflake_t guild_id);
	Promise<int>& getGuildPruneCount(snowflake_t guild_id, int days);
	Promise<QList<VoiceRegion>>& getGuildVoiceRegions(snowflake_t guild_id);
	Promise<QList<Invite>>& getGuildInvites(snowflake_t guild_id);
	Promise<QList<Integration>>& getGuildIntegrations(snowflake_t guild_id);
	Promise<GuildEmbed>& getGuildEmbed(snowflake_t guild_id);
	Promise<Invite>& getInvite(const QString& invite_code);
	Promise<User>& getCurrentUser();
	Promise<User>& getUser(snowflake_t user_id);
	Promise<QList<Guild>>& getCurrentUserGuilds();
	Promise<QList<Channel>>& getUserDms();
	Promise<QList<Connection>>& getUserConnections();
	Promise<QList<VoiceRegion>>& listVoiceRegions();
	Promise<QList<Webhook>>& getChannelWebhooks(snowflake_t channel_id);
	Promise<QList<Webhook>>& getGuildWebhooks(snowflake_t guild_id);
	Promise<Webhook>& getWebhook(snowflake_t webhook_id);
	Promise<Webhook>& getWebhookWithToken(snowflake_t webhook_id,
		const QString& token);

	enum class EmojiImageSupportedExtension { PNG, GIF };
	enum class IconImageSupportedExtension { PNG, JPEG, WEBP };
	enum class AvatarImageSupportedExtension { PNG, JPEG, WEBP, GIF };

	Promise<QPixmap>& getCustomEmojiPixmap(const Emoji& emoji,
		EmojiImageSupportedExtension extension);
	Promise<QPixmap>& getGuildIconPixmap(const Guild& guild,
		IconImageSupportedExtension extension);
	Promise<QPixmap>& getGuildSplashPixmap(const Guild& guild,
		IconImageSupportedExtension extension);
	Promise<QPixmap>& getDefaultUserAvatarPixmap(uint32_t discriminator);
	Promise<QPixmap>& getUserAvatarPixmap(const User& user,
		AvatarImageSupportedExtension extension);
	Promise<QPixmap>& getApplicationIconPixmap(const Activity& activity,
		IconImageSupportedExtension extension, bool large);

	void deleteChannel(snowflake_t channel_id);
	void deleteOwnReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji);
	void deleteUserReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji, snowflake_t user_id);
	void deleteAllReactions(snowflake_t channel_id, snowflake_t message_id);
	void deleteMessage(snowflake_t channel_id, snowflake_t message_id);
	void bulkDeleteMessages(snowflake_t channel_id,
		const QList<snowflake_t>& message_ids);
	void deleteChannelPermission(snowflake_t channel_id,
		snowflake_t overwrite_id);
	void deletePinnedChannelMessage(snowflake_t channel_id,
		snowflake_t message_id);
	void groupDmRemoveRecipient(snowflake_t channel_id, snowflake_t user_id);
	void deleteGuildEmoji(snowflake_t guild_id, snowflake_t emoji_id);
	void deleteGuild(snowflake_t guild_id);
	void removeGuildMemberRole(snowflake_t guild_id, snowflake_t user_id,
		snowflake_t role_id);
	void removeGuildMember(snowflake_t guild_id, snowflake_t user_id);
	void removeGuildBan(snowflake_t guild_id, snowflake_t user_id);
	void deleteGuildRole(snowflake_t guild_id, snowflake_t role_id);
	void beginGuildPrune(snowflake_t guild_id, int days);
	void deleteGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id);
	void deleteInvite(const QString& invite_code);
	void leaveGuild(snowflake_t guild_id);
	void deleteWebhook(snowflake_t webhook_id);
	void deleteWebhook(snowflake_t webhook_id, const QString& token);

	void createMessage(snowflake_t channel_id, const QString& content);
	void createMessage(snowflake_t channel_id, const Embed& embed);
	void createReaction(snowflake_t channel_id, snowflake_t message_id,
		const QString& emoji);
	void createChannelInvite(snowflake_t channel_id, int max_age, int max_uses,
		bool temporary, bool unique);
	void addPinnedChannelMessage(snowflake_t channel_id,
		snowflake_t message_id);
	void groupDmAddRecipient(snowflake_t channel_id, snowflake_t user_id,
		const QString& access_token, const QString& nick);
	void createGuildEmoji(snowflake_t guild_id, const QString& name,
		const QByteArray& image, const QList<snowflake_t>& role_ids);
	void createGuild(const QString& name, const QString& region,
		const QString& icon, VerificationLevel verification_level,
		DefaultMessageNotificationLevel default_message_notification_level,
		ExplicitContentFilterLevel explicit_content_filter_level,
		const QList<Role>& roles, const QList<Channel>& channels);
	void createGuildChannel(snowflake_t guild_id, const QString& name,
		ChannelType type, int bitrate, int user_limit,
		const QList<Overwrite>& permission_overwrites, snowflake_t parent_id,
		bool nsfw);
	void addGuildMember(snowflake_t guild_id, snowflake_t user_id,
		const QString& access_token, const QString& nick,
		const QList<snowflake_t>& roles, bool mute, bool deaf);
	void addGuildMemberRole(snowflake_t guild_id, snowflake_t user_id,
		snowflake_t role_id);
	void createGuildBan(snowflake_t guild_id, snowflake_t user_id,
		int delete_message_days, const QString& reason);
	void createGuildRole(snowflake_t guild_id, const QString& name,
		int permissions, int color, bool hoist, bool mentionable);
	void createGuildIntegration(snowflake_t guild_id, const QString& type,
		snowflake_t id);
	void createDm(snowflake_t recipient_id);
	void createGroupDm(const QList<QString>& access_tokens,
		const QList<QPair<snowflake_t, QString>>& nicks);
	void createWebhook(snowflake_t channel_id, const QString& name,
		const QByteArray& avatar);

	void modifyChannel(snowflake_t channel_id,
		const ChannelPatch& channel_patch);
	void editMessage(snowflake_t channel_id, snowflake_t message_id,
		const MessagePatch& message_patch);
	void editChannelPermissions(snowflake_t channel_id,
		snowflake_t overwrite_id, int allow, int deny, const QString& type);
	void modifyGuildEmoji(snowflake_t guild_id, snowflake_t emoji_id,
		const EmojiPatch& emoji_patch);
	void modifyGuild(snowflake_t guild_id, const GuildPatch& guild_patch);
	void modifyGuildChannelPositions(snowflake_t guild_id,
		const QList<QPair<snowflake_t, int>>& channel_position_updates);
	void modifyGuildMember(snowflake_t guild_id, snowflake_t user_id,
		const GuildMemberPatch& guild_member_patch);
	void modifyCurrentUserNick(snowflake_t guild_id, const QString& nick);
	void modifyGuildRolePositions(snowflake_t guild_id,
		const QList<QPair<snowflake_t, int>>& role_position_updates);
	void modifyGuildRole(snowflake_t guild_id, snowflake_t role_id,
		const RolePatch& role_patch);
	void modifyGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id, const IntegrationPatch& integration_patch);
	void syncGuildIntegration(snowflake_t guild_id,
		snowflake_t integration_id);
	void modifyGuildEmbed(snowflake_t guild_id,
		const GuildEmbedPatch& guild_embed_patch);
	void modifyCurrentUser(const UserPatch& user_patch);
	void modifyWebhook(snowflake_t webhook_id,
		const WebhookPatch& webhook_patch);
	void modifyWebhookWithToken(snowflake_t webhook_id, const QString& token,
		const WebhookPatch& webhook_patch);

	void triggerTypingIndicator(snowflake_t channel_id);

signals:
	void onReady(const User& user,
		const QList<Channel>& private_channels, const QList<Guild>& guilds);
	void onChannelCreate(const Channel& channel);
	void onChannelUpdate(const Channel& channel);
	void onChannelDelete(const Channel& channel);
	void onChannelPinsUpdate(snowflake_t channel_id,
		const QDateTime& last_pin_timestamp);
	void onGuildCreate(const Guild& guild);
	void onGuildUpdate(const Guild& guild);
	void onGuildDelete(snowflake_t guild_id, bool unavailable);
	void onGuildBanAdd(const User& user, snowflake_t guild_id);
	void onGuildBanRemove(const User& user, snowflake_t guild_id);
	void onGuildEmojisUpdate(snowflake_t guild_id, const QList<Emoji>& emojis);
	void onGuildIntegrationsUpdate(snowflake_t guild_id);
	void onGuildMemberAdd(const GuildMember& guild_member,
		snowflake_t guild_id);
	void onGuildMemberRemove(snowflake_t guild_id, const User& user);
	void onGuildMemberUpdate(snowflake_t guild_id,
		const QList<snowflake_t>& roles, const User& user,
		const QString& nick);
	void onGuildRoleCreate(snowflake_t guild_id,
		const QList<GuildMember>& members);
	void onGuildRoleUpdate(snowflake_t guild_id, const Role& role);
	void onGuildRoleDelete(snowflake_t guild_id, snowflake_t role_id);
	void onMessageCreate(const Message& message);
	void onMessageUpdate(const Message& message);
	void onMessageDelete(snowflake_t message_id, snowflake_t channel_id);
	void onMessageDeleteBulk(const QList<snowflake_t>& ids,
		snowflake_t channel_id);
	void onMessageReactionAdd(snowflake_t user_id,
		snowflake_t channel_id, snowflake_t message_id, const Emoji& emoji);
	void onMessageReactionRemove(snowflake_t user_id,
		snowflake_t channel_id, snowflake_t message_id, const Emoji& emoji);
	void onMessageReactionRemoveAll(snowflake_t channel_id,
		snowflake_t message_id);
	void onPresenceUpdate(const User& user,
		const QList<snowflake_t>& roles, const Activity& activity,
		snowflake_t guild_id, const QString& status);
	void onTypingStart(snowflake_t channel_id, snowflake_t user_id,
		int timestamp);
	void onUserUpdate(const User& user);
	void onVoiceStateUpdate(const VoiceState& voice_state);
	void onVoiceServerUpdate(const QString& token,
		snowflake_t guild_id, const QString& endpoint);
	void onWebhooksUpdate(snowflake_t guild_id, snowflake_t channel_id);
	void onUnhandledEvent(const QString& name, const QJsonObject& data);

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