precision mediump float;

varying vec3 v_normal;
varying vec3 v_pos;

uniform vec3 u_cameraPos;
uniform samplerCube tex0;

void main()
{             
    vec3 eye = u_cameraPos - v_pos;
    vec3 reflect_dir = reflect(normalize(-eye), normalize(v_normal));
    gl_FragColor = textureCube(tex0, reflect_dir);
}