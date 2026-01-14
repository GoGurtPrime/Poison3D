#pragma once

#include "compiler.h"
#include "vector3.h"
#include "vector4.h"

typedef HEADER_ALIGN(16) struct Transform {
    Vector3 position;
    Vector4 rotation;
    Vector3 scale;
} FOOTER_ALIGN(16) Transform;
