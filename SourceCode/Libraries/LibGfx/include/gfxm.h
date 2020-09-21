//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGFX_GLMATH_H__
#define __LIBRARY_LIBGFX_GLMATH_H__

typedef struct Vec3D {
    float x;
    float y;
    float z;
    float w;
} Vec3D;

typedef struct Mat4x4 {
    float m[4][4];
} Mat4x4;

Vec3D gfxm_vector_add(Vec3D v1, Vec3D v2);

Vec3D gfxm_vector_sub(Vec3D v1, Vec3D v2);

Vec3D gfxm_vector_mul(Vec3D v1, float k);

Vec3D gfxm_vector_mul_vector(Vec3D v1, Vec3D v2);

Vec3D gfxm_vector_div(Vec3D v1, float k);

Vec3D gfxm_vector_div_vector(Vec3D v1, Vec3D v2);

float gfxm_vector_dot_product(Vec3D v1, Vec3D v2);

float gfxm_vector_length(Vec3D v);

Vec3D gfxm_vector_normalise(Vec3D v1);

Vec3D gfxm_vector_cross_product(Vec3D v1, Vec3D v2);

Vec3D gfxm_matrix_multiply_vector(Mat4x4 m, Vec3D i);

Mat4x4 gfxm_matrix_multiply_matrix(Mat4x4 m1, Mat4x4 m2);

Mat4x4 gfxm_matrix_quick_inverse(Mat4x4 m);

#endif//__LIBRARY_LIBGFX_GLMATH_H__
