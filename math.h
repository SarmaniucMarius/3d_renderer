#ifndef MATH_H
#define MATH_H

// V4 declartions, functions

union v4 {
    struct {
        r32 x, y, z, w;
    };
    struct {
        r32 r, g, b, a;
    };
    r32 e[4];
};

inline v4 
V4(r32 a, r32 b, r32 c, r32 d)
{
    v4 result;
    result.x = a;
    result.y = b;
    result.z = c;
    result.w = d;
    return result;
}

inline v4
operator*(r32 a, v4 b)
{
    v4 result;
    result.x = b.x*a;
    result.y = b.y*a;
    result.z = b.z*a;
    result.w = b.w*a;
    return result;
}

inline v4
operator*(v4 b, r32 a)
{
    v4 result;
    result.x = b.x*a;
    result.y = b.y*a;
    result.z = b.z*a;
    result.w = b.w*a;
    return result;
}

inline v4 &
operator*=(v4 &b, r32 a)
{
    b = a*b;
    return b;
}

inline v4
operator-(v4 a)
{
    v4 result;
    result.x = -a.x; 
    result.y = -a.y; 
    result.z = -a.z; 
    result.w = -a.w;
    return result;
}


inline v4
operator+(v4 a, v4 b)
{
    v4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

inline v4 &
operator+=(v4 &a, v4 b)
{
    a = a + b;
    return a;
}

inline v4
operator-(v4 a, v4 b)
{
    v4 result;
    result.x = a.x - b.x; 
    result.y = a.y - b.y; 
    result.z = a.z - b.z; 
    result.w = a.w - b.w; 
    return result;
}

inline r32
length(v4 a)
{
    return (r32) sqrt(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
}

inline v4
normalize(v4 a)
{
    return a*(1.0f/length(a));
}

inline v4
lerp(v4 a, r32 t, v4 b)
{
    return (1 - t)*a + t*b;
}

// V3 declartions, functions

union v3 {
    struct {
         r32 x, y, z;
    };
    r32 e[3];
};

inline v3
V3(r32 a, r32 b, r32 c)
{
    v3 result;
    result.x = a;
    result.y = b;
    result.z = c;
    return result;
}

inline v3
operator*(r32 a, v3 b)
{
    v3 result;
    result.x = b.x*a;
    result.y = b.y*a;
    result.z = b.z*a;
    return result;
}

inline v3
operator*(v3 b, r32 a)
{
    v3 result;
    result.x = b.x*a;
    result.y = b.y*a;
    result.z = b.z*a;
    return result;
}

inline v3 &
operator*=(v3 &b, r32 a)
{
    b = a*b;
    return b;
}

inline v3
operator-(v3 a)
{
    v3 result;
    result.x = -a.x; 
    result.y = -a.y; 
    result.z = -a.z; 
    return result;
}

inline v3
operator+(v3 a, v3 b)
{
    v3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

inline v3 &
operator+=(v3 &a, v3 b)
{
    a = a + b;
    return a;
}

inline v3
operator-(v3 a, v3 b)
{
    v3 result;
    result.x = a.x - b.x; 
    result.y = a.y - b.y; 
    result.z = a.z - b.z; 
    return result;
}

inline r32
dot(v3 a, v3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline v3
cross(v3 a, v3 b)
{
    v3 result;
    result.x = a.y*b.z - a.z*b.y;
    result.y = a.z*b.x - a.x*b.z;
    result.z = a.x*b.y - a.y*b.x;
    return result;
}

inline r32
length(v3 a)
{
    return (r32) sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline v3
normalize(v3 a)
{
    return a*(1.0f/length(a));
}

inline v3
lerp(v3 a, r32 t, v3 b)
{
    return (1.0f - t)*a + t*b;
}

// V2 declarations, functions

union v2 {
    struct {
        r32 x, y;
    };
    r32 e[2];
};

inline v2 
V2(r32 a, r32 b)
{
    v2 result;
    result.x = a;
    result.y = b;
    return result;
}

inline v2
operator*(r32 a, v2 b)
{
    v2 result;
    result.x = b.x*a;
    result.y = b.y*a;
    return result;
}

inline v2
operator*(v2 b, r32 a)
{
    v2 result;
    result.x = b.x*a;
    result.y = b.y*a;
    return result;
}

inline v2 &
operator*=(v2 &b, r32 a)
{
    b = a*b;
    return b;
}

inline v2
operator-(v2 a)
{
    v2 result;
    result.x = -a.x; 
    result.y = -a.y; 
    return result;
}


inline v2
operator+(v2 a, v2 b)
{
    v2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

inline v2 &
operator+=(v2 &a, v2 b)
{
    a = a + b;
    return a;
}

inline v2
operator-(v2 a, v2 b)
{
    v2 result;
    result.x = a.x - b.x; 
    result.y = a.y - b.y; 
    return result;
}

inline r32
dot(v2 a, v2 b)
{
    return a.x*b.x + a.y*b.y;
}

inline v2
perp(v2 a)
{
    v2 result = {-a.y, a.x};
    return result;
}

inline r32
length(v2 a)
{
    return (r32) sqrt(a.x*a.x + a.y*a.y);
}

inline v2
normalize(v2 a)
{
    return a*(1.0f/length(a));
}

// V2i declarations, functions

union v2i {
    struct {
        i32 x, y;
    };
    i32 e[2];
};

inline v2i 
V2i(i32 a, i32 b)
{
    v2i result;
    result.x = a;
    result.y = b;
    return result;
}

inline v2i
operator+(v2i a, v2i b)
{
    v2i result;
    result.x = a.x + b.x; 
    result.y = a.y + b.y; 
    return result;
}

inline v2i
operator-(v2i a, v2i b)
{
    v2i result;
    result.x = a.x - b.x; 
    result.y = a.y - b.y; 
    return result;
}

inline i32
cross(v2i a, v2i b)
{
    return a.x*b.y - a.y*b.x;
}

// 2x2 matrix

struct m2x2
{
     r32 e[2][2];
};

inline m2x2
M2x2(r32 a11, r32 a12, r32 a21, r32 a22)
{
    m2x2 result = {a11, a12, a21, a22};
    return result;
}

inline m2x2
scale_m2x2(r32 value)
{
    m2x2 result = { value, 0.0f, 0.0f, value };
    return result;
}

inline m2x2
identity_m2x2()
{
    m2x2 result = { 1.0f, 0.0f, 0.0f, 1.0f};
    return result;
}

inline m2x2
rotation_m2x2(r32 angle)
{
    m2x2 result = { (r32)cos(angle), (r32)-sin(angle), (r32)sin(angle), (r32)cos(angle) };
    return result;
}

inline v2
operator*(m2x2 m, v2 v)
{
    v2 result;
    result.x = m.e[0][0]*v.x + m.e[0][1]*v.y;
    result.y = m.e[1][0]*v.x + m.e[1][1]*v.y;
    return result;
}

inline m2x2
operator*(m2x2 a, m2x2 b)
{
    m2x2 result;
    result.e[0][0] = a.e[0][0]*b.e[0][0] + a.e[0][1]*b.e[1][0];
    result.e[0][1] = a.e[0][0]*b.e[0][1] + a.e[0][1]*b.e[1][1];
    result.e[1][0] = a.e[1][0]*b.e[0][0] + a.e[1][1]*b.e[1][0];
    result.e[1][1] = a.e[1][0]*b.e[0][1] + a.e[1][1]*b.e[1][1];
    return result;
}

// 3x3 matrix

struct m3x3
{
    r32 e[3][3];
};

inline m3x3
M3x3(r32 a11, r32 a12, r32 a13, 
     r32 a21, r32 a22, r32 a23,
     r32 a31, r32 a32, r32 a33)
{
    m3x3 result = {
        a11, a12, a13, 
        a21, a22, a23,
        a31, a32, a33,
    };
    return result;
}

inline m3x3
scale_m3x3(r32 value)
{
    m3x3 result = { 
        value, 0.0f, 0.0f,
        0.0f, value, 0.0f,
        0.0f, 0.0f, value,
    };
    return result;
}

inline m3x3
identity_m3x3()
{
    m3x3 result = { 
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
    return result;
}

inline m3x3
zrotation_m3x3(r32 angle)
{
    m3x3 result = { 
        (r32)cos(angle), (r32)-sin(angle), 0.0f,
        (r32)sin(angle), (r32)cos(angle),  0.0f,
        0.0f,            0.0f,             1.0f
    };
    return result;
}

inline m3x3
yrotation_m3x3(r32 angle)
{
    m3x3 result = { 
        (r32)cos(angle), 0.0f, (r32)sin(angle),
        0.0f, 1.0f, 0.0f,
        -(r32)sin(angle),  0.0f, (r32)cos(angle),
    };
    return result;
}

inline m3x3
xrotation_m3x3(r32 angle)
{
    m3x3 result = { 
        1.0f, 0.0f, 0.0f,
        0.0f, (r32)cos(angle), -(r32)sin(angle),
        0.0f, (r32)sin(angle),  (r32)cos(angle),
    };
    return result;
}

inline v3
operator*(m3x3 m, v3 v)
{
    v3 result;
    result.x = m.e[0][0]*v.x + m.e[0][1]*v.y + m.e[0][2]*v.z;
    result.y = m.e[1][0]*v.x + m.e[1][1]*v.y + m.e[1][2]*v.z;
    result.z = m.e[2][0]*v.x + m.e[2][1]*v.y + m.e[2][2]*v.z;
    return result;
}

inline m3x3
operator*(m3x3 a, m3x3 b)
{
    m3x3 result;
    result.e[0][0] = a.e[0][0]*b.e[0][0] + a.e[0][1]*b.e[1][0] + a.e[0][2]*b.e[2][0];
    result.e[0][1] = a.e[0][0]*b.e[0][1] + a.e[0][1]*b.e[1][1] + a.e[0][2]*b.e[2][1];
    result.e[0][2] = a.e[0][0]*b.e[0][2] + a.e[0][1]*b.e[1][2] + a.e[0][2]*b.e[2][2];
    result.e[1][0] = a.e[1][0]*b.e[0][0] + a.e[1][1]*b.e[1][0] + a.e[1][2]*b.e[2][0];
    result.e[1][1] = a.e[1][0]*b.e[0][1] + a.e[1][1]*b.e[1][1] + a.e[1][2]*b.e[2][1];
    result.e[1][2] = a.e[1][0]*b.e[0][2] + a.e[1][1]*b.e[1][2] + a.e[1][2]*b.e[2][2];
    result.e[2][0] = a.e[2][0]*b.e[0][0] + a.e[2][1]*b.e[1][0] + a.e[2][2]*b.e[2][0];
    result.e[2][1] = a.e[2][0]*b.e[0][1] + a.e[2][1]*b.e[1][1] + a.e[2][2]*b.e[2][1];
    result.e[2][2] = a.e[2][0]*b.e[0][2] + a.e[2][1]*b.e[1][2] + a.e[2][2]*b.e[2][2];
    
    return result;
}

#endif