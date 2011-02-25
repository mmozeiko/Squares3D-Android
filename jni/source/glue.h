#pragma once

#include <jni.h>

#if __cplusplus
extern "C"
{
#endif

extern int quit_requested;
    
int Java_lv_bubu_Squares3D_Native_begin(JNIEnv* env, jclass);
void Java_lv_bubu_Squares3D_Native_resize(JNIEnv* env, jclass, int width, int height);
void Java_lv_bubu_Squares3D_Native_render(JNIEnv* env, jclass);
void Java_lv_bubu_Squares3D_Native_end(JNIEnv* env, jclass);

void Java_lv_bubu_Squares3D_Native_touchBegin(JNIEnv* env, jclass, int touch, float x, float y);
void Java_lv_bubu_Squares3D_Native_touchMove(JNIEnv* env, jclass, int touch, float x, float y);
void Java_lv_bubu_Squares3D_Native_touchEnd(JNIEnv* env, jclass, int touch);
    
#if __cplusplus
}
#endif
