precision mediump float;

uniform samplerCube  tex0;
varying vec3 v_pos;

void main()
{
	gl_FragColor = textureCube(tex0, v_pos);
}
