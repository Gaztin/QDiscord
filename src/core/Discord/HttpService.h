#pragma once
#include "Discord/Url.h"

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

class Channel;
class Token;

enum class UploadImageSupportedExtension { PNG, JPG, GIF };

struct UploadAttachment {
	UploadImageSupportedExtension type;
	QString name;
	QByteArray file;
};

class HttpService : public QObject
{
public:
	HttpService(const QString& user_agent, QObject* parent = nullptr);

	QNetworkReply* get(const Token& token, const QString& endpoint,
		const QJsonObject& payload = QJsonObject());
	QNetworkReply* get(const Token& token, const Url& url);
	QNetworkReply* del(const Token& token, const QString& endpoint);
	QNetworkReply* post(const Token& token, const QString& endpoint,
		const QJsonObject& payload);
	QNetworkReply* post(const Token& token, const Url& url);
	QNetworkReply* put(const Token& token, const QString& endpoint,
		const QJsonObject& payload);
	QNetworkReply* put(const Token& token, const Url& url);
	QNetworkReply* patch(const Token& token, const QString& endpoint,
		const QJsonObject& payload);

	QNetworkReply* getImage(const Token& token, const QString& endpoint);
	QNetworkReply* postMultipart(const Token& token, const QString& endpoint, const UploadAttachment &attachment, const QJsonObject &payload);

private slots:
	void onReply(QNetworkReply* reply);

private:
	QNetworkReply* sendRequest(const Url& url, const QByteArray& verb,
		const Token& token, const QJsonObject& payload = QJsonObject());

	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END