#include "socrates/socrates.h"

#include <cstdio>

#define VEC3_PRINT(v) printf("%f, %f, %f\n", v.x, v.y, v.z)
#define VEC4_PRINT(v) printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w)
#define MAT3_PRINT(m) for(int i = 0; i < 9; i++) {if(i % 3 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")
#define MAT4_PRINT(m) for(int i = 0; i < 16; i++) {if(i % 4 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")

int main() {
  soc::Vector4 vec(0.3f);
  soc::Matrix4 mat(1.0f);
  soc::Vector4 result = vec * mat;

  VEC4_PRINT(result);
}
