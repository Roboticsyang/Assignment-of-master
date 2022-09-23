function s=threesimple(X,Y,x,y0,yn)
%        �ڶ��߽��������� 
%        s������ʾ����������ֵ������ֵ���Ӧ�ĺ���ֵ
%        �������������������������D,h,A,g,M
%        x��ʾ����ֵ�㺯���㣬XΪ��֪��ֵ��        
         [D,h,A,g,M]=Cubic_Spline(X,Y,y0,yn);
         n=length(X); m=length(x);    
         for t=1:m
            for i=1:n-1
               if (x(t)<=X(i+1))&&(x(t)>=X(i))
                  p1=M(i,1)*(X(i+1)-x(t))^3/(6*h(i));
                  p2=M(i+1,1)*(x(t)-X(i))^3/(6*h(i));
                  p3=(A(i,1)-M(i,1)/6*(h(i))^2)*(X(i+1)-x(t))/h(i);
                  p4=(A(i+1,1)-M(i+1,1)/6*(h(i))^2)*(x(t)-X(i))/h(i);
                  s(t)=p1+p2+p3+p4; 
                  break;
               else
                   s(t)=0; 
               end
            end
         end
end