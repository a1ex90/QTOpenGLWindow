#version 130

in vec3 vertexPosition;

out vec3 position;

uniform mat4 modelViewMatrix;
uniform mat4 mvp;

void main()
{
	position = vec3( modelViewMatrix * vec4( vertexPosition, 1.0 ) );

    gl_PointSize = 3.0f;
    gl_Position = mvp * vec4( vertexPosition, 1.0 );
}
