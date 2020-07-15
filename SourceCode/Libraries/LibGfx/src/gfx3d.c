//
// Created by XingfengYang on 2020/7/7.
//

#include <gfx3d.h>
#include <math.h>

Vec3D gfx3d_vertex3f(float x, float y, float z) {
  Vec3D vec;
  vec.x = x;
  vec.y = y;
  vec.z = z;
  return vec;
}

uint32_t gfx3d_color3i(uint32_t r, uint32_t g, uint32_t b) {
  if (r >= 0xFF) {
    r = 0xFF;
  }
  if (g >= 0xFF) {
    g = 0xFF;
  }
  if (b >= 0xFF) {
    b = 0xFF;
  }
  return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

Vec3D gfx3d_color3f(float r, float g, float b) {
  Vec3D vec;
  vec.x = fmod(r, 1.0f);
  vec.y = fmod(g, 1.0f);
  vec.z = fmod(b, 1.0f);
  return vec;
}

Vec3D gfx3d_color1i2v(uint32_t color) {
  Vec3D col;
  col.x = ((float)((color >> 24) & 0xFF) / 255.0f);
  col.y = ((float)((color >> 16) & 0xFF) / 255.0f);
  col.z = ((float)((color >> 8) & 0xFF) / 255.0f);
  return col;
}

uint32_t gfx3d_colorv21i(Vec3D color) {
  return gfx3d_color3i((uint32_t)(color.x * 255.0f), (uint32_t)(color.y * 255.0f), (uint32_t)(color.z * 255.0f));
}

Mat4x4 gfx3d_matrix_make_identity() {
  Mat4x4 mat;
  mat.m[0][0] = 1.0f;
  mat.m[1][1] = 1.0f;
  mat.m[2][2] = 1.0f;
  mat.m[3][3] = 1.0f;
  return mat;
}

Mat4x4 gfx3d_matrix_make_rotationX(float angle) {
  Mat4x4 matrix;
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = cosf(angle);
  matrix.m[1][2] = sinf(angle);
  matrix.m[2][1] = -sinf(angle);
  matrix.m[2][2] = cosf(angle);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Mat4x4 gfx3d_matrix_make_rotationY(float angle) {
  Mat4x4 matrix;
  matrix.m[0][0] = cosf(angle);
  matrix.m[0][2] = sinf(angle);
  matrix.m[2][0] = -sinf(angle);
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = cosf(angle);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Mat4x4 gfx3d_matrix_make_rotationZ(float angle) {
  Mat4x4 matrix;
  matrix.m[0][0] = cosf(angle);
  matrix.m[0][1] = sinf(angle);
  matrix.m[1][0] = -sinf(angle);
  matrix.m[1][1] = cosf(angle);
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Mat4x4 gfx3d_matrix_make_translation(float x, float y, float z) {
  Mat4x4 matrix;
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  matrix.m[3][0] = x;
  matrix.m[3][1] = y;
  matrix.m[3][2] = z;
  return matrix;
}

Mat4x4 gfx3d_matrix_make_projection(float fovDegree, float aspectRatio, float near, float far) {
  float fFovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f);
  Mat4x4 matrix;
  matrix.m[0][0] = aspectRatio * fFovRad;
  matrix.m[1][1] = fFovRad;
  matrix.m[2][2] = far / (far - near);
  matrix.m[3][2] = (-far * near) / (far - near);
  matrix.m[2][3] = 1.0f;
  matrix.m[3][3] = 0.0f;
  return matrix;
}

Mat4x4 gfx3d_matrix_point_at(Vec3D *pos, Vec3D *target, Vec3D *up) {
  // caculate new forward direction
  Vec3D newForward = gfxm_vector_sub(*target, *pos);
  newForward = gfxm_vector_normalise(newForward);

  // caculate new up direction
  Vec3D a = gfxm_vector_mul(newForward, gfxm_vector_dot_product(*up, newForward));
  Vec3D newUp = gfxm_vector_sub(*up, a);
  newUp = gfxm_vector_normalise(newUp);

  // New Right direction is easy, its just cross product
  Vec3D newRight = gfxm_vector_cross_product(newUp, newForward);

  // Construct Dimensioning and Translation Matrix
  Mat4x4 matrix;
  matrix.m[0][0] = newRight.x;
  matrix.m[0][1] = newRight.y;
  matrix.m[0][2] = newRight.z;
  matrix.m[0][3] = 0.0f;
  matrix.m[1][0] = newUp.x;
  matrix.m[1][1] = newUp.y;
  matrix.m[1][2] = newUp.z;
  matrix.m[1][3] = 0.0f;
  matrix.m[2][0] = newForward.x;
  matrix.m[2][1] = newForward.y;
  matrix.m[2][2] = newForward.z;
  matrix.m[2][3] = 0.0f;
  matrix.m[3][0] = pos->x;
  matrix.m[3][1] = pos->y;
  matrix.m[3][2] = pos->z;
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Vec3D gfx3d_vector_intersect_plane(Vec3D *plane_p, Vec3D *plane_n, Vec3D *lineStart, Vec3D *lineEnd) {
  *plane_n = gfxm_vector_normalise(*plane_n);
  float plane_d = -gfxm_vector_dot_product(*plane_n, *plane_p);
  float ad = gfxm_vector_dot_product(*lineStart, *plane_n);
  float bd = gfxm_vector_dot_product(*lineEnd, *plane_n);
  float t = (-plane_d - ad) / (bd - ad);
  Vec3D lineStartToEnd = gfxm_vector_sub(*lineEnd, *lineStart);
  Vec3D lineToIntersect = gfxm_vector_mul(lineStartToEnd, t);
  return gfxm_vector_add(*lineStart, lineToIntersect);
}

float dist(Vec3D plane_p, Vec3D plane_n, Vec3D *p) {
  Vec3D n = gfxm_vector_normalise(*p);
  return (plane_n.x * p->x + plane_n.y * p->y + plane_n.z * p->z - gfxm_vector_dot_product(plane_n, plane_p));
}

int gfx3d_triangle_clip_against_plane(Vec3D plane_p, Vec3D plane_n, Triangle *in_tri, Triangle *out_tri1,
                                      Triangle *out_tri2) {
  plane_n = gfxm_vector_normalise(plane_n);

  Vec3D *inside_points[3];
  int nInsidePointCount = 0;
  Vec3D *outside_points[3];
  int nOutsidePointCount = 0;

  float d0 = dist(plane_p, plane_n, &in_tri->p[0]);
  float d1 = dist(plane_p, plane_n, &in_tri->p[1]);
  float d2 = dist(plane_p, plane_n, &in_tri->p[2]);

  if (d0 >= 0) {
    inside_points[nInsidePointCount++] = &in_tri->p[0];
  } else {
    outside_points[nOutsidePointCount++] = &in_tri->p[0];
  }
  if (d1 >= 0) {
    inside_points[nInsidePointCount++] = &in_tri->p[1];
  } else {
    outside_points[nOutsidePointCount++] = &in_tri->p[1];
  }
  if (d2 >= 0) {
    inside_points[nInsidePointCount++] = &in_tri->p[2];
  } else {
    outside_points[nOutsidePointCount++] = &in_tri->p[2];
  }

  if (nInsidePointCount == 0) {
    return 0; // No returned triangles are valid
  }

  if (nInsidePointCount == 3) {
    out_tri1 = in_tri;

    return 1; // Just the one returned original triangle is valid
  }

  if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
    out_tri1->color = in_tri->color;

    out_tri1->p[0] = *inside_points[0];

    out_tri1->p[1] = gfx3d_vector_intersect_plane(&plane_p, &plane_n, inside_points[0], outside_points[0]);
    out_tri1->p[2] = gfx3d_vector_intersect_plane(&plane_p, &plane_n, inside_points[0], outside_points[1]);

    return 1; // Return the newly formed single triangle
  }

  if (nInsidePointCount == 2 && nOutsidePointCount == 1) {

    // Copy appearance info to new triangles
    out_tri1->color = in_tri->color;

    out_tri2->color = in_tri->color;

    // intersects with the plane
    out_tri1->p[0] = *inside_points[0];
    out_tri1->p[1] = *inside_points[1];
    out_tri1->p[2] = gfx3d_vector_intersect_plane(&plane_p, &plane_n, inside_points[0], outside_points[0]);

    out_tri2->p[0] = *inside_points[1];
    out_tri2->p[1] = out_tri1->p[2];
    out_tri2->p[2] = gfx3d_vector_intersect_plane(&plane_p, &plane_n, inside_points[1], outside_points[0]);

    return 2; // Return two newly formed triangles which form a quad
  }
}

uint32_t gfx3d_get_lum_color(uint32_t color, float lum) {
  // liner light, color_vec * (n.l)
  uint32_t r = (uint32_t)(((color >> 24) & 0xFF) * lum);
  uint32_t g = (uint32_t)(((color >> 16) & 0xFF) * lum);
  uint32_t b = (uint32_t)(((color >> 8) & 0xFF) * lum);
  uint32_t a = (uint32_t)(((color >> 0) & 0xFF) * lum);

  return (uint32_t)(r << 24 | g << 16 | b << 8 | a << 0);
}

Vec3D gfx3d_get_specular_color(Vec3D mspec, Vec3D sspec, float lum) {
  Vec3D color = gfxm_vector_mul_vector(mspec, sspec);
  Vec3D result = gfxm_vector_mul(color, fmax(0.0f, lum));
  return result;
}

// specular=Ks∗lightColor∗(max(dot(N,R)),0)^shininess
// R=2∗(N·L)∗N−L
Vec3D gfx3d_get_specular_color_shiness(Vec3D mspec, Vec3D sspec, Vec3D normal, Vec3D light, float shiness) {
  float lum = gfxm_vector_dot_product(normal, light);
  Vec3D R1 = gfxm_vector_mul(normal, 2.0f * lum);
  Vec3D R = gfxm_vector_sub(R1, light);
  lum = gfxm_vector_dot_product(normal, R);
  return gfx3d_get_specular_color(mspec, sspec, powf(lum, shiness));
}

// diffuse=Kd∗lightColor∗max(dot(N,L),0)
Vec3D gfx3d_get_diffuse_color(Vec3D mdiff, Vec3D sdiff, Vec3D normal, Vec3D light) {
  float cos = gfxm_vector_dot_product(normal, light);
  Vec3D color = gfxm_vector_mul_vector(mdiff, sdiff);
  Vec3D result = gfxm_vector_mul(color, fmax(0.0f, cos));

  return result;
}

// ambient=Ka∗globalAmbient
Vec3D gfx3d_get_ambient_color(Vec3D mamb, Vec3D gamb) {
  Vec3D color = gfxm_vector_mul_vector(mamb, gamb);
  return color;
}

float gfx3d_get_attenuation_factor(float d) {
  return 1.0f / (GL_CONSTANT_ATTENUATION + GL_LINEAR_ATTENUATION * d + GL_QUADRATIC_ATTENUATION * d * d);
}
