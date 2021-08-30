#version 430

layout(location=0) in vec3 pos;
layout(location=1) in vec2 texCord;

layout(binding=0) uniform sampler2D sam;

uniform mat4 mv_Matrix;
uniform mat4 proj_Matrix;

out vec2 tc;

void main(){
	gl_Position = proj_Matrix * mv_Matrix * vec4(pos, 1.0);
	tc = texCord;
}
