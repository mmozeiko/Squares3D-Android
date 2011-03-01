#include "texture.h"
#include "file.h"
#include "vmath.h"
#include "config.h"
#include "dds.h"

Texture::Texture(const string& name, WrapType wrap) : m_wrap(wrap)
{
    glGenTextures(1, (GLuint*)&m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);
    
    File::Reader file("/data/textures/" + name + ".dds");
    if (!file.is_open())
    {
        Exception("Texture '" + name + "' doesn't exist");
    }

    uint32_t* signature = (uint32_t*)file.pointer();
    if (*signature != DDS_SIGNATURE)
    {
        Exception("Texture '" + name + "' has invalid signature");
    }

    DDS_HEADER* header = (DDS_HEADER*)(file.pointer() + sizeof(DDS_SIGNATURE));
    if (header->dwSize != sizeof(DDS_HEADER))
    {
        Exception("Texture '" + name + "' has invalid header");
    }
    
    unsigned char* image = file.pointer() + sizeof(DDS_SIGNATURE) + sizeof(DDS_HEADER);

    LOG("Loading texture %s, size=%ix%i, mipCount=%i, hasMips=%i", name.c_str(), header->dwWidth, header->dwHeight, header->dwMipMapCount, header->dwHeaderFlags & DDS_HEADER_FLAGS_MIPMAP);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    {
        unsigned char* ptr = image;
        int level = 0;
        int width = header->dwWidth;
        int height = header->dwHeight;
        while (level < header->dwMipMapCount)
        {
            GLint size;
            if (header->ddspf.dwFourCC == FOURCC_ETC_RGB)
            {
                size = (std::max<int>(width, 4) * std::max<int>(height, 4) * 4 + 7) / 8;
                glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_ETC1_RGB8_OES, width, height, 0, size, ptr);
            }
            else
            {
                size = width * height * 2;
                glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, ptr);
            }
            
            level++;
            ptr += size;
            width = std::max(width >> 1, 1);
            height = std::max(height >> 1, 1);
        }
    }

    m_mipmaps = header->dwMipMapCount > 1;
}

Texture::~Texture()
{
    glDeleteTextures(1, (GLuint*)&m_handle);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap == Repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap == Repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
