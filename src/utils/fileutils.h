#pragma once
#include "core/core.h"
#include <errno.h>
#include <iostream>
#include <string>

namespace Nata
{
    class FileUtils
    {
    public:
        static std::string ReadFile(const char* filepath);
    };
}