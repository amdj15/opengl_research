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

vec3 _colorDetector(float red, float green, float blue);
vec3 diffusedColor();
vec3 lightColor();

vec3 diffusedColor() {
  return _colorDetector(
    texture(texture_diffuse, v_TexCoords).r,
    texture(texture_diffuse, v_TexCoords).g,
    texture(texture_diffuse, v_TexCoords).b
  );
}

vec3 lightColor() {
  return _colorDetector(u_LightColor.r, u_LightColor.g, u_LightColor.b);
}

vec3 _colorDetector(float red, float green, float blue) {
  if (red > 0 || green > 0 || blue > 0) {
    return vec3(red, green, blue);
  }

  return vec3(1.0f, 1.0f, 1.0f);
}

void main()
{
  vec3 unitNormal = texture(texture_normal, v_TexCoords).rgb;
  unitNormal = normalize(unitNormal * 2.0 - 1.0);

  // ambient light
  float ambientStength = 0.1f;
  vec3 ambientLight = lightColor() * ambientStength * diffusedColor();

  // diffused light
  vec3 unitLightVector = normalize(ts.toLightVector);
  float dotProduct = dot(unitNormal, unitLightVector);
  float brightness = max(dotProduct, 0.0f);
  vec3 diffuseLight = brightness * lightColor() * diffusedColor();

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
