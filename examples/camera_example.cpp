#include "socrates.h"
#include "test_utils.h"

struct Camera3D {
  float yaw, pitch, zoom;

  soc::Vector3 position, up, direction, front;
  soc::Matrix4 view_projection;
};

Camera3D camera_create(const soc::Vector3& position, const soc::Vector3& target) {
  Camera3D  cam; 
 
  cam.yaw   = -90.0f;
  cam.pitch = 0.0f;
  cam.zoom  = 45.0f;

  soc::Vector3 look_dir(position - target); 
  soc::Vector3 up_axis(0.0f, 1.0f, 0.0f);
  soc::Vector3 right_axis = soc::vec3_normalize(soc::vec3_cross(up_axis, look_dir));
  
  cam.position    = position; 
  cam.up          = soc::vec3_normalize(soc::vec3_cross(look_dir, right_axis));
  cam.direction.x = cos((cam.yaw * SOC_DEG2RAD)) * cos((cam.pitch * SOC_DEG2RAD));
  cam.direction.y = sin((cam.pitch * SOC_DEG2RAD));
  cam.direction.z = sin((cam.yaw * SOC_DEG2RAD)) * cos((cam.pitch * SOC_DEG2RAD));
  cam.front       = soc::vec3_normalize(cam.direction);

  return cam;
}

void camera_update(Camera3D& cam) {
  cam.view_projection = soc::mat4_perspective((cam.zoom * SOC_DEG2RAD), 1280.0f / 720.0f, 0.1f, 100.0f) * 
    soc::mat4_look_at(cam.position, cam.position + cam.front, cam.up);

  cam.direction.x = soc::cos((cam.yaw * SOC_DEG2RAD)) * soc::cos((cam.pitch * SOC_DEG2RAD));
  cam.direction.y = soc::sin((cam.pitch * SOC_DEG2RAD));
  cam.direction.z = soc::sin((cam.yaw * SOC_DEG2RAD)) * soc::cos((cam.pitch * SOC_DEG2RAD));
  cam.front       = soc::vec3_normalize(cam.direction);
}

int main() {
  Camera3D cam = camera_create(soc::Vector3(10.0f, 0.0f, 10.0f), soc::Vector3(0.0f, 0.0f, -3.0f));

  while(true) {
    camera_update(cam);
    MAT4_PRINT(cam.view_projection);
  }
}
