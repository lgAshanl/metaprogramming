#include <stdint.h>
#include "stdio.h"

#pragma once
#ifndef CSV_READER_TUPLE_H
#define CSV_READER_TUPLE_H

template <uint32_t N, typename>
struct IndexHandler;

template<typename T, typename Tail = int>
struct Tuple
{
    const Tail m_tail;

    Tuple()
      : m_tail(Tail())
    { }

    template<typename P>
    Tuple<P, Tuple<T, Tail> > push() {
        return Tuple<P, Tuple<T, Tail> >();
    }
    
    template<typename Desired>
    int32_t getIndexOf() const {
        return IndexHandler<0, Tuple<T, Tail> >().template at<Desired>();
    }
};

template <uint32_t N, typename T, typename Tail>
struct IndexHandler<N, Tuple<T, Tail> > {
    template<typename Desired>
    int32_t at() const {
        return IndexHandler<N + 1, Tail >().template at<Desired>();
    }

    template<>
    int32_t at<T>() const {
        return N;
    }
};

template <uint32_t N, typename T>
struct IndexHandler<N, Tuple<T> > {
    template<typename Desired>
    int32_t at() const {
        return -1;
    }

    template<>
    int32_t at<T>() const {
        return N;
    }
};

template<typename T>
struct Tuple<T>
{
    Tuple()
    { }

    template<typename P>
    Tuple<P, T> push() {
        return Tuple<P, Tuple<T> >();
    }

    template<typename Desired>
    int32_t getIndexOf() const {
        return at<0, Desired>();
    }

    template<uint32_t N, typename Desired>
    int32_t at() const {
        return -1;
    }

    template<>
    int32_t at<0, T>() const {
        return 0;
    }
};

#endif // CSV_READER_TUPLE_H
