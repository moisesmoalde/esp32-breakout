#ifndef INCLUDE_UTILS
#define INCLUDE_UTILS

/**
 * @struct Vector
 * @brief 2D vector with float components.
 */
typedef struct {
  float x, y;
} Vector;

/**
 * @brief Computes dot product of two vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product.
 */
float dot_product(Vector v1, Vector v2);

/**
 * @brief Subtracts v2 from v1.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Result vector.
 */
Vector v_diff(Vector v1, Vector v2);

/**
 * @brief Scales a vector by a scalar.
 * @param v Vector to scale.
 * @param k Scalar.
 * @return Scaled vector.
 */
Vector v_scale(Vector v, float k);

/**
 * @brief Finds closest point on rectangle to a point.
 * @param v1 Point.
 * @param p_rect Rectangle position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Closest point vector.
 */
Vector v_closest_rect(Vector v1, Vector p_rect, int8_t width, int8_t height);

/**
 * @brief Squared magnitude of a vector.
 * @param v Vector.
 * @return Squared length.
 */
float modulo_sq(Vector v);

/**
 * @brief Squared distance between two points.
 * @param v1 First point.
 * @param v2 Second point.
 * @return Squared distance.
 */
float dist_sq(Vector v1, Vector v2);

#endif