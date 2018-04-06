#pragma once
#include <Discord/Client.h>

class TestBotClient : public Discord::Client
{
public:
	TestBotClient(QObject* parent = nullptr);

protected:
	virtual void onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds) override;
	virtual void onMessageCreate(const Discord::Message& message) override;
};