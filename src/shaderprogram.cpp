#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "shaderprogram.h"

ShaderProgram::ShaderProgram(GLuint programId)
: m_programId(programId) {

}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->m_programId);
}

void ShaderProgram::use() {
    glUseProgram(this->m_programId);
}

GLuint ShaderProgram::id() {
    return this->m_programId;
}

//##############################################################################
// ShaderProgram::Builder
//##############################################################################

ShaderProgram::Builder::Builder()
: m_shaderProgram(nullptr) {

}

ShaderProgram::Builder::~Builder() {
    for (auto it = m_shaders.begin(); it != m_shaders.end(); ++it) {
        glDeleteShader(*it);
    }
}

ShaderProgram* ShaderProgram::Builder::getResult() {
    GLuint programId = glCreateProgram();

    for (auto it = m_shaders.begin(); it != m_shaders.end(); ++it) {
        glAttachShader(programId, *it);
    }

    glLinkProgram(programId);

    // check program
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1) {
        std::vector<char> message(infoLogLength + 1);
        glGetShaderInfoLog(programId, infoLogLength, NULL, &message[0]);
        std::cerr << &message[0] << std::endl;
    }

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        return nullptr;
    }

    return (new ShaderProgram(programId));
}

void ShaderProgram::Builder::buildShader(const char* fileName, GLuint shaderType) {
    GLuint shaderId = glCreateShader(shaderType);

    // get shader code
    std::string code;
    std::ifstream codeStream(fileName, std::ios::in);
    if (!codeStream.is_open()) {
        std::cerr << "Could not open " << fileName << "." << std::endl;
        return;
    }
    std::string line = "";
    while (getline(codeStream, line)) {
        code += "\n" + line;
    }
    codeStream.close();

    // error variables that are passed by reference
    GLint result = GL_FALSE;
    int infoLogLength = 0;

    // compile code
    char const* source = code.c_str();
    glShaderSource(shaderId, 1, &source, NULL);
    glCompileShader(shaderId);

    // check compilation
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1)  {
        std::vector<char> errMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &errMessage[0]);
        std::cerr << "[" << fileName << "]" << std::endl;
        std::cerr << &errMessage[0] << std::endl;
    }

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        return;
    }

    m_shaders.push_back(shaderId);
}
