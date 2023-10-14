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
    vec4 Pos = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
    vec4 Nor = vec4(a_Normal, 0.) * u_InverseMatrix;

    gl_Position = Pos;
    v_Position = Pos.xyz;
    v_Normal = Nor.xyz;
}


#type fragment
#version 460 core

#define MAX_LIGHTS 128

layout(location = 0) out vec4 FragColor;

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
    vec3 N = normalize(v_Normal);
    vec3 Color = u_Ambient;
    for (int i = 0; i < nl; i++)
    {
        float Mag = dot(Lights[i].u_LightDir, N);
        if (Mag > 0.) 
        {
            vec3 R = 2. * Mag * N - Lights[i].u_LightDir;

            Color += Lights[i].u_LightColor.rgb * (u_Diffuse * max(0., Mag) + u_Specular.rgb * pow(max(0., R.z), u_Specular.w));
        }

        // Color += Lights[i].u_LightColor.rgb * u_Diffuse * max(0., dot(Lights[i].u_LightDir, v_Normal));
        // Color += Lights[i].u_LightColor.rgb * u_Diffuse;
        // Color += Lights[i].u_LightColor.rgb;
    }
    FragColor = vec4(sqrt(Color), u_Transparency);
}