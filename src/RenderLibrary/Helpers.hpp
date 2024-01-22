#pragma once

#include <string.h>
#include <stdlib.h>
#include <string>

namespace ShaderPlayground
{
    template <typename T>
    constexpr inline void deletePrt(T*& ptr) noexcept
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    template <typename T>
    constexpr inline void deleteArray(T*& ptr) noexcept
    {
        if (ptr != nullptr)
        {
            delete[] ptr;
            ptr = nullptr;
        }
    }

    template <typename T>
    constexpr inline void ReleasePtr(T*& ptr) noexcept
    {
        if (ptr != nullptr)
        {
            ptr->Release();
            ptr = nullptr;
        }
    }

    template <typename T>
    constexpr inline void ClosePtr(T*& ptr) noexcept
    {
        if (ptr != nullptr)
        {
            ptr->Close();
            delete ptr;
            ptr = nullptr;
        }
    }

    template <typename To, typename From>
    constexpr inline To cast(const From& value) noexcept 
    {
        return static_cast<To>(value);
    }
}
