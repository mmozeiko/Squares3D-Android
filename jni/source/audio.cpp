#include "openal_includes.h"

#include "audio.h"
#include "config.h"
#include "music.h"
#include "sound_buffer.h"
#include "sound.h"

template <class Audio> Audio* System<Audio>::instance = NULL;

static ALCdevice* device;
static ALCcontext* context;

static void audio_setup()
{
    LOG("Initializing audio.");

    device = alcOpenDevice(NULL);
    if (device==NULL)
    {
        Exception(alcGetString(NULL, alcGetError(NULL)));
    }
    
    static const int attr[] = { ALC_FREQUENCY, 22050, ALC_INVALID };

    context = alcCreateContext(device, attr);
    if (context==NULL)
    {
        string error = string(alcGetString(device, alcGetError(device)));
        alcCloseDevice(device);
        Exception(error);
    }
    alcMakeContextCurrent(context);

    int major=0, minor=0;
    alcGetIntegerv(device, ALC_MAJOR_VERSION, 1, &major);
    alcGetIntegerv(device, ALC_MINOR_VERSION, 1, &minor);

    LOG(" * Version    : %i.%i", major, minor);
    LOG(" * Vendor     : %s", alGetString(AL_VENDOR));
    LOG(" * Renderer   : %s", alGetString(AL_RENDERER));
    LOG(" * Device     : %s", alcGetString(device, ALC_DEVICE_SPECIFIER));
    LOG(" * Extensions : %s", alcGetString(device, ALC_EXTENSIONS));
}

static void audio_finish()
{
    LOG("Closing audio.");
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

Audio::Audio() : m_device(NULL), m_context(NULL) 
{
    audio_setup();
    
    m_device = device;
    m_context = context;
}

Audio::~Audio()
{
    audio_finish();

    m_device = NULL;
    m_context = NULL;
}

Music* Audio::loadMusic(const string& filename)
{
    return *m_music.insert(new Music(filename)).first;
}

void Audio::unloadMusic(Music* music)
{
    m_music.erase(music);
    delete music;
}

SoundBuffer* Audio::loadSound(const string& filename)
{
    SoundBufferMap::iterator iter = m_soundBuf.find(filename);
    if (iter != m_soundBuf.end())
    {
        return iter->second;
    }

    return m_soundBuf.insert(make_pair(filename, new SoundBuffer(filename))).first->second;
}

void Audio::unloadSound(SoundBuffer* soundBuf)
{
    for each_(SoundBufferMap, m_soundBuf, iter)
    {
        if (iter->second == soundBuf)
        {
            delete iter->second;
            m_soundBuf.erase(iter);
            break;
        }
    }
}

void Audio::update()
{
    for each_(MusicSet, m_music, iter)
    {
        (*iter)->update();
    }
}
