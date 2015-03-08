#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "shader.hpp"

Shader::Shader(const char* vertFilename, const char* fragFilename)
 : m_vertFilename(vertFilename)
 , m_fragFilename(fragFilename) {

}

bool Shader::Load() {
    GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);

    // get .vert code
    std::string vertCode;
    std::ifstream vertStream(this->m_vertFilename, std::ios::in);
    if (!vertStream.is_open()) {
        std::cerr << "Could not open " << this->m_vertFilename << "." << std::endl;
        return false;
    }
    std::string line = "";
    while (getline(vertStream, line)) {
        vertCode += "\n" + line;
    }
    vertStream.close();

    // get .frag code
    std::string fragCode;
    std::ifstream fragStream(this->m_fragFilename, std::ios::in);
    if (!fragStream.is_open()) {
        std::cerr << "Could not open " << this->m_fragFilename << "." << std::endl;
        return false;
    }
    line = "";
    while (getline(fragStream, line)) {
        fragCode += "\n" + line;
    }
    fragStream.close();

    GLint result = GL_FALSE;
    int infoLogLength;

    // compile .vert
    char const* vertSource = vertCode.c_str();
    glShaderSource(vertId, 1, &vertSource, NULL);
    glCompileShader(vertId);

    // check .vert
    glGetShaderiv(vertId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> vertErrMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertId, infoLogLength, NULL, &vertErrMessage[0]);
        std::cerr << &vertErrMessage[0] << std::endl;
    }

    // compile .frag
    char const* fragSource = fragCode.c_str();
    glShaderSource(fragId, 1, &fragSource, NULL);
    glCompileShader(fragId);

    // check .vert
    glGetShaderiv(fragId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> fragErrMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragId, infoLogLength, NULL, &fragErrMessage[0]);
        std::cerr << &fragErrMessage[0] << std::endl;
    }

    // link the program
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertId);
    glAttachShader(programId, fragId);
    glLinkProgram(programId);

    // check program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> message(infoLogLength + 1);
        glGetShaderInfoLog(programId, infoLogLength, NULL, &message[0]);
        std::cerr << &message[0] << std::endl;
    }

    glDeleteShader(vertId);
    glDeleteShader(fragId);

    this->m_programId = programId;

    return true;
}

Shader::~Shader() {
    glDeleteProgram(this->m_programId);
}

void Shader::Use() {
    glUseProgram(this->m_programId);
}

GLuint Shader::Id() {
    return this->m_programId;
}
