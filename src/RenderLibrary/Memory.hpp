#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Allocator {
    public:
        Allocator() {}
        ~Allocator() {}

        void* operator new(std::size_t size);
        void operator delete(void* ptr) noexcept;

        void* operator new[](std::size_t size);
        void operator delete[](void* ptr) noexcept;

        static void AddToCollection(void* ptr);
        static void RemoveFromCollection(void* ptr);
        static void PrintCollection();

    private:
        static std::unordered_set<void*> objectCollection;
    };
}

extern RENDERLIBRARY_API ShaderPlayground::Allocator Memory;
