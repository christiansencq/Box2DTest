#include "Coords2D.h"


const Coords2D Coords2D::Zero;

bool Coords2D::operator!=(const Coords2D& vec) const
{
    return !(*this == vec);
}

bool Coords2D::operator==(const Coords2D& vec) const
{
    return Compare(mX, vec.mX) && Compare(mY, vec.mY);
}

Coords2D Coords2D::operator-() const
{
    return Coords2D(-mX, -mY);
}

Coords2D Coords2D::operator*(float scale) const
{
    return Coords2D(mX * scale, mY * scale);
}

Coords2D operator*(float scalar, const Coords2D& vec)
{
    return vec * scalar;
}

Coords2D Coords2D::operator/(float scale) const
{
    assert(fabsf(scale) > EPSILON);

    return Coords2D(mX / scale, mY / scale);
}

Coords2D& Coords2D::operator*=(float scale)
{
    *this = *this * scale;
    return *this;
}

Coords2D& Coords2D::operator/=(float scale)
{
    assert(fabsf(scale) > EPSILON);
    *this = *this / scale;
    return *this;
}

Coords2D Coords2D::operator+(const Coords2D& vec) const
{
    return Coords2D(mX + vec.mX, mY + vec.mY);
}

Coords2D Coords2D::operator-(const Coords2D& vec) const
{
    return Coords2D(mX - vec.mX, mY - vec.mY);
}

Coords2D& Coords2D::operator+=(const Coords2D& vec)
{
    *this = *this + vec;
    return *this;
}

Coords2D& Coords2D::operator-=(const Coords2D& vec)
{
    *this = *this - vec;
    return *this;
}




Coords2D Coords2D::operator+(float addend) const
{
    return Coords2D(mX + addend, mY + addend);
}

Coords2D Coords2D::operator-(float subtrahend) const
{
    return Coords2D(mX - subtrahend, mY - subtrahend);
}


Coords2D& Coords2D::operator+=(float addend)
{
    *this = *this + addend;
    return *this;
}

Coords2D& Coords2D::operator-=(float subtrahend)
{
    *this = *this - subtrahend;
    return *this;
}


//Calculators

float Coords2D::Mag() const
{
    return sqrt( mX*mX + mY*mY );
}

float Coords2D::Distance(const Coords2D& vec) const
{
    return (vec - *this).Mag();
}

void Coords2D::Rotate(float angle, const Coords2D& aroundPoint)
{
    *this = RotatedVec(angle, aroundPoint);    
}

Coords2D Coords2D::RotatedVec(float angle, const Coords2D& aroundPoint) const
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Coords2D thisVec(mX, mY);
    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mY * sine + thisVec.mY * cosine;

    Coords2D rot = Coords2D(xRot, yRot);

    return rot + aroundPoint;    
}