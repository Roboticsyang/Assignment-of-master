#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//GL_COLOR_BUFFER_BIT表示清除颜色
	glClearColor(1.0, 1.0, 1.0, 1.0);//背景颜色
	glColor3f(1.0f, 0.0f, 0.0f);//指定线条颜色
	glLineWidth(5.0f);//指定线宽
	glPointSize(5.0f);//点的大小(默认为1个像素)

	//glEnable(GL_LINE_STIPPLE);//启动虚线模式，使用glDisable(GL_LINE_STIPPLE)可以关闭
	//glLineStipple(2, 0x0F0F);//设置虚线的样式
	//glBegin(GL_LINES); ///在下面2个点之间画一条虚线
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(0.5f, 0.5f);

	int i;
	int n = 100;
	glBegin(GL_LINE_LOOP); //GL_POINTS画点 GL_POLYGON表示画多边形（填充，由点连接） GL_LINE_LOOP不填充的闭合折线
	//GL_LINES 两两连线  GL_LINE_STRIP)不闭合的折线
	//for (i = 0; i < n; ++i)//圆
	//{
	//	glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));//点的位置，循环
	//}

	glVertex2f(0.0f, 0.0f);//矩形或者三角形
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.0f, 0.5f);



	glEnd();
	glFlush(); //保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）。
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //设置显示方式
	glutInitWindowPosition(100, 100); //设置窗口位置
	glutInitWindowSize(400, 400);//窗口大小
	glutCreateWindow("OpenGL程序"); //根据前面设置的信息创建窗口。参数将被作为窗口的标题。
	glutDisplayFunc(&myDisplay); //当需要画图时，请调用myDisplay函数
	glutMainLoop(); //进行一个消息循环
	return 0;
}

