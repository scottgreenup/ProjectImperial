#ifndef _SHADERPROGRAM_HPP_
#define _SHADERPROGRAM_HPP_

#include <vector>

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
public:
    class Builder;

    ShaderProgram(GLuint programId);
    ~ShaderProgram();

    void use();
    GLuint id();

private:
    ShaderProgram(const ShaderProgram& copy)             = delete;
    ShaderProgram& operator=(const ShaderProgram& right) = delete;
    
    GLuint m_programId;
};

class ShaderProgram::Builder {
public:
    Builder();
    ~Builder();

    void buildShader(const char* fileName, GLuint shadertype);

    ShaderProgram* getResult();

private:
    ShaderProgram* m_shaderProgram;

    std::vector<GLuint> m_shaders;
};

#endif
