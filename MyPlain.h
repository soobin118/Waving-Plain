#pragma once

#include<vgl.h>
#include<InitShader.h>
#include<vec.h>
#include<mat.h>

vec4 * vertex_pos;
vec4 * vertex_col;
class MyPlain {
public:
	int numVertices;
	GLuint vao, buffer, prog;
	vec4 * points;
	vec4 * colors;
	int sizeofPoints, sizeofColors;
	int ind;

	MyPlain() {
		points = NULL;
		colors = NULL;
	}
	~MyPlain() {
		delete[] points;
		delete[] colors;
		delete[] vertex_pos;
		delete[] vertex_col;
	}
	void makeQuad(int a, int b, int c, int d)
	{
		points[ind] = vertex_pos[a];	colors[ind] = vertex_col[a];	ind++;
		points[ind] = vertex_pos[b];	colors[ind] = vertex_col[a];	ind++;
		points[ind] = vertex_pos[c];	colors[ind] = vertex_col[a];	ind++;

		points[ind] = vertex_pos[c];	colors[ind] = vertex_col[a];	ind++;
		points[ind] = vertex_pos[d];	colors[ind] = vertex_col[a];	ind++;
		points[ind] = vertex_pos[a];	colors[ind] = vertex_col[a];	ind++;
	}
	void makePlain(int checkNum) {
		ind = 0;
		
		for (int i = 0; i < (checkNum + 1)*(checkNum + 1); i++)
		{
			if (i < checkNum*(checkNum + 1) && (i - checkNum) % (checkNum + 1) != 0)
			{
				makeQuad(i, i + 1, i + 1 + checkNum + 1, i + checkNum + 1);
			}
		}

	}

	void initPosition(int checkNum) {

		numVertices = (checkNum)*(checkNum)*6;

		points = new vec4[numVertices];
		colors = new vec4[numVertices];

		sizeofPoints = sizeof(vec4)*numVertices;
		sizeofColors = sizeof(vec4)*numVertices;

		vertex_pos = new vec4[(checkNum+1)*(checkNum+1)];
		vertex_col = new vec4[(checkNum + 1)*(checkNum + 1)];


		//make vertex_pos and vertex_col array

		float x = -0.8;
		float y = 0.8;
		float t = 1.6 / (float)checkNum;

		for (int i = 0; i < (checkNum+1); i++)
		{
			for (int j = 0; j < (checkNum + 1); j++)
			{
				vertex_pos[(i*(checkNum + 1)) + j].x = x+(t*j);
				vertex_pos[(i*(checkNum + 1)) + j].y = y-(t*i);
				vertex_pos[(i*(checkNum + 1)) + j].z = 0.0;
				vertex_pos[(i*(checkNum + 1)) + j].w = 1;
				if ((i + j) % 2 == 0)
					vertex_col[(i*(checkNum + 1)) + j] = vec4(0.6,0.6,0.6, 1.0);
				else
					vertex_col[(i*(checkNum + 1)) + j] = vec4(0.5, 0.5, 0.5, 1.0);
			}
		}

		makePlain(checkNum);
	}

	void initPlain(int checkNum) {
		initPosition(checkNum);

		// send data to GPU
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeofPoints + sizeofColors, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeofPoints, points);
		glBufferSubData(GL_ARRAY_BUFFER, sizeofPoints, sizeofColors, colors);

		// upload shaders to GPU
		prog = InitShader("vshader.glsl", "fshader.glsl");
		glUseProgram(prog);

		// link the data to the vshader
		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, false, 0, BUFFER_OFFSET(0));

		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, false, 0, BUFFER_OFFSET(sizeofPoints));
	}

	void redraw(int checkNum)
	{
		ind = 0;
		initPosition(checkNum);
		// send data to GPU
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeofPoints + sizeofColors, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeofPoints, points);
		glBufferSubData(GL_ARRAY_BUFFER, sizeofPoints, sizeofColors, colors);

		// upload shaders to GPU
		glUseProgram(prog);

		// link the data to the vshader
		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, false, 0, BUFFER_OFFSET(0));

		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, false, 0, BUFFER_OFFSET(sizeofPoints));
		
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		
	}

	void draw(float time,int wf) {
		glBindVertexArray(vao);
		glUseProgram(prog);

		GLuint uTime = glGetUniformLocation(prog, "uTime");
		glUniform1f(uTime, time);

		GLuint wavingflag = glGetUniformLocation(prog, "wavingflag");
		glUniform1i(wavingflag,wf);
	
	
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		

	}
};