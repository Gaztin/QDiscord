#pragma once
#include "Discord/Objects/Channel.h"
#include "Discord/Objects/Emoji.h"
#include "Discord/Objects/GuildMember.h"
#include "Discord/Objects/PresenceUpdate.h"
#include "Discord/Objects/Role.h"
#include "Discord/Objects/VoiceState.h"

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

enum class DefaultMessageNotificationLevel
{
	ALL_MESSAGES = 0,
	ONLY_MENTIONS,
};

enum class ExplicitContentFilterLevel
{
	DISABLED = 0,
	MEMBERS_WITHOUT_ROLES,
	ALL_MEMBERS,
};

enum class MultiFactorAuthenticationLevel
{
	NONE = 0,
	ELEVATED,
};

enum class VerificationLevel
{
	NONE,
	LOW,
	MEDIUM,
	HIGH,
	VERY_HIGH,
};

class Guild
{
public:
	explicit Guild(const QJsonObject& data);

	const QList<Role>& roles() const { return roles_; }
	const QList<Emoji>& emojis() const { return emojis_; }
	const QList<VoiceState>& voiceStates() const { return voice_states_; }
	const QList<GuildMember>& members() const { return members_; }
	const QList<Channel>& channels() const { return channels_; }
	const QList<PresenceUpdate>& presences() const { return presences_; }
	const QList<QString>& features() const { return features_; }
	
	const QDateTime& joinedAt() const { return joined_at_; }
	const QString& name() const { return name_; }
	const QString& icon() const { return icon_; }
	const QString& splash() const { return splash_; }
	const QString& region() const { return region_; }
	
	VerificationLevel verificationLevel() const { return verification_level_; }
	DefaultMessageNotificationLevel defaultMessageNotifications() const
		{ return default_message_notifications_; }
	ExplicitContentFilterLevel explicitContentFilter() const
		{ return explicit_content_filter_; }
	MultiFactorAuthenticationLevel mfaLevel() const { return mfa_level_; }
	
	snowflake_t id() const { return id_; }
	snowflake_t ownerId() const { return owner_id_; }
	snowflake_t afkChannelId() const { return afk_channel_id_; }
	snowflake_t embedChannelId() const { return embed_channel_id_; }
	snowflake_t applicationId() const { return application_id_; }
	snowflake_t widgetChannelId() const { return widget_channel_id_; }
	
	int afkTimeout() const { return afk_timeout_; }
	int memberCount() const { return member_count_; }
	
	bool embedEnabled() const { return embed_enabled_; }
	bool widgetEnabled() const { return widget_enabled_; }
	bool large() const { return large_; }
	bool unavailable() const { return unavailable_; }

	operator QJsonObject() const;

private:
	QList<Role> roles_;
	QList<Emoji> emojis_;
	QList<VoiceState> voice_states_;
	QList<GuildMember> members_;
	QList<Channel> channels_;
	QList<PresenceUpdate> presences_;
	QList<QString> features_;
	
	QDateTime joined_at_;
	QString name_;
	QString icon_;
	QString splash_;
	QString region_;
	
	VerificationLevel verification_level_;
	DefaultMessageNotificationLevel default_message_notifications_;
	ExplicitContentFilterLevel explicit_content_filter_;
	MultiFactorAuthenticationLevel mfa_level_;
	
	snowflake_t id_;
	snowflake_t owner_id_;
	snowflake_t afk_channel_id_;
	snowflake_t embed_channel_id_;
	snowflake_t application_id_;
	snowflake_t widget_channel_id_;
	
	int afk_timeout_;
	int member_count_;
	
	bool embed_enabled_;
	bool widget_enabled_;
	bool large_;
	bool unavailable_;
};

QDISCORD_NAMESPACE_END