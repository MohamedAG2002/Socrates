# What Is Socrates? 
Socrates is a simple, single-file math library specifically made for game/game engine development. It's made especially easy to read and use. Everything you'll need to know about the library is in the "socrates.h" file. It does not use any templates or function overloading. Every math type in the library has its own set of functions. For example, if you want to normalize a `Vector3` type, you can use the `vec3_normalize` function. Every function and math type in the library is inside the `soc` namespace. 

Socrates uses a row-major formula to calculate the multiplication of matrices. Socrates also prioritizes the left-hand coordinate system for calculating projection and view matrices. So please keep that in mind when you are using Socrates.

Something to also keep in mind, Socrates does not use classes to handle its types. Instead, it uses unions and structs to store the components. If you want to call a function on a type, you will have to pass in that type and receive the result from the function. However, every function in Socrates takes the parameters in as references. Therefore, no copies are happening out of nowhere. Moreover, the passed-in parameters are always `const`, meaning, unless it's an assignment, Socrates will _never_ change the state of a parameter. 

Here are the following math types that currently exist in Socrates: 
    - `Vector2`
    - `Vector3`
    - `Vector4`
    - `Quaternion`
    - `Matrix3`
    - `Matrix4`

Each type has its own variety of functions to manipulate it and every possible operator overload is also available for all of the types. Socrates also provides some miscellaneous functions like `distance`, `clamp`, `sin/cos`, `lerp`, and other very useful functions.

# Optimizations 
At the time of this writing, Socrates does not use any SIMD operations as an optimization method. Instead, Socrates tries to be as low on overhead as possible. As of now, I have tested it with a minimal OpenGL example and it ran at a very stable framerate with no indication of slowing down. However, do still keep in mind, that Socrates is not the most fully optimized math library out there. Perhaps in the future. But not now.

# How To Use? 
There is only one step needed to set and use Socrates: 
    - Copy the `socrates.h` file into the relevant directory in your project.

That's it. All the functions in Socrates are inlined and written in the header file itself. There is no need to use CMake, Make, or any other building system to configure Socrates. You don't even need to build it. It will just live there with the rest of your code. So greet it with welcoming arms, please. 

# Example 
Here's some simple examples of using Socrates: 

```c++
#include "socrates.h"

int main() {
    soc::Vector3 player_position(10.0f, 2.0f, 4.0f); // Creates a vector by initializing each component
    soc::Vector3 enemy_position(20.0f); // Creates a vector by taking one scalar and initializing the components with this scalar

    soc::Vector3 diff = enemy_position - player_position;
    diff = soc::vec3_normalize(diff); // Normalize the `diff` vector
    
    float dist = soc::vec3_distance(player_position, enemy_position); // Get the distance between two vectors

    // You can either access the components like this: 
    diff.x *= 2.0f; 
    diff.y *= 2.0f;
    diff.z *= 2.0f;

    // Or like this: 
    float x = diff[0]; // Returns the `X` component of the vector

    // However, the previous operation returns the component as a const. 
    // If you want to change the value or perhaps pass the components of the 
    // vector as an array (useful for graphics APIs like OpenGL), you can use: 
    diff.components[0] = 0.0f;

    // You can even do the same with matrices 
    soc::Matrix4 model_mat = soc::mat4_translate(player_position) * 
                             soc::mat4_rotate(soc::Vector3(1.0f, 0.0f, 0.0f), 2.0f) * 
                             soc::mat4_scale(soc::Vector3(2.0f));
    float* entries = model_mat.data;

    // Keep in mind, though, that the entries of the matrices are stored in a contiguous array. 
    // Not in a row and column fashion.
    // This is done for ease of use and better visualization.
    float m00 = model[0]; 
    float m11 = model[5];

    // You can also create Quaternion from matrices
    soc::Matrix3 rotate_mat = soc::mat3_rotate(soc::Vector3(1.0f), 90.0f * SOC_RAD2DEG);  
    soc::Quaternion quat1 = soc::quat_set_mat3(rotate_mat); // Set the rotation of the quaternion using the rotation matrix

    // But there are also many ways to construct quaternions 
    soc::Quaternion quat2(soc::Vector3(1.0f), 4.0f); // Takes in the `x`, `y`, and `z` components from the vector and the `w` component as just a scalar

    // You can also do the same with Vectors 
    soc::Vector3 vec(soc::Vector2(1.0f, 1.0f), 1.0f);

    // You can even fill in the columns of a Matrix3 using only Vector3s 
    soc::Matrix3 mat(soc::Vector3(1.0f, 0.0f, 0.0f), 
                     soc::Vector3(0.0f, 1.0f, 0.0f), 
                     soc::Vector3(0.0f, 0.0f, 1.0f));

    // The above code generates an identity Matrix3 by just using Vector3s. 
    // However, by default, any matrix that is constructed is automatically an identity 
    // matrix. 
    soc::Matrix4 iden_mat; // All the diagonals of this matrix are 1.0f

    // However, if you wish to fill in all of the entries of the matrix with a specific 
    // scalar value, you can use the following constructor:
    soc::Matrix4 only_fours(4.0f);

    // You can also just pass in an array of floats to a matrix 
    // Do note, however, that the above constructor does NOT check for the length 
    // of the given array. So if you passed in a bigger array than expected, then 
    // it will just ignore the extra values. With an array with values less than expected, however, 
    // there could be worse precautions. Please keep this in mind.
    float entries[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    soc::Matrix4 hom_mat(entries);
}
```

Here's another example of how you might create a 3D camera using Socrates: 

```c++
#include "socrates.h"

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
  }
}
```

More examples might be added in the future so keep your eyes open.
