#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <FreeImage.h>

#include <map>
#include <string>
#include <utility>

static std::map<std::string, std::pair<GLuint,GLuint>> data;

class Texture {
public:
    Texture(const char* fileName)
    : m_fileName(fileName) {
        if (data.find(fileName) != data.end()) {
            m_textureId = data[fileName].first;
            m_samplerId = data[fileName].second;

            return;
        }

        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP* dib(0);

        // get file format 
        fif = FreeImage_GetFileType(fileName, 0);
        if (fif == FIF_UNKNOWN) {
            fif = FreeImage_GetFIFFromFilename(fileName);
            if (fif == FIF_UNKNOWN) {
              return;
            }
        }

        // check if we can read the file
        if(FreeImage_FIFSupportsReading(fif)) {
            // read the file
            dib = FreeImage_Load(fif, fileName);
        }
        if(!dib) {
            std::cerr << "Texture: Failed to read file" << std::endl;
            return;
        }

        FIBITMAP *dib32 = FreeImage_ConvertTo32Bits(dib);


        // THE BRIDGE BETWEEN OPENGL and FREEIMAGE
        // get image data
        BYTE* dataPtr = FreeImage_GetBits(dib32);
        int width = FreeImage_GetWidth(dib32); // Get the image width and height
        int height = FreeImage_GetHeight(dib32);
        //int bitsPerPixel = FreeImage_GetBPP(dib);

        if(dataPtr == NULL || width == 0 || height == 0) {
            std::cerr << "Texture: Failed to get data from texture" << std::endl;
            return;
        }

        // THE OpenGL PART:
        // Generate an OpenGL texture ID for this texture
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        //int format = bitsPerPixel == 24 ? GL_RGB : bitsPerPixel == 8 ? GL_LUMINANCE : 0;

        glTexImage2D(
            GL_TEXTURE_2D,      // the target texture tyupe
            0,                  // level of detail number
            GL_RGBA8,           // internalformat of the texture
            width,              // width of the image
            height,             // height of the image
            0,                  // width of the border
            GL_BGRA,            // format of the texel data, MUST match internalformat
            GL_UNSIGNED_BYTE,   // type of the texel data
            dataPtr             // pointer to the image data
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glGenerateMipmap(GL_TEXTURE_2D);
        glGenSamplers(1, &m_samplerId);

        glBindTexture(GL_TEXTURE_2D, 0);

        data[fileName] = std::pair<GLuint,GLuint>(m_textureId, m_samplerId);

        FreeImage_Unload(dib);
    }

    ~Texture() {
        glDeleteSamplers(1, &m_samplerId);
        glDeleteTextures(1, &m_textureId);

        data.erase(m_fileName);
    }

    void bind() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glBindSampler(m_textureId, m_samplerId);
    }


private:
    GLuint m_textureId;
    GLuint m_samplerId;
    std::string m_fileName;

};


#endif
