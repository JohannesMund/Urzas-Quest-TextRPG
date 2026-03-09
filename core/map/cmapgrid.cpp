#include "cmapgrid.h"
#include <assert.h>

template <class TValueType>
void CMapGrid<TValueType>::resize(const TGridSize& sz)
{
    clear();
    _sz = sz;
}

template <class TValueType>
TGridSize CMapGrid<TValueType>::size() const
{
    if (_grid.size() == 0)
    {
        return {0, 0};
    }
    return {_grid.at(0).size(), _grid.size()};
}

template <class TValueType>
unsigned int CMapGrid<TValueType>::count() const
{
    return _sz.width * _sz.height;
}

template <typename TContainerType>
void CMapGrid<TContainerType>::clear()
{
    for (auto l : _grid)
    {
        l.clear();
    }
    _grid.clear();
}

template <typename TContainerType>
TContainerType CMapGrid<TContainerType>::at(const Map::SRoomCoords coords) const
{
    return _grid.at(coords.y).at(coords.x);
}

template <class TValueType>
std::optional<Map::SRoomCoords> CMapGrid<TValueType>::coordsOf(const TValueType& val)
{
    for (unsigned int y = 0; y < _grid.size(); y++)
    {
        for (unsigned int x = 0; x < _grid.at(y).size(); x++)
        {
            Map::SRoomCoords coords = {x, y};
            if (at(coords) == val)
            {
                return coords;
            }
        }
    }

    return {};
}

template <class TValueType>
void CMapGrid<TValueType>::push(const Map::SRoomCoords coords, TValueType& val)
{
    _grid.at(coords.y).at(coords.x) = val;
}

template <typename TContainerType>
std::optional<Map::SRoomCoords> CMapGrid<TContainerType>::push_back(const TContainerType& val)
{
    if (_grid.empty())
    {
        _grid.push_back(std::vector<TContainerType>{});
    };
    if (_grid.at(_grid.size() - 1).size() >= _sz.width)
    {
        _grid.push_back(std::vector<TContainerType>{});
    }
    _grid.at(_grid.size() - 1).push_back(val);

    return Map::SRoomCoords({(unsigned int)_grid.at(_grid.size() - 1).size() - 1, (unsigned int)_grid.size() - 1});
}
#include "cmapgridregister.h"
