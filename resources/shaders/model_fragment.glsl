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
  vec3 color = vec3(0.4, 0.1, 0.7);

  vec3 unitNormal = normalize(v_SurfaceNormal);
  vec3 unitLightVector = normalize(v_ToLightVector);

  // ambient light
  float ambientStength = 0.1f;
  vec3 ambientLight = u_LightColor * ambientStength;

  // diffused light
  float dotProduct = dot(unitNormal, unitLightVector);
  float brightness = max(dotProduct, 0.0f);

  vec3 diffuseLight = brightness * u_LightColor;

  vec3 resultColor = (ambientLight + diffuseLight) * color;
  outColor = vec4(resultColor, 1.0f);
}
