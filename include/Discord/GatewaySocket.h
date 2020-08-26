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
#include "Discord/Token.h"

#include <QtCore/QTimer>
#include <QtWebSockets/QWebSocket>

QDISCORD_NAMESPACE_BEGIN

struct Payload;

class GatewaySocket : public QWebSocket
{
	Q_OBJECT

public:
	GatewaySocket(QObject* parent = nullptr);

	void connectToGateway(const QUrl& gateway, const Token& token);
	void disconnectFromGateway(QWebSocketProtocol::CloseCode close_code =
		QWebSocketProtocol::CloseCodeNormal);
	void reconnectToGateway();

	void sendPayload(const Payload& payload);
	void identify();
	void resumeSession(const QString& session_token,
		const QString& session_id);
	void heartbeat();

	bool isConnectedToGateway() const { return is_connected_to_gateway_; }

signals:
	void event(const QString& name, const QJsonObject& data);

private slots:
	void onConnected();
	void onDisconnected();
	void onTextMessageReceived(const QString& message);
	void onHeartbeatTimerTick();

private:
	void handleIncomingPayload(const Payload& payload);

	QTimer heartbeat_timer_;
	QUrl last_gateway_;
	Token token_;

	int last_sequence_number_;

	bool is_connected_to_gateway_;
	bool heartbeat_answered_;
};

QDISCORD_NAMESPACE_END
