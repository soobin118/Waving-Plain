#include<vgl.h>
#include"MyPlain.h"
#define spacebar 32

float time = 0;
int checkNum = 30;
int stopflag = 0;
int wavingflag = 0;
MyPlain plain;

void myInit() {
	
	plain.initPlain(checkNum);
}
void myIdle()
{
	if (stopflag == 1)
	{
		time += 0.033;
		Sleep(33);
	}
	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (checkNum > 2) {
			checkNum -= 1;
			plain.redraw(checkNum);
		}
		printf("\nDivision: %d, Num.of Triangles: %d, Num. of Vertices: %d", checkNum, checkNum * checkNum*2, checkNum * checkNum * 6);
		break;
	case '2':
		checkNum += 1;
		plain.redraw(checkNum);
		printf("\nDivision: %d, Num.of Triangles: %d, Num. of Vertices: %d", checkNum, checkNum * checkNum * 2, checkNum * checkNum * 6);
		break;
	case spacebar:
		if (stopflag == 0)
			stopflag = 1;
		else
			stopflag = 0;
		break;
	case 'w':case'W':
		if (wavingflag == 0)
			wavingflag = 1;
		else
			wavingflag = 0;
		break;
	case 'q':case 'Q':
		exit(1);
		break;
	default:
		break;
	}
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	plain.draw(time,wavingflag);

	glutSwapBuffers();
}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow("16011087 ÀÌ¼öºó");
	
	printf("A Waving Color Plain\nProgramming Assignment #2 for Computer Graphics 2\n");
	printf("Department of Digital Contents, Sejong University\n\n");
	printf("----------------------------------------------------------------\n");
	printf("'1' key: Decreasing the Number of Division\n");
	printf("'2' key: Increasing the Number of Division\n");
	printf("'w' key: Showing/hiding the waving pattern\n");
	printf("Spacebar: starting/stoping rotating and waving\n");
	printf("\n'Q' Key: Exit the program.\n");
	printf("----------------------------------------------------------------\n");
	printf("\nDivision: %d, Num.of Triangles: %d, Num. of Vertices: %d", checkNum, checkNum * checkNum * 2, checkNum * checkNum * 6);
	glewExperimental = true;
	glewInit();

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return 0;
}