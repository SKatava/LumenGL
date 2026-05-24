// examples/02_cube/shaders/textured.frag
#version 460 core

in vec3 v_worldPos;
in vec3 v_normal;
in vec2 v_uv;

uniform sampler2D u_albedo;
uniform bool      u_hasAlbedo;
uniform vec4      u_color;
uniform vec3      u_camPos;

out vec4 FragColor;

const vec3  LIGHT_DIR   = normalize(vec3(1.0, 2.0, 1.0));
const vec3  LIGHT_COLOR = vec3(1.0);
const float AMBIENT     = 0.2;

void main() {
    vec4 baseColor = u_hasAlbedo
        ? texture(u_albedo, v_uv) * u_color
        : u_color;

    vec3 N     = normalize(v_normal);
    float diff = max(dot(N, LIGHT_DIR), 0.0);

    vec3 V     = normalize(u_camPos - v_worldPos);
    vec3 H     = normalize(LIGHT_DIR + V);
    float spec = pow(max(dot(N, H), 0.0), 64.0);

    vec3 lighting = (AMBIENT + diff + 0.3 * spec) * LIGHT_COLOR;

    FragColor = vec4(baseColor.rgb * lighting, baseColor.a);
}
