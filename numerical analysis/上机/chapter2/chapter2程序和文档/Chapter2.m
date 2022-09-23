clear;clc;
%% (1)对f(x) = x*exp(-x)以x0=2.0进行计算
syms x;  % 定义一个符号x
f(x) = x*exp(-x);    %定义函数,exp(n)表示e的n次方,
g(x) = diff(f(x));   %g(x)是f(x)的一阶导数。
fprintf('f(x)=');disp(f); 
fprintf('f’(x)=');disp(g);
e = 10^(-6);%根的容许误差
a = -1.0;
b = 2.0;
x0 = b;
x1 = double( x0-f(x0)/g(x0));%sysm字符转换为double型
while(abs(f(x1))>e)
    if (a<x1)&&(x1<b)
            if x1<0
                a=x1;
            else
                b=x1;
            end
    else
        x1=(a+b)/2;
            if x1<0
                a=x1;
            else
                b=x1;
            end
    end
end
fprintf('第(1)题f(x) = x*exp(-x)的近似根：');disp(x1);
%% (2)对f(x) = arctanx 以x0=1.45进行计算
syms x;  % 定义一个符号x
f(x) = atan(x);    %定义函数,exp(n)表示e的n次方,
g(x) = diff(f(x));   %g(x)是f(x)的一阶导数。
fprintf('f(x)=');disp(f);
fprintf('f’(x)=');disp(g);
e = 10^(-6);%根的容许误差
a = -1.0;
b = 1.45;
x0 = b;
x1 = double( x0-f(x0)/g(x0));%sysm字符转换为double型
while(abs(f(x1))>e)
    if (a<x1)&&(x1<b)
            if x1<0
                a=x1;
            else
                b=x1;
            end
    else
        x1=(a+b)/2;
            if x1<0
                a=x1;
            else
                b=x1;
            end
    end
end
fprintf('第(2)题f(x) = arctanx的近似根：');disp(x1);

