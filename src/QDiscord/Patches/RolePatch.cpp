#include "RolePatch.h"

QDISCORD_NAMESPACE_BEGIN

void RolePatch::setName(const QString& name)
{
	data_["name"] = name;
}

void RolePatch::setPermissions(int permissions)
{
	data_["permissions"] = permissions;
}

void RolePatch::setColor(int color)
{
	data_["color"] = color;
}

void RolePatch::setHoist(bool hoist)
{
	data_["hoist"] = hoist;
}

void RolePatch::setMentionable(bool mentionable)
{
	data_["mentionable"] = mentionable;
}

QDISCORD_NAMESPACE_END