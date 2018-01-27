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

EmbedFooter::operator QJsonObject() const
{
	QJsonObject data;
	data["text"] = text_;
	data["icon_url"] = icon_url_;
	data["proxy_icon_url"] = proxy_icon_url_;

	return data;
}

EmbedImage::EmbedImage(const QJsonObject& data)
	: url_(data["url"].toString())
	, proxy_url_(data["proxy_url"].toString())
	, height_(data["height"].toInt())
	, width_(data["width"].toInt())
{
}

EmbedImage::operator QJsonObject() const
{
	QJsonObject data;
	data["url"] = url_;
	data["proxy_url"] = proxy_url_;
	data["height"] = height_;
	data["width"] = width_;

	return data;
}

EmbedVideo::EmbedVideo(const QJsonObject& data)
	: url_(data["url"].toString())
	, height_(data["height"].toInt())
	, width_(data["width"].toInt())
{
}

EmbedVideo::operator QJsonObject() const
{
	QJsonObject data;
	data["url"] = url_;
	data["height"] = height_;
	data["width"] = width_;

	return data;
}

EmbedProvider::EmbedProvider(const QJsonObject& data)
	: name_(data["name"].toString())
	, url_(data["url"].toString())
{
}

EmbedProvider::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["url"] = url_;

	return data;
}

EmbedAuthor::EmbedAuthor(const QJsonObject& data)
	: name_(data["name"].toString())
	, url_(data["url"].toString())
	, icon_url_(data["icon_url"].toString())
	, proxy_icon_url_(data["proxy_icon_url"].toString())
{
}

EmbedAuthor::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["url"] = url_;
	data["icon_url"] = icon_url_;
	data["proxy_icon_url"] = proxy_icon_url_;

	return data;
}

EmbedField::EmbedField(const QJsonObject& data)
	: name_(data["name"].toString())
	, value_(data["value"].toString())
	, display_inline_(data["display_inline"].toBool())
{
}

EmbedField::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["value"] = value_;
	data["display_inline"] = display_inline_;

	return data;
}

Embed::Embed(const QJsonObject& data)
	: timestamp_(QDateTime::fromString(data["timestamp"].toString(),
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

Embed::operator QJsonObject() const
{
	QJsonObject data;
	data["timestamp"] = timestamp_.toString();
	data["title"] = title_;
	data["type"] = type_;
	data["description"] = description_;
	data["url"] = url_;
	data["footer"] = QJsonObject(footer_);
	data["image"] = QJsonObject(image_);
	data["thumbnail"] = QJsonObject(image_);
	data["video"] = QJsonObject(video_);
	data["provider"] = QJsonObject(provider_);
	data["author"] = QJsonObject(author_);
	data["color"] = color_;

	return data;
}

QDISCORD_NAMESPACE_END