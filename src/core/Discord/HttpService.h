#pragma once
#include "Discord.h"

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

struct Channel;

class HttpService : public QObject
{
public:
	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* get(const QString& token, const QString& endpoint);
	QNetworkReply* post(const QString& token, const QString& endpoint,
		const QJsonObject& payload = QJsonObject());

	QNetworkReply* getGateway(const QString& token);
	QNetworkReply* getGatewayBot(const QString& token);

	QNetworkReply* postMessage(const QString& token, snowflake_t channel_id,
		const QString& content);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END