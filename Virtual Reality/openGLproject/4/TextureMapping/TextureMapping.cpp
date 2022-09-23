// TextureMapping.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <GL/GLAUX.H>
#include <GL/gluax.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>   
#include<iostream>
#pragma comment(lib, "glut32.lib")  
using namespace std;
GLfloat roate = 0.0;//设置旋转速率
GLfloat rote = 0.0;//旋转角度
GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//当左键按下时记录鼠标坐标  
GLfloat oldy;

#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];

// create 2D texture
void makeStripeImage(void)
{
    int j;
    for (j = 0; j < stripeImageWidth; j++)
    {
        stripeImage[4 * j + 0] = (GLubyte)((j <= 4) ? 255 : 0);
        stripeImage[4 * j + 1] = (GLubyte)((j > 4) ? 255 : 0);
        stripeImage[4 * j + 2] = (GLubyte)0;
        stripeImage[4 * j + 3] = (GLubyte)255;
    }
}

static GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat slanted[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat* currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);//背景黑色  
    //glEnable(GL_DEPTH_TEST);//打开深度茶壶就看不到了
    glShadeModel(GL_SMOOTH);
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);//纹理环绕方式GL_REPEAT 重复
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);//截断

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        /*用来设置纹理参数，通常需要设置的参数有4个：
        第一个是GL_TEXTURE_MAG_FILTER，指当目标大于当前纹理图像时如何处理；
        第二个是GL_TEXTURE_MIN_FILTER，指当目标小于当前纹理图像时如何处理；
        第三个是GL_TEXTURE_WRAP_S，指当纹理坐标的第一维坐标值大于1.0或者小于0.0时如何处理。*/
    glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    //currentGenMode = GL_EYE_LINEAR;
    //currentPlane = GL_EYE_PLANE;


    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
    roangles = 45.0f;
}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); //画笔黄色
    glLoadIdentity();  //加载单位矩阵  
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rote, 0.0f, 1.0f, 0.0f);
    glRotatef(anglex, 1.0, 0.0, 0.0);
    glRotatef(angley, 0.0, 1.0, 0.0);
    glRotatef(anglez, 0.0, 0.0, 1.0);
    glutSolidTeapot(1.5);
    rote += roate;

    glutSwapBuffers();
};

void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            roate = 0;
            rote = 0;
            oldx = x;//当左键按下时记录鼠标坐标  
            oldy = y;
            cout << "left" << endl;
        }

    }
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            roate += 0.5f;
            cout << "right" << endl;
        }

    }

}
void motion(int x, int y)
{
    GLint deltax = oldx - x;
    GLint deltay = oldy - y;
    anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
    angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
    anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
    oldx = x;//记录此时的鼠标坐标，更新鼠标坐标  
    oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控  
    glutPostRedisplay();
    glutPostRedisplay();
}

void idle()
{
    roangles += 0.05f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutIdleFunc(idle);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}


