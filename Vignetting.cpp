#include "Vignetting.h"
#include <algorithm>

struct Pos {
    Pos() : _x(0), _y(0) {}
    Pos(int x, int y) : _x(x), _y(y) {}
    int _x;
    int _y;

    inline Pos operator-(const Pos& p) { return Pos(this->_x - p._x, this->_y - p._y); }
    inline Pos operator+(const Pos& p) { return Pos(this->_x + p._x, this->_y + p._y); }
    inline Pos& operator-=(const Pos& p) {
        this->_x -= p._x;
        this->_y -= p._y;
        return *this;
    }
    inline Pos& operator+=(const Pos& p) {
        this->_x += p._x;
        this->_y += p._y;
        return *this;
    }
    inline float len() { return (float)sqrt(_x * _x + _y * _y); }
    inline float distance(const Pos& p) { return (*this - p).len(); }
    inline float distance(int w, int h) { return (*this - Pos(w, h)).len(); }
};

int ApplyVignetting(unsigned char* channelY, const int width, const int height, const float startPos,
                    const float endStrength) {
    if (channelY == nullptr) {
        return -1;
    }
    if (width <= 0 || height <= 0) {
        return -2;
    }
    if (startPos <= 0 || startPos >= 1) {
        return -3;
    }
    if (endStrength <= 0 || endStrength >= 1) {
        return -4;
    }

    Pos center(width / 2, height / 2);
    float startLen = startPos * center.len();
    float range = center.len() - startLen;
    for (int h = 0; h < height / 2; h++) {
        for (int w = 0; w < width / 2; w++) {
            float dis = center.distance(w, h);
            if (dis < startLen) {
                break;
            }
            unsigned char& pix1 = channelY[h * width + w];
            unsigned char& pix2 = channelY[h * width + width - w - 1];
            unsigned char& pix3 = channelY[(height - h - 1) * width + w];
            unsigned char& pix4 = channelY[(height - h - 1) * width + width - w - 1];
            float strength = (dis - startLen) / range * (1 - endStrength);
            unsigned char movement = (unsigned char)(255.f * strength);
            pix1 = movement > pix1 ? 0 : pix1 - movement;
            pix2 = movement > pix2 ? 0 : pix2 - movement;
            pix3 = movement > pix3 ? 0 : pix3 - movement;
            pix4 = movement > pix4 ? 0 : pix4 - movement;
        }
    }

    return 0;
}
