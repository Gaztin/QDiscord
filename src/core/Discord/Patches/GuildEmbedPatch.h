#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class GuildEmbedPatch : public Patch
{
public:
	void setEnabled(bool enabled);
	void setChannelId(snowflake_t channel_id);
};

QDISCORD_NAMESPACE_END