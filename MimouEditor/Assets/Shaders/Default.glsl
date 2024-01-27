#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;

out vec3 v_Position;
out vec3 v_Normal;
out mat4 v_InverseMatrix;
out vec2 v_TexCoord;

void main()
{
    vec4 vertPos = u_TransformMatrix * vec4(a_Position, 1.0);

    gl_Position =  u_ViewProjection * vertPos;

    vec4 Nor = vec4(a_Normal, 0.)* u_InverseMatrix;

    v_Position = vertPos.xyz;
    v_Normal = Nor.xyz;
}


#type fragment
#version 460 core

#define MAX_LIGHTS 128

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 Color2;
layout(location = 2) out int EntityID;

struct SceneLight
{
    vec3 LightColor;
    vec3 LightDir;
    float Intensity;
};

uniform int u_nl;
uniform SceneLight u_Lights[MAX_LIGHTS];

uniform vec4 u_Ambient;
uniform vec4 u_Diffuse;
uniform vec4 u_Specular;
uniform float u_Transparency;
uniform float u_IrradiPerp;
uniform vec3 ViewPos;

in vec3 v_Position;
in vec3 v_Normal;

void main()
{
    vec3 N = normalize(v_Normal);
    vec3 Radiance = u_Ambient.rgb;
    for (int i = 0; i < u_nl; i++)
    {
        vec3 LightColor = u_Lights[i].LightColor * u_Lights[i].Intensity;
        vec3 L = -u_Lights[i].LightDir;
        float Irriadiance = dot(L, N);
        if (Irriadiance > 0.)
        {
            vec3 R = 2. * Irriadiance * N - L;
            vec3 V = normalize(ViewPos - v_Position);
            Irriadiance = Irriadiance * u_IrradiPerp;
            Radiance += LightColor * (Irriadiance * u_Diffuse.rgb);

            float Specular = pow(max(0., dot(R, V)), u_Specular.w);
            Radiance += LightColor * (Specular * u_Specular.rgb);
        }
    }
    FragColor = vec4(Radiance, u_Transparency);
    Color2 = vec4(0.9, 0.2, 0.3, 1.0);
    EntityID = 15;
}