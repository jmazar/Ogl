#version 150
uniform float move;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelViewProjectionMatrix;

in vec4 in_Position;

void main(void) {
  gl_Position = ModelViewMatrix * in_Position;
}