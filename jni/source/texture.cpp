#include "texture.h"
#include "file.h"
#include "vmath.h"
#include "config.h"
#include "dds.h"

Texture::Texture(const string& name, WrapType wrap)
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

    if (header->ddspf.dwFourCC != FOURCC_ATC_RGB && header->ddspf.dwFourCC != FOURCC_ATC_RGBA_EXPLICIT)
    {
        Exception("Texture '" + name + "' has invalid FourCC");
    }
    
    unsigned char* image = file.pointer() + sizeof(DDS_SIGNATURE) + sizeof(DDS_HEADER);

    LOG("Loading texture %s, size=%ix%i, mipCount=%i, hasMips=%i", name.c_str(), header->dwWidth, header->dwHeight, header->dwMipMapCount, header->dwHeaderFlags & DDS_HEADER_FLAGS_MIPMAP);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    {
        GLenum format = header->ddspf.dwFourCC == FOURCC_ATC_RGB ? GL_ATC_RGB_AMD : GL_ATC_RGBA_EXPLICIT_ALPHA_AMD; 
        
        unsigned char* ptr = image;
        int level = 0;
        int width = header->dwWidth;
        int height = header->dwHeight;
        while (level < header->dwMipMapCount)
        {
            GLint size = (std::max<int>(width, 4) * std::max<int>(height, 4) * 4 + (format == GL_ATC_RGB_AMD ? 7 : 3)) / (format == GL_ATC_RGB_AMD ? 8 : 4);
            
            LOG(" * level=%i, format=%i, w=%i, h=%i, size=%i", level, format, width, height, size);
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, ptr);
            
            level++;
            ptr += size;
            width = std::max(width >> 1, 1);
            height = std::max(height >> 1, 1);
        }
    }

    if (header->dwMipMapCount > 1)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
           
    switch (wrap)
    {
        case Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case ClampToEdge:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, (GLuint*)&m_handle);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}
