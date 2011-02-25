#include "source/common.h"
#include "source/glue.h"
#include "source/game.h"
#include "source/video.h"
#include "source/random.h"
#include "source/version.h"
#include "source/input.h"
#include "source/utilities.h"

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <sys/time.h>

int quit_requested = 0;

static Game* game = NULL;

static timeval g_time;

int Java_lv_bubu_Squares3D_Native_begin(JNIEnv* env, jclass)
{
    LOG("*** Squares 3D version: %s ***", g_version.c_str());
    LOG("Started: %s", getDateTime().c_str());
    
    Randoms::init();

    game = new Game();

    gettimeofday(&g_time, NULL);

    return 1;
}

void Java_lv_bubu_Squares3D_Native_resize(JNIEnv* env, jclass, int width, int height)
{
    if (game != NULL)
    {
        game->m_video->resize(width, height);
    }
}

void Java_lv_bubu_Squares3D_Native_render(JNIEnv* env, jclass)
{
    timeval now;
    gettimeofday(&now, NULL);

    float delta = (now.tv_sec - g_time.tv_sec) + (now.tv_usec - g_time.tv_usec) * 1e-6f;
    g_time = now;

    //__android_log_print(ANDROID_LOG_INFO, "Squares3D", "FPS=%.2f", 1.0f / delta);

    game->update(delta);
    if (quit_requested)
    {
        LOG("quit requested");
        quit_requested = 0;
        exit(0);
    }
    game->render(delta);
}

void Java_lv_bubu_Squares3D_Native_end(JNIEnv* env, jclass)
{
    delete game;

    LOG("Finished: %s", getDateTime().c_str());
}

void Java_lv_bubu_Squares3D_Native_touchBegin(JNIEnv* env, jclass, int touch, float x, float y)
{
    if (Input::instance != NULL);
    {
        Input::instance->m_touches.insert(make_pair((void*)(touch | 0x80000000), make_pair(x, y)));
        Input::instance->m_buffer.push_back((void*)(touch | 0x80000000));
    }
}

void Java_lv_bubu_Squares3D_Native_touchMove(JNIEnv* env, jclass, int touch, float x, float y)
{
    if (Input::instance != NULL);
    {
        Input::instance->m_touches[(void*)(touch | 0x80000000)] = make_pair((int)x, (int)y);
    }
}

void Java_lv_bubu_Squares3D_Native_touchEnd(JNIEnv* env, jclass, int touch)
{
    if (Input::instance != NULL);
    {
        Input::m_touches.erase((void*)(touch | 0x80000000));
    }
}
