#pragma once
#include "Discord.h"

#include <QtCore/QObject>

QDISCORD_NAMESPACE_BEGIN

template<typename T>
class Promise : public QObject
{
public:
	using ResolvedFunctor = std::function<void(const T&)>;
	using RejectedFunctor = std::function<void()>;

	Promise(QObject* parent = nullptr);

	void resolve(const T& result);
	void reject();

	Promise<T>& then(ResolvedFunctor&& resolved_functor);
	Promise<T>& otherwise(RejectedFunctor&& rejected_functor);

private:
	std::function<void(const T&)> resolved_functor_;
	std::function<void()> rejected_functor_;
};

template<typename T>
Promise<T>::Promise(QObject* parent)
	: QObject(parent)
{
}

template<typename T>
void Promise<T>::resolve(const T& result)
{
	if (resolved_functor_)
		resolved_functor_(result);
}

template<typename T>
void Promise<T>::reject()
{
	if (rejected_functor_)
		rejected_functor_();
}

template<typename T>
Promise<T>& Promise<T>::then(ResolvedFunctor&& resolved_functor)
{
	resolved_functor_ = resolved_functor;
	return (*this);
}

template<typename T>
Promise<T>& Promise<T>::otherwise(RejectedFunctor&& rejected_functor)
{
	rejected_functor_ = rejected_functor;
	return (*this);
}

QDISCORD_NAMESPACE_END