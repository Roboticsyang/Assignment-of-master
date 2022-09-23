clear;clc;
%%运行的主函数
%样本数据
X = [2;3;4;5;6;7;8;9;10;11];
Y = [58;50;44;38;34;30;29;26;25;24];
syms x;
syms t;
%% (2)a*e^(bx)
Z = log(Y);
m0 = [1;1;1;1;1;1;1;1;1;1];%定义基底
m1 = X;
m = [m0'*m0 m0'*m1; m1'*m0 m1'*m1];
c = m\[Z'*m0; Z'*m1];
c0 = c(1,1);
c1 = c(2,1);
a = exp(c0);
b = c1;
y(t) = a*exp(b*t);
%拟合误差T3
T3 = 0;
for i=1:1:10
    T3 = T3+double((y(X(i,1))-Y(i,1))^2);
end
T3
y(x) = a+b*log(x);
x=2:0.1:11;
plot(x,y(x),'r');%用红色曲线画图
title(['y=a*e^(bx) 拟合误差：',num2str(T3)]);
grid;%画网格