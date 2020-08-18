#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Attachment
{
public:
	explicit Attachment(const QJsonObject& data);

	const QString& filename() const { return filename_; }
	const QString& url() const { return url_; }
	const QString& proxyUrl() const { return proxy_url_; }
	snowflake_t id() const { return id_; }
	int size() const { return size_; }
	int height() const { return height_; }
	int width() const { return width_; }

private:
	QString filename_;
	QString url_;
	QString proxy_url_;

	snowflake_t id_;
	
	int size_;
	int height_;
	int width_;
};

QDISCORD_NAMESPACE_END