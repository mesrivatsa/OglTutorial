#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
out vec3 Color;

uniform mat4 transform;

void main()
{
	Color = VertexColor;
	gl_Position = transform * vec4(VertexPosition,1.0);
}