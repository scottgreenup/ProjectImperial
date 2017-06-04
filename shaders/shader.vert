#version 300 es

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inCoord;

uniform mat4 normalMatrix;
uniform mat4 modelView;
uniform mat4 projection;
uniform vec3 solidColor;

smooth out vec3 fragColor;
smooth out vec3 fragNormal;
smooth out vec4 fragModelView;
out vec2 texCoord;

void main() {
    fragModelView = modelView * vec4(inPosition, 1.0);
    gl_Position = projection * fragModelView;

    vec4 normalised = (normalMatrix * vec4(inNormal, 0.0));

    fragNormal = normalised.xyz;
    fragColor = solidColor;
    texCoord = inCoord;
}
