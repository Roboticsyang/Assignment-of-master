#include <iostream>
#include<cmath>
#include<iostream>
using namespace std;

int mi(int a, int b)//快速幂
{
	int ans = 1;
	while (b)
	{
		if (b & 1)
			ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

class vEBTree
{
private:
	//min不出现在簇和summary中，插入空树和从只有一个元素的树中删除就只需要 O(1) 时间
	int max;//最大值
	int min;//最小值
	int u;//全域
	//当 u 为2的奇数次幂  根号下u不为整数
	vEBTree* summary;// v=2^( [log2(u)/2] ) log2(u)/2向下取整  例：u=8 得到 2   summary指向一个全域大小 u/v的vBETree
	vEBTree** cluster;//簇指针， 有 u/v个簇，每个簇全域为v 储存[i*v , (i+1)*v-1]元素信息
public:
	int MIN();
	int MAX();
	int extractmin();
	vEBTree(int u_);
	int high(int x);
	int low(int x);
	int index(int x, int y);
	bool Member(int x);
	int successor(int x);
	int extractsucc(int x);
	int predecessor(int x);
	void Insert(int x);
	void Insert_Empty(int x);
	void Delete(int x);
	void Out();
};
int vEBTree::MIN()//最小值
{
	return min;
}
int vEBTree::MAX()//最大值
{
	return max;
}
int vEBTree::extractmin()//删除并返回VEB树中的the minimum priority key value
{
	int m = min;
	vEBTree::Delete(min);
	return m;
}
vEBTree::vEBTree(int u_)//以递归建立树
{
	u = u_;
	min = max = -1;
	if (u == 2)//基础形式
	{
		summary = nullptr;
		cluster = nullptr;
	}
	else
	{
		int q = log(double(u)) / log(2.0);
		q = q / 2;
		int v = mi(2, q);
		int w = u / v;
		summary = new vEBTree(w);//当第[i*v , (i+1)*v-1]个元素全为0，summary[i]对应0
		cluster = new vEBTree * [w];//簇
		for (int i = 0; i < w; i++)
		{
			cluster[i] = new vEBTree(v);
		}
	}
}
int vEBTree::high(int x)//x在第几个簇中
{
	int q = log(double(u)) / log(2.0);
	q = q / 2;
	int v = mi(2, q);
	return x / v;
}
int vEBTree::low(int x)//x在所在簇中下标是几
{
	int q = log(double(u)) / log(2.0);
	q = q / 2;
	int v = mi(2, q);
	return x % v;
}
int vEBTree::index(int x, int y)//x为第几个簇，y为簇中的下标，返回this vEBTree中x的位置
{
	int q = log(double(u)) / log(2.0);
	q = q / 2;
	int v = mi(2, q);
	return x * v + y;
}
bool vEBTree::Member(int x)//是否包含元素x
{
	if (x == min || x == max)
		return true;
	else if (u == 2)//基础情形
	{
		return false;
	}
	else//在簇中查找，递归
		return cluster[high(x)]->Member(low(x));
}
int vEBTree::successor(int x)//x不一定在集合中  求后继
{
	if (u == 2)//基础情形
	{
		if (x == 0 && max == 1)
			return 1;
		else
			return -1;
	}
	else if (min != -1 && x < min)//是否严格小于最小值 min不出现在簇中，单独判断
	{
		return min;
	}
	else
	{
		int max_low = cluster[high(x)]->MAX();//x所在簇中最大值在簇中的位置
		int offset;//后继在簇中的位置
		if (max_low != -1 && low(x) < max_low)//后继在本簇中
		{
			offset = cluster[high(x)]->successor(low(x));
			return index(high(x), offset);
		}
		else
		{
			int succ_cluster = summary->successor(high(x));//后继所在的簇
			if (succ_cluster == -1)//查找失败
				return -1;
			else
			{
				offset = cluster[succ_cluster]->MIN();
				return index(succ_cluster, offset);
			}
		}
	}
}
int vEBTree::extractsucc(int x)//删除并返回VEB树中大于x的下一个最小priority key value
{
	int succ = vEBTree::successor(x);
	vEBTree::Delete(succ);
	return succ;
}
int vEBTree::predecessor(int x)//前驱
{
	if (u == 2)
	{
		if (x == 1 && min == 0)
			return 0;
		else
			return -1;
	}
	else if (max != -1 && x > max)
		return max;
	else
	{
		int min_low = cluster[high(x)]->MIN();
		int offset;
		if (min_low != -1 && low(x) > min_low)
		{
			offset = cluster[high(x)]->predecessor(low(x));
			return index(high(x), offset);
		}
		else
		{
			int pred_cluster = summary->predecessor(high(x));
			if (pred_cluster == -1)
			{
				if (min != -1 && x > min)//附加情形，当x前驱是min元素，由于min不出现在簇中和summary中
					return min;
				else
					return -1;
			}
			else
			{
				offset = cluster[pred_cluster]->MAX();
				return index(pred_cluster, offset);
			}
		}
	}
}
void vEBTree::Insert_Empty(int x)//min值不出现在簇中 可在O（1）时间完成
{
	min = x;
	max = x;
}
void vEBTree::Insert(int x)//将该the priority key x插入到VEB树中
{
	if (min == -1)//空树
		Insert_Empty(x);
	else
	{
		if (x < min)//实际插入结点变为原min   min不出现在簇中，min直接更换更换即可   min变换后旧的min应出现在簇中
		{
			int t = x;
			x = min;
			min = t;
		}
		if (u > 2)
		{
			if (cluster[high(x)]->MIN() == -1)
			{
				summary->Insert(high(x));//x需出现在簇中
				cluster[high(x)]->Insert_Empty(low(x));
			}
			else
				cluster[high(x)]->Insert(low(x));
		}
		if (x > max)
			max = x;
	}
}
void vEBTree::Delete(int x)
{
	if (min == max)//只包含一个元素，min本不在簇中，不必递归的在簇中删除x
	{
		min = max = -1;
	}
	else if (u == 2)//基础情形
	{
		if (x == 0)
			min = 1;
		else
			min = 0;
		max = min;
	}
	else
	{
		if (x == min)//删除最小值
		{
			int first_cluster = summary->MIN();//原min不对summary起作用
			x = index(first_cluster, cluster[first_cluster]->MIN());
			min = x;//新的min，由于min不包括在簇和summary中，故x（min)成为真正要删掉的结点
		}
		cluster[high(x)]->Delete(low(x));
		if (cluster[high(x)]->MIN() == -1)//簇变为空的
		{
			summary->Delete(high(x));
			if (x == max)
			{
				int summary_max = summary->MAX();
				if (summary_max == -1)
					max = min;
				else
					max = index(summary_max, cluster[summary_max]->MAX());
			}
		}
		else if (x == max)
		{
			max = index(high(x), cluster[high(x)]->MAX());
		}
	}
}
void vEBTree::Out()
{
	if (min != max)
	{
		cout << min << " ";
		for (int i = min + 1; i < max; i++)
			if (Member(i))
				cout << i << " ";
		cout << max << endl;
	}
	else
		cout << min << endl;
}

int main()
{
    std::cout << "vEB树测试\n";
	int universe = 16;
	vEBTree vEB(universe);//创建u = universe的vEB树
	//vEBTree *vEB = new vEBTree(universe);
	//采用随机函数初始化
	srand((unsigned)time(NULL));
	std::cout << "vEB树初始化的输入如下：\n";
	for (int i = 0; i < universe; i++)
	{
		int j = rand() % 2;
		if (j)
		{
			vEB.Insert(i);//elements i
			cout << "A[" << i << "]=" << j << "\t";
		}
		else
		{
			cout << "A[" << i << "]=" << j << "\t";
			continue;
		}
	}
	cout << endl << "初始化后的vEB树如下：" << endl;
	vEB.Out();
	cout << "删除并返回VEB树中的the minimum priority key value:删除" << vEB.extractmin() << endl;
	cout << "删除the minimum priority key value后的vEB树如下：" << endl;
	vEB.Out();
	cout << "此时每个数的successor分别是（小于最小值的后继直接输出最小值，-1表示没有后继）：" << endl;
	for (int i = 0; i < universe; i++)
	{
		cout << i << "->" << vEB.successor(i) << "\t";
	}
	cout << endl;
	int r = rand() % 16;
	cout << "删除并返回VEB树中大于" << r << "的下一个最小priority key value:删除" << vEB.extractsucc(r) << endl;
	cout << "删除successor后的vEB树如下:" << endl;
	vEB.Out();
	return 0;
}
