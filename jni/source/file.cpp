#include "file.h"

#include <stdlib.h>
#include <jni.h>

static JavaVM* javaVM;

extern "C"
{

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    javaVM = vm;
    return JNI_VERSION_1_2;
}

}

// PRIVATE part

namespace File
{  

    Reader::Reader(const string& filename, bool inWriteFolder) : m_pointer(NULL)
    {
        JNIEnv* env;
        if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_2) == JNI_OK)
        {
            jclass klass = env->FindClass("lv/bubu/Squares3D/Native");
            jmethodID method = env->GetStaticMethodID(klass, "getAsset", "(Ljava/lang/String;)[B");

            jstring str = env->NewStringUTF(filename.c_str());
            jarray arr = (jarray)env->CallStaticObjectMethod(klass, method, str);

            if (arr != NULL)
            {
                m_size = env->GetArrayLength(arr);
                m_pointer = (unsigned char*)malloc(m_size);

                void* src = env->GetPrimitiveArrayCritical(arr, NULL);
                memcpy(m_pointer, src, m_size);
                env->ReleasePrimitiveArrayCritical(arr, src, 0);
            }
        }
    }
    
    Reader::~Reader()
    {
        if (m_pointer != NULL)
        {
            free(m_pointer);
        }
    }
               
    bool Reader::is_open() const
    {
        return m_pointer != NULL;
    }
               
    size_t Reader::size() const
    {
        return m_size;
    }
               
    unsigned char* Reader::pointer() const
    {
        return m_pointer;
    }

    Writer::Writer(const string& filename, bool append)
        : m_handle(NULL)
//        : m_handle(fopen(("/sdcard/Squares3D" + filename).c_str(), append ? "ab" : "wb"))
    {
    }
    
    Writer::~Writer()
    {
/*
        if (m_handle != NULL)
        {
            fclose(m_handle);
            m_handle = NULL;
        }
*/
    }
    
    bool Writer::is_open() const
    {
//        return m_handle != NULL;
        return true;
    }

    size_t Writer::write(const void* buffer, size_t size)
    {
//        return fwrite(buffer, 1, size, m_handle);
        return size;
    }

    bool exists(const string& filename)
    {
        return true;
/*
        FILE* f = fopen(("/sdcard/Squares3D" + filename).c_str(), "rb");
        if (f == NULL)
        {
            f = fopen(("/sdcard/Squares3D" + filename).c_str(), "rb");
        }
        if (f == NULL)
        {
            return false;
        }
        fclose(f);
        return true;
*/
    }

}
