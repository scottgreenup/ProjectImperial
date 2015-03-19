#version 300 es

precision highp float;

smooth in vec3 fragNormal;
smooth in vec3 fragColor;

out vec4 color;

void main() {

    vec3 vColor = vec3(1.0, 0.0, 0.0);
    vec3 vDirection = vec3(0.0, 1.0, 0.0);
    float intensity = 0.35f;

    float diffuse = max(0.0, dot(normalize(fragNormal), -vDirection));

    color = vec4(fragColor, 1.0) * vec4(vColor * (intensity + diffuse), 1.0);


//    color = fragColor;
}
