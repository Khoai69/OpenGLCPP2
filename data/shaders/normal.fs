precision mediump float;

varying vec2 v_uv;
varying vec3 v_bitangent;
varying vec3 v_tangent;
varying vec3 v_normal;
varying vec3 v_pos;

uniform vec3 u_light_pos;
uniform sampler2D  tex0; //tex
uniform sampler2D  tex1; //tex_normal

#define tex             tex0
#define tex_normal		tex1
void main()
{
	vec3 light_direction = normalize(v_pos - u_light_pos);
    vec3 normal = texture2D(tex_normal,v_uv).xyz;
    mat3 TBN = mat3(normalize(v_tangent),normalize(v_bitangent),normalize(v_normal));
    vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));
    float diffuse = max(0.0, dot(-light_direction,normalW));
    vec4 color = texture2D(tex,v_uv);
	//gl_FragColor = texture2D(tex1,v_uv);
    gl_FragColor = vec4(diffuse * color.xyz,color.a);
}


