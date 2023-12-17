#include "StdAfx.h"

#include "Memory.hpp"
#include "Log.hpp"

#include <iostream>
#include <new>

#pragma section(".Hook", read)

using namespace ShaderPlayground;

void* Allocator::operator new(std::size_t size) {
    void* ptr = std::malloc(size);
    return ptr;
}

void Allocator::operator delete(void* ptr) noexcept {
    std::free(ptr);
}

void* Allocator::operator new[](std::size_t size) {
    void* ptr = std::malloc(size);
    return ptr;
}

void Allocator::operator delete[](void* ptr) noexcept {
    std::free(ptr);
}

#pragma init_seg(lib)
__declspec(allocate(".Hook"))
Allocator Memory;
