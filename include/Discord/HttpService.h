/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once
#include "Discord/Url.h"

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

QDISCORD_NAMESPACE_BEGIN

class Channel;
class Token;

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

private slots:
	void onReply(QNetworkReply* reply);

private:
	QNetworkReply* sendRequest(const Url& url, const QByteArray& verb,
		const Token& token, const QJsonObject& payload = QJsonObject());

	QString user_agent_;
	QNetworkAccessManager network_access_manager_;
};

QDISCORD_NAMESPACE_END
