#include <stdint.h>

#pragma once
#ifndef TYPE_LIST_H
#define TYPE_LIST_H

template <uint32_t N, typename> struct TypeHandler;

template<typename T, typename... Args>
struct TypeList
{
    const TypeList<Args...> m_tail;
    typedef T m_type;

    TypeList()
      : m_tail()
    { }
};

template <typename T, typename... Args>
struct TypeHandler<0, TypeList<T, Args...>> {
  typedef T m_type;
};

template <uint32_t N, typename T, typename... Args>
struct TypeHandler<N, TypeList<T, Args...>> {
  typedef typename TypeHandler<N - 1, TypeList<Args...>>::m_type m_type;
};

template<typename T>
struct TypeList<T>
{
    TypeList()
    { }
};

#endif // TYPE_LIST_H
