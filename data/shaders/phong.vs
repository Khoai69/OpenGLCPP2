
attribute vec3 a_pos;
attribute vec3 a_normal;
attribute vec2 a_uv;

uniform mat4 u_model; 
uniform mat4 u_mvp;

varying vec3 v_normal;
varying vec3 v_pos;
varying vec2 v_uv;

float determinant(mat2 m) 
{
	return m[0][0]*m[1][1] - m[1][0]*m[0][1] ;
 }

  
  mat4 transpose(mat4 inMatrix)
  {
    highp vec4 i0 = inMatrix[0];
    highp vec4 i1 = inMatrix[1];
    highp vec4 i2 = inMatrix[2];
    highp vec4 i3 = inMatrix[3];

    highp mat4 outMatrix = mat4(
                 vec4(i0.x, i1.x, i2.x, i3.x),
                 vec4(i0.y, i1.y, i2.y, i3.y),
                 vec4(i0.z, i1.z, i2.z, i3.z),
                 vec4(i0.w, i1.w, i2.w, i3.w)
                 );

    return outMatrix;
}

  mat2 inverse(mat2 m) 
  {
	  float d = 1.0 / determinant(m) ;
	  return d * mat2( m[1][1], -m[0][1], -m[1][0], m[0][0]) ;
  }

  mat4 inverse(mat4 m)
   {
	  mat2 a = inverse(mat2(m));
	  mat2 b = mat2(m[2].xy,m[3].xy);
	  mat2 c = mat2(m[0].zw,m[1].zw);
	  mat2 d = mat2(m[2].zw,m[3].zw);

	  mat2 t = c*a;
	  mat2 h = inverse(d - t*b);
	  mat2 g = - h*t;
	  mat2 f = - a*b*h;
	  mat2 e = a - f*t;

	  return mat4( vec4(e[0],g[0]), vec4(e[1],g[1]), 
					  vec4(f[0],h[0]), vec4(f[1],f[1]) );
  }

void main()
{
    v_normal =vec3(u_model * vec4(a_normal, 0.0));
    v_pos = vec3(u_model * vec4(a_pos, 1.0));
	v_uv = a_uv;
    gl_Position = u_mvp * vec4(a_pos, 1.0) ;
}  
   