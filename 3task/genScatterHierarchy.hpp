#include "typelist.hpp"

#pragma once

#ifndef GEN_SCATTER_HIERARCHY_H
#define GEN_SCATTER_HIERARCHY_H

template <class TList, template <class> class Unit>
class GenScatterHierarchy;

template <template <class> class Unit, class T, typename... Args>
class GenScatterHierarchy<TypeList<T, Args...>, Unit>
  : public GenScatterHierarchy<TypeList<T>, Unit>,
    public GenScatterHierarchy<TypeList<Args...>, Unit>
{
public:
    using TList = TypeList<T, Args...>;
    using LeftBase = GenScatterHierarchy<TypeList<T>, Unit>;
    using RightBase = GenScatterHierarchy<TypeList<Args...>, Unit>;

    template<uint32_t N>
    typename TypeHandler<N, TypeList<T, Args...>>::m_type at() const {
        return RightBase::template at<N - 1>();
    }

    template<>
    typename TypeHandler<0, TypeList<T, Args...>>::m_type at<0>() const {
        return LeftBase::value;
    }
    
};

template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy<TypeList<AtomicType>, Unit>
    : public Unit<AtomicType>
{
public:
    using LeftBase = Unit<AtomicType>;

    template<uint32_t N>
    AtomicType at() const;

    template<>
    AtomicType at<0>() const {
        return LeftBase::value;
    }
};

#endif // GEN_SCATTER_HIERARCHY_H
