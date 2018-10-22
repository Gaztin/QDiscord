#include "HttpService.h"

#include "Discord/Payload.h"
#include "Discord/Token.h"

#include <QtCore/QBuffer>
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

QNetworkReply* HttpService::get(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "GET", token, payload);
}

QNetworkReply* HttpService::get(const Token& token, const Url& url)
{
	return sendRequest(url, "GET", token);
}

QNetworkReply* HttpService::del(const Token& token, const QString& endpoint)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "DELETE", token);
}

QNetworkReply* HttpService::post(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "POST", token, payload);
}

QNetworkReply* HttpService::post(const Token& token, const Url& url)
{
	return sendRequest(url, "POST", token);
}

QNetworkReply* HttpService::put(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "PUT", token, payload);
}

QNetworkReply* HttpService::put(const Token& token, const Url& url)
{
	return sendRequest(url, "PUT", token);
}

QNetworkReply* HttpService::patch(const Token& token, const QString& endpoint,
		const QJsonObject& payload)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "PATCH", token, payload);
}

QNetworkReply* HttpService::getImage(const Token& token, const QString& endpoint)
{
	return sendRequest(Url(BaseUrl::API, endpoint), "GET", token);
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

QNetworkReply* HttpService::sendRequest(const Url& url, const QByteArray& verb,
		const Token& token, const QJsonObject& payload)
{
	QNetworkRequest request(url.url());

	request.setRawHeader("Authorization", token.authorization());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	if (payload.empty())
	{
		return network_access_manager_.sendCustomRequest(request, verb);
	}
	else
	{
		request.setRawHeader("Content-Type", "application/json");
		QBuffer* buf = new QBuffer;
		buf->open(QBuffer::WriteOnly);
		buf->write(QJsonDocument(payload).toJson(QJsonDocument::Compact));
		buf->close();
		buf->open(QBuffer::ReadOnly);
		QNetworkReply* reply = network_access_manager_.sendCustomRequest(request, verb, buf);
		connect(reply, &QNetworkReply::finished, [buf] { delete buf; });
		return reply;
	}
}

QDISCORD_NAMESPACE_END