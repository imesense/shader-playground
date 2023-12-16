#include "StdAfx.h"

#include "Memory.hpp"
#include "Log.hpp"

#pragma section(".Hook", read)

using namespace ShaderPlayground;

template <typename T>
Allocator<T>::Allocator(const char* object) {
    Log::Get()->Debug("Инициализация памяти для объекта: %s", object);
}

template <typename T>
Allocator<T>::~Allocator() {
    Log::Get()->Debug("Очитка памяти");
}

template <typename T>
void* Allocator<T>::operator new(size_t size) {
    return malloc(size);
}

template <typename T>
void Allocator<T>::operator delete(void* ptr) {
    free(ptr);
}

template <typename T>
void* Allocator<T>::operator new[](size_t size) {
    return malloc(size);
}

template <typename T>
void Allocator<T>::operator delete[](void* ptr) {
    free(ptr);
}

#pragma init_seg(lib)
template <typename T>
__declspec(allocate(".Hook"))
Allocator<T> Memory;
