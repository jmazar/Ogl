#version 150
uniform mat3 ModelViewMatrix;

in vec3 in_Position;

void main(void) {
  gl_Position = gl_Projection * ModelViewMatrix * gl_Vertex;
}