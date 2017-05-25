precision mediump float;

varying vec2 v_uv;
varying vec3 v_bitangent;
varying vec3 v_tangent;
varying vec3 v_normal;
varying vec3 v_pos;

uniform vec3 u_light_pos;
uniform vec3 u_cameraPos;
uniform sampler2D  tex0; //tex
uniform sampler2D  tex1; //tex_normal
uniform sampler2D  tex2; //tex disp
uniform samplerCube  tex3; //tex_cube
uniform float u_time;

#define tex             tex0
#define tex_normal		tex1
#define tex_disp        tex2
#define tex_cube		tex3

float calc_dmax()
{
	return clamp(v_uv.x - 0.7, 0.025, 0.1);
}
float calc_water_alpha()
{
	return clamp(v_uv.x - 0.7, 0.0, 1.0);
}
float calc_light_strenght()
{
	return clamp(v_uv.x , 1.0, 2.0);
}
vec2 calc_displacement()
{
	 vec2 disp = texture2D(tex_disp, vec2(v_uv.x, v_uv.y + u_time)).rg;
	 vec2 offset = (2.0 * disp - 1.0) * calc_dmax();
	 vec2 tex_coords_displaced = v_uv + offset;
	 return tex_coords_displaced;
}

void main()
{

	vec4 stage1,stage2,stage3,stage4,stage5,stage6,stage7,stage8;
	vec4 water_color = vec4(64.0 / 255.0,164.0 / 255.0,223.0 /255.0, 0.0);
	water_color.a = calc_water_alpha();
	vec4 color = texture2D(tex,v_uv);
	vec4 final_color = vec4(1.0, 1.0, 1.0, 1.0);
	float FresnelPower = 1.0;


	//stage 1 - reflect
	vec3 norm = normalize(v_normal);
	vec3 eye = normalize(u_cameraPos - v_pos);
	vec3 light_direction = normalize(u_light_pos - v_pos);
	vec3 reflect_dir = reflect(-eye, norm);

	stage1 = textureCube(tex_cube, reflect_dir);
	final_color = stage1; //DEBUG

	
	//stage 2 - normal
	vec3 normal_tex = texture2D(tex_normal,calc_displacement()).xyz; //displacement normal
	mat3 TBN = mat3(normalize(v_tangent),normalize(v_bitangent),normalize(v_normal));
	vec3 normalW = normalize(TBN * (2.0 * normal_tex - 1.0));
	float diffuse = max(0.0, dot(light_direction,normalW)) * calc_light_strenght();
	
	stage2 =  vec4(diffuse * stage1.xyz, stage1.a) ;
	final_color = stage2; //DEBUG

	//stage3 - fresnel
	float fresnel = pow((1.0 - abs(dot(-eye, normalW))), FresnelPower);
	stage3 = fresnel *stage2;//vec4(fresnel * stage2.xyz, stage2.a);
	final_color = color + stage3; //DEBUG

	//stage4 - displacement color
	color = texture2D(tex,calc_displacement());
	stage4 = (stage3 * water_color) + color; //surface water color
	final_color = stage4; //DEBUG

	//final stage
	final_color = stage4;
	

	gl_FragColor = final_color;
}


