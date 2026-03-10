#pragma once
#include "cmapgriditerator.h"
#include "sroomcoords.h"

#include <optional>

/**
 * @brief The TGridSize struct
 * A struct for the size
 * @remark nice to have to see if it is valid or count the fields..
 */

struct TGridSize
{
    size_t width;
    size_t height;
    size_t numFields() const
    {
        return width * height;
    }
    bool operator!() const
    {
        return width == 0 || height == 0;
    }
};

/**
 * @brief The CMapGrid class
 * a two dimensional container.
 * also provides an intator so we can use std::ranges to iterate and filter.
 */
template <class TValueType>
class CMapGrid
{
public:
    /**
     * Typdefs for iterators
     */
    using Iterator = CMapGridIterator<TValueType, std::vector<std::vector<TValueType>>>;
    using ConstIterator =
        CMapGridIterator<std::add_const_t<TValueType>, std::add_const_t<std::vector<std::vector<TValueType>>>>;

    /**
     * @brief begin
     * @return the begin-iterator
     */
    Iterator begin()
    {
        return Iterator::begin(&_grid);
    }

    /**
     * @brief end
     * @return the end-Iterator
     */
    Iterator end()
    {
        return Iterator::end(&_grid);
    }

    /**
     * @brief begin
     * @return the const begin-Iterator
     */
    ConstIterator begin() const
    {
        return ConstIterator::begin(&_grid);
    }

    /**
     * @brief end
     * @return the const end-Iterator
     */
    ConstIterator end() const
    {
        return ConstIterator::end(&_grid);
    }

    /**
     * @brief CMapGrid
     * A explicit default contstructor, needed for the iterators
     */
    CMapGrid() = default;

    /**
     * @brief resize
     * gives the container size
     * does not create elements at all
     * @remark everything is cleared
     * @remark needed for push_back
     */
    void resize(const TGridSize& sz);

    /**
     * @brief size
     * @return Getter for the size
     * @remark returns the intended size
     */
    TGridSize size() const;

    /**
     * @brief count
     * @return the actual count of elements
     */
    unsigned int count() const;

    /**
     * @brief clear
     * leert alle vektoren.
     * @remark Die Größe bleibt unangetastet.
     */
    void clear();

    /**
     * @brief at
     * returns the value at coords
     * @param coords coordinates ot the value
     * @remark no access check
     */
    TValueType at(const Map::SRoomCoords coords) const;

    /**
     * @brief coordsOf
     * returns the coords of a value if the value exists in the container
     */
    std::optional<Map::SRoomCoords> coordsOf(const TValueType& val);

    /**
     * @brief push
     * adds a value at coords
     * @remark no access check
     */
    void push(const Map::SRoomCoords coords, TValueType& val);

    /**
     * @brief push_back
     * adds a value to the end of the container.
     */
    std::optional<Map::SRoomCoords> push_back(const TValueType& val);

private:
    std::vector<std::vector<TValueType>> _grid;
    TGridSize _sz = {0, 0};
};
