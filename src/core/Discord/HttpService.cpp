#include "HttpService.h"

#include "Discord/Channel.h"
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
	QNetworkRequest request("https://discordapp.com/api" + endpoint);

	request.setRawHeader("Authorization", token.authorization());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	return network_access_manager_.get(request);
}

QNetworkReply* HttpService::post(const Token& token, const QString& endpoint,
		ContentType content_type, const QJsonObject& payload)
{
	QNetworkRequest request("https://discordapp.com/api" + endpoint);
	QByteArray data = QJsonDocument(payload).toJson(QJsonDocument::Compact);

	request.setRawHeader("Authorization", token.authorization());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	switch (content_type)
	{
		case ContentType::JSON:
			request.setRawHeader("Content-Type", "application/json");
		break;

		case ContentType::X_WWW_FORM_URLENCODED:
			request.setRawHeader("Content-Type",
				"application/x-www-form-urlencoded");
		break;
	}

	return network_access_manager_.post(request, data);
}

QNetworkReply* HttpService::getGateway(const Token& token)
{
	QString endpoint;

	switch (token.type())
	{
		case Token::Type::BOT:
			endpoint = "/gateway/bot";
		break;

		default:
			endpoint = "/gateway";
		break;
	}

	return get(token, endpoint);
}

QNetworkReply* HttpService::postMessage(const Token& token,
		snowflake_t channel_id, const QString& content)
{
	QString endpoint = QString("/channels/%1/messages").arg(channel_id);
	QJsonObject payload;

	payload["content"] = content;

	return post(token, endpoint, ContentType::JSON, payload);
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