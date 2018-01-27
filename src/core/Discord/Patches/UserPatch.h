#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class UserPatch : public Patch
{
public:
	void setUsername(const QString& username);
	void setAvatar(const QByteArray& avatar);
};

QDISCORD_NAMESPACE_END