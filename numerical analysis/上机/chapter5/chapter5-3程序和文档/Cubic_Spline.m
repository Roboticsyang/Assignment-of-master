function [ D,h,A,g,M ] = Cubic_Spline( X,Y,y0,yn )
%        ��Ȼ�߽�������������������(�ڶ��ֱ߽�����)
%        �˺���ΪMֵ��ֵ����
%        D,h,A,g,M������ֱ�Ϊϵ������D����ֵ���h�����̱�A��gֵ,Mֵ 
         n=length(X); 
         A=zeros(n,n);A(:,1)=Y';D=zeros(n-2,n-2);g=zeros(n-2,1);
         for  j=2:n
            for i=j:n
                A(i,j)=(A(i,j-1)- A(i-1,j-1))/(X(i)-X(i-j+1));
            end
         end
         
         for i=1:n-1
             h(i)=X(i+1)-X(i);
         end
         for i=1:n-2
             D(i,i)=2;
             g(i,1)=(6/(h(i+1)+h(i)))*(A(i+2,2)-A(i+1,2));
         end
         for i=2:n-2
             u(i)=h(i)/(h(i)+h(i+1));
             n(i-1)=h(i)/(h(i-1)+h(i));
             D(i-1,i)=n(i-1);
             D(i,i-1)=u(i);             
         end
         M=D\g;
         M=[0;M;0];     
end