#include "IntegrationPatch.h"

QDISCORD_NAMESPACE_BEGIN

void IntegrationPatch::setExpireBehavior(int expire_behavior)
{
	data_["expire_behavior"] = expire_behavior;
}

void IntegrationPatch::setExpireGracePeriod(int expire_grace_period)
{
	data_["expire_grace_period"] = expire_grace_period;
}

void IntegrationPatch::setEnableEmoticons(bool enable_emoticons)
{
	data_["enable_emoticons"] = enable_emoticons;
}

QDISCORD_NAMESPACE_END