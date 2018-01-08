#include "HttpService.h"

#include "Discord/Channel.h"
#include "Discord/Payload.h"

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

QNetworkReply* HttpService::get(const QString& token, const QString& endpoint)
{
	QNetworkRequest request("https://discordapp.com/api" + endpoint);

	request.setRawHeader("Authorization", ("Bot " + token).toUtf8());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	return network_access_manager_.get(request);
}

QNetworkReply* HttpService::post(const QString& token, const QString& endpoint,
		const QJsonObject& payload)
{
	QNetworkRequest request("https://discordapp.com/api" + endpoint);
	QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

	request.setRawHeader("Authorization", ("Bot " + token).toUtf8());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());
	request.setRawHeader("Content-Type", "application/json");

	return network_access_manager_.post(request, data);
}

QNetworkReply* HttpService::getGateway(const QString& token)
{
	return get(token, "/gateway");
}

QNetworkReply* HttpService::getGatewayBot(const QString& token)
{
	return get(token, "/gateway/bot");
}

QNetworkReply* HttpService::postMessage(const QString& token,
		snowflake_t channel_id, const QString& content)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QJsonObject payload;

	payload["content"] = content;

	return post(token, endpoint, payload);
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

QDISCORD_NAMESPACE_END