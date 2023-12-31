#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main()
{
    v_Position = a_Position;
    gl_Position = vec4(a_Position, 1.0);
}	


#type fragment
#version 460 core

precision highp float;
float noise(vec3 point)
{
    float r = 0.0;
    for (int i = 0; i < 16; i++)
    {
        vec3 D;
        vec3 p = point + mod(vec3(i, i / 4, i / 8), vec3(4.0, 2.0, 2.0)) + 1.7 * sin(vec3(i, 5 * i, 8 * i));
        vec3 C = floor(p);
        vec3 P = p - C - 0.5;
        vec3 A = abs(P);
        C += mod(C.x + C.y + C.z, 2.0) * step(max(A.yzx, A.zxy), A) * sign(P);
        D = 34.0 * sin(987.0 * float(i) + 876.0 * C + 76.0 * C.yzx + 765.0 * C.zxy);
        P = p - C - 0.5;
        r += sin(6.3 * dot(P, fract(D) - 0.5)) * pow(max(0.0, 1.0 - 2.0 * dot(P, P)), 4.0);
    }
    return 0.5 * sin(r);
}

uniform float uTime;

layout(location = 0) out vec4 Color;

in vec3 v_Position;

void main()
{
    Color = vec4(1.0,  1.0, 1.0, 1.0);
    Color.x = sin(v_Position.x) * sin(v_Position.x) - cos(v_Position.x) * cos(v_Position.x);
    Color.y = sin(v_Position.y) * sin(v_Position.y) - cos(v_Position.y) * cos(v_Position.y);
    Color.z = sin(v_Position.z) * sin(v_Position.z) - cos(v_Position.z) * cos(v_Position.z);
}