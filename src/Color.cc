
#include "Color.h"

#include <cmath>


void RGBtoHSV(float r, float g, float b, float& h, float& s, float& v) {
    
    float min = r < g ? r : g;
    min = min < b ? min : b;

    float max = r > g ? r : g;
    max = max > b ? max : b;

    v = max;

    float delta = max - min;

    if (max <= 0.0f) {
        s = 0.0f;
        h = NAN;
        return;
    }

    s = (delta / max);

    if (r >= max) {
        h = (g - b) / delta;
    } else if (g >= max) {
        h = 2.0f + (b - r) / delta;
    } else {
        h = 4.0f + (r - g) / delta;
    }

    h *= 60.0f;

    if (h < 0.0f) {
        h += 360.0f;
    }
}

void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b) {
    if (s <= 0.0f) {
        r = v;
        g = v;
        b = v;
        return;
    }

    float hh = h;

    if (hh >= 360.0f) {
        hh = 0.0f;
    }

    hh /= 60.0f;

    long i = (long)hh;
    float ff = hh - i;

    float p = v * (1.0f - s);
    float q = v * (1.0f - (s * ff));
    float t = v * (1.0f - (s * (1.0f - ff)));

    switch(i) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
}
