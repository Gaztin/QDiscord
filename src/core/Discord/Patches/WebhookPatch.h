#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class WebhookPatch : public Patch
{
public:
	void setName(const QString& name);
	void setAvatar(const QByteArray& avatar);
	void setChannelId(snowflake_t channel_id);
};

QDISCORD_NAMESPACE_END