#pragma once
#include "Discord.h"

#include <QtCore/QTimer>
#include <QtWebSockets/QWebSocket>

QDISCORD_NAMESPACE_BEGIN

struct Payload;

class GatewaySocket : public QWebSocket
{
	Q_OBJECT

public:
	GatewaySocket(QObject* parent = nullptr);

	void connectToGateway(const QUrl& gateway, const QString& token);
	void disconnectFromGateway(QWebSocketProtocol::CloseCode close_code =
		QWebSocketProtocol::CloseCodeNormal);

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
	QString token_;

	int last_sequence_number_;

	bool is_connected_to_gateway_;
	bool heartbeat_answered_;
};

QDISCORD_NAMESPACE_END