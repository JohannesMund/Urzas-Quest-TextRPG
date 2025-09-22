#pragma once

#include <optional>
#include <string>

/**
 * @brief Console Namespace
 * Some Features to mess with the Terminal
 * @remark This code is not platform independent.
 * @remark  Windows and Linux are covered. Mac and Posix should work as well
 */

namespace Console
{

/**
 * @brief The EAlignment enum
 * defines for text alignments to be used with printLn
 * @sa printLn
 */
enum class EAlignment
{
    eLeft,
    eCenter,
    eRight
};

/**
 * @brief confirmToContinue
 * Displays "Press <Enter>" and blocks until enter is pressed
 */
void confirmToContinue();

/**
 * @brief hr Horizontal ruler
 * draws a horizontal roler with Ressources::Config::Settings::ScreenWidth characters width
 */
void hr();

/**
 * @brief br break
 * a line break. (or paragraph break)
 */
void br();

/**
 * @brief cls Clears the Screen
 */
void cls(const bool bHud = true);

/**
 * @brief printLn Prints of line of text, with automatic breaks and alignment
 * @param text the text to be printed
 * @param align the alignment
 * @param bReset auto true, reset colors at end of output.
 */
void printLn(const std::string_view& text, const EAlignment align = EAlignment::eLeft, const bool bReset = true);

void printErr(const std::string_view& text);

/**
 * @brief printWithSpacer Prints two lines of text with a spacer inbetween
 * @param text1 the left text
 * @param text2 the right text
 */
void printLnWithSpacer(const std::string& text1, const std::string& text2);

/**
 * @brief setEcho Swtiches console echo on or of
 * @param on on or off
 */
void setEcho(const bool on);

/**
 * @brief getAcceptableInput blocks, until a character in acceptableChars is pressed
 * @remark no enter is necessary
 * @param accepableChars a string with all char that shall be accepted
 * @return the accepted char
 */
unsigned char getAcceptableInput(std::string_view accepableChars);

/**
 * @brief getNumberInputWithEcho blocks until a integer beween min and max is entered
 * @remark this time, enter must be pressed.
 * @remark only one try here. will return, as soon enter is pressed.
 * @param min the minimum
 * @param max the maximum
 * @return if a acceptable number was pressed, the number
 */
std::optional<int> getNumberInputWithEcho(const int min = 0, const int max = 99);
} // namespace Console
