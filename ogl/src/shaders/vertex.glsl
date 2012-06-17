#version 330
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;

in vec4 in_vPosition;
in vec3 in_vNormal;
in vec2 in_vTexCoord;

smooth out vec3 vNormalW;
smooth out vec3 vPosW;
smooth out vec2 vTexCoord;

void main(void) {
	vNormalW = (modelMatrix * vec4(in_vNormal, 1.0)).xyz;
	vNormalW = normalize(vNormalW);

	vPosW = (modelMatrix * in_vPosition).xyz;

	vTexCoord = in_vTexCoord;

	gl_Position = mvpMatrix * in_vPosition; 
}