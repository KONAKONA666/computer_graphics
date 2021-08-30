#version 430

in vec2 tc;

uniform mat4 mv_Matrix;
uniform mat4 proj_Matrix;

layout(binding=0) uniform sampler2D samp;

out vec4 color;

void main(){
	color = texture(samp, tc);
}