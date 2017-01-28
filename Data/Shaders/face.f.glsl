#version 130

uniform vec3 triangleVertex[3];
uniform vec3 borderColor[3];
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
	float largestWeight = 0.0;

	int k = 0;

	for( int i = 0; i < 3; i++ )
	{
		int j = ( i + 1 ) % 3;
		
		float distance;
		distanceToLineSeg( triangleVertex[i], triangleVertex[j], trianglePoint, distance );

		float weight = max( 1.f - min( distance / borderThickness, 1.f ), 0.f );
		if( weight > largestWeight )
		{
			largestWeight = weight;
			k = i;
		}
	}
	
	// This is pretty crappy.  Instead of only blending with the
	// border we weigh the most with, could we weight the result
	// against all borders?  I think this could fill in some painfully
	// visible gaps when the border is drawn thicker.
	largestWeight = clamp( largestWeight, 0.f, 1.f );
	vec3 blendedColor = mix( color, borderColor[k], largestWeight );
	gl_FragColor = vec4( blendedColor, 1.f );
}