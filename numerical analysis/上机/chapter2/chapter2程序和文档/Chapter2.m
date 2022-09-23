clear;clc;
%% (1)��f(x) = x*exp(-x)��x0=2.0���м���
syms x;  % ����һ������x
f(x) = x*exp(-x);    %���庯��,exp(n)��ʾe��n�η�,
g(x) = diff(f(x));   %g(x)��f(x)��һ�׵�����
fprintf('f(x)=');disp(f); 
fprintf('f��(x)=');disp(g);
e = 10^(-6);%�����������
a = -1.0;
b = 2.0;
x0 = b;
x1 = double( x0-f(x0)/g(x0));%sysm�ַ�ת��Ϊdouble��
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
fprintf('��(1)��f(x) = x*exp(-x)�Ľ��Ƹ���');disp(x1);
%% (2)��f(x) = arctanx ��x0=1.45���м���
syms x;  % ����һ������x
f(x) = atan(x);    %���庯��,exp(n)��ʾe��n�η�,
g(x) = diff(f(x));   %g(x)��f(x)��һ�׵�����
fprintf('f(x)=');disp(f);
fprintf('f��(x)=');disp(g);
e = 10^(-6);%�����������
a = -1.0;
b = 1.45;
x0 = b;
x1 = double( x0-f(x0)/g(x0));%sysm�ַ�ת��Ϊdouble��
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
fprintf('��(2)��f(x) = arctanx�Ľ��Ƹ���');disp(x1);

