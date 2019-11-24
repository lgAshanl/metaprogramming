#include <stdint.h>
#include "argspack.hpp"

#pragma once
#ifndef FUNCTOR_H
#define FUNCTOR_H

template <class TCE>
struct CEWrapper {
private:
    TCE m_CallableEntity;

public:
    CEWrapper(const TCE& ptr) : m_CallableEntity(ptr) {}

    template<typename... Params2>
    auto operator()(Params2... args) const -> decltype(m_CallableEntity(args...))
    {
        return m_CallableEntity(args...);
    }
};

template<class TObject, typename TCE>
struct SimpleDelegate {
private:
    TObject& m_Object;
    TCE m_CallableEntity;

public:
    SimpleDelegate(TObject& object, const TCE& ptr)
      : m_Object(object), m_CallableEntity(ptr)
    { }

    template<typename... Args>
    auto operator()(Args... args) const
        -> decltype((m_Object.*m_CallableEntity) (args...))
    {
        return (m_Object.*m_CallableEntity) (args...);
    }
};

template<class TCallableEntity, class... Args>
class Functor
{
private:
    TCallableEntity m_CallableEntity;
    ArgsPack<Args...> m_base;

public:
    Functor(const TCallableEntity& func, Args... args)
      : m_CallableEntity(func), m_base(args...)
    { }

    template<class TCE = TCallableEntity>
    auto call()
        -> decltype(m_base.call(CEWrapper<TCE>(m_CallableEntity))) const
    {
        return m_base.call(m_CallableEntity);
    }

    template<class Object>
    auto call(Object& object)
        -> decltype(m_base.call(SimpleDelegate<Object, TCallableEntity>(object, m_CallableEntity))) const
    {
        return m_base.call(SimpleDelegate<Object, TCallableEntity>(object, m_CallableEntity));
    }

};

template<class TCallableEntity, typename...Params>
Functor<TCallableEntity, Params...> make_functor(const TCallableEntity& callable_entity, Params&&... given_params)
{
    return Functor<TCallableEntity, Params...>(callable_entity, std::forward<Params>(given_params)...);
}

#endif // FUNCTOR_H
