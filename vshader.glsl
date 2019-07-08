#version 330



uniform int wavingflag;
uniform float uTime;
in vec4 vPosition;
in vec4 vColor;
out vec4 color;
out vec4 position;

void main()
{
	color = vColor;
	position = vPosition;

	float theta, s, c, time, theta2, s2, c2,oc;

	time = uTime;
	mat4 m1 = mat4(1.0f);//rotating matrix
	theta = time*30/180.0*3.141592;
	s = sin(theta);
	c = cos(theta);
	oc=1.0-c;
	
	float x = 0.0;
	float y = -sqrt(2)/2.0;
	float z = -sqrt(2)/2.0;
	float w = 1.0;

	m1[0][0] = oc*x*x+c;	m1[1][0] = oc*x*y-z*s;	m1[2][0] = oc*z*x+y*s;	m1[3][0] = 0.0f;
	m1[0][1] = oc*x*y+z*s;	m1[1][1] = oc*y*y+c;	m1[2][1] = oc*y*z-x*s;	m1[3][1] = 0.0f;
	m1[0][2] = oc*z*x-y*s;	m1[1][2] = oc*y*z+x*s;	m1[2][2] = oc*z*z+c;	m1[3][2] = 0.0f;
	m1[0][3] = 0.0f;		m1[1][3] = 0.0f;		m1[2][3] = 0.0f;		m1[3][3] = 1.0f;
	
	mat4 m2 = mat4(1.0f);//camera down
	theta2 =-45/180.0*3.141592;
	s2 = sin(theta2);
	c2 = cos(theta2);
	m2[0][0] = 1.0f;	m2[1][0] = 0.0f;	m2[2][0] = 0.0f;	m2[3][0] = 0.0f;
	m2[0][1] = 0.0f;	m2[1][1] = c2;		m2[2][1] = -s2;		m2[3][1] = 0.0f;
	m2[0][2] = 0.0f;	m2[1][2] = s2;		m2[2][2] = c2;		m2[3][2] = 0.0f;
	m2[0][3] = 0.0f;	m2[1][3] = 0.0f;	m2[2][3] = 0.0f;	m2[3][3] = 1.0f;

	if(wavingflag==1)
	{
		float x,y;
		x = position.x;
		y = position.y;
		float r = sqrt((x*x)+(y*y));
		float e = exp(-7*r*r)*cos(r*30-5*time);
		if(position.x!=0.8 && position.x!=-0.8 && position.y!=0.8 && position.y!=-0.8)
		{
			position.z = e/3;
		}
	}
	gl_Position = m1*m2*position;
}