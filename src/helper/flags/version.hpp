#pragma once

#include <string>
#include <sstream>

const int NEBRIX_MAJOR_VERSION = 0;
const int NEBRIX_MINOR_VERSION = 0;
const int NEBRIX_PATCH_LEVEL   = 1;

typedef struct {

    int major;
    int minor;
    int patch;

} Nebrix_version;

/// Macro to determine Zura version.
/// @param x A pointer to a Zura_version struct to initialize.
#define NEBRIX_VERSION(x)               \
{                                       \
    (x)->major = NEBRIX_MAJOR_VERSION;  \
    (x)->minor = NEBRIX_MINOR_VERSION;  \
    (x)->patch = NEBRIX_PATCH_LEVEL;    \
}

std::string get_Nebrix_version_string(void) 
{
    Nebrix_version v = {};
    NEBRIX_VERSION(&v);

    std::string version;
    std::ostringstream build_version;

    build_version << v.major << '.' << v.minor << '.' << v.patch;
    
    version = build_version.str();

    return version;
}