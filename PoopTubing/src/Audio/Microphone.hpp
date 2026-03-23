#pragma once
#include "Core.hpp"

namespace PT
{

class MicrophoneDevice
{
public:
    std::string GetName();
};

class Microphone
{
public:
    PT_FORCE_INLINE static const Microphone& Get()
    {
        if(!s_instance)
        {
            s_instance = std::make_unique<Microphone>();
            s_instance->Init();
        }

        return *s_instance;
    }

    PT_FORCE_INLINE const std::vector<MicrophoneDevice>& GetDevices() const
    {
        return m_devices;
    }

private:
    void Init();

private:
    std::vector<MicrophoneDevice> m_devices;
    static std::unique_ptr<Microphone> s_instance;
};

}
