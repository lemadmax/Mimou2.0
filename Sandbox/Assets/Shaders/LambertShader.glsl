#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec3 v_Normal;

void main()
{
    v_Position = a_Position;
    v_Normal = a_Normal;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}	


#type fragment
#version 460 core

layout(location = 0) out vec4 Color;

uniform vec4 u_Ambient;
uniform vec4 u_LightColor;
uniform vec3 u_LightDir;
uniform vec3 u_CameraPos;
uniform float u_Transparency;

in vec3 v_Position;
in vec3 v_Normal;

void main()
{
    vec3 LambertDiffuse = u_Ambient.rgb * u_Ambient.w;
    Color = vec4(LambertDiffuse + u_LightColor.w * u_LightColor.rgb * dot(v_Normal, u_LightDir), u_Transparency);
}