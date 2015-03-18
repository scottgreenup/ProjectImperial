#version 300 es

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;
uniform vec3 solidColor;

out vec3 fragmentColor;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    fragmentColor = solidColor;
}
