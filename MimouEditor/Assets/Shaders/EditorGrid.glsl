#type vertex
#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;
uniform float u_zNear;
uniform float u_zFar;

// layout(location = 0) out vec3 Position;
out vec3 NearPoint;
out vec3 FarPoint;
out float fading;

vec3 gridPlane[4] = vec3[4](vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, -1, 0));

float computeDepth(vec3 pos)
{
    vec4 clipSpacePos = u_ViewProjection * vec4(pos, 1.0);
    return clipSpacePos.z / clipSpacePos.w;
}

float computeLinearDepth(float depth)
{
    // float clipSpaceDepth = depth * 2.0 - 1.0;
    // // float linearDepth = (2.0 * u_zNear * u_zFar) / (u_zFar + u_zNear - clipSpaceDepth * (u_zFar - u_zNear));
    // float linearDepth = clipSpaceDepth * (u_zFar - u_zNear);
    // return linearDepth / (u_zFar - u_zNear);
    float linearDepth = 1.0/160.0 * depth * depth - 3.0/80.0 * depth;
    return linearDepth;
}

void main()
{
    vec4 p = vec4(gridPlane[gl_VertexID], 1.0);
    mat4 viewInv = inverse(u_ViewMat);
    mat4 projInv = inverse(u_ProjMat);
    vec4 unprojNearPoint = viewInv * projInv * vec4(p.x, p.y, 0.0, 1.0);
    vec4 unprojFarPoint = viewInv * projInv * vec4(p.x, p.y, 1.0, 1.0);
    NearPoint = unprojNearPoint.xyz / unprojNearPoint.w;
    FarPoint = unprojFarPoint.xyz / unprojFarPoint.w;

    float t = -NearPoint.y / (FarPoint.y - NearPoint.y);
    vec3 fragPos3D = NearPoint + t * (FarPoint - NearPoint);
    p.z = computeDepth(fragPos3D);
    gl_Position = p;

    float linearDepth = computeLinearDepth(fragPos3D.z);
    fading = max(0, (1.0 - linearDepth));
}	


#type fragment
#version 460 core

// layout(location = 0) in vec3 Position;
in vec3 NearPoint;
in vec3 FarPoint;
in float fading;

layout(location = 0) out vec4 FragColor;

vec4 grid(vec3 fragPos3D, float scale)
{
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.5, 0.5, 0.5, 1.0 - min(line, 1.0));

    if (fragPos3D.x > -minimumx && fragPos3D.x < minimumx)
    {
        color.z = 1.0;
    }

    if (fragPos3D.z > -minimumz && fragPos3D.z < minimumz)
    {
        color.x = 1.0;
    }

    return color;
}

void main()
{
    float t = -NearPoint.y / (FarPoint.y - NearPoint.y);
    vec3 fragPos3D = NearPoint + t * (FarPoint - NearPoint);

    FragColor = grid(fragPos3D, 1) * float(t > 0);
    FragColor.a *= fading;
}