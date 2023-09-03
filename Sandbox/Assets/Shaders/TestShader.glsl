#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
}	


#type fragment
#version 460 core
			
layout(location = 0) out vec4 Color;

in vec4 v_Color;

void main()
{
    Color = vec4(1.0, 0.0, 0.0, 1.0);
}