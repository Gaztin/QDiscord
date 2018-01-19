#include "GuildPatch.h"

QDISCORD_NAMESPACE_BEGIN

void GuildPatch::setName(const QString& name)
{
	data_["name"] = name;
}

void GuildPatch::setRegion(const QString& region)
{
	data_["region"] = region;
}

void GuildPatch::setIcon(const QString& icon)
{
	data_["icon"] = icon;
}

void GuildPatch::setSplash(const QString& splash)
{
	data_["splash"] = splash;
}

void GuildPatch::setAfkChannelId(snowflake_t afk_channel_id)
{
	data_["afk_channel_id"] = QString::number(afk_channel_id);
}

void GuildPatch::setOwnerId(snowflake_t owner_id)
{
	data_["owner_id"] = QString::number(owner_id);
}

void GuildPatch::setSystemChannelId(snowflake_t system_channel_id)
{
	data_["system_channel_id"] = QString::number(system_channel_id);
}

void GuildPatch::setVerificationLevel(int verification_level)
{
	data_["verification_level"] = verification_level;
}

void GuildPatch::setDefaultMessageNotifications(
		int default_message_notifications)
{
	data_["default_message_notifications"] = default_message_notifications;
}

void GuildPatch::setExplicitContentFilter(int explicit_content_filter)
{
	data_["explicit_content_filter"] = explicit_content_filter;
}

void GuildPatch::setAfkTimeout(int afk_timeout)
{
	data_["afk_timeout"] = afk_timeout;
}

QDISCORD_NAMESPACE_END