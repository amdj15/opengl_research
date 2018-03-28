#version 330 core

out vec4 outColor;
in vec2 v_TexCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
  outColor = texture(u_Texture, v_TexCoords) * u_Color;
}
