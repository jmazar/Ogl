#version 330
precision highp float;

smooth in vec4 vVaryingColor;

out vec4 gl_FragColor;

void main(void) {
  gl_FragColor = vVaryingColor;
}