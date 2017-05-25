attribute vec3 a_pos;
varying vec3 v_pos;
uniform mat4 u_mvp;

void main()
{
	vec4 pos = u_mvp * vec4(a_pos, 1.0) ;
	v_pos = a_pos;
	gl_Position = pos;
}
   