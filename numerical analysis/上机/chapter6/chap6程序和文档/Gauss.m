function Gauss
% 复化三点高斯求积公式

a = 0;%分母不能为0，用比较小的数代替
b = 1;
epsilon = 5e-8;
tol = epsilon;
fun = @(x) atan(x)*(x)^(-1.5);
k=0; % 迭代次数
n=2; % 区间划分个数
h=b-a;
G(1)=(h/2)*((5/9)*fun(0.5*(a+b)-0.1*h*sqrt(15))+(8/9)*fun(0.5*(a+b))+(5/9)*fun(0.5*(a+b)+0.1*h*sqrt(15)));%计算未复合的Gauss
err=1;%积分误差初始化
while err>=tol
    k=k+1;
    h=1/n;
    tmp=0;
    for i=0:n-1
        tmp=tmp+(h/2)*((5/9)*fun(0.5*(a+i*h+a+(i+1)*h)-0.1*h*sqrt(15))+(8/9)*fun(0.5*(a+i*h+a+(i+1)*h))+(5/9)*fun(0.5*(a+i*h+a+(i+1)*h)+0.1*h*sqrt(15)));
    end
    
    G(k+1)=tmp;%新的值放入数组
    n=n+1;
    err=abs(G(k+1)-G(k));%更新积分误差
end
G = G(k+1)
end