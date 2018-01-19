#pragma once
#include "Discord.h"

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class EmbedFooter
{
public:
	explicit EmbedFooter(const QJsonObject& data);

private:
	QString text_;
	QString icon_url_;
	QString proxy_icon_url_;
};

class EmbedImage
{
public:
	explicit EmbedImage(const QJsonObject& data);

private:
	QString url_;
	QString proxy_url_;
	int height_;
	int width_;
};

class EmbedThumbnail
{
public:
	explicit EmbedThumbnail(const QJsonObject& data);

private:
	QString url_;
	QString proxy_url_;
	int height_;
	int width_;
};

class EmbedVideo
{
public:
	explicit EmbedVideo(const QJsonObject& data);

private:
	QString url_;
	int height_;
	int width_;
};

class EmbedProvider
{
public:
	explicit EmbedProvider(const QJsonObject& data);

private:
	QString name_;
	QString url_;
};

class EmbedAuthor
{
public:
	explicit EmbedAuthor(const QJsonObject& data);

private:
	QString name_;
	QString url_;
	QString icon_url_;
	QString proxy_icon_url_;
};

class EmbedField
{
public:
	explicit EmbedField(const QJsonObject& data);

private:
	QString name_;
	QString value_;
	bool display_inline_;
};

class Embed
{
public:
	explicit Embed(const QJsonObject& data);

	const QList<EmbedField>& fields() const { return fields_; }
	
	const QDateTime& timestamp() const { return timestamp_; }
	const QString& title() const { return title_; }
	const QString& type() const { return type_; }
	const QString& description() const { return description_; }
	const QString& url() const { return url_; }
	
	EmbedFooter footer() const { return footer_; }
	EmbedImage image() const { return image_; }
	EmbedThumbnail thumbnail() const { return thumbnail_; }
	EmbedVideo video() const { return video_; }
	EmbedProvider provider() const { return provider_; }
	EmbedAuthor author() const { return author_; }
	
	int color() const { return color_; }

private:
	QList<EmbedField> fields_;
	
	QDateTime timestamp_;
	QString title_;
	QString type_;
	QString description_;
	QString url_;
	
	EmbedFooter footer_;
	EmbedImage image_;
	EmbedThumbnail thumbnail_;
	EmbedVideo video_;
	EmbedProvider provider_;
	EmbedAuthor author_;
	
	int color_;
};

QDISCORD_NAMESPACE_END