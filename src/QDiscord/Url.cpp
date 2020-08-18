#include "Url.h"

QDISCORD_NAMESPACE_BEGIN

Url::Url(BaseUrl base_url, QString endpoint)
	: base_url_(base_url)
	, endpoint_(endpoint)
{
	// Fix endpoints without leading slash
	if (endpoint_.length() > 0 && endpoint_[0] != '/')
		endpoint_.push_front('/');
}

QUrl Url::url() const
{
	QUrl url;

	// Set base URL
	switch (base_url_)
	{
	case Discord::BaseUrl::API:
		url.setUrl("https://discordapp.com/api" + endpoint_);
		break;

	case Discord::BaseUrl::IMAGE:
		url.setUrl("https://cdn.discordapp.com" + endpoint_);
		break;
	}

	// Set queries
	if (!queries_.isEmpty())
	{
		QString query(queries_[0].key + '=' + queries_[0].value);
		for (int i = 1; i < queries_.count(); ++i)
		{
			query.push_back('&' + queries_[i].key + '=' + queries_[i].value);
		}

		url.setQuery(query);
	}

	return url;
}

QDISCORD_NAMESPACE_END
