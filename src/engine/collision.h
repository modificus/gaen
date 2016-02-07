//------------------------------------------------------------------------------
// collision.h - Collision calculations
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2015 Lachlan Orr
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

#ifndef GAEN_ENGINE_COLLISION_H
#define GAEN_ENGINE_COLLISION_H

#include <glm/vec3.hpp>

namespace gaen
{
// sqrt(2) - useful for 1-1-sqrt(2) 45-deg right triangles
static const f32 kSqrtOf2 = 1.4142135623730951;

// sqrt(3) - calc half diag of cube = radius * sqrt(3)
static const f32 kSqrtOf3 = 1.7320508075688772;

struct Ray
{
    Ray() {}
    Ray(const glm::vec3 & pos, const glm::vec3 & dir)
      : pos(pos)
      , dir(dir)
    {}

    glm::vec3 pos;
    glm::vec3 dir;
};

struct Plane
{
    Plane() {}

    Plane(const glm::vec3 & p0, const glm::vec3 & p1, const glm::vec3 & p2)
    {
        norm = glm::cross(p1 - p0, p2 - p0);
        glm::normalize(norm);
        dist = glm::dot(norm, p0);
    }

    glm::vec3 norm;  // plane's normalized surface normal
    f32 dist;   // distance from origin
};

struct Sphere
{
    Sphere(const glm::vec3 & center, f32 radius)
      : cent(center)
      , rad(radius)
    {}

    glm::vec3 cent; // center point
    f32 rad;   // radius
};

struct AABB_MinMax
{
    glm::vec3 min; // min coord values along each axis
    glm::vec3 max; // max coord values along each axis

    AABB_MinMax() {}

    AABB_MinMax(const glm::vec3 & min, const glm::vec3 & max)
      : min{min}
      , max{max}
    {}

    AABB_MinMax(glm::vec3 cent, f32 rad)
      : min{cent.x - rad, cent.y - rad, cent.z - rad}
      , max{cent.x + rad, cent.y + rad, cent.z + rad}
    {}

    AABB_MinMax(f32 rad)
      : min{-rad, -rad, -rad}
      , max{rad, rad, rad}
    {}

    glm::vec3 center() const
    {
        return min + ((max - min) / 2.0f);
    }
};

struct AABB_MinDiam
{
    glm::vec3 min;   // min coord values along each axis
    f32 diamX;  // x width
    f32 diamY;  // y width
    f32 diamZ;  // z width
};

struct AABB_CentRad
{
    glm::vec3 cent; // center point
    f32 radX;  // x half-width
    f32 radY;  // y half-width
    f32 radZ;  // z half-width
};

// Axis-aligned bounding cube
struct AABC
{
    glm::vec3 cent; // center point
    f32 rad;   // half-width

    // Corner distance from center.
    // Equates to bounding sphere radius.
    f32 diagRad()
    {
        return rad * kSqrtOf3;
    }

    Sphere sphere()
    {
        return Sphere(cent, diagRad());
    }
};

struct OBB
{
    glm::vec3 cent; // center point
    glm::vec3 locX; // local x axis
    glm::vec3 locY; // local y axis
    glm::vec3 ext;  // positive halfwidth extends along each axis
    
    glm::vec3 locZ()
    {
        return glm::cross(locX, locY);
    }
};

// Oriented bounding cube
struct OBC
{
    glm::vec3 cent; // center point
    glm::vec3 locX; // local x axis
    glm::vec3 locY; // local y axis
    f32 rad;   // half-width

    glm::vec3 locZ()
    {
        return glm::cross(locX, locY);
    }

    // Corner distance from center.
    // Equates to bounding sphere radius.
    f32 diagRad()
    {
        return rad * kSqrtOf3;
    }

    Sphere sphere()
    {
        return Sphere(cent, diagRad());
    }
};

// Determine whether sphere intersects with negative halfspace of plane
inline bool test_sphere_halfspace(const glm::vec3 & sCent, f32 sRad, const Plane & p)
{
    f32 dist = glm::dot(sCent, p.norm) - p.dist;
    return dist <= sRad;
}
inline bool test_sphere_halfpspace(const Sphere & s, const Plane & p)
{
    return test_sphere_halfspace(s.cent, s.rad, p);
}

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_COLLISION_H


