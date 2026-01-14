#pragma once
#include <math.h>

typedef union Vector3 {
    struct {
        float x, y, z;
    };

    float components[3];
} Vector3;

const Vector3 VECTOR3_ZERO = (Vector3) {0, 0, 0};

typedef float (*FloatOperation)(float);

static inline Vector3 vector3_add(Vector3 vector1, Vector3 vector2) {
    return (Vector3){ 
        vector1.x + vector2.x,
        vector1.y + vector2.y,
        vector1.z + vector2.z  
    };
}

static inline Vector3 vector3_subtract(Vector3 vector1, Vector3 vector2) {
    return (Vector3) {
        vector1.x - vector2.x,
        vector1.y - vector2.y,
        vector1.z - vector2.z
    };
}

static inline Vector3 vector3_multiply(Vector3 vector1, Vector3 vector2) {
    return (Vector3) {
        vector1.x * vector2.x,
        vector1.y * vector2.y,
        vector1.z * vector2.z
    };
}

static inline Vector3 vector3_cross(Vector3 vector1, Vector3 vector2) {
    return (Vector3) {
        (vector1.y * vector2.z) - (vector2.z * vector2.y),
        (vector1.z * vector2.x) - (vector2.x * vector2.z),
        (vector1.x * vector2.y) - (vector2.y * vector2.x)
    }
}

static inline float vector3_magnitude_square(Vector3 vector) {
    return (vector.x * vector.x) +
           (vector.y * vector.y) + 
           (vector.z * vector.z);
}

static inline Vector3 vector3_normalize(Vector3 vector) {
    float magsq = vector3_magnitude_square(vector);

    if (magsq < 0.000001f) {
        return (Vector3){0, 0, 0};
    }

    float inverseMagnitude = 1.0f / sqrtf(magsq);

    return (Vector3) {
        vector.x * inverseMagnitude,
        vector.y * inverseMagnitude,
        vector.z * inverseMagnitude
    }
}

static inline float vector3_dot(Vector3 vector1, Vector3 vector2) {
    return (vector1.x * vector2.x) +
           (vector1.y * vector2.y) +
           (vector1.z * vector2.z);
}

float vector3_length_sqrd(Vector3 vector);

float vector3_magnitude(Vector3 vector);

float vector3_distance(Vector3 vector1, Vector3 vector2);

/// @brief Applies an operation to each element of a Vector3
/// @param vector The vector to apply an operation to.
/// @param operation The float operation to apply to each element.
/// @return Modified Vector3
Vector3 vector3_apply_operation(Vector3 vector, FloatOperation operation);
