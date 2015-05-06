#ifndef _SHADERPROGRAM_HPP_
#define _SHADERPROGRAM_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader(const char* vertFilename, const char* fragFilename);
    ~Shader();

    bool Load();
    void Use();
    GLuint Id();

private:
    Shader();
    Shader(const Shader& copy) { (void)copy; }
    //Shader& operator = (const Shader& right) { (void)right; }
    
    const char* m_vertFilename;
    const char* m_fragFilename;

    GLuint m_programId;
};

#endif
