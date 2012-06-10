#version 330
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 vLightPosition;
uniform vec4 diffuseColor;

in vec4 in_vPosition;
in vec3 in_vNormal;

smooth out vec4 vVaryingColor;

void main(void) {
	vec3 vEyeNormal = mul(modelMatrix, in_vPosition).xyz;
	vEyeNormal = normalize(vEyeNormal);

	vec4 vPosition4 = mvMatrix * in_vPosition;
	vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

	vec3 vLightDir = normalize(vLightPosition - vPosition3);

	float diff = max(0.0, dot(vEyeNormal, vLightDir));

	vVaryingColor.xyz = diff * diffuseColor.xyz;
	vVaryingColor.a = 1.0;

	gl_Position = mvpMatrix * in_vPosition; 
}