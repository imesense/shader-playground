#pragma once

namespace ShaderPlayground {
    class FpsCounter {
    private:
        int _fps;
        int _count;
        unsigned long _startTime;

    public:
        FpsCounter();
        virtual ~FpsCounter();

        void Initialize();
        void Frame();
        int GetFps() const;
    };
}
