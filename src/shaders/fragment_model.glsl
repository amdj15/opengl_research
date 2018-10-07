#version 330 core

out vec4 outColor;

in vec2 v_TexCoords;

in v_TangentSpace {
  vec3 toLightVector;
  vec3 toCameraVector;
} ts;

struct Material {
  float shininess;
  float specularStrength;
};

uniform vec3 u_LightColor;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;

uniform Material material;

void main()
{
  vec3 unitNormal = texture(texture_normal, v_TexCoords).rgb;
  unitNormal = normalize(unitNormal * 2.0 - 1.0);

  // ambient light
  float ambientStength = 0.1f;
  vec3 ambientLight = u_LightColor * ambientStength * texture(texture_diffuse, v_TexCoords).rgb;

  // diffused light
  vec3 unitLightVector = normalize(ts.toLightVector);
  float dotProduct = dot(unitNormal, unitLightVector);
  float brightness = max(dotProduct, 0.0f);

  vec3 diffuseLight = brightness * u_LightColor * texture(texture_diffuse, v_TexCoords).rgb;

  // specular ligth
  float damperFactor = 0.0f;
  if (brightness > 0.0f) {
    vec3 unitToCameraVector = normalize(ts.toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
    float specularFactor = max(dot(reflectedLightDirection, unitToCameraVector), 0.0f);
    damperFactor = pow(specularFactor, material.shininess);
  }

  vec3 specularLight = material.specularStrength * damperFactor * u_LightColor * texture(texture_specular, v_TexCoords).rgb;

  // result
  vec3 resultColor = ambientLight + diffuseLight + specularLight;
  outColor = vec4(resultColor, 1.0f);
}
