#version 330
precision highp float;

uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 vLightPosition;
uniform vec4 diffuseColor;
uniform vec3 vEyeLocation;

smooth in vec3 vNormalW;
smooth in vec3 vPosW;
in vec2 TexCoord;

uniform sampler2D Texture;

void main(void) {
	vec3 worldNormal = normalize(vNormalW);
	vec3 vLightDir = normalize(vLightPosition - vPosW);

	float s = max(dot(vLightDir, worldNormal), 0.0f);

	vec3 vToEye = normalize(vEyeLocation - vPosW);
	vec3 vReflect = reflect(vLightDir, worldNormal);

	float t = pow(max(dot(vReflect, vToEye), 0.0), 128.0);

	vec4 specular = t * vec4(0.65, 0.65, 0.25, 1);
	vec4 diffuse = s * diffuseColor;

	vec3 texColor = vec3(texture(Texture, TexCoord));

	gl_FragColor = vec4(texColor, 1.0) + specular + diffuse + vec4(0.0, 0.0, 0.02, 1.0);
}