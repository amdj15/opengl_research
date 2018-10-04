#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent;

out vec2 v_TexCoords;

out v_TangentSpace {
  vec3 toLightVector;
  vec3 toCameraVector;
} tangentSpace;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main()
{
  vec4 worldPosition = u_Model * vec4(position, 1.0);

  // Tangent space matrix
  vec3 T = normalize(vec3(u_Model * vec4(tangent, 0.0)));
  vec3 N = normalize(vec3(u_Model * vec4(normal, 0.0)));
  vec3 B = cross(N, T);

  mat3 TBN = transpose(mat3(T, B, N));

  vec3 worldPositionTBN = TBN * worldPosition.xyz;
  vec3 lightPositionTBN = TBN * u_LightPosition;
  vec3 cameraPositionTBN = TBN * u_CameraPosition;

  gl_Position = u_Projection * u_View * worldPosition;

  v_TexCoords = texCoords;
  tangentSpace.toLightVector = lightPositionTBN - worldPositionTBN;
  tangentSpace.toCameraVector = cameraPositionTBN - worldPositionTBN;
}
