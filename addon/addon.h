#pragma once
#ifndef _ADDON_H_
#define _ADDON_H_
/** ------------------------------------------------------------------------
 * @brief This feature will allow the user to generate random extensions if needed
 *
 * @details Use grep -R 'RANDOM_EXTENSIONS' ../ or ./ to find where it is used
*/
#ifdef RANDOM_EXTENSIONS
    #define RANDOM_EXTENSIONS 0
#endif
/** ------------------------------------------------------------------------
 * @brief This feature will allow the user to disable the interpreter or enable it at compile time 
 *
 * @details Either the compiler flag or interpreter flag must be enabled, not both
 * @details By default the compiler flag is disabled and the interpreter flag is enabled
 * @details Depending on the language the user chooses, the compiler flag or the interpreter flag will be overwritten 
 * @details Use grep -R 'RANDOM_EXTENSIONS' ../ or ./ to find where it is used
*/
#define ENABLE_INTERPRETER(...) setI(1 __VA_OPT__(,) __VA_ARGS__)

/** ------------------------------------------------------------------------
 * @brief This feature will allow the user to choose to enable the compiler or disable it at compile time 
 *
 * @details Either the interpreter needs to be enabled or the compiler, not both at the same time
 * @details Use grep -R 'ENABLE_COMPILER' ../ or ./ to find where it is used
*/
#define ENABLE_COMPILER(...) setC(0 __VA_OPT__(,) __VA_ARGS__)
#endif  // End of addon.h 
