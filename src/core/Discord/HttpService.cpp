#include "HttpService.h"

#include "Discord/Payload.h"
#include "Discord/Token.h"

#include <QtCore/QBuffer>
#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QtGui/QPixmap>
#include <QtNetwork/QHttpMultiPart>
#include <QtCore/QFile>

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

QNetworkReply* HttpService::postMultipart(const Token& token, const QString& endpoint, const UploadAttachment &attachment, const QJsonObject &payload) {
	QJsonDocument doc(payload);
	int docsize = 0;
	doc.rawData(&docsize);

	QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QBuffer *payload_buffer = new QBuffer;
	payload_buffer->open(QBuffer::WriteOnly);
	payload_buffer->write(QJsonDocument(payload).toJson(QJsonDocument::Compact));
	payload_buffer->close();
	payload_buffer->open(QBuffer::ReadOnly);

	QBuffer *file_buffer = new QBuffer;
	file_buffer->open(QBuffer::WriteOnly);
	file_buffer->write(attachment.file);
	file_buffer->close();
	file_buffer->open(QBuffer::ReadOnly);

	QHttpPart text_part;
	text_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"payload_json\""));
	text_part.setBodyDevice(payload_buffer);

	QHttpPart image_part;
	if (attachment.type == UploadImageSupportedExtension::PNG) {
		image_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
	} else if (attachment.type == UploadImageSupportedExtension::JPG) {
		image_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
	} else if (attachment.type == UploadImageSupportedExtension::GIF) {
		image_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/gif"));
	}
	image_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + attachment.name + "\""));
	image_part.setBodyDevice(file_buffer);

	multi_part->append(text_part);
	multi_part->append(image_part);

	QNetworkRequest request(Url(BaseUrl::API, endpoint).url());
	request.setRawHeader("Authorization", token.authorization());
	request.setRawHeader("User-Agent", user_agent_.toUtf8());

	QNetworkReply* reply = network_access_manager_.post(request, multi_part);
	multi_part->setParent(reply);
	connect(reply, &QNetworkReply::finished, [multi_part, payload_buffer, file_buffer ] { 
		delete multi_part; 
		delete payload_buffer;
		delete file_buffer;
	});

	return reply;
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
		request.setRawHeader("Content-Length", "0");
		return network_access_manager_.sendCustomRequest(request, verb);
	}
	else
	{
		QJsonDocument doc(payload);
		int docsize = 0;
		doc.rawData(&docsize);
		request.setRawHeader("Content-Type", "application/json");
		request.setRawHeader("Content-Length", QString::number(docsize).toLocal8Bit());

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