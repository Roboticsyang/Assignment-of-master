clear;clc;
%%���е�������
%% (1)������
figure(1);
t=0:pi/100:2*pi;
r=1;%�Ŵ�����
x=r*(2*sin(t)-sin(2*t));
y=r*(2*cos(t)-cos(2*t));
subplot(3,1,1);% x��ʾ���м��У�y��ʾ�м��У�n�ڼ���ͼƬ
plot(x,y,'r');%�ú�ɫ���߻�ͼ
title('������');
grid;%������

%������������ߵ�tֵ����x����Сֵ
m=0.5*pi:0.001*pi:pi;
y=abs(cos(m)-cos(2*m));
[a,b]=min(y);
m(b);
hold on
%�����ߵ�����������ֵ
t=-m(b):pi/10:m(b);%ȡ�㻭��ֵ��
r=1;
x=r*(2*sin(t)-sin(2*t));
y=r*(2*cos(t)-cos(2*t));
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=-inf;         %  S'(xn)=f'(xn)=yn
x0=r*(2*sin(t)-sin(2*t));
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %���Ƶ�һ�߽�������ֵ����ͼ��
grid on
hold on
plot(x,y,'o')%��ֵ��
xlabel('�Ա��� X'), ylabel('����� Y')

%% (2)����
figure(1);
r = 1;
t = -2*r*pi:0.001:2*r*pi;
x = r*(t-sin(t));
y = r*(1-cos(t));
subplot(3,1,2);
plot(x,y,'r');
title('����');
grid;

hold on
%���ߵ�����������ֵ
t=0:pi/10:2*r*pi;%ȡ�㻭��ֵ��
r=1;
x = r*(t-sin(t));
y = r*(1-cos(t));
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=-inf;          %  S'(xn)=f'(xn)=yn
x0=0:pi/10:2*r*pi;%ȡ���ֵ
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %���Ƶ�һ�߽�������ֵ����ͼ��
grid on
hold on
plot(x,y,'o')%��ֵ��
xlabel('�Ա��� X'), ylabel('����� Y')

%% (3)������
figure(1);
r = 1;
t = -2*r*pi:0.001:2*r*pi;%�涨t��ȡֵ,���ȥ0.001
x=r*cos(t).^3;
y=r*sin(t).^3;
subplot(3,1,3);
plot(x,y,'r')
title('������');
grid;

hold on
%���ߵ�����������ֵ
t=1.5*r*pi:pi/20:2*r*pi;%ȡ�㻭��ֵ��
r=1;
x=r*cos(t).^3;
y=r*sin(t).^3;
y0=+inf;         %  S'(x0)=f'(x0)=y0   
yn=0;          %  S'(xn)=f'(xn)=yn
x0=r*cos(t).^3;%ȡ���ֵ
s=threesimple(x,y,x0,y0,yn);
plot(x0,s,'b');        %���Ƶ�һ�߽�������ֵ����ͼ��
grid on
hold on
plot(x,y,'o')%��ֵ��
xlabel('�Ա��� X'), ylabel('����� Y')