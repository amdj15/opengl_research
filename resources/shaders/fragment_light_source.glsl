#version 330 core

out vec4 outColor;

uniform vec3 u_LightColor;

void main() {
  outColor = vec4(u_LightColor, 1.0f);
}
