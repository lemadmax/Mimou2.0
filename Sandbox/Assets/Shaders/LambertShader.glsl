#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;

out vec3 v_Position;
out vec3 v_Normal;

void main()
{
    v_Position = a_Position;

    vec4 Nor = vec4(a_Normal, 0.) * u_InverseMatrix;
    v_Normal = Nor.xyz;
    gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
}	


#type fragment
#version 460 core

#define MAX_LIGHTS 128

layout(location = 0) out vec4 Color;

struct SceneLight
{
    vec4 u_LightColor;
    vec3 u_LightDir;
};

uniform int nl;
uniform SceneLight Lights[MAX_LIGHTS];

uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec4 u_Specular;
uniform float u_Transparency;

in vec3 v_Position;
in vec3 v_Normal;

void main()
{
    vec3 OutColor = u_Ambient + Lights[0].u_LightColor.w * Lights[0].u_LightColor.rgb * max(0., dot(Lights[0].u_LightDir, v_Normal));
    Color = vec4(sqrt(OutColor), u_Transparency);
}