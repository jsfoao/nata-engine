#pragma once
#define LOG(x) std::cout << x << std::endl
#define LOGVEC2(x, y) std::cout << "(" << x << ", " << y << ")" << std::endl
#define LOGVEC3(x, y, z) std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl
#define LOGVEC4(x, y, z, w) std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl

namespace Nata
{
    class NTime
    {
    public:
        static float Time;
        static float DeltaTime;
    };

    class NEngine
    {
    public:
        static class NWindow* Window;
        static class NInput* Input;
        static class CCamera* ActiveCamera;
        static float WindowSizeX;
        static float WindowSizeY;
    };
}