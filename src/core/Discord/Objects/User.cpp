#include "User.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

User::User(const QJsonObject& data)
	: username_(data["username"].toString())
	, discriminator_(data["discriminator"].toString())
	, avatar_(data["avatar"].toString())
	, email_(data["email"].toString())
	, id_(data["id"].toString().toULongLong())
	, bot_(data["bot"].toBool())
	, mfa_enabled_(data["mfa_enabled"].toBool())
	, verified_(data["verified"].toBool())
{
}

QDISCORD_NAMESPACE_END