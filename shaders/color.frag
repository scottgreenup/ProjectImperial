#version 300 es
#
precision highp float;

smooth in vec3 fragColor;
smooth in vec4 fragModelView;

out vec4 color;

void main() {
    color = vec4(fragColor, 1.0);
}
