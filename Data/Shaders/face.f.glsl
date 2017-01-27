#version 110

uniform vec3 triangleVertex[3];
uniform float borderMask[3];
uniform float maxSubTriangleArea;
uniform vec3 borderColor;

varying vec4 trianglePoint;

void main()
{
	float smallestSubTriangleArea = 1000.0;
	
	for( int i = 0; i < 3; i++ )
	{
		vec3 vertexA = triangleVertex[i];
		vec3 vertexB = triangleVertex[ mod( i + 1, 3 ) ];
		
		vec3 edgeA = vertexA - trianglePoint;
		vec3 edgeB = vertexB - trianglePoint;
		
		vec3 cross = cross( edgeA, edgeB );
		subTriangleArea = length( cross ) / 2.0;
		subTriangleArea += borderMask[i] * maxSubTriangleArea;
		
		smallestSubTriangleArea = min( subTriangleArea, smallestSubTriangleArea );
	}
	
	float areaRatio = min( smallestSubTriangleArea / maxSubTriangleArea, 1.0 );
	
	vec3 color = mix( borderColor, gl_Color, areaRatio );
	
	gl_FragColor = vec4( color, 1.0 );
}