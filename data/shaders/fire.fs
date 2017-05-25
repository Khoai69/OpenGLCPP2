precision mediump float;

uniform sampler2D  tex0; //tex
uniform sampler2D  tex1; //tex_disp
uniform sampler2D  tex2; //tex_mask

#define tex             tex0
#define tex_disp      tex1
#define tex_mask    tex2 

uniform float u_time;
varying vec2 v_uv;



void main()
{

  vec2 disp = texture2D(tex_disp, vec2(v_uv.x, v_uv.y + u_time)).rg; //where u_time holds the total time

  vec2 offset = (2.0 * disp - 1.0) * 0.1; //dmax = -0.2

  vec2 tex_coords_displaced = v_uv + offset;
  vec4 fire_color = texture2D (tex, tex_coords_displaced);

  vec4 alphavalue = texture2D(tex_mask, v_uv);

  gl_FragColor = fire_color * (1.0, 1.0, 1.0, alphavalue.r);
 

}
