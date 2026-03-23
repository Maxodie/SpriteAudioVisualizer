#include "Audio/Microphone.hpp"
#include "Log/Log.hpp"
#include <portaudio.h>

namespace PT
{

std::unique_ptr<Microphone> Microphone::s_instance = nullptr;

void Microphone::Init()
{
    PaError err;
    err = Pa_Initialize();
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));

    int numDevices = Pa_GetDeviceCount();
    CORE_LOG_DEBUG("Detected device count: %d", numDevices);

    if(numDevices < 0)
    {
        CORE_LOG_ERROR("Error getting device count.");
        return;
    }
    else if(numDevices == 0)
    {
        CORE_LOG_ERROR("No device detected. Please connect one and restart the app.");
        return;
    }

    const PaDeviceInfo* deviceInfo;
    for(int i = 0; i < numDevices; ++i)
    {
        deviceInfo = Pa_GetDeviceInfo(i);
        CORE_LOG_DEBUG("device %d name : %s", i, deviceInfo->name);
    }

    err = Pa_Terminate();
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));
}

}
