#include "GuildEmbedPatch.h"

QDISCORD_NAMESPACE_BEGIN

void GuildEmbedPatch::setEnabled(bool enabled)
{
	data_["enabled"] = enabled;
}

void GuildEmbedPatch::setChannelId(snowflake_t channel_id)
{
	data_["channel_id"] = QString::number(channel_id);
}

QDISCORD_NAMESPACE_END