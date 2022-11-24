#include "fileutils.h"

namespace Nata
{
    std::string FileUtils::ReadFile(const char* filepath)
    {
        // r: readonly; t: text file
        FILE* file = fopen(filepath, "rt");
        
        errno = 0;
        std::string result = "";
        if (file == nullptr)
        {
            std::cout << "Error " << errno << ": " << filepath << std::endl;
            return result;
        }

        // go to end of file
        fseek(file, 0, SEEK_END);

        // length of file in bytes
        unsigned long length = ftell(file);
        char* data = new char[length + 1];

        // set everything to 0
        memset(data, 0, length + 1);

        // go back to beginning of file
        fseek(file, 0, SEEK_SET);

        fread(data, 1, length, file);
        fclose(file);

        // copy data to string
        result = data;
        delete[] data;
        return result;
    }
}