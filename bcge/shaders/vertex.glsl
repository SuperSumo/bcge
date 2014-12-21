#version 150

in vec4 inVertex;
in vec4 inColor;
out vec4 vsColor;
out vec4 vsVertex;

void main()
{
	vsColor = inColor;
	gl_Position = inVertex;
}
