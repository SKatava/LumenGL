#version 430 core

in vec2 v_tex_cords;

out vec4 frag_color;

uniform vec3 u_color;

uniform sampler2D tex0;

void main()
{
    frag_color = texture(tex0, v_tex_cords) * vec4(u_color, 1.f);

}
