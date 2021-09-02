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

out vec4 varyingColor;

void main(){

	vec4 P = mv_matrix * vec4(pos, 1.0f);
	vec3 N = normalize((norm_matrix*vec4(normal, 1.0)).xyz);
	vec3 L = normalize(light.position - P.xyz);

	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);

	vec3 ambient = ((globalAmbient*material.ambient+light.ambient*material.ambient).xyz);
	vec3 diffuse = (light.diffuse * material.diffuse).xyz*max(0.0, dot(N, L));
	vec3 specular = (material.specular*light.specular).xyz*pow(max(0.0, dot(R, V)), material.shininess);

	varyingColor = vec4(ambient+diffuse+specular, 1.0);
	gl_Position = proj_matrix*mv_matrix*vec4(pos, 1.0);

}