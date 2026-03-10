#pragma once

#include <cmath>
#include <iterator>
#include <vector>

/**
 * @brief The CMapIterator class
 * An iterator for a 2-dimensional vector
 * @remark There might be easier ways to do this, but this ways we can iterate the map like a vector without having to
 * think about every single access.
 * @sa CMapGrid
 */

template <typename TIteratorType, class TContainerType>
struct CMapGridIterator
{
public:
    /**
     * @remark Some definitions.
     */

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<TIteratorType>;
    using pointer = TIteratorType*;
    using reference = TIteratorType&;

    /**
     * for readability
     */
    using self_type = CMapGridIterator;

    /**
     * @brief CMapGridIterator
     * Constructor for the iterator
     * @param vv points to the container
     * @param outer y-Pos
     * @param inner x-Pos
     */

    CMapGridIterator(TContainerType* vv, std::size_t outer, std::size_t inner) :
        _vectorOfVectors(vv),
        _outerIndex(outer),
        _innerIndex(inner)
    {
    }

    CMapGridIterator() = default;
    /**
     * default from hereon
     * @remark everything must be const and not const
     */

    reference operator*()
    {
        return _vectorOfVectors->at(_outerIndex).at(_innerIndex);
    }

    reference operator*() const
    {
        return _vectorOfVectors->at(_outerIndex).at(_innerIndex);
    }

    pointer operator->()
    {
        return this;
    }

    pointer operator->() const
    {
        return this;
    }

    /**
     * Increment und Decrement as Postfix and as Prefix
     */
    self_type& operator++()
    {
        if (numericIndex() >= numericSize())
        {
            return end();
        }

        if (_innerIndex + 1 < width())
        {
            ++_innerIndex;
        }
        else
        {
            if (_outerIndex + 1 < height())
            {
                ++_outerIndex;
                _innerIndex = 0;
            }
            else
            {
                return end();
            }
        }
        return *this;
    }

    self_type operator++(int)
    {
        self_type retval(*this);
        ++(*this);
        return retval;
    }

    self_type& operator--()
    {

        if (_innerIndex > 0)
        {
            --_innerIndex;
        }
        else
        {
            if (_outerIndex > 0)
            {
                --_outerIndex;
                _innerIndex = _vectorOfVectors->at(_outerIndex).size() - 1;
            }
            else
            {
                return begin();
            }
        }
        return *this;
    }

    self_type operator--(int)
    {
        self_type retval(*this);
        --(*this);
        return retval;
    }

    /**
     * For Random Access iterators (the god-mother of iterators) we need arithmetic operato2rs
     */

    inline difference_type operator-(const self_type& rhs) const
    {
        return (_innerIndex + _outerIndex) - (rhs._innerIndex + rhs._outerIndex);
    }

    inline self_type operator+(const difference_type rhs) const
    {
        if (rhs < 0)
        {
            return *this - std::abs(rhs);
        }
        if (numericIndex() + rhs > numericSize())
        {
            return end(_vectorOfVectors);
        }

        self_type it(_vectorOfVectors, _outerIndex, _innerIndex);

        int ctr(rhs);
        while (ctr > 0)
        {
            ++it;
            --ctr;
        }

        return it;
    }

    inline self_type operator-(const difference_type rhs) const
    {
        if (rhs < 0)
        {
            return *this + std::abs(rhs);
        }

        int idx = (int)numericIndex();
        if (idx - rhs <= 0)
        {
            return begin(_vectorOfVectors);
        }

        self_type it(_vectorOfVectors, _outerIndex, _innerIndex);

        int ctr(rhs);
        while (ctr > 0)
        {
            --it;
            --ctr;
        }

        return it;
    }
    friend inline self_type operator+(const difference_type lhs, const self_type& rhs)
    {
        return lhs + rhs;
    }
    friend inline self_type operator-(const difference_type lhs, const self_type& rhs)
    {
        return lhs - rhs;
    }

    /**
     * and a little comparison
     */

    bool operator==(self_type const& other) const
    {
        return other._vectorOfVectors == _vectorOfVectors && other._outerIndex == _outerIndex &&
               other._innerIndex == _innerIndex;
    }
    bool operator!=(self_type const& other) const
    {
        return !(*this == other);
    }

    inline bool operator>(self_type const& rhs) const
    {
        return numericSize() > rhs.numericSize();
    }
    inline bool operator<(self_type const& rhs) const
    {
        return numericSize() < rhs.numericSize();
    }
    inline bool operator>=(self_type const& rhs) const
    {
        return numericSize() >= rhs.numericSize();
    }
    inline bool operator<=(self_type const& rhs) const
    {
        return numericSize() <= rhs.numericSize();
    }

    /**
     * @brief x
     * Access to x-coord
     * @return x-coordinate
     */
    size_t x() const
    {
        return _innerIndex;
    }

    /**
     * @brief y
     * Access to y-coord
     * @return y-coordinate
     */
    size_t y() const
    {
        return _outerIndex;
    }

    /**
     * @brief begin
     * begin for iteration
     */
    static self_type begin(TContainerType* vv)
    {
        self_type it(vv, 0, 0);
        it.begin();
        return it;
    }

    /**
     * @brief end
     * end for iterations
     */
    static self_type end(TContainerType* vv)
    {
        self_type it(vv, 0, 0);
        it.end();
        return it;
    }

private:
    size_t numericSize() const
    {
        return height() * width();
    }

    size_t width() const
    {
        return _vectorOfVectors->size() ? _vectorOfVectors->at(0).size() : 0;
    }

    size_t height() const
    {
        return _vectorOfVectors->size();
    }

    size_t numericIndex() const
    {
        return (_outerIndex * width()) + _innerIndex;
    }

    self_type& begin()
    {
        _innerIndex = 0;
        _outerIndex = 0;
        return *this;
    }

    self_type& end()
    {
        _innerIndex = 0;
        _outerIndex = _vectorOfVectors->size();
        return *this;
    }

    TContainerType* _vectorOfVectors;
    std::size_t _outerIndex = 0;
    std::size_t _innerIndex = 0;
};
