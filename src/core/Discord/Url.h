#pragma once
#include "Discord.h"

#include <QtCore/QUrl>

QDISCORD_NAMESPACE_BEGIN

enum class BaseUrl
{
	API,
	IMAGE,
};

class Url
{
public:
	Url(BaseUrl base_url, QString endpoint);

	Url& addQuery(const QString& query);

	template<typename T>
	Url& addQuery(const QString& key, const T& value)
	{
		return addQuery(QString("?%1=%2").arg(key).arg(value));
	}

	QUrl& url() { return url_; }
	const QUrl& url() const { return url_; }

private:
	QUrl url_;
};

QDISCORD_NAMESPACE_END
