#version 300 es

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 normalMatrix;
uniform mat4 modelView;
uniform mat4 projection;

smooth out vec3 fragColor;
smooth out vec4 fragModelView;

void main() {
    fragModelView = modelView * vec4(inPosition, 1.0);
    gl_Position = projection * fragModelView;

    fragColor = inColor;
}
