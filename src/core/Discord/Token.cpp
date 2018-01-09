#include "Token.h"

QDISCORD_NAMESPACE_BEGIN

Token::Token()
	: token_base_()
	, type_(Type::UNKNOWN)
{
}

void Token::generate(const QString token_base, Type type)
{
	token_base_ = token_base;
	type_ = type;
}

QByteArray Token::authorization() const
{
	switch (type_)
	{
		case Type::BOT:
			return ("Bot " + token_base_).toUtf8();
		break;

		case Type::OAUTH2_BEARER:
			return ("Bearer " + token_base_).toUtf8();
		break;

		default:
			return token_base_.toUtf8();
		break;
	}
}

QDISCORD_NAMESPACE_END