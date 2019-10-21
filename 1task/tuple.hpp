#include <stdint.h>
#include "exception.hpp"

#pragma once
#ifndef CSV_READER_TUPLE_H
#define CSV_READER_TUPLE_H

template <uint32_t N, typename> struct TypeHandler;

template<typename T, typename... Args>
struct Tuple
{
    const T m_value;
    const Tuple<Args...> m_tail;
    typedef T m_type;

    Tuple() = delete;

    Tuple(T value, Args... args)
      : m_value(value), m_tail(args ...)
    { }

    Tuple(T value, Tuple<Args...>&& tuple)
      : m_value(value), m_tail(tuple)
    { }
    
    template<uint32_t N>
    typename TypeHandler<N, Tuple<T, Args...>>::m_type at() const {
        return m_tail.template at<N - 1>();
    }

    template<>
    typename TypeHandler<0, Tuple<T, Args...>>::m_type at<0>() const {
        return m_value;
    }

    static Tuple<T, Args...> from_istringstream(std::istringstream& stream) {
        T value;
        stream >> value;
        if (stream.eof())
            throw BadLine();
        return Tuple<T, Args...>(value, Tuple<Args...>::from_istringstream(stream));
    }
};

template <typename T, typename... Args>
struct TypeHandler<0, Tuple<T, Args...>> {
  typedef T m_type;
};

template <uint32_t N, typename T, typename... Args>
struct TypeHandler<N, Tuple<T, Args...>> {
  typedef typename TypeHandler<N - 1, Tuple<Args...>>::m_type m_type;
};

template<typename T>
struct Tuple<T>
{
    const T m_value;

    Tuple(T value)
      : m_value(value)
    { }

    template<uint32_t N>
    T at() const;

    template<>
    T at<0>() const {
        return m_value;
    }

    static Tuple<T> from_istringstream(std::istringstream& stream) {
        T value;
        stream >> value;
        return Tuple<T>(value);
    }
};

#endif // CSV_READER_TUPLE_H
