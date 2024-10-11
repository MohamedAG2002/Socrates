#include "socrates.h"

#include <cstdio>

#define VEC2_PRINT(v) printf("%f, %f\n", v.x, v.y)
#define VEC3_PRINT(v) printf("%f, %f, %f\n", v.x, v.y, v.z)
#define VEC4_PRINT(v) printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w)
#define MAT3_PRINT(m) for(int i = 0; i < 9; i++) {if(i % 3 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")
#define MAT4_PRINT(m) for(int i = 0; i < 16; i++) {if(i % 4 == 0) {printf("\n");} printf("%f ", m[i]);} printf("\n")

int main() {
  soc::Matrix4 projection = soc::mat4_perspective(180.0f, 1920.0f / 1080.0f, 0.0f, 150.0f);
  soc::Matrix4 view = soc::mat4_look_at(soc::Vector3(5.0f), soc::Vector3(0.0f, 0.0f, -3.0f), soc::Vector3(0.0f, 1.0f, 0.0f));
  

  MAT4_PRINT((projection * view));
}
