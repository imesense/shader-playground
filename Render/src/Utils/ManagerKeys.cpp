#include "stdafx.h"
#include "ManagerKeys.h"

ManagerKeys::CommandLineArguments* pCommandLineArguments = nullptr;

namespace ManagerKeys
{
    CommandLineArguments::CommandLineArguments() : m_argc(0), m_argv(nullptr)
    {
        int argc;
        LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);

        m_argv = std::make_unique<char* []>(argc);
        for (int i = 0; i < argc; ++i)
        {
            auto length = WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, nullptr, 0, nullptr, nullptr);
            m_argv[i] = new char[length];
            WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, m_argv[i], length, nullptr, nullptr);
        }

        LocalFree(argvW);

        m_argc = argc;
    }

    CommandLineArguments::~CommandLineArguments()
    {
        for (int i = 0; i < m_argc; ++i)
        {
            delete[] m_argv[i];
        }
    }

    bool CommandLineArguments::CheckKey(const std::string& key)
    {
        for (int i = 1; i < m_argc; ++i)
        {
            if (std::strcmp(key.c_str(), m_argv[i]) == 0)
                return true;
        }
        return false;
    }
}
