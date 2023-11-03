#type vertex
#version 460 core

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformMatrix;
uniform mat4 u_InverseMatrix;

vec3 gridPlane[4] = vec3[4](vec3(-1, 1, 0), vec3(1, 1, 0), vec3(-1, -1, 0), vec3(1, -1, 0));

void main()
{
    gl_Position = u_ViewProjection * vec4(gridPlane[gl_VertexID].xyz, 1.0);
}	


#type fragment
#version 460 core

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}