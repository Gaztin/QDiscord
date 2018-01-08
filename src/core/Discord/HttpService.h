#pragma once
#include "Discord.h"

#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

class HttpService : public QObject
{
public:
	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* sendRequest(const QString& token, const QString& endpoint,
		const QString& method);
	QNetworkReply* getGateway(const QString& token);
	QNetworkReply* getGatewayBot(const QString& token);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END