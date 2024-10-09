#pragma once

namespace soc { // Start of soc

// Typedefs
///////////////////////////////////////////////////////////////
typedef char  int8;
typedef short int16; 
typedef int   int32; 
typedef long  int64;

typedef unsigned char  uint8;
typedef unsigned short uint16; 
typedef unsigned int   uint32; 
typedef unsigned long  uint64;

typedef float  float32;
typedef double float64;
///////////////////////////////////////////////////////////////

// Platform defines
///////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#define SOC_INLINE   __forceinline 
#define SOC_NOINLINE __declspec(noinline)
#else 
#define SOC_INLINE   inline 
#define SOC_NOINLINE 
#endif
///////////////////////////////////////////////////////////////

// Defines
///////////////////////////////////////////////////////////////
#define SOC_PI          3.14159265359
#define SOC_RAD2DEG (180.0f / SOC_PI)
#define SOC_DEG2RAD (SOC_PI / 180.0f)
///////////////////////////////////////////////////////////////

// Socrates types
///////////////////////////////////////////////////////////////

// Two component vector
union Vector2 {
  struct {
    float32 x, r, u; 
    float32 y, g, v;
  };
  
  // Default CTOR
  Vector2() {
    x = 0.0f; 
    y = 0.0f;
  }

  // Takes the `x` and `y` components of the vector 
  Vector2(float32 x, float32 y) 
    :x(x), y(y)
  {}

  // Fils all of the components with the given value 
  Vector2(float32 s)
    :x(s), y(s) 
  {}
};

// Three component vector
union Vector3 {
  struct {
    float32 x, r, u; 
    float32 y, g, v;
    float32 z, b, w;
  };
  
  // Default CTOR
  Vector3() {
    x = 0.0f; 
    y = 0.0f; 
    z = 0.0f;
  } 

  // Takes the `x`, `y`, and `z` components of the vector 
  Vector3(float32 x, float32 y, float32 z) 
    :x(x), y(y), z(z)
  {}

  // Takes a `Vector2` to fill the `x` and `y` components and also a `z` component
  Vector3(const Vector2& v, float32 z) 
    :x(v.x), y(v.y), z(z)
  {}
  
  // Fils all of the components with the given value 
  Vector3(float32 s)
    :x(s), y(s), z(s) 
  {}
};

// Four component vector 
union Vector4 {
  struct {
    float32 x, r; 
    float32 y, g;
    float32 z, b;
    float32 w, a;
  };
  
  // Default CTOR
  Vector4() {
    x = 0.0f; 
    y = 0.0f; 
    z = 0.0f; 
    w = 0.0f;
  }

  // Takes the `x`, `y`, `z`, and `w` components of the vector 
  Vector4(float32 x, float32 y, float32 z, float32 w) 
    :x(x), y(y), z(z), w(w)
  {}
  
  // Takes a `Vector3` to fill the `x`, `y`, `w` components and also the `w` component
  Vector4(const Vector3& v, float32 w) 
    :x(v.x), y(v.y), z(v.z), w(w)
  {}
  
  // Fils all of the components with the given value 
  Vector4(float32 s)
    :x(s), y(s), z(s), w(s) 
  {}
};

// A 3x3 matrix 
struct Matrix3 {
  // Entries
  float32 data[9];

  // Default CTOR where the matrix gets initialized as an identity matrix
  Matrix3() {
    data[0] = 1; data[1] = 0; data[2] = 0;
    data[3] = 0; data[4] = 1; data[5] = 0;
    data[6] = 0; data[7] = 0; data[8] = 1;
  }

  // Takes in every single entry for the matrix
  Matrix3(float32 m0, float32 m1, float32 m2,
          float32 m3, float32 m4, float32 m5,
          float32 m6, float32 m7, float32 m8) {
    data[0] = m0; data[1] = m1; data[2] = m2;
    data[3] = m3; data[4] = m4; data[5] = m5;
    data[6] = m6; data[7] = m7; data[8] = m8;
  }

  // Takes in an array of floats and fills the entries of the matrix 
  // NOTE: The constructor does not check if the array of values given 
  // is valid or has the same size as the matrix. 
  Matrix3(float32* values) {
    for(uint8 i = 0; i < 9; i++) {
      data[i] = values[i];
    }
  }

  // Takes the scalar and sets all entries to this scalar
  Matrix3(float32 scalar) {
    data[0] = scalar; data[1] = scalar; data[2] = scalar;
    data[3] = scalar; data[4] = scalar; data[5] = scalar;
    data[6] = scalar; data[7] = scalar; data[8] = scalar;
  }
  
  float32 operator[](const uint32 index) {
    if(index > 9 || index < 0) {
      return 0.0f;
    }

    return data[index];
  }

  float32 operator[](const uint32 index) const {
    if(index > 9 || index < 0) {
      return 0.0f;
    }

    return data[index];
  }
};

// A 4x4 matrix
union Matrix4 {
  // Entries
  float32 data[16]; 
  
  // Default CTOR where the matrix gets initialized as an identity matrix
  Matrix4() {
    data[0]  = 1; data[1]  = 0; data[2]  = 0; data[3]  = 0;
    data[4]  = 0; data[5]  = 1; data[6]  = 0; data[7]  = 0;
    data[8]  = 0; data[9]  = 0; data[10] = 1; data[11] = 0;
    data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
  }

  // Takes in every single entry for the matrix
  Matrix4(float32 m0, float32 m1, float32 m2, float32 m3,
          float32 m4, float32 m5, float32 m6, float32 m7,
          float32 m8, float32 m9, float32 m10, float32 m11,
          float32 m12, float32 m13, float32 m14, float32 m15) {
    data[0]  = m0;  data[1]  = m1;  data[2]  = m2;  data[3]  = m3; 
    data[4]  = m4;  data[5]  = m5;  data[6]  = m6;  data[7]  = m7; 
    data[8]  = m8;  data[9]  = m9;  data[10] = m10; data[11] = m11; 
    data[12] = m12; data[13] = m13; data[14] = m14; data[15] = m15; 
  }

  // Takes in an array of floats and fills the entries of the matrix 
  // NOTE: The constructor does not check if the array of values given 
  // is valid or has the same size as the matrix. 
  Matrix4(float32* values) {
    for(uint8 i = 0; i < 16; i++) {
      data[i] = values[i];
    }
  }

  // Takes the scalar and sets all entries to this scalar
  Matrix4(float32 scalar) {
    data[0]  = scalar; data[1]  = scalar; data[2]  = scalar; data[3]  = scalar;
    data[4]  = scalar; data[5]  = scalar; data[6]  = scalar; data[7]  = scalar;
    data[8]  = scalar; data[9]  = scalar; data[10] = scalar; data[11] = scalar;
    data[12] = scalar; data[13] = scalar; data[14] = scalar; data[15] = scalar;
  }
  
  float32 operator[](const uint32 index) {
    if(index > 16 || index < 0) {
      return 0.0f;
    }

    return data[index];
  }
  
  float32 operator[](const uint32 index) const {
    if(index > 16 || index < 0) {
      return 0.0f;
    }

    return data[index];
  }
};

///////////////////////////////////////////////////////////////

// Vector2 operator overloading
///////////////////////////////////////////////////////////////
SOC_INLINE Vector2 operator+(const Vector2& v1, const Vector2& v2) {
  return Vector2(v1.x + v2.x, v1.y + v2.y);
}

SOC_INLINE Vector2 operator+(const Vector2& v, const float32& s) {
  return Vector2(v.x + s, v.y + s);
}

SOC_INLINE Vector2 operator-(const Vector2& v1, const Vector2& v2) {
  return Vector2(v1.x - v2.x, v1.y - v2.y);
}

SOC_INLINE Vector2 operator-(const Vector2& v, const float32& s) {
  return Vector2(v.x - s, v.y - s);
}

SOC_INLINE Vector2 operator*(const Vector2& v1, const Vector2& v2) {
  return Vector2(v1.x * v2.x, v1.y * v2.y);
}

SOC_INLINE Vector2 operator*(const Vector2& v, const float32& s) {
  return Vector2(v.x * s, v.y * s);
}

SOC_INLINE Vector2 operator/(const Vector2& v1, const Vector2& v2) {
  return Vector2(v1.x / v2.x, v1.y / v2.y);
}

SOC_INLINE Vector2 operator/(const Vector2& v, const float32& s) {
  return Vector2(v.x / s, v.y / s);
}

SOC_INLINE void operator+=(Vector2& v1, const Vector2& v2) {
  v1 = v1 + v2;
}

SOC_INLINE void operator+=(Vector2& v, const float32& s) {
  v = v + s;
}

SOC_INLINE void operator-=(Vector2& v1, const Vector2& v2) {
  v1 = v1 - v2;
}

SOC_INLINE void operator-=(Vector2& v, const float32& s) {
  v = v - s;
}

SOC_INLINE void operator*=(Vector2& v1, const Vector2& v2) {
  v1 = v1 * v2;
}

SOC_INLINE void operator*=(Vector2& v, const float32& s) {
  v = v * s;
}

SOC_INLINE void operator/=(Vector2& v1, const Vector2& v2) {
  v1 = v1 / v2;
}

SOC_INLINE void operator/=(Vector2& v, const float32& s) {
  v = v / s;
}

SOC_INLINE Vector2 operator-(const Vector2& v) {
  return Vector2(-v.x, -v.y);
}
///////////////////////////////////////////////////////////////

// Vector3 operator overloading
///////////////////////////////////////////////////////////////
SOC_INLINE Vector3 operator+(const Vector3& v1, const Vector3& v2) {
  return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

SOC_INLINE Vector3 operator+(const Vector3& v, const float32 s) {
  return Vector3(v.x + s, v.y + s, v.z + s);
}

SOC_INLINE Vector3 operator-(const Vector3& v1, const Vector3& v2) {
  return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

SOC_INLINE Vector3 operator-(const Vector3& v, const float32 s) {
  return Vector3(v.x - s, v.y - s, v.z - s);
}

SOC_INLINE Vector3 operator*(const Vector3& v1, const Vector3& v2) {
  return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

SOC_INLINE Vector3 operator*(const Vector3& v, const float32 s) {
  return Vector3(v.x * s, v.y * s, v.z * s);
}

SOC_INLINE Vector3 operator*(const Vector3& v, const Matrix3& m) {
  return Vector3((v.x * m[0]) + (v.y * m[1]) + (v.z * m[2]), 
                 (v.x * m[3]) + (v.y * m[4]) + (v.z * m[5]), 
                 (v.x * m[6]) + (v.y * m[7]) + (v.z * m[8]));
}

SOC_INLINE Vector3 operator/(const Vector3& v1, const Vector3& v2) {
  return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

SOC_INLINE Vector3 operator/(const Vector3& v, const float32 s) {
  return Vector3(v.x / s, v.y / s, v.z / s);
}

SOC_INLINE void operator+=(Vector3& v1, const Vector3& v2) {
  v1 = v1 + v2;
}

SOC_INLINE void operator+=(Vector3& v, const float32& s) {
  v = v + s;
}

SOC_INLINE void operator-=(Vector3& v1, const Vector3& v2) {
  v1 = v1 - v2;
}

SOC_INLINE void operator-=(Vector3& v, const float32& s) {
  v = v - s;
}

SOC_INLINE void operator*=(Vector3& v1, const Vector3& v2) {
  v1 = v1 * v2;
}

SOC_INLINE void operator*=(Vector3& v, const float32& s) {
  v = v * s;
}

SOC_INLINE void operator/=(Vector3& v1, const Vector3& v2) {
  v1 = v1 / v2;
}

SOC_INLINE void operator/=(Vector3& v, const float32& s) {
  v = v / s;
}

SOC_INLINE Vector3 operator-(const Vector3& v) {
  return Vector3(-v.x, -v.y, -v.z);
}
///////////////////////////////////////////////////////////////

// Vector4 operator overloading
///////////////////////////////////////////////////////////////
SOC_INLINE Vector4 operator+(const Vector4& v1, const Vector4& v2) {
  return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

SOC_INLINE Vector4 operator+(const Vector4& v, const float32 s) {
  return Vector4(v.x + s, v.y + s, v.z + s, v.w + s);
}

SOC_INLINE Vector4 operator-(const Vector4& v1, const Vector4& v2) {
  return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

SOC_INLINE Vector4 operator-(const Vector4& v, const float32 s) {
  return Vector4(v.x - s, v.y - s, v.z - s, v.w - s);
}

SOC_INLINE Vector4 operator*(const Vector4& v1, const Vector4& v2) {
  return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

SOC_INLINE Vector4 operator*(const Vector4& v, const float32 s) {
  return Vector4(v.x * s, v.y * s, v.z * s, v.w * s);
}

SOC_INLINE Vector4 operator*(const Vector4& v, const Matrix4& m) {
  return Vector4((v.x * m[0])  + (v.y * m[1])  + (v.z * m[2])  + (v.w * m[3]), 
                 (v.x * m[4])  + (v.y * m[5])  + (v.z * m[6])  + (v.w * m[7]), 
                 (v.x * m[8])  + (v.y * m[9])  + (v.z * m[10]) + (v.w * m[11]), 
                 (v.x * m[12]) + (v.y * m[13]) + (v.z * m[14]) + (v.w * m[15]));
}

SOC_INLINE Vector4 operator/(const Vector4& v1, const Vector4& v2) {
  return Vector4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

SOC_INLINE Vector4 operator/(const Vector4& v, const float32 s) {
  return Vector4(v.x / s, v.y / s, v.z / s, v.w / s);
}

SOC_INLINE void operator+=(Vector4& v1, const Vector4& v2) {
  v1 = v1 + v2;
}

SOC_INLINE void operator+=(Vector4& v, const float32& s) {
  v = v + s;
}

SOC_INLINE void operator-=(Vector4& v1, const Vector4& v2) {
  v1 = v1 - v2;
}

SOC_INLINE void operator-=(Vector4& v, const float32& s) {
  v = v - s;
}

SOC_INLINE void operator*=(Vector4& v1, const Vector4& v2) {
  v1 = v1 * v2;
}

SOC_INLINE void operator*=(Vector4& v, const float32& s) {
  v = v * s;
}

SOC_INLINE void operator/=(Vector4& v1, const Vector4& v2) {
  v1 = v1 / v2;
}

SOC_INLINE void operator/=(Vector4& v, const float32& s) {
  v = v / s;
}

SOC_INLINE Vector4 operator-(const Vector4& v) {
  return Vector4(-v.x, -v.y, -v.z, -v.w);
}
///////////////////////////////////////////////////////////////

// Matrix3 operator overloading
///////////////////////////////////////////////////////////////
SOC_INLINE Matrix3 operator+(const Matrix3& m1, const Matrix3& m2) {
  Matrix3 result(0.0f);

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = m1[i] + m2[i];
  }

  return result;
}

SOC_INLINE Matrix3 operator+(const Matrix3& m, const float32 s) {
  Matrix3 result(0.0f);

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = m[i] + s;
  }

  return result;
}

SOC_INLINE Matrix3 operator-(const Matrix3& m1, const Matrix3& m2) {
  Matrix3 result(0.0f);

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = m1[i] - m2[i];
  }

  return result;
}

SOC_INLINE Matrix3 operator-(const Matrix3& m, const float32 s) {
  Matrix3 result(0.0f);

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = m[i] - s;
  }

  return result;
}

SOC_INLINE Matrix3 operator*(const Matrix3& m1, const Matrix3& m2) {
  return Matrix3(
                 (m1[0] * m2[0]) + (m1[1] * m2[3]) + (m1[2] * m2[6]), // m0 
                 (m1[0] * m2[1]) + (m1[1] * m2[4]) + (m1[2] * m2[7]), // m1 
                 (m1[0] * m2[2]) + (m1[1] * m2[5]) + (m1[2] * m2[8]), // m2 
                 
                 (m1[3] * m2[0]) + (m1[4] * m2[3]) + (m1[5] * m2[6]), // m3 
                 (m1[3] * m2[1]) + (m1[4] * m2[4]) + (m1[5] * m2[7]), // m4 
                 (m1[3] * m2[2]) + (m1[4] * m2[5]) + (m1[5] * m2[8]), // m5 
                 
                 (m1[6] * m2[0]) + (m1[7] * m2[3]) + (m1[8] * m2[6]), // m6 
                 (m1[6] * m2[1]) + (m1[7] * m2[4]) + (m1[8] * m2[7]), // m7 
                 (m1[6] * m2[2]) + (m1[7] * m2[5]) + (m1[8] * m2[8])  // m8 
                );
}

SOC_INLINE Matrix3 operator*(const Matrix3& m, const float32 s) {
  Matrix3 result(0.0f);

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = m[i] * s;
  }

  return result;
}

SOC_INLINE Matrix3 operator-(const Matrix3& m) {
  Matrix3 result(0.0f); 

  for(uint32 i = 0; i < 9; i++) {
    result.data[i] = -m[i];
  }

  return result;
}

SOC_INLINE void operator+=(Matrix3& m1, const Matrix3& m2) {
  m1 = m1 + m2;
}

SOC_INLINE void operator+=(Matrix3& m, const float32 s) {
  m = m + s;
}

SOC_INLINE void operator-=(Matrix3& m1, const Matrix3& m2) {
  m1 = m1 - m2;
}

SOC_INLINE void operator-=(Matrix3& m, const float32 s) {
  m = m - s;
}

SOC_INLINE void operator*=(Matrix3& m1, const Matrix3& m2) {
  m1 = m1 * m2;
}

SOC_INLINE void operator*=(Matrix3& m, const float32 s) {
  m = m * s;
}
//////////////////////////////////////////////////////////////

// Matrix4 operator overloading
///////////////////////////////////////////////////////////////
SOC_INLINE Matrix4 operator+(const Matrix4& m1, const Matrix4& m2) {
  Matrix4 result(0.0f);

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = m1[i] + m2[i];
  }

  return result;
}

SOC_INLINE Matrix4 operator+(const Matrix4& m, const float32 s) {
  Matrix4 result(0.0f);

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = m[i] + s;
  }

  return result;
}

SOC_INLINE Matrix4 operator-(const Matrix4& m1, const Matrix4& m2) {
  Matrix4 result(0.0f);

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = m1[i] - m2[i];
  }

  return result;
}

SOC_INLINE Matrix4 operator-(const Matrix4& m, const float32 s) {
  Matrix4 result(0.0f);

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = m[i] - s;
  }

  return result;
}

SOC_INLINE Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
  return Matrix4((m1[0] * m2[0]) + (m1[1] * m2[4]) + (m1[2] * m2[8])  + (m1[3] * m2[12]), // m0
                 (m1[0] * m2[1]) + (m1[1] * m2[5]) + (m1[2] * m2[9])  + (m1[3] * m2[13]), // m1
                 (m1[0] * m2[2]) + (m1[1] * m2[6]) + (m1[2] * m2[10]) + (m1[3] * m2[14]), // m2
                 (m1[0] * m2[3]) + (m1[1] * m2[7]) + (m1[2] * m2[11]) + (m1[3] * m2[15]), // m3
                 
                 (m1[4] * m2[0]) + (m1[5] * m2[4]) + (m1[6] * m2[8])  + (m1[7] * m2[12]), // m4
                 (m1[4] * m2[1]) + (m1[5] * m2[5]) + (m1[6] * m2[9])  + (m1[7] * m2[13]), // m5
                 (m1[4] * m2[2]) + (m1[5] * m2[6]) + (m1[6] * m2[10]) + (m1[7] * m2[14]), // m6
                 (m1[4] * m2[3]) + (m1[5] * m2[7]) + (m1[6] * m2[11]) + (m1[7] * m2[15]), // m7
                 
                 (m1[8] * m2[0]) + (m1[9] * m2[4]) + (m1[10] * m2[8])  + (m1[11] * m2[12]), // m8
                 (m1[8] * m2[1]) + (m1[9] * m2[5]) + (m1[10] * m2[9])  + (m1[11] * m2[13]), // m9
                 (m1[8] * m2[2]) + (m1[9] * m2[6]) + (m1[10] * m2[10]) + (m1[11] * m2[14]), // m10
                 (m1[8] * m2[3]) + (m1[9] * m2[7]) + (m1[10] * m2[11]) + (m1[11] * m2[15]), // m11
                 
                 (m1[12] * m2[0]) + (m1[13] * m2[4]) + (m1[14] * m2[8])  + (m1[15] * m2[12]), // m12
                 (m1[12] * m2[1]) + (m1[13] * m2[5]) + (m1[14] * m2[9])  + (m1[15] * m2[13]), // m13
                 (m1[12] * m2[2]) + (m1[13] * m2[6]) + (m1[14] * m2[10]) + (m1[15] * m2[14]), // m14
                 (m1[12] * m2[3]) + (m1[13] * m2[7]) + (m1[14] * m2[11]) + (m1[15] * m2[15])  // m15
                 );
}

SOC_INLINE Matrix4 operator*(const Matrix4& m, const float32 s) {
  Matrix4 result(0.0f);

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = m[i] * s;
  }

  return result;
}

SOC_INLINE Matrix4 operator-(const Matrix4& m) {
  Matrix4 result(0.0f); 

  for(uint32 i = 0; i < 16; i++) {
    result.data[i] = -m[i];
  }

  return result;
}

SOC_INLINE void operator+=(Matrix4& m1, const Matrix4& m2) {
  m1 = m1 + m2;
}

SOC_INLINE void operator+=(Matrix4& m, const float32 s) {
  m = m + s;
}

SOC_INLINE void operator-=(Matrix4& m1, const Matrix4& m2) {
  m1 = m1 - m2;
}

SOC_INLINE void operator-=(Matrix4& m, const float32 s) {
  m = m - s;
}

SOC_INLINE void operator*=(Matrix4& m1, const Matrix4& m2) {
  m1 = m1 * m2;
}

SOC_INLINE void operator*=(Matrix4& m, const float32 s) {
  m = m * s;
}

///////////////////////////////////////////////////////////////

} // End of soc
