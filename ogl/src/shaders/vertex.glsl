#version 330
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 vLightPosition;
uniform vec4 diffuseColor;

in vec4 in_vPosition;
in vec3 in_vNormal;

smooth out vec3 vNormalW;
smooth out vec3 vPosW;

void main(void) {
	vNormalW = mul(modelMatrix, vec4(in_vNormal, 1.0)).xyz;
	vNormalW = normalize(vNormalW);

	vPosW = mul(modelMatrix, in_vPosition).xyz;

	gl_Position = mvpMatrix * in_vPosition; 
}