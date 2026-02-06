#pragma once

#include <exception>
#include <string>

/**
 * Exceptions are used to exit the game loop (without numerous nested "if( player->isDead() ) return" - calls)
 */

/**
 * @brief can be thrown, when the player died.
 *        exit the game loop, trigger death effects
 * @param[in] what a death text to be displayed.
 * @remark cbattle throws this exception if the player looses a battle
 */
class CPlayerDiedException : public std::exception
{
public:
    CPlayerDiedException(const std::string_view& what) : std::exception()
    {
        _what = what;
    }

private:
    std::string _what;
    virtual const char* what() const throw()
    {
        return _what.c_str();
    }
};

/**
 * @brief can be thrown to end the game.
 *        no save - no mercy when this is thrown from inside the game loop. the game ends
 */
class CGameOverException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Game Over";
    }
};
