#include "Overwrite.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Overwrite::Overwrite(const QJsonObject& data)
	: type_(data["type"].toString())
	, id_(data["id"].toString().toULongLong())
	, allow_(data["allow"].toInt())
	, deny_(data["deny"].toInt())
{
}

Overwrite::operator QJsonObject() const
{
	QJsonObject object;
	object["type"] = type_;
	object["id"] = QString::number(id_);
	object["allow"] = allow_;
	object["deny"] = deny_;

	return object;
}

QDISCORD_NAMESPACE_END