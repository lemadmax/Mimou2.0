#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
    vec4 Pos = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
    vec4 Nor = vec4(a_Normal, 0.) * u_InverseMatrix;

    gl_Position = Pos;
    v_Position = Pos.xyz;
    v_Normal = Nor.xyz;
    v_TexCoord = a_TexCoord;
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

uniform sampler2D u_Texture;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

void main()
{
    vec3 N = normalize(v_Normal);
    vec3 OutColor = u_Ambient;
    for (int i = 0; i < u_nl; i++)
    {
        vec3 L = -u_Lights[i].LightDir;
        OutColor += u_Lights[i].LightColor * u_Lights[i].Intensity * max(0., dot(L, N));
    }
    OutColor = pow(OutColor, vec3(1.0 / 2.2)); // Gamma correction

    // FragColor = vec4(OutColor, u_Transparency);
    FragColor = texture(u_Texture, v_TexCoord);
    // FragColor = vec4(OutColor, u_Transparency) * texture(u_Texture, v_TexCoord);
}