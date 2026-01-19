#version 430 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_cords;

out vec2 v_tex_cords;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;


void main()
{
    gl_Position = camMatrix * modelMatrix * vec4(a_pos, 1.0);
    v_tex_cords = a_tex_cords;
}
