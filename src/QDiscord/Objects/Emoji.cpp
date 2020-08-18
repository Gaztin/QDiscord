#include "Emoji.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Emoji::Emoji(const QJsonObject& data)
	: name_(data["name"].toString())
	, id_(data["id"].toString().toULongLong())
	, require_colons_(data["require_colons"].toBool())
	, managed_(data["managed"].toBool())
{
}

QDISCORD_NAMESPACE_END