/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
	EmbedFooter();
	EmbedFooter(const QString& text, const QString& icon_url);
	explicit EmbedFooter(const QJsonObject& data);

	/* Setters */

	void setText(const QString& text) { text_ = text; }
	void setIconUrl(const QString& icon_url) { icon_url_ = icon_url; }
	void setProxyIconUrl(const QString& proxy_icon_url) { proxy_icon_url_
		= proxy_icon_url; }
	
	/* Getters */

	const QString& text() const { return text_; }
	const QString& iconUrl() const { return icon_url_; }
	const QString& proxyIconUrl() const { return proxy_icon_url_; }

	operator QJsonObject() const;

private:
	QString text_;
	QString icon_url_;
	QString proxy_icon_url_;
};

class EmbedImage
{
public:
	EmbedImage();
	EmbedImage(const QString& url);
	explicit EmbedImage(const QJsonObject& data);

	/* Setters */

	void setUrl(const QString& url) { url_ = url;}
	void setProxy_url(const QString& proxy_url) { proxy_url_ = proxy_url;}

	void setHeight(int height) { height_ = height;}
	void setWidth(int width) { width_ = width;}

	/* Getters */

	const QString& url() const { return url_; }
	const QString& proxyUrl() const { return proxy_url_; }

	int height() const { return height_; }
	int width() const { return width_; }

	operator QJsonObject() const;

private:
	QString url_;
	QString proxy_url_;

	int height_;
	int width_;
};

class EmbedVideo
{
public:
	EmbedVideo();
	EmbedVideo(const QString& url);
	explicit EmbedVideo(const QJsonObject& data);

	/* Setters */

	void setUrl(const QString& url) { url_ = url; }

	void setHeight(int height) { height_ = height; }
	void setWidth(int width) { width_ = width; }

	/* Getters */

	const QString& url() const { return url_; }

	int height() const { return height_; }
	int width() const { return width_; }

	operator QJsonObject() const;

private:
	QString url_;

	int height_;
	int width_;
};

class EmbedProvider
{
public:
	EmbedProvider();
	EmbedProvider(const QString& name, const QString& url);
	explicit EmbedProvider(const QJsonObject& data);

	/* Setters */

	void setName(const QString& name) { name_ = name; }
	void setUrl(const QString& url) { url_ = url; }

	/* Getters */

	const QString& name() const { return name_; }
	const QString& url() const { return url_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString url_;
};

class EmbedAuthor
{
public:
	EmbedAuthor();
	EmbedAuthor(const QString& name, const QString& url,
		const QString& icon_url);
	explicit EmbedAuthor(const QJsonObject& data);

	/* Setters */

	void setName(const QString& name) { name_ = name; }
	void setUrl(const QString& url) { url_ = url; }
	void setIconUrl(const QString& icon_url) { icon_url_ = icon_url; }
	void setProxyIconUrl(const QString& proxy_icon_url) { proxy_icon_url_
		= proxy_icon_url; }

	/* Getters */

	const QString& name() const { return name_; }
	const QString& url() const { return url_; }
	const QString& iconUrl() const { return icon_url_; }
	const QString& proxyIconUrl() const { return proxy_icon_url_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString url_;
	QString icon_url_;
	QString proxy_icon_url_;
};

class EmbedField
{
public:
	EmbedField();
	EmbedField(const QString& name, const QString& value, bool display_inline);
	explicit EmbedField(const QJsonObject& data);

	/* Setters */

	void setName(const QString& name) { name_ = name; }
	void setValue(const QString& value) { value_ = value; }

	void setDisplayInline(bool display_inline) { display_inline_
		= display_inline; }

	/* Getters */

	const QString& name() const { return name_; }
	const QString& value() const { return value_; }

	bool displayInline() const { return display_inline_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString value_;

	bool display_inline_;
};

class Embed
{
public:
	Embed();
	Embed(const QList<EmbedField>& fields, const QDateTime& timestamp,
		const QString& title, const QString& description, const QString& url,
		const EmbedFooter& footer, const EmbedImage& image,
		const EmbedImage& thumbnail, const EmbedAuthor& author, int color);
	explicit Embed(const QJsonObject& data);

	/* Setters */
	
	void setFields(const QList<EmbedField>& fields) { fields_ = fields; }

	void setTimestamp(const QDateTime& timestamp) { timestamp_ = timestamp; }
	void setTitle(const QString& title) { title_ = title; }
	void setType(const QString& type) { type_ = type; }
	void setDescription(const QString& description) { description_
		= description; }
	void setUrl(const QString& url) { url_ = url; }

	void setFooter(const EmbedFooter& footer) { footer_ = footer; }
	void setImage(const EmbedImage& image) { image_ = image; }
	void setThumbnail(const EmbedImage& thumbnail) { thumbnail_ = thumbnail; }
	void setVideo(const EmbedVideo& video) { video_ = video; }
	void setProvider(const EmbedProvider& provider) { provider_ = provider; }
	void setAuthor(const EmbedAuthor& author) { author_ = author; }

	void setColor(int color) { color_ = color; }

	/* Getters */

	const QList<EmbedField>& fields() const { return fields_; }
	
	const QDateTime& timestamp() const { return timestamp_; }
	const QString& title() const { return title_; }
	const QString& type() const { return type_; }
	const QString& description() const { return description_; }
	const QString& url() const { return url_; }
	
	const EmbedFooter& footer() const { return footer_; }
	const EmbedImage& image() const { return image_; }
	const EmbedImage& thumbnail() const { return thumbnail_; }
	const EmbedVideo& video() const { return video_; }
	const EmbedProvider& provider() const { return provider_; }
	const EmbedAuthor& author() const { return author_; }

	int color() const { return color_; }

	operator QJsonObject() const;

private:
	QList<EmbedField> fields_;
	
	QDateTime timestamp_;
	QString title_;
	QString type_;
	QString description_;
	QString url_;
	
	EmbedFooter footer_;
	EmbedImage image_;
	EmbedImage thumbnail_;
	EmbedVideo video_;
	EmbedProvider provider_;
	EmbedAuthor author_;
	
	int color_;
};

QDISCORD_NAMESPACE_END
