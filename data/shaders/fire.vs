attribute vec3 a_pos;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_mvp;

void main()
{
	vec4 pos = u_mvp * vec4(a_pos, 1.0) ;
  v_uv = a_uv;
	gl_Position = pos;
}
   