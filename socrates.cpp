#include "socrates.h"

#include <cmath>

namespace soc { // Start of soc

// Matrix3 functions
///////////////////////////////////////////////////////////////
SOC_INLINE const float32 mat3_det(const Matrix3& m);
SOC_INLINE const Matrix3 mat3_transpose(const Matrix3& m);
SOC_INLINE const Matrix3 mat3_inverse(const Matrix3& m);
SOC_INLINE const Matrix3 mat3_rotate(const Vector3& axis, const float32 angle);
SOC_INLINE const Matrix3 mat3_scale(const Vector3& axis, const float32 scale);
SOC_INLINE const Matrix3 mat3_reflect(const Vector3& point);
SOC_INLINE const Matrix3 mat3_skew(const Vector3& axis, const Vector3& direction, const float32 scale);
///////////////////////////////////////////////////////////////

// Matrix4 functions 
///////////////////////////////////////////////////////////////
SOC_INLINE const float32 mat4_det(const Matrix4& m);
SOC_INLINE const Matrix4 mat4_transpose(const Matrix4& m);
SOC_INLINE const Matrix4 mat4_inverse(const Matrix4& m);
SOC_INLINE const Matrix4 mat4_translate(const Vector3& position);
SOC_INLINE const Matrix4 mat4_rotate(const Vector3& axis, const float32 angle);
SOC_INLINE const Matrix4 mat4_scale(const Vector3& axis, const float32 scale);
///////////////////////////////////////////////////////////////

} // End of soc
