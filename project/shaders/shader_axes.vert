#version 120

uniform mat4 camera_projection;
uniform mat4 camera_modelview;

varying vec4 color;


void main (void)
{
    vec4 p=gl_Vertex;
    p.xyz *= 0.10;
    gl_Position=camera_projection*camera_modelview*p;
    gl_Position.xy += vec2(0.85,-0.8);

    color=gl_Color;
}
