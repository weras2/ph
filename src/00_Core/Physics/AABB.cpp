#include "Physics/AABB.hpp"

ARM bool AABB::func_ov000_0208e680() {
    return max.x >= min.x && max.y >= min.y && max.z >= min.z;
}

ARM void AABB::GetCenter(Vec3p *center) {
    center->x = (min.x + max.x) >> 1;
    center->y = (min.y + max.y) >> 1;
    center->z = (min.z + max.z) >> 1;
}

ARM q20 AABB::GetSizeX() {
    return ABS(max.x - min.x);
}

ARM q20 AABB::GetSizeZ() {
    return ABS(max.z - min.z);
}

ARM q20 AABB::GetSizeY() {
    return ABS(max.y - min.y);
}

ARM bool AABB::Contains(Vec3p *vec) {
    bool result     = false;
    bool aboveMin   = false;
    bool aboveMinXY = false;
    if (vec->x >= min.x && vec->y >= min.y) {
        aboveMinXY = true;
    }
    if (aboveMinXY && vec->z >= min.z) {
        aboveMin = true;
    }
    if (aboveMin && vec->x < max.x && vec->y < max.y && vec->z < max.z) {
        result = true;
    }
    return result;
}

ARM bool AABB::ContainsInXZ(Vec3p *vec) {
    if (vec->x >= min.x && vec->x < max.x && vec->z >= min.z && vec->z < max.z) {
        return true;
    }
    return false;
}

ARM bool AABB::ContainsInXY(Vec3p *vec) {
    if (vec->x >= min.x && vec->x < max.x && vec->y >= min.y && vec->y < max.y) {
        return true;
    }
    return false;
}

ARM bool AABB::IntersectsCube(Cube *cube) {
    q20 size = cube->size;
    Vec3p radius;
    radius.x = size;
    radius.y = size;
    radius.z = size;
    AABB grown;
    Vec3p_Sub(&min, &radius, &grown.min);
    Vec3p_Add(&max, &radius, &grown.max);
    return grown.Contains(&cube->center);
}

ARM bool AABB::func_ov000_0208e87c(Cube *cube, Vec3p *vec, u32 *out) {
    AABB box = *this;
    box.GrowScalar(cube->size);

    Vec3p backNormal;
    backNormal.x = 0;
    backNormal.y = 0;
    backNormal.z = -FLOAT_TO_Q20(1.0);
    if (Vec3p_Dot(vec, &backNormal) > 0) {
        q20 t = CoDivide64By32(box.max.z - cube->center.z, vec->z);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 x = cube->center.x + MUL_Q20(t, vec->x);
            q20 y = cube->center.y + MUL_Q20(t, vec->y);
            if (box.min.x <= x && x < box.max.x && box.min.y <= y && y < box.max.y) {
                *out = t;
                return true;
            }
        }
    }

    Vec3p frontNormal;
    frontNormal.x = 0;
    frontNormal.y = 0;
    frontNormal.z = FLOAT_TO_Q20(1.0);
    if (Vec3p_Dot(vec, &frontNormal) > 0) {
        q20 t = CoDivide64By32(box.min.z - cube->center.z, vec->z);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 x = cube->center.x + MUL_Q20(t, vec->x);
            q20 y = cube->center.y + MUL_Q20(t, vec->y);
            if (box.min.x <= x && x < box.max.x && box.min.y <= y && y < box.max.y) {
                *out = t;
                return true;
            }
        }
    }

    Vec3p rightNormal;
    rightNormal.x = -FLOAT_TO_Q20(1.0);
    rightNormal.y = 0;
    rightNormal.z = 0;
    if (Vec3p_Dot(vec, &rightNormal) > 0) {
        q20 t = CoDivide64By32(box.max.x - cube->center.x, vec->x);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 z = cube->center.z + MUL_Q20(t, vec->z);
            q20 y = cube->center.y + MUL_Q20(t, vec->y);
            if (box.min.z <= z && z < box.max.z && box.min.y <= y && y < box.max.y) {
                *out = t;
                return true;
            }
        }
    }

    Vec3p leftNormal;
    leftNormal.x = FLOAT_TO_Q20(1.0);
    leftNormal.y = 0;
    leftNormal.z = 0;
    if (Vec3p_Dot(vec, &leftNormal) > 0) {
        q20 t = CoDivide64By32(box.min.x - cube->center.x, vec->x);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 z = cube->center.z + MUL_Q20(t, vec->z);
            q20 y = cube->center.y + MUL_Q20(t, vec->y);
            if (box.min.z <= z && z < box.max.z && box.min.y <= y && y < box.max.y) {
                *out = t;
                return true;
            }
        }
    }

    Vec3p topNormal;
    topNormal.x = 0;
    topNormal.y = -FLOAT_TO_Q20(1.0);
    topNormal.z = 0;
    if (Vec3p_Dot(vec, &topNormal) > 0) {
        q20 t = CoDivide64By32(box.max.y - cube->center.y, vec->y);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 x = cube->center.x + MUL_Q20(t, vec->x);
            q20 z = cube->center.z + MUL_Q20(t, vec->z);
            if (box.min.x <= x && x < box.max.x && box.min.z <= z && z < box.max.z) {
                *out = t;
                return true;
            }
        }
    }

    Vec3p bottomNormal;
    bottomNormal.x = 0;
    bottomNormal.y = FLOAT_TO_Q20(1.0);
    bottomNormal.z = 0;
    if (Vec3p_Dot(vec, &bottomNormal) > 0) {
        q20 t = CoDivide64By32(box.min.y - cube->center.y, vec->y);
        if (t >= 0 && t <= FLOAT_TO_Q20(1.0)) {
            q20 x = cube->center.x + MUL_Q20(t, vec->x);
            q20 z = cube->center.z + MUL_Q20(t, vec->z);
            if (box.min.x <= x && x < box.max.x && box.min.z <= z && z < box.max.z) {
                *out = t;
                return true;
            }
        }
    }
    return false;
}

ARM void AABB::GrowToPoint(Vec3p *point) {
    if (min.x >= point->x) {
        min.x = point->x;
    }
    if (min.y >= point->y) {
        min.y = point->y;
    }
    if (min.z >= point->z) {
        min.z = point->z;
    }
    if (max.x <= point->x) {
        max.x = point->x;
    }
    if (max.y <= point->y) {
        max.y = point->y;
    }
    if (max.z <= point->z) {
        max.z = point->z;
    }
}

ARM void AABB::Grow(Vec3p *dimensions) {
    Vec3p_Sub(&min, dimensions, &min);
    Vec3p_Add(&max, dimensions, &max);
}

ARM void AABB::GrowScalar(q20 amount) {
    Vec3p lower;
    lower.x = amount;
    lower.y = amount;
    lower.z = amount;
    Vec3p_Sub(&min, &lower, &min);
    Vec3p upper;
    upper.x = amount;
    upper.y = amount;
    upper.z = amount;
    Vec3p_Add(&max, &upper, &max);
}
