#version 110

uniform vec3 triangleVertex[3];
uniform float borderMask[3];
uniform float maxDistance;
uniform vec3 borderColor;

varying vec4 trianglePoint;

void main()
{
	float smallestDistance = 1000.0;
	
	for( int i = 0; i < 3; i++ )
	{
		int j = mod( i + 1, 3 );
		
		vec3 edge = triangleVertex[j] - triangleVertex[i];
		vec3 vec = trianglePoint - triangleVertex[i];
		
		float projDistance = dot( vec, normalize( edge ) );
		float hypotenuse = length( vec )
		float distance = sqrt( hypotenuse * hypotenuse - projDistance * projDistance );
		
		distance += borderMask[i] * maxDistance;
		smallestDistance = min( smallestDistance, distance );
	}
	
	float lengthRatio = min( smallestDistance / maxDistance, 1.0 );
	vec3 color = mix( borderColor, gl_Color, lengthRatio );
	
	gl_FragColor = vec4( color, 1.0 );
}