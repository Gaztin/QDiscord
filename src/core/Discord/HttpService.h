#pragma once
#include "Discord.h"

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

class Channel;
class Token;

class HttpService : public QObject
{
public:
	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* get(const Token& token, const QString& endpoint);
	QNetworkReply* get(const Token& token, const QString& endpoint,
		const QJsonObject& payload);
	QNetworkReply* del(const Token& token, const QString& endpoint);
	QNetworkReply* post(const Token& token, const QString& endpoint,
		const QJsonObject& payload);
	QNetworkReply* put(const Token& token, const QString& endpoint,
		const QJsonObject& payload);
	QNetworkReply* patch(const Token& token, const QString& endpoint,
		const QJsonObject& payload);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QNetworkReply* sendRequest(const QByteArray& verb, const Token& token,
		const QString& endpoint, const QJsonObject& payload,
		const QString& base_url = "https://discordapp.com/api");

	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END