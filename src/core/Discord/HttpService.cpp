#include "HttpService.h"

#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/qauthenticator.h>

QDISCORD_NAMESPACE_BEGIN

HttpService::HttpService(const QString& user_agent, QObject* parent)
	: QObject(parent)
	, user_agent_(user_agent)
	, network_access_manager_(this)
{
	connect(&network_access_manager_, &QNetworkAccessManager::finished, this,
		&HttpService::onReply);
}

QNetworkReply* HttpService::sendRequest(const QString& token,
		const QString& endpoint, const QString& method)
{
	QUrl url("https://discordapp.com/api" + endpoint);
	QNetworkRequest request(url);

	request.setRawHeader("Authorization", token.toLocal8Bit());
	request.setRawHeader("User-Agent", user_agent_.toLocal8Bit());

	return network_access_manager_.sendCustomRequest(request,
		method.toLocal8Bit());
}

QNetworkReply* HttpService::getGateway(const QString& token)
{
	return sendRequest(token, "/gateway", "GET");
}

QNetworkReply* HttpService::getGatewayBot(const QString& token)
{
	return sendRequest(token, "/gateway/bot", "GET");
}

void HttpService::onReply(QNetworkReply* reply)
{
	reply->deleteLater();
}

QDISCORD_NAMESPACE_END