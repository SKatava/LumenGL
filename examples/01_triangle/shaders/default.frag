// examples/01_triangle/shaders/triangle.frag
#version 460 core

in vec3 v_normal;
in vec2 v_uv;

uniform vec4 u_color;
uniform bool u_hasAlbedo;

out vec4 FragColor;

void main() {
    FragColor = u_color;
}
