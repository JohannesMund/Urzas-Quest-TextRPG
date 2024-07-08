#include <exception>
#include <string>

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

class CGameOverException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Game Over";
    }
};
