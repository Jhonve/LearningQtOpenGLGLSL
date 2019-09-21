#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;

out vec3 our_color;

void main(){
  gl_Position = projMatrix * mvMatrix * vec4(aPos, 1.0f) ;
  our_color = aColor;
}