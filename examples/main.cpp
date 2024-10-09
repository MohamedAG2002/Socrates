#include "socrates.h"

#include <cstdio>

#define VEC2_PRINT(v) printf("%f, %f\n", v.x, v.y)
#define VEC3_PRINT(v) printf("%f, %f, %f\n", v.x, v.y, v.z)
#define VEC4_PRINT(v) printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w)
#define MAT3_PRINT(m) for(int i = 0; i < 9; i++) {if(i % 3 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")
#define MAT4_PRINT(m) for(int i = 0; i < 16; i++) {if(i % 4 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")

int main() {
  soc::Matrix3 mat3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  soc::Matrix4 mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  
  MAT3_PRINT(soc::mat3_inverse(mat3));
  printf("\n\n");
  MAT4_PRINT(soc::mat4_inverse(mat4));
}
