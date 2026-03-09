#pragma once

#include <cmath>
#include <iterator>
#include <vector>

/**
 * @brief The CBattleFieldGridIterator class
 * Wir bauen uns einen Iterator für einen 2 dimensionalen Vektor
 * @remark Ist es sinnvoll einen Container zu erfinden, und einen Iterator dafür zu bauen, wenn sich das mit STL
 * Containern umsetzen ließe? - NEIN!
 * Ist es einfacher einen Container zu erfinden, und einen Iterator dafür zu bauen, wenn sich das mit STL
 * Containern umsetzen ließe? - Um Gottes Willen, NEIN!
 * Machen wir es trotzdem? - FUCK YEAH!
 * Warum? - Weil wir es können!
 * @remark - Wir implementieren alles in den Header. Das ist nicht schön, aber wir haben eine Template Klasse, und
 * müssen den Compiler zwingen die Klasse kompiliert zu haben, wenn wir sie Brauchen. Das ist eine Möglichkeit, die
 * andere Option findet sich im Container.
 * @sa CBattleFieldGrid
 */

template <typename TIteratorType, class TContainerType>
struct CMapGridIterator
{
public:
    /**
     * @remark Diese definitionen sind notwendig, damit der Compiler das ganze Konstrukt als Iterator nutzen kann
     * Wie bauen einen Random Access Iterator, man kann also in beide Richtungen iterieren und auch frei hin- und
     * herspringem.
     */

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<TIteratorType>;
    using pointer = TIteratorType*;
    using reference = TIteratorType&;

    /**
     * für die Bessere Lesbarkeit
     * der self_type ist nicht notwendig.
     */
    using self_type = CMapGridIterator;

    /**
     * @brief CBattleFieldGridIterator
     * Im Konstruktor bekommt der Iterator einen Zeiger auf das Grid, und eine Startposition
     * @param vv Zeiger auf den Container
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
     * Ab hier Standard. Alle Iteratoren müssen die folgenden Operatoren implementieren. Die Zugriffsopteratoren (* und
     * ->) müssen const und nicht-const vorhanden sein. Aufpassen beim Lesen, *this benutzt den ersten *-Operatore zum
     * dereferenzieren des Wertes. (Also das, was der Iterator landläufig so macht.) Natürlich implementieren wir den
     * Zugriff nur einmal und benutzen ihn dann.
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
     * Inkrement und Dekrement jeweils als Postfix und als Prefix
     * Auch hier wieder einmal implementieren und dann nutzen.
     * Wir greifen auch auf den reference operator zurück
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
     * Und weil wir es wissen wollten und einen Random Access Iterator gebaut haben (sozusagen die Königin Mutter der
     * Iteratoren), müssen wir auch arithmetische Operatoren haben.
     */

    // Man beachte die Typen, hier geht es um den Abstand zwischen zwei Iteratoren
    // z.B.: int i = Iterator1 - Iterator2;
    inline difference_type operator-(const self_type& rhs) const
    {
        return (_innerIndex + _outerIndex) - (rhs._innerIndex + rhs._outerIndex);
    }

    // Alle weiteren Operatoren schieben in die ein- oder andere Richtung

    // z.B.: Iterator1 = Iterator2 + 5;
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

    // z.B.: Iterator1 = Iterator2 - 5;
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
     * Und zu guter Letzt muss der Kram noch vergleichbar sein.
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
     * der Iterator soll auch seine Position verraten
     * @return x-coordinate
     */
    size_t x() const
    {
        return _innerIndex;
    }

    /**
     * @brief y
     * der Iterator soll auch seine Position verraten
     * @return y-coordinate
     */
    size_t y() const
    {
        return _outerIndex;
    }

    /**
     * @brief begin
     * Statische Funktion, die den begin() Iterator für einen Container zurückgibt
     */
    static self_type begin(TContainerType* vv)
    {
        self_type it(vv, 0, 0);
        it.begin();
        return it;
    }

    /**
     * @brief end
     * Statische Funktion, die den end() Iterator für einen Container zurückgibt
     */
    static self_type end(TContainerType* vv)
    {
        self_type it(vv, 0, 0);
        it.end();
        return it;
    }

private:
    /**
     * Hilfsfunktionen
     * Wir missbrauchen das Iteratorkonzept ein wenig.
     * Normalerweise hat ein Iterator einen Zeiger und schubst den hin- oder her. Wir bewegen uns in einem
     * 2-dimensionalen Container und beachten die Grenzen.
     */

    /**
     * @brief numericSize
     * Die Anzahl an Elementen im Container
     */
    size_t numericSize() const
    {
        return height() * width();
    }

    /**
     * @brief width
     * Breite des Containers
     */
    size_t width() const
    {
        return _vectorOfVectors->size() ? _vectorOfVectors->at(0).size() : 0;
    }

    /**
     * @brief height
     * @return Höhe des Containers
     */
    size_t height() const
    {
        return _vectorOfVectors->size();
    }

    /**
     * @brief numericIndex
     * Die Elemente sind zählbar, wir zählen zeilenweise.
     * Also können wir auch einen eindeutigen Index bestimmen.
     */
    size_t numericIndex() const
    {
        return (_outerIndex * width()) + _innerIndex;
    }

    /**
     * @brief begin
     * Setzt this auf begin()
     * @remark nur für den internen Gebrauch
     */
    self_type& begin()
    {
        _innerIndex = 0;
        _outerIndex = 0;
        return *this;
    }

    /**
     * @brief end
     * Setzt this auf end()
     * @remark nur für den internen Gebrauch
     */
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
