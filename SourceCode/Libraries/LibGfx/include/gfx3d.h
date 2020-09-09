//
// Created by XingfengYang on 2020/7/7.
//

#ifndef __LIBRARY_LIBGFX_GL3D_H__
#define __LIBRARY_LIBGFX_GL3D_H__

#include <gfxm.h>
#include <kvector.h>
#include <stdint.h>

#define GL_CONSTANT_ATTENUATION 1.0f
#define GL_LINEAR_ATTENUATION 0
#define GL_QUADRATIC_ATTENUATION 0

typedef struct Triangle {
    Vec3D p[3];
    uint32_t color;
    ListNode* node;
} Triangle;

typedef struct Mesh {
    KernelVector tris;
} Mesh;

Vec3D gfx3d_get_specular_color_shiness(Vec3D mspec, Vec3D sspec, Vec3D normal, Vec3D light, float shiness);

Vec3D gfx3d_get_specular_color(Vec3D mspec, Vec3D sspec, float lum);

Vec3D gfx3d_get_diffuse_color(Vec3D mdiff, Vec3D sdiff, Vec3D normal, Vec3D light);

Vec3D gfx3d_get_ambient_color(Vec3D mamb, Vec3D gamb);

uint32_t gfx3d_get_lum_color(uint32_t color, float lum);

float gfx3d_get_attenuation_factor(float d);

Vec3D gfx3d_vertex3f(float x, float y, float z);

uint32_t gfx3d_color3i(uint32_t r, uint32_t g, uint32_t b);

Vec3D gfx3d_color3f(float r, float g, float b);

Vec3D gfx3d_color1i2v(uint32_t color);

uint32_t gfx3d_colorv21i(Vec3D color);

Mat4x4 gfx3d_matrix_make_identity();

Mat4x4 gfx3d_matrix_make_rotationX(float angle);

Mat4x4 gfx3d_matrix_make_rotationY(float angle);

Mat4x4 gfx3d_matrix_make_rotationZ(float angle);

Mat4x4 gfx3d_matrix_make_translation(float x, float y, float z);

Mat4x4 gfx3d_matrix_make_projection(float fovDegree, float aspectRatio, float near, float far);

Mat4x4 gfx3d_matrix_point_at(Vec3D* pos, Vec3D* target, Vec3D* up);

Vec3D gfx3d_vector_intersect_plane(Vec3D* plane_p, Vec3D* plane_n, Vec3D* lineStart, Vec3D* lineEnd);

int gfx3d_triangle_clip_against_plane(Vec3D plane_p, Vec3D plane_n, Triangle* in_tri, Triangle* out_tri1,
    Triangle* out_tri2);

#endif //__LIBRARY_LIBGFX_GL3D_H__
