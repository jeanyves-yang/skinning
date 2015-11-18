#version 120

varying vec4 position_3d_original;
varying vec4 position_3d_modelview;
varying vec3 normal;
varying vec4 color;

uniform sampler2D texture;

uniform vec3 light=vec3(0.5,0.3,5.0);


void main (void)
{
    vec3 n=normalize(normal);

    vec3 p=position_3d_modelview.xyz;
    vec3 vertex_to_light=normalize(light-p);
    vec3 reflected_light=reflect(-vertex_to_light,n);
    vec3 user_to_vertex=normalize(-p);

    float diffuse_term=0.8*clamp(abs(dot(n,vertex_to_light)),0.0,1.0);
    float specular_term=0.2*pow(clamp(dot(reflected_light,user_to_vertex),0.0,1.0),128.0);
    float ambiant_term=0.4;

    vec4 white=vec4(1.0,1.0,1.0,0.0);
    vec2 tex_coord=gl_TexCoord[0].xy;
    vec4 color_texture=texture2D(texture,tex_coord);
    vec4 color_final=color*color_texture;

    gl_FragColor = (ambiant_term+diffuse_term)*color_final+specular_term*white;

}
