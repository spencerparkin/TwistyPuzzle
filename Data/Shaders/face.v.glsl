#version 130

varying vec3 trianglePoint;
varying vec3 color;

void main()
{
	trianglePoint = gl_Vertex.xyz;
	color = gl_Color.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}