#pragma once

namespace ShaderPlayground {
    class Timer {
    private:
        INT64 _frequency;
        INT64 _startTime;

        float _ticksPerMs;
        float _frameTime;

    public:
        Timer();
        virtual ~Timer();

        bool Init();
        void Frame();

        float GetTime() const;
    };
}
