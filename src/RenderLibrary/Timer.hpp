#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Timer {
    private:
        INT64 _frequency;
        INT64 _startTime;

        float _ticksPerMs;
        float _frameTime;

    public:
        bool Init();
        void Frame();

        float GetTime() const;
    };
}
