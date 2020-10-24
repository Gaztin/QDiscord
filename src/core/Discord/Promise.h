#pragma once
#include "Discord.h"

#include <QtCore/QObject>

#include <functional>
#include <type_traits>

QDISCORD_NAMESPACE_BEGIN

template<typename... Ts>
class Promise : public QObject
{
public:
	using ResolvedFunctor = std::function<void(Ts...)>;
	using RejectedFunctor = std::function<void()>;

	Promise(QObject* parent = nullptr)
		: QObject(parent)
	{
	}

	void resolve(Ts... values)
	{
		if (resolved_functor_)
			resolved_functor_(values...);
	}

	void reject()
	{
		if (rejected_functor_)
			rejected_functor_();
	}

	Promise& then(ResolvedFunctor resolved_functor)
	{
		resolved_functor_ = std::move(resolved_functor);
		return *this;
	}

	Promise& otherwise(RejectedFunctor rejected_functor)
	{
		rejected_functor_ = std::move(rejected_functor);
		return *this;
	}

private:
	ResolvedFunctor resolved_functor_;
	RejectedFunctor rejected_functor_;
};

QDISCORD_NAMESPACE_END
