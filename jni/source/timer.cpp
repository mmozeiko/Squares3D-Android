#include "timer.h"
#include <sys/time.h>
#include <time.h>

static uint64_t T()
{
    struct timeval t;
    t.tv_sec = t.tv_usec = 0;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000LL + t.tv_usec;
}

Timer::Timer(bool start) :
    m_running(start ? 1 : 0),
    m_elapsed(0),
    m_resumed(0)
{
    reset(start);
}

void Timer::pause()
{
    m_running--;
    if (m_running != 0)
    {
        return;
    }

    m_elapsed += T() - m_resumed;
}

void Timer::resume()
{
    m_running++;
    if (m_running != 1)
    {
        return;
    }

    m_resumed = T();
}

void Timer::reset(bool start)
{
    m_running = (start ? 1 : 0);
    if (start)
    {
        m_resumed = T();
    }
    m_elapsed = 0;
}

float Timer::read() const
{
    uint64_t res;
    if (m_running <= 0)
    {
        res = m_elapsed;
    }
    res = T() - m_resumed + m_elapsed;

    return res * 1e-6;
}
