function Romberg
% 龙贝格(Romberg数值求解公式)
% inputs:
%   -fun：积分函数句柄
%   -a/b：积分上下限
%   -tol：积分误差
% Outputs:
%   -R：Romberg积分值
%   -k：迭代次数
%   -T：整个迭代过程

a = 1e-6;%分母不能为0，用比较小的数代替
b = 1;
epsilon = 5e-8;
tol = epsilon;
fun = @(x) atan(x)*(x)^(-1.5);
k=0; % 迭代次数
n=1; % 区间划分个数
h=b-a;
T=h/2*(fun(a)+fun(b));%计算T(0,0)
err=1;%积分误差初始化
while err>=tol
    k=k+1;
    h=h/2;
    tmp=0;
    for i=1:n
        tmp=tmp+fun(a+(2*i-1)*h);%此时直接用0代替a
    end
    T(k+1,1)=T(k)/2+h*tmp;%外推算法
    for j=1:k
        T(k+1,j+1)=T(k+1,j)+(T(k+1,j)-T(k,j))/(4^j-1);%外推算法
    end
    n=n*2;
    err=abs(T(k+1,k+1)-T(k,k));%更新积分误差
end
R=T(k+1,k+1)
end