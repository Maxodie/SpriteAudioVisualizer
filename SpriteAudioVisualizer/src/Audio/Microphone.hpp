#pragma once
#include "Core.hpp"
#include "Log/Log.hpp"
#include <portaudio.h>

namespace PT
{

class MicrophoneDevice
{
public:

    MicrophoneDevice() = delete;
    MicrophoneDevice(const PaDeviceInfo* deviceInfo, int32_t id);

    PT_FORCE_INLINE bool IsStreaming() const
    {
        return m_stream != nullptr;
    }

    PT_FORCE_INLINE std::string GetName() const
    {
        return m_deviceInfo->name;
    }

    PT_FORCE_INLINE long GetStreamReadPosition() const
    {
        return Pa_GetStreamReadAvailable(m_stream);
    }

    PT_FORCE_INLINE const float* GetInputData() const
    {
        if(IsStreaming())
        {
            PaError err = Pa_ReadStream(m_stream, static_cast<void*>(m_inputBuffer), m_framePerBuffer);
            //input overflowed can appear when the app is shutdown or if the result is glitched
            PT_CORE_ASSERT(err == paNoError || err == paInputOverflowed, "error portaudio : %s", Pa_GetErrorText(err));

            return m_inputBuffer;
        }

        return nullptr;
    }

    void StartStream(unsigned long framePerBuffer);
    void StopStream();

private:
    const PaDeviceInfo* m_deviceInfo;
    PaStream* m_stream = nullptr;
    float* m_inputBuffer;
    int32_t m_id;

    static constexpr double s_sampleRate = 44100;
    unsigned long m_framePerBuffer = 512;
};

class Microphone
{
public:
    PT_FORCE_INLINE static void Init()
    {
        PT_CORE_ASSERT(!s_instance, "Microphone instance already initialized");
        s_instance = new Microphone();
        s_instance->InitDevices();
    }

    PT_FORCE_INLINE static void Shutdown()
    {
        PT_CORE_ASSERT(s_instance, "Microphone instance has not been initialized yet");
        s_instance->ShutdownDevices();
        delete s_instance;
        s_instance = nullptr;
    }

    PT_FORCE_INLINE static Microphone& Get()
    {
        PT_CORE_ASSERT(s_instance, "Microphone instance has not been initialized yet");
        return *s_instance;
    }

    PT_FORCE_INLINE size_t GetDeviceNum() const
    {
        return m_devices.size();
    }

    PT_FORCE_INLINE const float* GetStreamInputData(int32_t id) const
    {
        PT_CORE_ASSERT(m_devices.size() > id, "Trying to get an out of bound id device");
        return m_devices[id].GetInputData();
    }

    PT_FORCE_INLINE long GetStreamReadPosition(int32_t id) const
    {
        PT_CORE_ASSERT(m_devices.size() > id, "Trying to get an out of bound id device");
        return m_devices[id].GetStreamReadPosition();
    }

    PT_FORCE_INLINE void StartStream(int32_t id, unsigned long framePerBuffer)
    {
        PT_CORE_ASSERT(m_devices.size() > id, "Trying to get an out of bound id device");
        m_devices[id].StartStream(framePerBuffer);
    }

    PT_FORCE_INLINE void StopStream(int32_t id)
    {
        PT_CORE_ASSERT(m_devices.size() > id, "Trying to get an out of bound id device");
        m_devices[id].StopStream();
    }

    PT_FORCE_INLINE std::string GetDevice(int32_t id)
    {
        PT_CORE_ASSERT(m_devices.size() > id, "Trying to get an out of bound id device");
        return m_devices[id].GetName();
    }

private:
    void InitDevices();
    void ShutdownDevices();

private:
    std::vector<MicrophoneDevice> m_devices;
    static Microphone* s_instance;
};

}
