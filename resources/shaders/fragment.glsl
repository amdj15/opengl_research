#version 330 core

out vec4 outColor;
in vec2 v_TexCoords;

uniform vec4 u_Color;

uniform sampler2D u_TextureBg;
uniform sampler2D u_TextureTag;

void main()
{
  outColor = vec4(0.1, 0.3, 0.7, 1.0);
  // outColor = mix(texture(u_TextureBg, v_TexCoords), texture(u_TextureTag, v_TexCoords), 0.6);
}
