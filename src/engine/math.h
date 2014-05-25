//------------------------------------------------------------------------------
// math.h - Vector and matrix math
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014 Lachlan Orr
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.
//------------------------------------------------------------------------------

#ifndef GAEN_ENGINE_MATH_H
#define GAEN_ENGINE_MATH_H

#include <cmath>

#include "core/base_defines.h"

namespace gaen
{

static const f32 kPi = 3.1415926535897932384626433832795f;
inline f32 deg2rad(f32 deg) { return deg * kPi * (1.0f / 180.0f); }

static const f32 kFpErrThreshold = 0.00000001f;
inline bool is_fp_eq(f32 actual, f32 expected) { return (actual >= expected - kFpErrThreshold) && (actual <= expected + kFpErrThreshold); }

f32 invSqrt(const f32 x);
f32 fastSqrt(const f32 x);


struct Vec3
{
    // constructors
    Vec3() = default;
    Vec3(f32 x, f32 y, f32 z);
    Vec3(const struct Vec4 &rhs);

    f32 length() const;
    void normalize();
    void normalizeIfNecessary();

    static f32 dot(const Vec3 &lhs, const Vec3 &rhs);
    static Vec3 cross(const Vec3 &lhs, const Vec3 &rhs);

    f32 x;
    f32 y;
    f32 z;
};

Vec3 operator-(const Vec3 & lhs, const Vec3& rhs);
bool operator==(const Vec3 & lhs,const Vec3 & rhs);
Vec3 triNormal(const Vec3 & p0, const Vec3 & p1, const Vec3 & p2);

struct Vec4
{
    Vec4() = default;
    Vec4(f32 x, f32 y, f32 z, f32 w);
    Vec4(const Vec3 &vec3, f32 w);

    f32 length() const;
    void normalize();
    void normalizeIfNecessary();

    static f32 dot(const Vec3 &lhs, const Vec3 &rhs);
    static Vec4 cross(const Vec4 &lhs, const Vec4 &rhs);

    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

bool operator==(const Vec4 & lhs,const Vec4 & rhs);

struct Mat4;
struct Mat3
{
    Mat3();
    Mat3(f32 e0, f32 e1, f32 e2,
         f32 e3, f32 e4, f32 e5,
         f32 e6, f32 e7, f32 e8);

    static const Mat3 & zero();
    static const Mat3 & identity();

    static f32 determinant(const Mat3 & mat3);
    static Mat3 inverse(const Mat3 & mat3);

    // build a 3x3 matrix to use to transform normals
    static Mat3 model_view_to_normal_transform(const Mat4 & mv);

    f32 & operator[](size_t idx);
    const f32 & operator[](size_t idx) const;

    f32 elems[9];
};


struct Mat34
{
    Mat34();
    Mat34(const Mat4 & mat4);
    Mat34(f32 e0, f32 e1,  f32 e2,
          f32 e3, f32 e4,  f32 e5,
          f32 e6, f32 e7,  f32 e8,
          f32 e9, f32 e10, f32 e11);

    static const Mat34 & zero();
    static const Mat34 & identity();

    static Mat34 build_from_vec4(const Vec4 & vec4_0,
                                 const Vec4 & vec4_1,
                                 const Vec4 & vec4_2);

    static Vec4 multiply(const Mat34 & mat34, const Vec4 & vec4);
    static Mat34 multiply(const Mat34 & lhs, const Mat34 & rhs);

    static f32 determinant(const Mat34 & mat34);
    static Mat34 inverse(const Mat34 & mat34);

    static Mat34 build_translation(const Vec3 & pos);
    static Mat34 build_rotation(const Vec3 & rot);
    static Mat34 build_scale(f32 scale);
    static Mat34 build_transform(const Vec3 & pos,
                                 const Vec3 & rot,
                                 f32 scale);

    f32 & operator[](size_t idx);
    const f32 & operator[](size_t idx) const;

    Vec4  operator* (const Vec4 & rhs) const;
    Mat34 operator* (const Mat34 & rhs) const;

    Vec4 & vec4(size_t idx);
    const Vec4 & vec4(size_t idx) const;

    f32 elems[12];
};

struct Mat4
{
    Mat4();
    Mat4(f32 e0,  f32 e1,  f32 e2,  f32 e3,
         f32 e4,  f32 e5,  f32 e6,  f32 e7,
         f32 e8,  f32 e9,  f32 e10, f32 e11,
         f32 e12, f32 e13, f32 e14, f32 e15);
    Mat4(const Mat34 & mat34);

    static const Mat4 & zero();
    static const Mat4 & identity();

    static Vec4 multiply(const Mat4 & mat4, const Vec4 & vec4);
    static Mat4 multiply(const Mat4 & lhs, const Mat4 & rhs);

    static f32 determinant(const Mat4 & mat4);
    static Mat4 inverse(const Mat4 & mat4);

    static Mat4 build_translation(const Vec3 & pos);
    static Mat4 build_rotation(const Vec3 & rot);
    static Mat4 build_scale(f32 scale);
    static Mat4 build_transform(const Vec3 & pos,
                                const Vec3 & rot,
                                f32 scale);

    static Mat4 frustum(f32 left, f32 right, f32 bottom, f32 top, f32 nearZ, f32 farZ);
    static Mat4 perspective(f32 fovy, f32 aspect, f32 nearZ, f32 farZ);
    static Mat4 orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 nearZ, f32 farZ);

    f32 & operator[](size_t idx);
    const f32 & operator[](size_t idx) const;

    Vec4 operator* (const Vec4 & rhs) const;
    Mat4 operator* (const Mat4 & rhs) const;

    f32 elems[16];
};




//------------------------------------------------------------------------------
// Inline function definitions
//------------------------------------------------------------------------------

// This is the Quake 3 Walsh method
inline f32 invSqrt(const f32 x)
{
    const f32 xhalf = 0.5f * x;
 
    union // get bits for floating value
    {
        f32 x;
        int i;
    } u;

    u.x = x;
    u.i = 0x5f3759df - (u.i >> 1); // gives initial guess y0
    u.x = u.x*(1.5f - xhalf * u.x * u.x); // Newton step, repeating increases accuracy
    return u.x;
}

inline f32 fastSqrt(const f32 x)
{
    return x * invSqrt(x);
}


//--------------------------------------
// Vec3 inlined methods
//--------------------------------------
inline Vec3::Vec3(f32 x, f32 y, f32 z)
  : x(x)
  , y(y)
  , z(z) {}

inline Vec3::Vec3(const Vec4 &vec4)
  : x(vec4.x)
  , y(vec4.y)
  , z(vec4.z) {}

inline f32 Vec3::length() const
{
    return sqrt(x*x + y*y + z*z);
}

inline void Vec3::normalize()
{
    //float inv_mag = invSqrt(x*x + y*y + z*z);
    f32 inv_mag = 1.0f / sqrt(x*x + y*y + z*z);
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
}

inline void Vec3::normalizeIfNecessary()
{
    f32 sumSquares = x*x + y*y + z*z;
    if (!is_fp_eq(sumSquares, 1.0f))
    {
        f32 inv_mag = 1.0f / sqrt(sumSquares);
        x *= inv_mag;
        y *= inv_mag;
        z *= inv_mag;
    }
}

inline f32 Vec3::dot(const Vec3 &lhs, const Vec3 &rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

inline Vec3 Vec3::cross(const Vec3 &lhs, const Vec3 &rhs)
{
    Vec3 vec(lhs.y*rhs.z - lhs.z*rhs.y,
             lhs.z*rhs.x - lhs.x*rhs.z,
             lhs.x*rhs.y - lhs.y*rhs.x);
    return vec;
}

inline Vec3 operator-(const Vec3 & lhs, const Vec3 & rhs)
{
    return Vec3(lhs.x - rhs.x,
                lhs.y - rhs.y,
                lhs.z - rhs.z);
}

inline bool operator==(const Vec3 & lhs, const Vec3 & rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z;
}

inline Vec3 triNormal(const Vec3 & p0, const Vec3 & p1, const Vec3 & p2)
{
    Vec3 vecA = p1 - p0;
    Vec3 vecB = p2 - p0;
    return Vec3::cross(vecA, vecB);
}


//--------------------------------------
// Vec4 inlined methods
//--------------------------------------
inline Vec4::Vec4(f32 x, f32 y, f32 z, f32 w) 
  : x(x)
  , y(y)
  , z(z)
  , w(w) {}

inline Vec4::Vec4(const Vec3 &vec3, f32 w)
  : x(vec3.x)
  , y(vec3.y)
  , z(vec3.z)
  , w(w) {}

inline f32 Vec4::length() const 
{ 
    return sqrt(x*x + y*y + z*z + w*w);
}

inline void Vec4::normalize()
{
    //float inv_mag = invSqrt(x*x + y*y + z*z);
    f32 inv_mag = 1.0f / sqrt(x*x + y*y + z*z);
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
}

inline void Vec4::normalizeIfNecessary()
{
    f32 sumSquares = x*x + y*y + z*z;
    if (!is_fp_eq(sumSquares, 1.0f))
    {
        f32 inv_mag = 1.0f / sqrt(sumSquares);
        x *= inv_mag;
        y *= inv_mag;
        z *= inv_mag;
    }
}

inline f32 Vec4::dot(const Vec3 &lhs, const Vec3 &rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

inline Vec4 Vec4::cross(const Vec4 &lhs, const Vec4 &rhs)
{
    Vec4 vec(lhs.y*rhs.z - lhs.z*rhs.y,
             lhs.z*rhs.x - lhs.x*rhs.z,
             lhs.x*rhs.y - lhs.y*rhs.x,
             0.0f);
    return vec;
}

inline bool operator==(const Vec4 & lhs,const Vec4 & rhs)
{
    return lhs.x == rhs.x &&
        lhs.y == rhs.y &&
        lhs.z == rhs.z &&
        lhs.w == rhs.w;
}


//--------------------------------------
// Mat3 inlined methods
//--------------------------------------
inline Mat3::Mat3() {}
inline Mat3::Mat3(f32 e0, f32 e1, f32 e2,
                  f32 e3, f32 e4, f32 e5,
                  f32 e6, f32 e7, f32 e8)
{
    elems[0] = e0;
    elems[1] = e1;
    elems[2] = e2;

    elems[3] = e3;
    elems[4] = e4;
    elems[5] = e5;

    elems[6] = e6;
    elems[7] = e7;
    elems[8] = e8;
}

inline const Mat3 & Mat3::zero()
{
    static Mat3 zero3{0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f};
    return zero3;
}

inline const Mat3 & Mat3::identity()
{
    static Mat3 ident3{1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 1.0f};
    return ident3;
}

inline f32 & Mat3::operator[](size_t idx)
{
    ASSERT(idx < 9);
    return elems[idx];
}

inline const f32 & Mat3::operator[](size_t idx) const
{
    ASSERT(idx < 9);
    return elems[idx];
}

//--------------------------------------
// Mat34 inlined methods
//--------------------------------------
inline Mat34::Mat34() {}
inline Mat34::Mat34(f32 e0, f32 e1,  f32 e2,
                    f32 e3, f32 e4,  f32 e5,
                    f32 e6, f32 e7,  f32 e8,
                    f32 e9, f32 e10, f32 e11)
{
    elems[0]  = e0;
    elems[1]  = e1;
    elems[2]  = e2;

    elems[3]  = e3;
    elems[4]  = e4;
    elems[5]  = e5;

    elems[6]  = e6;
    elems[7]  = e7;
    elems[8]  = e8;

    elems[9]  = e9;
    elems[10] = e10;
    elems[11] = e11;
}
inline Mat34::Mat34(const Mat4 & mat4)
{
    ASSERT_MSG(mat4[3]  == 0.0f &&
               mat4[7]  == 0.0f &&
               mat4[11] == 0.0f &&
               mat4[15] == 1.0f,
               "Incompatible Mat4 array to convert to Mat34");

    elems[0]  = mat4[0];
    elems[1]  = mat4[1];
    elems[2]  = mat4[2];

    elems[3]  = mat4[4];
    elems[4]  = mat4[5];
    elems[5]  = mat4[6];

    elems[6]  = mat4[8];
    elems[7]  = mat4[9];
    elems[8]  = mat4[10];

    elems[9]  = mat4[12];
    elems[10] = mat4[13];
    elems[11] = mat4[14];
}

inline const Mat34 & Mat34::zero()
{
    static Mat34 zero34{0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f};
    return zero34;
}

inline const Mat34 & Mat34::identity()
{
    static Mat34 ident34{1.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 1.0f,
                         0.0f, 0.0f, 0.0f};
    return ident34;
}

inline Mat34 Mat34::build_from_vec4(const Vec4 & vec4_0,
                           const Vec4 & vec4_1,
                           const Vec4 & vec4_2)
{
    Mat34 mat34;
    mat34.vec4(0) = vec4_0;
    mat34.vec4(1) = vec4_1;
    mat34.vec4(2) = vec4_2;
    return mat34;
}

inline Mat34 Mat34::build_transform(const Vec3 & pos,
                                    const Vec3 & rot,
                                    f32 scale)
{
    return build_translation(pos) * build_rotation(rot) * build_scale(scale);
}

inline f32 & Mat34::operator[](size_t idx)
{
    ASSERT(idx < 12);
    return elems[idx];
}

inline const f32 & Mat34::operator[](size_t idx) const
{
    ASSERT(idx < 12);
    return elems[idx];
}

inline Vec4 Mat34::operator* (const Vec4 & rhs) const
{
    return multiply(*this, rhs);
}

inline Mat34 Mat34::operator* (const Mat34 & rhs) const
{
    return multiply(*this, rhs);
}


inline Vec4 & Mat34::vec4(size_t idx)
{
    ASSERT(idx < 3);
    return *reinterpret_cast<Vec4*>(&elems[idx * 4]);
}

inline const Vec4 & Mat34::vec4(size_t idx) const
{
    ASSERT(idx < 3);
    return *reinterpret_cast<const Vec4*>(&elems[idx * 4]);
}


//--------------------------------------
// Mat4 inlined methods
//--------------------------------------
inline Mat4::Mat4() {}
inline Mat4::Mat4(f32 e0,  f32 e1,  f32 e2,  f32 e3,
                  f32 e4,  f32 e5,  f32 e6,  f32 e7,
                  f32 e8,  f32 e9,  f32 e10, f32 e11,
                  f32 e12, f32 e13, f32 e14, f32 e15)
{
    elems[0]  = e0;
    elems[1]  = e1;
    elems[2]  = e2;
    elems[3]  = e3;

    elems[4]  = e4;
    elems[5]  = e5;
    elems[6]  = e6;
    elems[7]  = e7;

    elems[8]  = e8;
    elems[9]  = e9;
    elems[10] = e10;
    elems[11] = e11;

    elems[12] = e12;
    elems[13] = e13;
    elems[14] = e14;
    elems[15] = e15;
}
inline Mat4::Mat4(const Mat34 & mat34)
{
    elems[0]  = mat34[0];
    elems[1]  = mat34[1];
    elems[2]  = mat34[2];
    elems[3]  = 0.0f;

    elems[4]  = mat34[3];
    elems[5]  = mat34[4];
    elems[6]  = mat34[5];
    elems[7]  = 0.0f;

    elems[8]  = mat34[6];
    elems[9]  = mat34[7];
    elems[10] = mat34[8];
    elems[11] = 0.0f;

    elems[12] = mat34[9];
    elems[13] = mat34[10];
    elems[14] = mat34[11];
    elems[15] = 1.0f;
}

inline const Mat4 & Mat4::zero()
{
    static Mat4 zero4{0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f};
    return zero4;
}

inline const Mat4 & Mat4::identity()
{
    static Mat4 ident4{1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f};
    return ident4;
}

inline Mat4 Mat4::build_transform(const Vec3 & pos,
                                  const Vec3 & rot,
                                  f32 scale)
{
    return build_translation(pos) * build_rotation(rot) * build_scale(scale);
}

inline f32 & Mat4::operator[](size_t idx)
{
    ASSERT(idx < 16);
    return elems[idx];
}

inline const f32 & Mat4::operator[](size_t idx) const
{
    ASSERT(idx < 16);
    return elems[idx];
}

inline Vec4 Mat4::operator* (const Vec4 & rhs) const
{
    return multiply(*this, rhs);
}

inline Mat4 Mat4::operator* (const Mat4 & rhs) const
{
    return multiply(*this, rhs);
}



//------------------------------------------------------------------------------
// Inline Function definitions (END)
//------------------------------------------------------------------------------


// Sanity checks for sizeof our structs.  Just in case a different compiler/platform pads stuff unexpectedly.
static_assert(sizeof(Vec3) == 12,      "geometry struct has unexpected size");
static_assert(sizeof(Vec3[10]) == 120, "geometry struct has unexpected size");
static_assert(sizeof(Vec4) == 16,      "geometry struct has unexpected size");
static_assert(sizeof(Vec4[10]) == 160, "geometry struct has unexpected size");
static_assert(sizeof(Mat3) == 36,      "geometry struct has unexpected size");
static_assert(sizeof(Mat3[10]) == 360, "geometry struct has unexpected size");
static_assert(sizeof(Mat34) == 48,     "geometry struct has unexpected size");
static_assert(sizeof(Mat34[10]) == 480,"geometry struct has unexpected size");
static_assert(sizeof(Mat4) == 64,      "geometry struct has unexpected size");
static_assert(sizeof(Mat4[10]) == 640, "geometry struct has unexpected size");


} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MATH_H
