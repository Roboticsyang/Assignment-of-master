#include<iostream>
using namespace std;

int* hornerRule(int list[],int m,int x0, int a);	//Horner���������ʽֵ 

int jiecheng(int m)	//��׳�
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

    int list[]= {1, 2, 3, 4, 5};		//���ϵ��an
	n = sizeof(list) / sizeof(*list)-1;	//ע���Ѿ���1��
    cout<<"x0 ��ֵ:"<<endl;
    cin>>x0;

	cout<<"a ��ֵ"<<endl;
    cin>>a;
    int* m = hornerRule(list,n,x0,a);

	for (i = 0; i <= n; i++)
	{
		cout << *(m + i) << endl;	//�������ֵ
	}

	system("pause");

    return 0;
}

int* hornerRule(int list[],int n,int x0, int a)
{
	int i,j,k;	//k��ʾ��k�׵�����ֵ
	cout<<"��Ҫ�����Ľ���k��";
	cin>>k;
	for(j=0;j<=k;j++)
	{
		for(i=n-1;i>=j;i--)
		{
			list[i]=(x0-a)*list[i+1]+list[i];	//bn�ĺ�����ʽ
		}
		list[j]=list[j]*jiecheng(j);
	}
	return list;
}