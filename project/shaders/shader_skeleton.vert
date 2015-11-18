#version 120

uniform mat4 camera_projection;
uniform mat4 camera_modelview;




void main (void)
{
    gl_Position = camera_projection*camera_modelview*gl_Vertex;
}
