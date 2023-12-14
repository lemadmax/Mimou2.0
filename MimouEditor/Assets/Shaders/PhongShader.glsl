#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;

out vec3 v_Position;
out vec3 v_Normal;
out mat4 v_InverseMatrix;

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
    vec3 LightColor;
    vec3 LightDir;
    float Intensity;
};

uniform int u_nl;
uniform SceneLight u_Lights[MAX_LIGHTS];

uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec4 u_Specular;
uniform float u_Transparency;
uniform float u_IrradiPerp;

in vec3 v_Position;
in vec3 v_Normal;

void main()
{
    vec3 N = normalize(v_Normal);
    vec3 Radiance = u_Ambient;
    for (int i = 0; i < u_nl; i++)
    {
        vec3 LightColor = u_Lights[i].LightColor * u_Lights[i].Intensity;
        vec3 L = -u_Lights[i].LightDir;
        float Irriadiance = max(0., dot(L, N)) * u_IrradiPerp;
        float specular = 0.0;
        if (Irriadiance > 0.)
        {
            vec3 R = 2. * dot(N, -L) * N + L;
            vec3 V = normalize(-v_Position);
            specular = pow(max(dot(R, V), 0.0), u_Lights[i].Intensity);
        }
        Radiance += Irriadiance * u_Diffuse + specular * u_Specular.rgb;
    }
    Radiance = pow(Radiance, vec3(1.0 / 2.2)); // Gamma correction
    FragColor = vec4(Radiance, u_Transparency);
}