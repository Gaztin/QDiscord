#include "Url.h"

QDISCORD_NAMESPACE_BEGIN

Url::Url(BaseUrl base_url, QString endpoint)
{
	// Fix endpoints without leading slash
	if (endpoint.length() > 0 && endpoint[0] != '/')
		endpoint.push_front('/');

	switch (base_url)
	{
	case Discord::BaseUrl::API:
		url_.setUrl("https://discordapp.com/api" + endpoint);
		break;

	case Discord::BaseUrl::IMAGE:
		url_.setUrl("https://cdn.discordapp.com" + endpoint);
		break;
	}
}

Url& Url::addQuery(const QString& query)
{
	url_.setQuery(url_.query() + query);
	return *this;
}

QDISCORD_NAMESPACE_END
