function Romberg
% ������(Romberg��ֵ��⹫ʽ)
% inputs:
%   -fun�����ֺ������
%   -a/b������������
%   -tol���������
% Outputs:
%   -R��Romberg����ֵ
%   -k����������
%   -T��������������

a = 1e-6;%��ĸ����Ϊ0���ñȽ�С��������
b = 1;
epsilon = 5e-8;
tol = epsilon;
fun = @(x) atan(x)*(x)^(-1.5);
k=0; % ��������
n=1; % ���仮�ָ���
h=b-a;
T=h/2*(fun(a)+fun(b));%����T(0,0)
err=1;%��������ʼ��
while err>=tol
    k=k+1;
    h=h/2;
    tmp=0;
    for i=1:n
        tmp=tmp+fun(a+(2*i-1)*h);%��ʱֱ����0����a
    end
    T(k+1,1)=T(k)/2+h*tmp;%�����㷨
    for j=1:k
        T(k+1,j+1)=T(k+1,j)+(T(k+1,j)-T(k,j))/(4^j-1);%�����㷨
    end
    n=n*2;
    err=abs(T(k+1,k+1)-T(k,k));%���»������
end
R=T(k+1,k+1)
end