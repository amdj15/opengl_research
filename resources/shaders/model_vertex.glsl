#version 330 core

layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 normal;
// layout(location = 2) in vec2 texCoords;

// out vec2 v_TexCoords;
// out vec3 v_SurfaceNormal;
// out vec3 v_ToLightVector;
// out vec3 v_ToCamerVector;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main()
{
  vec4 worldPosition = u_Model * vec4(position, 1.0);
  gl_Position = u_Projection * u_View * worldPosition;

  // v_TexCoords = texCoords;
  // v_SurfaceNormal = (u_Model * vec4(normal, 0.0)).xyz;
  // v_ToLightVector = u_LightPosition - worldPosition.xyz;
  // v_ToCamerVector = u_CameraPosition - worldPosition.xyz;
}
