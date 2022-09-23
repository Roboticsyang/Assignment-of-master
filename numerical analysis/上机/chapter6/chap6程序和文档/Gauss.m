function Gauss
% ���������˹�����ʽ

a = 0;%��ĸ����Ϊ0���ñȽ�С��������
b = 1;
epsilon = 5e-8;
tol = epsilon;
fun = @(x) atan(x)*(x)^(-1.5);
k=0; % ��������
n=2; % ���仮�ָ���
h=b-a;
G(1)=(h/2)*((5/9)*fun(0.5*(a+b)-0.1*h*sqrt(15))+(8/9)*fun(0.5*(a+b))+(5/9)*fun(0.5*(a+b)+0.1*h*sqrt(15)));%����δ���ϵ�Gauss
err=1;%��������ʼ��
while err>=tol
    k=k+1;
    h=1/n;
    tmp=0;
    for i=0:n-1
        tmp=tmp+(h/2)*((5/9)*fun(0.5*(a+i*h+a+(i+1)*h)-0.1*h*sqrt(15))+(8/9)*fun(0.5*(a+i*h+a+(i+1)*h))+(5/9)*fun(0.5*(a+i*h+a+(i+1)*h)+0.1*h*sqrt(15)));
    end
    
    G(k+1)=tmp;%�µ�ֵ��������
    n=n+1;
    err=abs(G(k+1)-G(k));%���»������
end
G = G(k+1)
end