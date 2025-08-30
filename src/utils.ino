/**
 * @file utils.ino
 * @brief Implementation of vector utility functions.
 */

#include "utils.h"

float dot_product(Vector v1, Vector v2) {
  return (v1.x * v2.x + v1.y * v2.y);
}

Vector v_diff(Vector v1, Vector v2) {
  Vector v = {v1.x - v2.x, v1.y - v2.y};
  return v;
}

Vector v_scale(Vector v, float k) {
  Vector scaled = {k * v.x, k * v.y};
  return scaled;
}

Vector v_closest_rect(Vector v1, Vector p_rect, int8_t width, int8_t height) {
  float closest_x = max(p_rect.x, min(v1.x, p_rect.x + width));
  float closest_y = max(p_rect.y, min(v1.y, p_rect.y + height));
  Vector v_closest = {closest_x, closest_y};
  return v_closest;
}

float modulo_sq(Vector v) {
  return dot_product(v, v);
}

float dist_sq(Vector v1, Vector v2) {
  return modulo_sq(v_diff(v1, v2));
}