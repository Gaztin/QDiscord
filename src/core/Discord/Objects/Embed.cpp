#include "Embed.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

EmbedFooter::EmbedFooter(const QJsonObject& data)
	: text_(data["text"].toString())
	, icon_url_(data["icon_url"].toString())
	, proxy_icon_url_(data["proxy_icon_url"].toString())
{
}

EmbedImage::EmbedImage(const QJsonObject& data)
	: url_(data["url"].toString())
	, proxy_url_(data["proxy_url"].toString())
	, height_(data["height"].toInt())
	, width_(data["width"].toInt())
{
}

{

}

EmbedVideo::EmbedVideo(const QJsonObject& data)
	: url_(data["url"].toString())
	, height_(data["height"].toInt())
	, width_(data["width"].toInt())
{
}

EmbedProvider::EmbedProvider(const QJsonObject& data)
	: name_(data["name"].toString())
	, url_(data["url"].toString())
{
}

EmbedAuthor::EmbedAuthor(const QJsonObject& data)
	: name_(data["name"].toString())
	, url_(data["url"].toString())
	, icon_url_(data["icon_url"].toString())
	, proxy_icon_url_(data["proxy_icon_url"].toString())
{

}

EmbedField::EmbedField(const QJsonObject& data)
	: name_(data["name"].toString())
	, value_(data["value"].toString())
	, display_inline_(data["display_inline"].toBool())
{
}

Embed::Embed(const QJsonObject& data)
	: timestamp_(QDateTime::fromString(data["timestamps"].toString(),
		Qt::ISODate))
	, title_(data["title"].toString())
	, type_(data["type"].toString())
	, description_(data["description"].toString())
	, url_(data["url"].toString())
	, footer_(data["footer"].toObject())
	, image_(data["image"].toObject())
	, thumbnail_(data["thumbnail"].toObject())
	, video_(data["video"].toObject())
	, provider_(data["provider"].toObject())
	, author_(data["author"].toObject())
	, color_(data["color"].toInt())
{
	QJsonArray fields_array = data["fields"].toArray();
	for (QJsonValue field_value : fields_array)
	{
		fields_.append(EmbedField(field_value.toObject()));
	}
}

QDISCORD_NAMESPACE_END