#version 330
precision highp float;

uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 vLightPosition;
uniform vec4 diffuseColor;

smooth in vec3 vNormalW;
smooth in vec3 vPosW;

void main(void) {
	vec3 worldNormal = normalize(vNormalW);
	vec3 vLightDir = normalize(vLightPosition - vPosW);

	float s = max(dot(vLightDir, worldNormal), 0.0f);

	vec4 diffuse = s * diffuseColor;


	gl_FragColor = diffuse + vec4(0.0, 0.0, 0.2, 1.0);
}