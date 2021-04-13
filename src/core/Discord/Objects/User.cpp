#include "User.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

User::User(const QJsonObject& data)
	: username_(data["username"].toString())
	, discriminator_(data["discriminator"].toString())
	, avatar_(data["avatar"].toString())
	, email_(data["email"].toString())
	, locale_(data["locale"].toString())
	, id_(data["id"].toString().toULongLong())
	, bot_(data["bot"].toBool())
	, mfa_enabled_(data["mfa_enabled"].toBool())
	, verified_(data["verified"].toBool())
{
}

User::operator QJsonObject() const
{
	QJsonObject data;
	data["username"] = username_;
	data["discriminator"] = discriminator_;
	data["avatar"] = avatar_;
	data["email"] = email_;
	data["locale"] = locale_;
	data["id"] = QString::number(id_);
	data["bot"] = bot_;
	data["mfa_enabled"] = mfa_enabled_;
	data["verified"] = verified_;

	return data;
}

QDISCORD_NAMESPACE_END