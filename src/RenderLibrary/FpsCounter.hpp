#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API FpsCounter {
    private:
        int _fps;
        int _count;
        unsigned long _startTime;

    public:
        void Initialize();
        void Frame();
        int GetFps() const;
    };
}
