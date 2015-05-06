#version 300 es
#
precision highp float;

uniform struct FogParameters {
    vec4 color;
    float start;
    float end;
    float density;
} fogParams;

float GetFogFactor(FogParameters p, float coord) {
    float result = (p.end - coord) / (p.end - p.start);
    result = 1.0 - clamp(result, 0.0, 1.0);
    return result;
}

smooth in vec3 fragNormal;
smooth in vec3 fragColor;
smooth in vec4 fragModelView;

out vec4 color;

void main() {
    vec3 vColor = vec3(1.0, 0.0, 0.0);
    vec3 vDirection = vec3(0.0, 1.0, 0.0);
    float intensity = 0.35f;

    float diffuse = max(0.0, dot(normalize(fragNormal), -vDirection));
    color = vec4(fragColor, 1.0) * vec4(vColor * (intensity + diffuse), 1.0);
    //color = vec4(fragColor, 1.0);

    float fogCoord = abs(fragModelView.z / fragModelView.w);
    color = mix(color, fogParams.color, GetFogFactor(fogParams, fogCoord));
}
