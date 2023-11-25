#type vertex
#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

// layout(location = 0) out vec3 Position;
out vec3 NearPoint;
out vec3 FarPoint;
out mat4 ViewMat;
out mat4 ProjMat;
out mat4 ViewProjMat;

vec3 gridPlane[4] = vec3[4](vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, -1, 0));

void main()
{
    vec4 p = vec4(gridPlane[gl_VertexID], 1.0);
    mat4 viewInv = inverse(u_ViewMat);
    mat4 projInv = inverse(u_ProjMat);
    vec4 unprojNearPoint = viewInv * projInv * vec4(p.x, p.y, -1.0, 1.0);
    vec4 unprojFarPoint = viewInv * projInv * vec4(p.x, p.y, 1.0, 1.0);
    NearPoint = (unprojNearPoint.xyz / unprojNearPoint.w).xyz;
    FarPoint = (unprojFarPoint.xyz / unprojFarPoint.w).xyz;

    gl_Position = p;
    ViewMat = u_ViewMat;
    ProjMat = u_ProjMat;
    ViewProjMat = u_ViewProjection;
}	


#type fragment
#version 460 core

uniform float u_zNear;
uniform float u_zFar;

// layout(location = 0) in vec3 Position;
in vec3 NearPoint;
in vec3 FarPoint;
in mat4 ViewMat;
in mat4 ProjMat;
in mat4 ViewProjMat;

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

    if (fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
    {
        color.z = 1.0;
    }

    if (fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
    {
        color.x = 1.0;
    }

    return color;
}

float computeDepth(vec3 pos)
{
    vec4 clipSpacePos = ViewProjMat * vec4(pos.xyz, 1.0);
    return (clipSpacePos.z / clipSpacePos.w);
    // return clipSpacePos.z;
}

float computeLinearDepth(float depth)
{
    float clipSpaceDepth = depth * 2.0 - 1.0;
    float linearDepth = (2.0 * u_zNear * u_zFar) / (u_zFar + u_zNear - clipSpaceDepth * (u_zFar - u_zNear));
    return linearDepth / u_zFar;
}

void main()
{
    float t = -NearPoint.y / (FarPoint.y - NearPoint.y);
    vec3 fragPos3D = NearPoint + t * (FarPoint - NearPoint);
    gl_FragDepth = computeDepth(fragPos3D);

    float linearDepth = computeLinearDepth(gl_FragDepth);
    float fading = max(0, (1.0 - linearDepth));

    FragColor = grid(fragPos3D, 1) * float(t > 0);
    // FragColor = vec4(0.6, 0.2, 0.2, 1.0);
    // FragColor.a *= fading;
}