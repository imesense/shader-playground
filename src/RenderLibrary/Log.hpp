#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Log {
    private:
        static Log* _instance;

        void Initialize();
        void Close();
        void Print(const char* levtext, const char* text);

        FILE* _file;

    public:
        Log();
        ~Log();

        static Log* Get() {
            return _instance;
        }

        void Print(const char* message, ...);
        void Debug(const char* message, ...);
        void Err(const char* message, ...);
    };
}
