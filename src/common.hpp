#pragma once

#include <stdint.h>

/// Exit codes used in the Nebrix Interpreter.
///
/// Add additional exit codes to this list whenever an appropriate
/// reason is encountered to do so. 
///
/// @sa NebrixExit

typedef enum {
    OK = 0,
    INVALID_FILE_EXTENSION = 10,
    INVALID_FILE           = 11,
    LEXER_ERROR            = 12,
    PARSER_ERROR           = 13,
    GENERATOR_ERROR        = 14,
} Nebrix_Exit_Value;

/// Exits the Nebrix interpreter using an appropriate exit value.
/// @param exit_value An exit value specific to the Nebrix interpreter code base.
/// @sa Nebrix_Exit_Value
void NebrixExit(Nebrix_Exit_Value exit_value);