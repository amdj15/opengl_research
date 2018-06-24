#version 330 core

out vec4 outColor;

// in vec2 v_TexCoords;
// in vec3 v_SurfaceNormal;
// in vec3 v_ToLightVector;
// in vec3 v_ToCamerVector;

uniform vec4 u_Color;
uniform vec3 u_LightColor;

uniform sampler2D u_TextureBg;
uniform sampler2D u_TextureTag;

void main()
{
  vec3 color = vec3(0.4, 0.1, 0.7);

  // // ambient light
  // float ambientStength = 0.1f;
  // vec3 ambientLight = u_LightColor * ambientStength;

  // // diffused light
  // vec3 unitNormal = normalize(v_SurfaceNormal);
  // vec3 unitLightVector = normalize(v_ToLightVector);
  // float dotProduct = dot(unitNormal, unitLightVector);
  // float brightness = max(dotProduct, 0.0f);

  // vec3 diffuseLight = brightness * u_LightColor;

  // // specular ligth
  // float reflectivity = 1.0f;
  // float shineDamper = 10.f;

  // float damperFactor = 0.0f;
  // if (brightness > 0.0f) {
  //   vec3 unitToCameraVector = normalize(v_ToLightVector);
  //   vec3 lightDirection = -unitLightVector;
  //   vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
  //   float specularFactor = max(dot(reflectedLightDirection, unitToCameraVector), 0.0f);
  //   damperFactor = pow(specularFactor, shineDamper);
  // }

  // vec3 specularLight = damperFactor * reflectivity * u_LightColor;

  // // result
  // vec3 resultColor = (ambientLight + diffuseLight + specularLight) * color;
  outColor = vec4(color, 1.0f);
}
