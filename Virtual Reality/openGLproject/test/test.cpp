// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          //设置窗口背景色为白色
    glMatrixMode(GL_PROJECTION);        //指定设定投影参数
    gluOrtho2D(0.0, 200, 0.0, 150.0);            //设置投影参数
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);        //用当前背景色填充窗口
    glColor3f(0.0f, 0.0f, 0.0f);                  //设置当前的绘图颜色为黑色
    glRectf(50.0f, 100.0f, 150.0f, 50.0f);          //绘制一个矩形
    glFlush();                          //清空OpenGL命令缓冲区，执行OpenGL命令 
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //初始化窗口的显示模式
    glutInitWindowPosition(100, 100);                //设置窗口的位置
    glutInitWindowSize(400, 400);                   //设置窗口的大小
    glutCreateWindow("第一个OpenGL程序");       //创建窗口
    glutDisplayFunc(&myDisplay);                  //设置当前窗口的显示回调函数
    Initial();                                     //完成窗口初始化
    glutMainLoop();                              //启动主 GLUT事件处理循环
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
