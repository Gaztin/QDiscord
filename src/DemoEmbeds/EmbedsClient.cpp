#include "EmbedsClient.h"

#include <Discord/Objects/Message.h>
#include <Discord/Patches/ChannelPatch.h>
#include <Discord/Patches/GuildPatch.h>
#include <Discord/Patches/GuildMemberPatch.h>
#include <Discord/Promise.h>

EmbedsClient::EmbedsClient(QObject* parent)
	: Discord::Client("embeds-bot")
{
}
