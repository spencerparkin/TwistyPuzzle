#version 110

varying vec4 trianglePoint;

void main()
{
	trianglePoint = gl_Vertex;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}