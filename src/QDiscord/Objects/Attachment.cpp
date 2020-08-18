#include "Attachment.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Attachment::Attachment(const QJsonObject& data)
	: filename_(data["filename"].toString())
	, url_(data["url"].toString())
	, proxy_url_(data["proxy_url"].toString())
	, id_(data["id"].toString().toULongLong())
	, size_(data["size"].toInt())
	, height_(data["height"].toInt())
	, width_(data["width"].toInt())
{
}

QDISCORD_NAMESPACE_END