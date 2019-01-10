
#include "GatewaySocket.h"

#include "Discord/Payload.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>

QDISCORD_NAMESPACE_BEGIN

GatewaySocket::GatewaySocket(QObject* parent)
	: QWebSocket()
	, heartbeat_timer_(this)
	, last_gateway_()
	, token_()
	, last_sequence_number_(0)
	, is_connected_to_gateway_(false)
	, heartbeat_answered_(false)
{
	heartbeat_timer_.setSingleShot(false);

	connect(&heartbeat_timer_, &QTimer::timeout, this,
		&GatewaySocket::onHeartbeatTimerTick);
	connect(this, &QWebSocket::connected, this,
		&GatewaySocket::onConnected);
	connect(this, &QWebSocket::disconnected, this,
		&GatewaySocket::onDisconnected);
	connect(this, &QWebSocket::textMessageReceived, this,
		&GatewaySocket::onTextMessageReceived);
}

void GatewaySocket::connectToGateway(const QUrl& gateway, const Token& token)
{
	last_gateway_ = gateway;
	token_ = token;

	open(gateway);
}

void GatewaySocket::disconnectFromGateway(
		QWebSocketProtocol::CloseCode close_code)
{
	close(close_code);
}

void GatewaySocket::sendPayload(const Payload& payload)
{
	QJsonObject json_object;
	json_object["op"] = static_cast<int>(payload.opcode);
	json_object["d"] = payload.event_data;
	json_object["s"] = payload.sequence_number;
	json_object["t"] = payload.event_name;

	sendTextMessage(QJsonDocument(json_object).toJson());
}

void GatewaySocket::identify()
{
#if defined(Q_OS_WIN)
	QString os = "windows";
#elif defined(Q_OS_LINUX)
	QString os = "linux";
#elif defined(Q_OS_MACOS)
	QString os = "macosx";
#endif

	QJsonObject properties;
	properties["$os"] = os;
	properties["$browser"] = "QDiscord";
	properties["$device"] = "QDiscord";

	QJsonArray shard_data;
	shard_data.append(0);
	shard_data.append(1);

	QJsonObject event_data;
	event_data["token"] = token_.tokenBase();
	event_data["properties"] = properties;
	event_data["compress"] = false;
	event_data["large_threshold"] = 250;
	event_data["shard"] = shard_data;

	Payload payload;
	payload.opcode = PayloadOpcode::IDENTIFY;
	payload.event_data = event_data;

	sendPayload(payload);
}

void GatewaySocket::resumeSession(const QString& session_token,
		const QString& session_id)
{
	QJsonObject event_data;
	event_data["token"] = session_token;
	event_data["session_id"] = session_id;
	event_data["seq"] = static_cast<int>(last_sequence_number_);

	Payload payload;
	payload.opcode = PayloadOpcode::RESUME;
	payload.event_data = event_data;

	sendPayload(payload);
}

void GatewaySocket::heartbeat()
{
	Payload payload;
	payload.opcode = PayloadOpcode::HEARTBEAT;
	payload.sequence_number = last_sequence_number_;

	sendPayload(payload);

#ifdef QT_DEBUG
	qDebug("Heartbeat %d", last_sequence_number_);
#endif
}

void GatewaySocket::onConnected()
{
	is_connected_to_gateway_ = true;

#ifdef QT_DEBUG
	qDebug("Connected");
#endif
}

void GatewaySocket::onDisconnected()
{
	is_connected_to_gateway_ = false;
	heartbeat_timer_.stop();

#ifdef QT_DEBUG
	qDebug("Disconnected. Close code (%d) Reason: %s", closeCode(),
		qPrintable(closeReason()));
#endif
}

void GatewaySocket::onTextMessageReceived(const QString& message)
{
	QJsonDocument json_document = QJsonDocument::fromJson(
		message.toLocal8Bit());
	QJsonObject json_object = json_document.object();
	Payload payload;

	payload.opcode = static_cast<PayloadOpcode>(json_object["op"].toInt());
	payload.event_data = json_object["d"].toObject();
	payload.sequence_number = json_object["s"].toInt();
	payload.event_name = json_object["t"].toString();

	handleIncomingPayload(payload);
}

void GatewaySocket::onHeartbeatTimerTick()
{
	if (heartbeat_answered_)
	{
		heartbeat();
	}
	else
	{
#ifdef QT_DEBUG
		qDebug("Unanswered heartbeat. Reestablishing connection.");
#endif
		disconnectFromGateway(
			QWebSocketProtocol::CloseCodeAbnormalDisconnection);
		connectToGateway(last_gateway_, token_);
	}
}

void GatewaySocket::handleIncomingPayload(const Payload& payload)
{
	switch (payload.opcode)
	{
		case PayloadOpcode::DISPATCH:
			last_sequence_number_ = payload.sequence_number;
			emit event(payload.event_name, payload.event_data.toObject());
		break;

		case PayloadOpcode::HEARTBEAT:
			heartbeat();
		break;

		case PayloadOpcode::RECONNECT:
#ifdef QT_DEBUG
			qDebug("Requested reconnect from server..");
#endif
			disconnectFromGateway();
			connectToGateway(last_gateway_, token_);
		break;

		case PayloadOpcode::INVALID_SESSION:
		{
			const bool should_retry = payload.event_data.toBool();
			if (should_retry)
			{
#ifdef QT_DEBUG
				qDebug("Invalid session. Retrying..");
#endif
				disconnectFromGateway();
				connectToGateway(last_gateway_, token_);
			}
			else
			{
#ifdef QT_DEBUG
				qDebug("Invalid session. Can't resume.");
#endif
			}
		}
		break;

		case PayloadOpcode::HELLO:
		{
			QJsonObject json_object = payload.event_data.toObject();
			const int heartbeat_interval = json_object.value(
				"heartbeat_interval").toInt();

			heartbeat_answered_ = true;
			heartbeat_timer_.start(heartbeat_interval);

			identify();
		}
		break;

		case PayloadOpcode::HEARTHBEAT_ACK:
			heartbeat_answered_ = true;
		break;

		default:
#ifdef QT_DEBUG
			qDebug("Unhandled opcode (%d) in incoming payload",
				static_cast<int>(payload.opcode));
#endif
		break;
	}
}

QDISCORD_NAMESPACE_END
