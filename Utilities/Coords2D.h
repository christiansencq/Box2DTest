#ifndef COORDS2D_H
#define COORDS2D_H


#include <cassert>
#include "Utilities.h"

class Coords2D {
    // A 2 Dimensional geometric vector (eg. screen coordinates.)
public:
    static const Coords2D Zero;

    Coords2D() : Coords2D(0, 0) {}
    Coords2D(float x, float y) : mX(x), mY(y) {}

    void SetX(float x) {mX = x;}
    void SetY(float y) {mY = y;}
    float GetX() const {return mX;}
    float GetY() const {return mY;}

    bool operator==(const Coords2D& vec) const;
    bool operator!=(const Coords2D& vec) const;

    Coords2D operator-() const;
    Coords2D operator*(float scale) const;
    Coords2D operator/(float scale) const;
    Coords2D& operator*=(float scale);
    Coords2D& operator/=(float scale);

    Coords2D operator+(const Coords2D& vec) const;
    Coords2D operator-(const Coords2D& vec) const;
    Coords2D& operator+=(const Coords2D& vec);
    Coords2D& operator-=(const Coords2D& vec);

    Coords2D operator+(float addend) const;
    Coords2D operator-(float subtrahend) const;
    Coords2D& operator+=(float addend);
    Coords2D& operator-=(float subtrahend);

    float Mag() const;
    float Distance(const Coords2D& GeoVec) const;

    void Rotate(float angle, const Coords2D& aroundPoint);
    Coords2D RotatedVec(float angle, const Coords2D& aroundPoint) const;



private:
    float mX, mY;
};

#endif