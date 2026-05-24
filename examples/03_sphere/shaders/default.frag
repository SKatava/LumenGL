// examples/03_planet/shaders/planet.frag
#version 460 core

in vec3 v_worldPos;
in vec3 v_normal;
in vec2 v_uv;

uniform sampler2D u_albedo;
uniform bool      u_hasAlbedo;
uniform vec4      u_color;
uniform vec3      u_camPos;

// Optional: second texture for specular mask
// (ocean = shiny, land = matte)
uniform sampler2D u_specularMap;
uniform bool      u_hasSpecularMap;

out vec4 FragColor;

const vec3  SUN_DIR     = normalize(vec3(1.0, 0.3, 0.5));
const vec3  SUN_COLOR   = vec3(1.0, 0.95, 0.85);  // slightly warm
const vec3  SKY_COLOR   = vec3(0.15, 0.2, 0.4);    // blue ambient from sky
const float AMBIENT     = 0.04;

void main() {
    vec4 baseColor = u_hasAlbedo
        ? texture(u_albedo, v_uv) * u_color
        : u_color;

    vec3 N = normalize(v_normal);
    vec3 V = normalize(u_camPos - v_worldPos);

    // Diffuse
    float NdotL = max(dot(N, SUN_DIR), 0.0);

    // Hemisphere ambient — sky above, dark below
    // gives a subtle blue tint on the night side
    float hemi   = dot(N, vec3(0.0, 1.0, 0.0)) * 0.5 + 0.5;
    vec3  ambient = mix(vec3(AMBIENT), SKY_COLOR * 0.1, hemi);

    // Specular — use specular map if available
    // oceans are shiny (1.0), land is matte (0.0)
    float specMask = u_hasSpecularMap
        ? texture(u_specularMap, v_uv).r
        : 0.3;

    vec3  H    = normalize(SUN_DIR + V);
    float spec = pow(max(dot(N, H), 0.0), 128.0) * specMask;

    // Atmospheric rim — thin bright edge facing away from camera
    float rim  = 1.0 - max(dot(N, V), 0.0);
    rim        = pow(rim, 4.0) * NdotL * 0.6;
    vec3  rimColor = SUN_COLOR * rim;

    // Night side glow — very subtle warm tint on the terminator
    float nightGlow = smoothstep(-0.1, 0.1, -NdotL) * 0.03;

    vec3 lighting =
          ambient
        + NdotL * SUN_COLOR
        + spec  * SUN_COLOR
        + rimColor
        + nightGlow;

    FragColor = vec4(baseColor.rgb * lighting, baseColor.a);
}
