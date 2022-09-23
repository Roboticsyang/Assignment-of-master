// project3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
float width, highth;

// 将立方体的八个顶点保存到一个数组里面 
static const float vertex_list[][3] =
{
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
};

// 将要使用的顶点的序号保存到一个数组里面 
static const GLint index_list[][2] =
{
	{0, 1},
	{2, 3},
	{4, 5},
	{6, 7},
	{0, 2},
	{1, 3},
	{4, 6},
	{5, 7},
	{0, 4},
	{1, 5},
	{7, 3},
	{2, 6}
};

void DrawCube(void)// 绘制立方体
{
	int i, j;
	glBegin(GL_LINES);
	for (i = 0; i < 12; ++i) // 12 条线段
	{
		for (j = 0; j < 2; ++j) // 每条线段 2个顶点

		{
			glVertex3fv(vertex_list[index_list[i][j]]);
		}
	}
	glEnd();
}

static float rotatex = 0, rotatey = 0, rotatez = 0;//旋转
static float scalex = 1, scaley = 1, scalez = 1;//放缩
static float transx = 0, transy = 0, transz = 0;//平移
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GL_COLOR_BUFFER_BIT清除颜色缓冲区
	glColor3f(0.0, 1.0, 1.0);//指定线条颜色

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(0 + transx, 0 + transy, 0 + transz); // 平移

	glScalef(scalex, scaley, scalez);

	glRotatef(rotatex, 1, 0, 0);//围绕x轴
	glRotatef(rotatey, 0, 1, 0);//围绕y轴
	glRotatef(rotatez, 0, 0, 1);//围绕z轴
	DrawCube();

	glPopMatrix();
	glutSwapBuffers();
}


void mySpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
		transx += 0.1;
	if (key == GLUT_KEY_LEFT)
		transx -= 0.1;
	if (key == GLUT_KEY_UP)
		transy += 0.1;
	if (key == GLUT_KEY_DOWN)
		transy -= 0.1;
	glutPostRedisplay();//重新绘制
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 'x' || key == 'X')
		rotatex += 0.3;
	if (key == 'y' || key == 'Y')
		rotatey += 0.3;
	if (key == 'z' || key == 'Z')
		rotatez += 0.3;

	if (key == 'w' || key == 'W')
		transz += 0.1;
	if (key == 's' || key == 'S')
		transz -= 0.1;

	if (key == 'q' || key == 'Q')
		scalez += 0.2;

	glutPostRedisplay(); //重新调用绘制函数 
}

void mymouse(int button, int state, int x, int y)//鼠标控制缩放
{
	if (state == GLUT_DOWN)//状态按下
	{
		if (button == GLUT_LEFT_BUTTON)//判断哪个按下
		{
			scalex += 0.2;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			scaley += 0.2;
		}
		else if (button == GLUT_MIDDLE_BUTTON)
		{
			scalex -= 0.2;
			scaley -= 0.2;
			scalez -= 0.2;
		}
		glutPostRedisplay();//重新调用绘制函数
	}

	return;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);//对GLUT库进行初始化，这个函数必须在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//设置显示方式

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("鼠标左右xy轴放大,q放大z，中缩小，方向键控制xy移动，WS控制z轴移动，xyz控制旋转轴");

	//glutReshapeFunc(reShape);
	glutDisplayFunc(display);
	glutIdleFunc(display); //glutIdleFunc()函数来实现动画效果

	glutSpecialFunc(mySpecialKeyboard);//调用方向键专用
	glutMouseFunc(&mymouse);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();//进行一个消息循环
	return 0;
}