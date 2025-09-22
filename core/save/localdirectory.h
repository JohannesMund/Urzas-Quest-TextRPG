#pragma once

#include <filesystem>

/**
 * @brief Console LocalDirectory
 * Handles a local directory to store stuff (~/.UrzasQuestTextRPG)
 * @remark This code is not platform independent.
 * @remark  Windows and Linux are covered. Mac and Posix should work as well
 * @remark throws exceptions
 * @sa save/exceptions.h CSaveFileException
 */

namespace LocalDirectory
{
/**
 * @brief returns a path the a local, writable directory
 * @remark directory will be the same on the same pc
 * @remark directory will be created when it does njot exist
 */
std::filesystem::path getLocalDirectoryPath();
}; // namespace LocalDirectory