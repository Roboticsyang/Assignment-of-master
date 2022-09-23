#include<iostream>
using namespace std;

int* hornerRule(int list[],int m,int x0, int a);	//Horner法则求多项式值 

int jiecheng(int m)	//求阶乘
{
	int k=1;
	for(;m>1;m--)
	{
		k = m*k;
	}
	return k;
}

int main() 
{
	int i,n,x0,a;

    int list[]= {1, 2, 3, 4, 5};		//存放系数an
	n = sizeof(list) / sizeof(*list)-1;	//注意已经减1了
    cout<<"x0 的值:"<<endl;
    cin>>x0;

	cout<<"a 的值"<<endl;
    cin>>a;
    int* m = hornerRule(list,n,x0,a);

	for (i = 0; i <= n; i++)
	{
		cout << *(m + i) << endl;	//输出导数值
	}

	system("pause");

    return 0;
}

int* hornerRule(int list[],int n,int x0, int a)
{
	int i,j,k;	//k表示第k阶导数的值
	cout<<"需要求导数的阶数k：";
	cin>>k;
	for(j=0;j<=k;j++)
	{
		for(i=n-1;i>=j;i--)
		{
			list[i]=(x0-a)*list[i+1]+list[i];	//bn的函数形式
		}
		list[j]=list[j]*jiecheng(j);
	}
	return list;
}