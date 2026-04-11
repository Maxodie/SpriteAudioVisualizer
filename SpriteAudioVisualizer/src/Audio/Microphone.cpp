#include "Audio/Microphone.hpp"
#include "Log/Log.hpp"
#include "portaudio.h"

namespace PT
{

// static int PaTestCallback(
//     const void* inputBuffer, void* outputBuffer,
//     unsigned long framePerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
//     PaStreamCallbackFlags statusFlags, void* userData)
// {
//     (void)outputBuffer;
//     (void)inputBuffer;
//
//     return 0;
// }

MicrophoneDevice::MicrophoneDevice(const PaDeviceInfo* deviceInfo, int32_t id)
    : m_deviceInfo(deviceInfo), m_id(id)
{
}

void MicrophoneDevice::StartStream(unsigned long framePerBuffer)
{
    m_framePerBuffer = framePerBuffer;
    m_inputBuffer = static_cast<float*>(std::malloc(framePerBuffer * sizeof(float)));

    PaStreamParameters inputParameters;

    inputParameters.channelCount = 1;
    inputParameters.device = m_id;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = m_deviceInfo->defaultLowInputLatency;

    PaError err = Pa_OpenStream(
        &m_stream,
        &inputParameters,
        nullptr,
        s_sampleRate,
        m_framePerBuffer,
        paClipOff,
        nullptr,
        this);

    if(err == paNoError)
    {
        err = Pa_StartStream(m_stream);
        PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));

        CORE_LOG_SUCCESS("Stream on device %s started", m_deviceInfo->name);
    }
    else
    {
        CORE_LOG_ERROR("Portaudio error: %s on device %s.", Pa_GetErrorText(err), m_deviceInfo->name);
    }
}

void MicrophoneDevice::StopStream()
{
    PaError err = Pa_StopStream(m_stream);
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));

    err = Pa_CloseStream(m_stream);
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));

    m_stream = nullptr;
    std::free(m_inputBuffer);
    m_inputBuffer = nullptr;

    CORE_LOG_SUCCESS("Stream on device %d stopped", m_deviceInfo->name);
}

Microphone* Microphone::s_instance = nullptr;

void Microphone::InitDevices()
{
    PaError err;
    err = Pa_Initialize();
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));

    int numDevices = Pa_GetDeviceCount();
    CORE_LOG_TRACE("Detected device count: %d", numDevices);

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

    CORE_LOG_TRACE("Seletected Input and Output Microphone devices : ");
    const PaDeviceInfo* deviceInfo;
    for(int i = 0; i < numDevices; ++i)
    {
        deviceInfo = Pa_GetDeviceInfo(i);
        if(deviceInfo->maxInputChannels > 0)
        {
            CORE_LOG_TRACE("------------------------");
            CORE_LOG_TRACE("    input device %d name : %s", i, deviceInfo->name);
            CORE_LOG_TRACE("        max input channels : %d", deviceInfo->maxInputChannels);
            CORE_LOG_TRACE("        max output channels : %d", deviceInfo->maxOutputChannels);
            CORE_LOG_TRACE("        default low input latency : %f", deviceInfo->defaultLowInputLatency);
            CORE_LOG_TRACE("        default high input latency : %f", deviceInfo->defaultHighInputLatency);
            CORE_LOG_TRACE("        default sample rate : %f", deviceInfo->defaultSampleRate);
            m_devices.emplace_back(std::move(deviceInfo), std::move(i));
        }
    }

    CORE_LOG_SUCCESS("Microphone initialized");
}

void Microphone::ShutdownDevices()
{
    for(auto& device : m_devices)
    {
        if(device.IsStreaming())
        {
            device.StopStream();
        }
    }

    PaError err = Pa_Terminate();
    PT_CORE_ASSERT(err == paNoError, "Portaudio error: %s.", Pa_GetErrorText(err));
    CORE_LOG_SUCCESS("Microphone shutdown");
}

}
