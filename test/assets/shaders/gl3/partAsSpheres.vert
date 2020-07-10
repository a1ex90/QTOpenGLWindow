#version 130

in vec3 vertexPosition;
out vec3 position;
uniform mat4 modelViewMatrix;
uniform mat4 mvp;
uniform mat4 invmvp;
uniform mat4 invProjectionMatrix;
uniform vec4 color;

uniform vec4 viewport;
//attribute float R;
uniform float R;

varying mat4 VPMTInverse;
varying mat4 VPInverse;
varying vec3 centernormclip;

void main() {
    gl_Position = mvp * vec4( vertexPosition, 1.0 );
    position = vec3( modelViewMatrix * vec4( vertexPosition, 1.0 ) );
    gl_FrontColor = color;

    mat4 T = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            vertexPosition.x/R, vertexPosition.y/R, vertexPosition.z/R, 1.0/R);

    mat4 PMTt = transpose(mvp * T);

    vec4 r1 = PMTt[0];
    vec4 r2 = PMTt[1];
    vec4 r4 = PMTt[3];
    float r1Dr4T = dot(r1.xyz,r4.xyz)-r1.w*r4.w;
    float r1Dr1T = dot(r1.xyz,r1.xyz)-r1.w*r1.w;
    float r4Dr4T = dot(r4.xyz,r4.xyz)-r4.w*r4.w;
    float r2Dr2T = dot(r2.xyz,r2.xyz)-r2.w*r2.w;
    float r2Dr4T = dot(r2.xyz,r4.xyz)-r2.w*r4.w;

//    gl_Position = vec4(-r1Dr4T, -r2Dr4T, gl_Position.z/gl_Position.w*(-r4Dr4T), -r4Dr4T);


    float discriminant_x = r1Dr4T*r1Dr4T-r4Dr4T*r1Dr1T;
    float discriminant_y = r2Dr4T*r2Dr4T-r4Dr4T*r2Dr2T;
    float screen = max(float(viewport.z), float(viewport.w));

//    gl_PointSize = sqrt(max(discriminant_x, discriminant_y))*screen/(-r4Dr4T);


    // prepare varyings

    mat4 TInverse = mat4(
            1.0,          0.0,          0.0,         0.0,
            0.0,          1.0,          0.0,         0.0,
            0.0,          0.0,          1.0,         0.0,
            -vertexPosition.x, -vertexPosition.y, -vertexPosition.z, R);
    mat4 VInverse = mat4( // TODO: move this one to CPU
            2.0/float(viewport.z), 0.0, 0.0, 0.0,
            0.0, 2.0/float(viewport.w), 0.0, 0.0,
            0.0, 0.0,                   2.0/gl_DepthRange.diff, 0.0,
            -float(viewport.z+2.0*viewport.x)/float(viewport.z), -float(viewport.w+2.0*viewport.y)/float(viewport.w), -(gl_DepthRange.near+gl_DepthRange.far)/gl_DepthRange.diff, 1.0);
    VPMTInverse = TInverse*invmvp*VInverse;
    VPInverse = invProjectionMatrix*VInverse; // TODO: move to CPU
    vec4 centerclip = modelViewMatrix*gl_Vertex;
    centernormclip = vec3(centerclip)/centerclip.w;



    gl_PointSize = R;
    gl_Position = mvp * vec4( vertexPosition, 1.0 );
}