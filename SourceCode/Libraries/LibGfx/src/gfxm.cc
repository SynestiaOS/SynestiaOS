//
// Created by XingfengYang on 2020/7/7.
//

#include "libmath/math.h"
#include <libgfx/gfxm.h>

Vec3D gfxm_vector_add(Vec3D v1, Vec3D v2) {
    Vec3D vec;
    vec.x = v1.x + v2.x;
    vec.y = v1.y + v2.y;
    vec.z = v1.z + v2.z;
    return vec;
}

Vec3D gfxm_vector_sub(Vec3D v1, Vec3D v2) {
    Vec3D vec;
    vec.x = v1.x - v2.x;
    vec.y = v1.y - v2.y;
    vec.z = v1.z - v2.z;
    return vec;
}

Vec3D gfxm_vector_mul(Vec3D v1, float k) {
    Vec3D vec;
    vec.x = v1.x * k;
    vec.y = v1.y * k;
    vec.z = v1.z * k;
    return vec;
}

Vec3D gfxm_vector_mul_vector(Vec3D v1, Vec3D v2) {
    Vec3D vec;
    vec.x = v1.x * v2.x;
    vec.y = v1.y * v2.y;
    vec.z = v1.z * v2.z;
    return vec;
}

Vec3D gfxm_vector_div(Vec3D v1, float k) {
    Vec3D vec;
    vec.x = v1.x / k;
    vec.y = v1.y / k;
    vec.z = v1.z / k;
    return vec;
}

Vec3D gfxm_vector_div_vector(Vec3D v1, Vec3D v2) {
    Vec3D vec;
    vec.x = v1.x / v2.x;
    vec.y = v1.y / v2.y;
    vec.z = v1.z / v2.z;
    return vec;
}

float gfxm_vector_dot_product(Vec3D v1, Vec3D v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

float gfxm_vector_length(Vec3D v) { return q_rsqrt(gfxm_vector_dot_product(v, v)); }

Vec3D gfxm_vector_normalise(Vec3D v1) {
    Vec3D vec;
    float l = gfxm_vector_length(v1);
    vec.x = v1.x / l;
    vec.y = v1.y / l;
    vec.z = v1.z / l;
    return vec;
}

Vec3D gfxm_vector_cross_product(Vec3D v1, Vec3D v2) {
    Vec3D vec;
    vec.x = v1.y * v2.z - v1.z * v2.y;
    vec.y = v1.z * v2.x - v1.x * v2.z;
    vec.z = v1.x * v2.y - v1.y * v2.x;
    return vec;
}

Vec3D gfxm_matrix_multiply_vector(Mat4x4 m, Vec3D i) {
    Vec3D vec;
    vec.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    vec.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    vec.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    vec.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    return vec;
}

Mat4x4 gfxm_matrix_multiply_matrix(Mat4x4 m1, Mat4x4 m2) {
    Mat4x4 matrix;
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] +
                             m1.m[r][3] * m2.m[3][c];
        }
    }
    return matrix;
}

Mat4x4 gfxm_matrix_quick_inverse(Mat4x4 m) {
    Mat4x4 matrix;
    matrix.m[0][0] = m.m[0][0];
    matrix.m[0][1] = m.m[1][0];
    matrix.m[0][2] = m.m[2][0];
    matrix.m[0][3] = 0.0f;

    matrix.m[1][0] = m.m[0][1];
    matrix.m[1][1] = m.m[1][1];
    matrix.m[1][2] = m.m[2][1];
    matrix.m[1][3] = 0.0f;

    matrix.m[2][0] = m.m[0][2];
    matrix.m[2][1] = m.m[1][2];
    matrix.m[2][2] = m.m[2][2];
    matrix.m[2][3] = 0.0f;

    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    matrix.m[3][3] = 1.0f;
    return matrix;
}
