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
	enum class ContentType
	{
		JSON,
		X_WWW_FORM_URLENCODED,
	};

	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* get(const Token& token, const QString& endpoint);
	QNetworkReply* post(const Token& token, const QString& endpoint,
		ContentType content_type, const QJsonObject& payload = QJsonObject());

	QNetworkReply* getGateway(const Token& token);

	QNetworkReply* postMessage(const Token& token, snowflake_t channel_id,
		const QString& content);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END