#pragma once
#include <Discord/Client.h>

class EmbedsClient : public Discord::Client
{
public:
	EmbedsClient(QObject* parent = nullptr);

protected:
	virtual void onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds) override;
	virtual void onMessageCreate(const Discord::Message& message) override;
};