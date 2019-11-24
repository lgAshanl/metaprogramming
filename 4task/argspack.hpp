#include <stdint.h>
#include <utility>

#pragma once
#ifndef ARGSPACK_H
#define ARGSPACK_H

template<typename T>
inline T* ConvertToPtr(T& t) {
    return &t;
}
template<typename T>
inline T* ConvertToPtr(T* t) {
    return t;
}

template<typename T>
inline T& ConvertToRef(T& t) {
    return t;
}
template<typename T>
inline T& ConvertToRef(T* t) {
    return *t;
}

template<typename... Tail>
class ArgsPack;

template<>
class ArgsPack<> {
public:
    ArgsPack()
    { }

    template<class Delegate, typename... Args>
    auto call(const Delegate& delegate, Args&&... args)
        -> decltype(delegate(args...))
    {
        return delegate(args...);
    }
};

template<typename Head, typename... Tail>
class ArgsPack<Head, Tail...>
{
private:
    Head m_param;
    ArgsPack<Tail...> m_tail;

public:
    
    template<typename _Head, typename... _Tail>
    explicit ArgsPack(_Head&& head, _Tail&&... tail)
      : m_param(std::forward<Head>(head)),
        m_tail(std::forward<_Tail>(tail)...)        
    { }

    template<class Delegate, typename... Args>
    auto call(const Delegate& delegate, Args&&... args)
        -> decltype(m_tail.call(delegate, args..., ConvertToRef(m_param)))
    {
        return m_tail.call(delegate, args..., ConvertToRef(m_param));
    }

    template<class Delegate, typename... Args>
    auto call(const Delegate& delegate, Args&&... args)
        -> decltype(m_tail.call(delegate, args..., ConvertToPtr(m_param)))
    {
        return m_tail.call(delegate, args..., ConvertToPtr(m_param));
    }
};

#endif // ARGSPACK_H
