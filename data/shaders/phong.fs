precision mediump float;

varying vec3 v_normal;
varying vec3 v_pos;
varying vec2 v_uv;

uniform vec3 u_light_pos;
uniform vec3 u_light_color;
uniform vec3 u_cameraPos;
uniform sampler2D tex0;


void main()
{         
	vec4 objColor = texture2D(tex0, v_uv);
	vec4 final_color = vec4(1.0, 1.0, 1.0, 1.0);
	float weight = 0.2;
	// Ambient
    float ambients_strength = 0.1;
   vec3 ambient = vec3(1.0, 1.0, 1.0);
	// Diffuse 
   // vec3 ambient = ambients_strength * u_light_color;
    vec3 norm = normalize(v_normal);
	vec3 light_direction = normalize(u_light_pos - v_pos);
	vec3 diff = max(dot(norm, light_direction), 0.0) * u_light_color;


	// Specular
	float specular_strength = 0.5;
	vec3 reflect_vector = normalize(reflect(light_direction, norm));
	vec3 eye = normalize(u_cameraPos - v_pos);
	//vec3 specular = pow(max(dot(reflect_vector, eye), 0.0), 20.0) * u_light_color * specular_strength;
	vec3 specular = pow(max(dot(reflect_vector, eye), 0.0), 20.0) * u_light_color;

	// Combine to final color
	final_color = vec4(((ambient * weight + diff * (1.0 - weight)) * objColor.xyz + specular), objColor.w);

	//vec3 phong_color = (ambient + diff * objColor.xyz + specular) ; // where is the f*cking weight?
	//final_color = vec4(phong_color, objColor.w);
    
 
    gl_FragColor = final_color;
}