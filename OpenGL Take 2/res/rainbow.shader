#shader vertex
#version 330 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

uniform mat4 u_matrix;

out vec3 color;

void main()
{
	color = vertex_color;
	gl_Position = u_matrix * vec4(vertex_position, 1.0);
}



#shader fragment
#version 330 core
in vec3 color;
out vec3 frag_color;

void main()
{
	frag_color = color;
}

