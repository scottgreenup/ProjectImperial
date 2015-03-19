#version 300 es

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

uniform mat4 normalMatrix;
uniform mat4 modelView;
uniform mat4 projection;
uniform vec3 solidColor;

smooth out vec3 fragColor;
smooth out vec3 fragNormal;

void main() {
    //gl_Position = MVP * vec4(inPosition, 1);

    gl_Position = projection * modelView * vec4(inPosition, 1.0); 
    vec4 res = normalMatrix * vec4(inNormal, 0.0);

    fragNormal = res.xyz;
    fragColor = solidColor;
}

