#version 430

layout (location=0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
//uniform float tf;

out vec4 varyingColor;

mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x,   y,   z,   1.0);
    return trans;
}

mat4 buildRotateX(float rad) {
    mat4 xrot = mat4(1.0, 0.0,      0.0,       0.0,
                     0.0, cos(rad), -sin(rad), 0.0,
                     0.0, sin(rad), cos(rad),  0.0,
                     0.0, 0.0,      0.0,       1.0);
    return xrot;
}


mat4 buildRotateY(float rad) {
    mat4 yrot = mat4(cos(rad),  0.0, sin(rad), 0.0,
                     0.0,       1.0, 0.0,      0.0,
                     -sin(rad), 0.0, cos(rad), 0.0,
                     0.0,       0.0, 0.0,      1.0);
    return yrot;
}


mat4 buildRotateZ(float rad) {
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                     sin(rad), cos(rad),  0.0, 0.0,
                     0.0,      0.0,       1.0, 0.0,
                     0.0,      0.0,       0.0, 1.0);
    return zrot;
}

void main(void) {
    
    //float i = gl_InstanceID + tf;
    //float a = sin(2.1 * i) * 2.0;
    //float b = cos(1.2 * i) * 1.0;
    //float c = sin(3.0 * i) * 1.0;

    //mat4 localRotX = buildRotateX(2.0*i);
    //mat4 localRotY = buildRotateY(0.12*i);
    //mat4 localRotZ = buildRotateZ(0.35*i);
    //mat4 localTranslate = buildTranslate(a, b, c);

    //mat4 m_matrix = localTranslate * localRotX * localRotY * localRotZ;
    //mat4 mv_matrix = v_matrix * m_matrix;

    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0)*0.5 + vec4(0.5, 0.5, 0.5, 0.5); 
}