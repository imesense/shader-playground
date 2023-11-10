#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <shellapi.h>

namespace ManagerKeys
{
    static std::vector<std::string> keys =
    {
        "-use_dx10",
        "-use_dx11",
        "-use_open_gl"
    };

    class CommandLineArguments
    {
    public:
        CommandLineArguments(/*char* lpCmdLine, int nCmdShow*/);
        ~CommandLineArguments();
        bool CheckKey(const std::string& key);

    private:
        int m_argc;
        std::unique_ptr<char* []> m_argv;
    };
}

extern ManagerKeys::CommandLineArguments* pCommandLineArguments;