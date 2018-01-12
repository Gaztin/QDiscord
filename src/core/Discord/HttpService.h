#pragma once
#include "Discord.h"

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

class Token;
struct Channel;

class HttpService : public QObject
{
public:
	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* get(const Token& token, const QString& endpoint);
	QNetworkReply* post(const Token& token, const QString& endpoint,
		const QJsonObject& payload);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END