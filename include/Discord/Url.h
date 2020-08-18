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

	template<typename T>
	Url& addQuery(const QString& key, const T& value)
	{
		queries_.push_back({key, QString("%1").arg(value)});
		return *this;
	}

	QUrl url() const;

private:
	struct Query
	{
		QString key;
		QString value;
	};

	BaseUrl base_url_;
	QString endpoint_;
	QList<Query> queries_;
};

QDISCORD_NAMESPACE_END
