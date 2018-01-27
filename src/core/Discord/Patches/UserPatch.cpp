#include "UserPatch.h"

QDISCORD_NAMESPACE_BEGIN

void UserPatch::setUsername(const QString& username)
{
	data_["username"] = username;
}

void UserPatch::setAvatar(const QByteArray& avatar)
{
	data_["avatar"] = QString(avatar);
}

QDISCORD_NAMESPACE_END