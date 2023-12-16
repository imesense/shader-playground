#pragma once

#include <cstdlib>

namespace ShaderPlayground {
    template <typename T>
    class RENDERLIBRARY_API Allocator {
    protected:
        Allocator(const char* object);
        ~Allocator();

    public:
        static void* operator new(size_t size);
        static void operator delete(void* ptr);

        static void* operator new[](size_t size);
        static void operator delete[](void* ptr);
    };
}
