#version 330 core

out vec4 outColor;
in vec2 v_TexCoords;
in vec3 v_SurfaceNormal;
in vec3 v_ToLightVector;

uniform vec4 u_Color;
uniform vec3 u_LightColor;

uniform sampler2D u_TextureBg;
uniform sampler2D u_TextureTag;

void main()
{
  vec3 unitNormal = normalize(v_SurfaceNormal);
  vec3 unitLightVector = normalize(v_ToLightVector);

  float dotProduct = dot(unitNormal, unitLightVector);
  float brightness = max(dotProduct, 0.0f);

  vec3 diffuse = brightness * u_LightColor;

  outColor = vec4(diffuse, 1.0f) * vec4(0.1, 0.3, 0.7, 1.0);

  // outColor = mix(texture(u_TextureBg, v_TexCoords), texture(u_TextureTag, v_TexCoords), 0.6);
}
