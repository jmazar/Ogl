#version 330
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;

in vec4 in_vPosition;
in vec3 in_vNormal;

out vec2 TexCoord;
smooth out vec3 vNormalW;
smooth out vec3 vPosW;

vec2 SphereMap(const in vec3 position, const in vec3 normal) {
	float m;
	vec3 r, u;
	u = normalize(position);
	r = reflect(u, normal);
	r.z += 1.0;
	m = 0.5 * inversesqrt( dot(r,r));
	return r.xy * m + 0.5;
}

void main(void) {
	vNormalW = mul(modelMatrix, vec4(in_vNormal, 1.0)).xyz;
	vNormalW = normalize(vNormalW);

	vPosW = mul(modelMatrix, in_vPosition).xyz;
	TexCoord = SphereMap(vPosW, vNormalW);

	gl_Position = mvpMatrix * in_vPosition; 
}