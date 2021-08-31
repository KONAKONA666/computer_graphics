#version 430

layout(location=0) in vec3 pos;

uniform mat4 mv_Matrix;
uniform mat4 proj_Matrix;

out vec4 varyingColor;

void main(){
	gl_Position = proj_Matrix * mv_Matrix * vec4(pos, 1.0);
	varyingColor = vec4(pos.x*0.5, pos.y*0.5, pos.z*0.5, 1.0) + vec4(0.5);
}
