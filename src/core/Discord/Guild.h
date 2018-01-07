#pragma once
#include "Discord/Channel.h"
#include "Discord/Emoji.h"
#include "Discord/GuildMember.h"
#include "Discord/PresenceUpdate.h"
#include "Discord/Role.h"
#include "Discord/VoiceState.h"

#include <QtCore/QDateTime>

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

struct Guild
{
	QList<Role> roles;
	QList<Emoji> emojis;
	QList<VoiceState> voice_states;
	QList<GuildMember> members;
	QList<Channel> channels;
	QList<PresenceUpdate> presences;
	QList<QString> features;

	QDateTime joined_at;
	QString name;
	QString icon;
	QString splash;
	QString region;

	VerificationLevel verification_level;
	DefaultMessageNotificationLevel default_message_notifications;
	ExplicitContentFilterLevel explicit_content_filter;
	MultiFactorAuthenticationLevel mfa_level;

	snowflake_t id;
	snowflake_t owner_id;
	snowflake_t afk_channel_id;
	snowflake_t embed_channel_id;
	snowflake_t application_id;
	snowflake_t widget_channel_id;

	int afk_timeout;
	int member_count;

	bool embed_enabled;
	bool widget_enabled;
	bool large;
	bool unavailable;
};

QDISCORD_NAMESPACE_END