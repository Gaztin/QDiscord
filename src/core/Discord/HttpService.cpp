#include "HttpService.h"

#include "Discord/Payload.h"
#include "Discord/Token.h"

#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>

QDISCORD_NAMESPACE_BEGIN

HttpService::HttpService(const QString& user_agent, QObject* parent)
	: QObject(parent)
	, user_agent_(user_agent)
	, network_access_manager_(this)
{
	connect(&network_access_manager_, &QNetworkAccessManager::finished, this,
		&HttpService::onReply);
}

QNetworkReply* HttpService::get(const Token& token, const QString& endpoint)
{
	return sendRequest("https://discordapp.com/api", "GET", token, endpoint, QJsonObject());
}

QNetworkReply* HttpService::get(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest("https://discordapp.com/api", "GET", token, endpoint, payload);
}

QNetworkReply* HttpService::del(const Token& token, const QString& endpoint)
{
	return sendRequest("https://discordapp.com/api", "DELETE", token, endpoint, QJsonObject());
}

QNetworkReply* HttpService::post(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest("https://discordapp.com/api", "POST", token, endpoint, payload);
}

QNetworkReply* HttpService::put(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest("https://discordapp.com/api", "PUT", token, endpoint, payload);
}

QNetworkReply* HttpService::patch(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest("https://discordapp.com/api", "PATCH", token, endpoint, payload);
}

QNetworkReply* HttpService::getImage(const Token& token, const QString& endpoint)
{
	return sendRequest("https://cdn.discordapp.com/", "GET", token, endpoint, QJsonObject());
}

void HttpService::onReply(QNetworkReply* reply)
{
#ifdef QT_DEBUG
	if (reply->error() != QNetworkReply::NoError)
	{
		qDebug("%s", qPrintable(reply->errorString()));
	}
#endif

	reply->deleteLater();
}

QNetworkReply* HttpService::sendRequest(const QString& base_url,
		const QByteArray& verb, const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	QNetworkRequest request(base_url + endpoint);
	QByteArray data;

	request.setRawHeader("Authorization", token.authorization());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	if (!payload.empty())
	{
		request.setRawHeader("Content-Type", "application/json");
		data = QJsonDocument(payload).toJson(QJsonDocument::Compact);
	}

	return network_access_manager_.sendCustomRequest(request, verb, data);
}

QDISCORD_NAMESPACE_END