clear;clc;
%%运行的主函数
%样本数据
X = [2;3;4;5;6;7;8;9;10;11];
Y = [58;50;44;38;34;30;29;26;25;24];
syms x;
syms t;
%% (2)a+blnx
T = log(X);
m0 = [1;1;1;1;1;1;1;1;1;1];%定义基底
m1 = T;
m = [m0'*m0 m0'*m1; m1'*m0 m1'*m1];
c = m\[Y'*m0; Y'*m1];
a = c(1,1);
b = c(2,1);
y(t) = a+b*t;
%拟合误差T2
T2 = 0;
for i=1:1:10
    T2 = T2+double((y(T(i,1))-Y(i,1))^2);
end
T2
y(x) = a+b*log(x);
x=2:0.1:11;
plot(x,y(x),'r');%用红色曲线画图
title(['y=a+blnx 拟合误差：',num2str(T2)]);
grid;%画网格