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

QDISCORD_NAMESPACE_END