attribute vec3 a_pos;

attribute vec3 a_tangent;
attribute vec3 a_bitangent;
attribute vec3 a_normal;
attribute vec2 a_uv;

varying vec2 v_uv;
varying vec3 v_bitangent;
varying vec3 v_tangent;
varying vec3 v_normal;
varying vec3 v_pos;

uniform mat4 u_mvp;
uniform mat4 u_model;

void main()
{
	vec4 pos = u_mvp * vec4(a_pos, 1.0) ;
	v_uv = a_uv;
	v_normal = normalize(vec3(u_model * vec4(a_normal, 0.0)));
	v_tangent = normalize(vec3(u_model * vec4(a_tangent, 0.0)));
	v_bitangent = normalize(vec3(u_model * vec4(a_bitangent, 0.0)));
    //v_normal = normalize((u_model * vec4(a_normal, 0.0).xyz);
    //v_tangent = normalize((u_model * vec4(a_tangent, 0.0).xyz);
    //v_bitangent = normalize((u_model * vec4(a_bitangent, 0.0).xyz);
	v_pos = vec3(u_model * vec4(a_pos, 1.0));
	gl_Position = pos;
}
 