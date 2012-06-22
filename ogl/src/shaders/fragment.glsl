#version 330
precision highp float;

uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 vLightPosition;
uniform vec4 diffuseColor;
uniform vec4 vEyeLocation;

smooth in vec3 vNormalW;
smooth in vec3 vPosW;
smooth in vec2 vTexCoord;

uniform sampler2D Texture;

void main(void) {
	vec3 worldNormal = normalize(vNormalW);
	vec3 vLightDir = normalize(vLightPosition - vPosW);
	vec3 vToEye = normalize(vec3(-vEyeLocation.xyz) - vPosW);
	vec3 vReflect = normalize(reflect(vLightDir, worldNormal));

	float s = max(0.0, dot(vLightDir, worldNormal));

	float t = pow(max(0.0, dot(vToEye, vReflect)), 128.0);

	vec4 specular = t * vec4(0.65, 0.65, 0.25, 1);
	vec4 diffuse = s * diffuseColor;

	diffuse = diffuse * texture(Texture, vTexCoord);

	gl_FragColor = specular + diffuse;
}