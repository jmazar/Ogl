#version 150

in vec2 in_Position;

void main(void) {
  gl_Position = vec4(in_Position.x - 0.1, in_Position.y, 0.0, 1.0);
}