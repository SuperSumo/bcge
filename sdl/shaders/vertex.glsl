#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4 inVertex;
in vec4 inColor;
out vec4 vsColor;
out vec4 vsVertex;

void main()
{
	vsVertex = projection*view*model*inVertex;
	vsColor = inColor;

	gl_Position = vsVertex;
}
