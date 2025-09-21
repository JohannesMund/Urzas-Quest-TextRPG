#include "localdirectory.h"
#include "globals.h"
#include "ressources.h"
#include "save/exceptions.h"

#include <format>

#ifdef _USE_WINDOWS
#include <ShlObj_core.h>
#include <windows.h>
#else
#include <pwd.h>
#include <unistd.h>
#endif

namespace
{
void checkAndExpandPath(std::filesystem::path& p)
{
    if (!std::filesystem::exists(p))
    {
        throw SaveFile::CSaveFileException("Local Directory does not exist");
    }
    p.append(std::format(".{}", Ressources::Settings::appName));
    if (!std::filesystem::exists(p))
    {
        if (!std::filesystem::create_directories(p))
        {
            throw SaveFile::CSaveFileException("Cannot create program direcotr");
        }
    }
}
} // namespace

std::filesystem::path LocalDirectory::getLocalDirectoryPath()
{
    std::filesystem::path result = {};
#ifdef _USE_WINDOWS
    PWSTR homeDir = nullptr;
    SHGetKnownFolderPath(FOLDERID_Profile, KF_FLAG_DEFAULT, nullptr, &homeDir);
    std::filesystem::path p{homeDir};
    result = p;
    CoTaskMemFree(homeDir);
#else
    const char* homeDir = getpwuid(getuid())->pw_dir;
    std::filesystem::path p{homeDir};
    result = p;
#endif
    checkAndExpandPath(result);
    return result;
}
