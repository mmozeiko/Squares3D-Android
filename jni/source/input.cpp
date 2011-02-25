#include "input.h"
#include "video.h"
#include "glue.h"

template <class Input> Input* System<Input>::instance = NULL;

Touches Input::m_touches;
Touches Input::m_empty;
vector<void*> Input::m_buffer;

Input::Input() : m_waitForRelease(false)
{
    LOG("Initializing input... ");
}

Input::~Input()
{
    LOG("Closing input.");
}

void Input::init()
{
    m_touches.clear();
}

void Input::waitForRelease()
{
    m_waitForRelease = true;
}

void Input::update()
{
    if (m_waitForRelease && m_touches.empty())
    {
        m_waitForRelease = false;
    }
}

void Input::clearBuffer()
{
    m_buffer.clear();
}

void* Input::popTouch()
{
    if (m_buffer.empty())
    {
        return NULL;
    }
    
    void* ret = m_buffer[0];
    m_buffer.erase(m_buffer.begin());
    return ret;
}

const Touches& Input::touches() const
{
    return m_waitForRelease ? m_empty : m_touches;
}
