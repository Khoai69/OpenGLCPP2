precision mediump float;
uniform sampler2D tex0;
varying vec2 v_uv;

void main()
{
	vec4 final_color = texture2D(tex0, v_uv);
	vec3 lightColor = vec3(0.33, 0.42, 0.18);
	vec3 toyColor = vec3(1.0, 0.5, 0.31);
	gl_FragColor = vec4(lightColor * toyColor, 1.0);
	//gl_FragColor = texture2D(tex0, v_uv);
}
