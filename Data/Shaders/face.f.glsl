#version 130

uniform vec3 lineSegEndPointA[4];
uniform vec3 lineSegEndPointB[4];
uniform vec3 borderColor;
uniform float borderThickness;

varying vec3 trianglePoint;
varying vec3 color;

void distanceToLineSeg( in vec3 vertexA, in vec3 vertexB, in vec3 point, out float distance )
{
	vec3 lineSeg = vertexB - vertexA;
	vec3 vector = point - vertexA;
	float lineSegLength = length( lineSeg );

	float projDistance = dot( vector, lineSeg ) / lineSegLength;
	float lerpValue = projDistance / lineSegLength;

	if( lerpValue < 0.0 )
		distance = length( point - vertexB );
	else if( lerpValue > 1.0 )
		distance = length( vector );
	else
	{
		float hypotenuse = length( vector );
		distance = sqrt( max( hypotenuse * hypotenuse - projDistance * projDistance, 0.f ) );
	}
}

void main()
{
	float smallestDistance = 1000.f;

	// This loop should get unrolled.
	for( int i = 0; i < 4; i++ )
	{
		float distance;
		distanceToLineSeg( lineSegEndPointA[i], lineSegEndPointB[i], trianglePoint, distance );
		smallestDistance = min( smallestDistance, distance );
	}
	
	float blendFactor = min( smallestDistance / borderThickness, 1.f );
	vec3 blendedColor = mix( borderColor, color, blendFactor );
	gl_FragColor = vec4( blendedColor, 1.f );
}