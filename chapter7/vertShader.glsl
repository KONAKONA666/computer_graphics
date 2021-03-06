#version 430

layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;

struct PositionalLight{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;

out vec3 varyingNormal;
out vec3 varyingPosition;
out vec3 varyingLightDir;

void main(){

	varyingPosition = (mv_matrix*vec4(pos, 1.0)).xyz;
	varyingNormal = (norm_matrix*vec4(normal, 1.0f)).xyz;
	varyingLightDir = (light.position-varyingPosition);

	gl_Position = proj_matrix*mv_matrix*vec4(pos, 1.0);

}