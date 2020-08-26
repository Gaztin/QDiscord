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
#include "Discord.h"

#include <QtCore/QObject>

#include <functional>

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
