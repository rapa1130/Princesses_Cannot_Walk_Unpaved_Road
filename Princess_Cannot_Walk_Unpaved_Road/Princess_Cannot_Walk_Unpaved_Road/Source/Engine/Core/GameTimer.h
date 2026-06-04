//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************
#pragma once

#include <cstdint>

namespace Bisang
{
    class GameTimer
    {
    public:
        GameTimer();

        float TotalTime() const;     // in seconds
        float DeltaTime() const;     // in seconds
        float DeltaTimeMS() const;   // in mili-seconds, Ãß°¡

        void Reset();   // Call before message loop.
        void Start();   // Call when unpaused.
        void Stop();    // Call when paused.
        void Tick();    // Call every frame.

    private:
        double mSecondsPerCount = 0.0;
        double mDeltaTime = 0.0;

        int64_t mBaseTime = 0;
        int64_t mPausedTime = 0;
        int64_t mStopTime = 0;
        int64_t mPrevTime = 0;
        int64_t mCurrTime = 0;

        bool mStopped = false;
    };
}