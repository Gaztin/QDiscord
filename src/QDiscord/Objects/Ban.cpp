#include "Ban.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Ban::Ban(const QJsonObject& data)
	: reason_(data["reason"].toString())
	, user_(data["user"].toObject())
{
}

Ban::operator QJsonObject() const
{
	QJsonObject data;
	data["reason"] = reason_;
	data["user"] = QJsonObject(user_);

	return data;
}

QDISCORD_NAMESPACE_END