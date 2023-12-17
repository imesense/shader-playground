#pragma once

#include <cstdlib>

namespace ShaderPlayground {
    class RENDERLIBRARY_API Allocator {
    public:
        Allocator() {}
        ~Allocator() {}

        void* operator new(std::size_t size);
        void operator delete(void* ptr) noexcept;

        void* operator new[](std::size_t size);
        void operator delete[](void* ptr) noexcept;
    };
}

extern RENDERLIBRARY_API ShaderPlayground::Allocator Memory;
