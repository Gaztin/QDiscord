#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class GuildPatch : public Patch
{
public:
	void setName(const QString& name);
	void setRegion(const QString& region);
	void setIcon(const QString& icon);
	void setSplash(const QString& splash);

	void setAfkChannelId(snowflake_t afk_channel_id);
	void setOwnerId(snowflake_t owner_id);
	void setSystemChannelId(snowflake_t system_channel_id);

	void setVerificationLevel(int verification_level);
	void setDefaultMessageNotifications(int default_message_notifications);
	void setExplicitContentFilter(int explicit_content_filter);
	void setAfkTimeout(int afk_timeout);
};

QDISCORD_NAMESPACE_END