clear;clc;
%%运行的主函数
%% (1)心脏线
figure(1);
t=0:pi/100:2*pi;
r=1;%放大因子
x=r*(2*sin(t)-sin(2*t));
y=r*(2*cos(t)-cos(2*t));
subplot(3,1,1);% x表示共有几行，y表示有几列，n第几幅图片
plot(x,y,'r');%用红色曲线画图
title('心脏线');
grid;%画网格

%求心脏线最左边的t值，即x的最小值
m=0.5*pi:0.001*pi:pi;
y=abs(cos(m)-cos(2*m));
[a,b]=min(y);
m(b);
hold on
%心脏线的三次样条插值
t=-m(b):pi/10:m(b);%取点画插值点
r=1;
x=r*(2*sin(t)-sin(2*t));
y=r*(2*cos(t)-cos(2*t));
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=-inf;         %  S'(xn)=f'(xn)=yn
x0=r*(2*sin(t)-sin(2*t));
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %绘制第一边界条件插值函数图像
grid on
hold on
plot(x,y,'o')%插值点
xlabel('自变量 X'), ylabel('因变量 Y')

%% (2)摆线
figure(1);
r = 1;
t = -2*r*pi:0.001:2*r*pi;
x = r*(t-sin(t));
y = r*(1-cos(t));
subplot(3,1,2);
plot(x,y,'r');
title('摆线');
grid;

hold on
%摆线的三次样条插值
t=0:pi/10:2*r*pi;%取点画插值点
r=1;
x = r*(t-sin(t));
y = r*(1-cos(t));
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=-inf;          %  S'(xn)=f'(xn)=yn
x0=0:pi/10:2*r*pi;%取点插值
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %绘制第一边界条件插值函数图像
grid on
hold on
plot(x,y,'o')%插值点
xlabel('自变量 X'), ylabel('因变量 Y')

%% (3)星形线
figure(1);
r = 1;
t = -2*r*pi:0.001:2*r*pi;%规定t的取值,间隔去0.001
x=r*cos(t).^3;
y=r*sin(t).^3;
subplot(3,1,3);
plot(x,y,'r')
title('星形线');
grid;

hold on
%摆线的三次样条插值
t=1.5*r*pi:pi/20:2*r*pi;%取点画插值点
r=1;
x=r*cos(t).^3;
y=r*sin(t).^3;
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=0;          %  S'(xn)=f'(xn)=yn
x0=r*cos(t).^3;%取点插值
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %绘制第一边界条件插值函数图像
grid on
hold on
plot(x,y,'o')%插值点
xlabel('自变量 X'), ylabel('因变量 Y')