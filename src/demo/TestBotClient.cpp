#include "TestBotClient.h"

#include <Discord/Message.h>

TestBotClient::TestBotClient(QObject* parent)
	: Discord::Client("test-bot")
{
}

void TestBotClient::onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds)
{
#ifdef QT_DEBUG
	qDebug("onReady()");
#endif
}

void TestBotClient::onMessageCreate(const Discord::Message& message)
{
#ifdef QT_DEBUG
	qDebug("onMessageCreate (%s)", qPrintable(message.content));
#endif
}