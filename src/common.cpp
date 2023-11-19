#include <stdlib.h>
#include "common.hpp"

void NebrixExit(Nebrix_Exit_Value exit_value) {
    exit(Nebrix_Exit_Value(exit_value));    
}