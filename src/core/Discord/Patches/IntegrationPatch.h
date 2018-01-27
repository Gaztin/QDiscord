#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class IntegrationPatch : public Patch
{
public:
	void setExpireBehavior(int expire_behavior);
	void setExpireGracePeriod(int expire_grace_period);
	void setEnableEmoticons(bool enable_emoticons);
};

QDISCORD_NAMESPACE_END