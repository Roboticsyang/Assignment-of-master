#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr auto MaxInt = 30000;       //表示极大值，即∞,不用32767是为了防止溢出
constexpr auto MVNum = 100;         //最大顶点数
typedef char VerTexType;    //设顶点的数据类型为字符型
typedef int ArcType;        //假设边的权值类型为整型
vector<int> dis(MVNum, MaxInt);//初始化所有顶点到源点的距离,为上界

struct Base { }; //为未命名的类命名
typedef struct NamedType : Base
{
    vector<VerTexType> vexs{ MVNum };     //顶点表
    vector<vector<ArcType>> arcs{ MVNum ,vector<ArcType>(MVNum,MaxInt)}; //邻接矩阵，权值初始化为极大值
    int vexnum = 0, arcnum = 0;         //图的当前点数和边数
}AMGraph;//Adjacency Matrix Graph

struct node     //顶点节点
{
    int vlue;//表示访问的顶点
    int key;//表示顶点到源点的距离
    int parent;//表示顶点的父顶点
    node()//构造函数
    {
        vlue = -1;
        key = MaxInt;
        parent = -1;
    }
    node* operator= (const node* t) {
        this->key = t->key;
        this->vlue = t->vlue;
        this->parent = t->parent;
        return this;
    }
    friend bool operator<(node a, node b)   //因要实现最小堆，按升序排列，因而需要重载运算符，重定义优先级，以小为先
    {
        return a.key > b.key;
    }
    friend bool operator>(node a, node b) 
    {
        return a.key < b.key;
    }
};

//fibonacci堆实现优先队列
template<class T>
class FibHeap {
private:
	struct node
	{
		T data;
		bool mark = false;;
		int degree = 0;
		node* left = this, * right = this;
		node* child = nullptr, * parent = nullptr;
	};
    int size = 0;//结点个数
    node* min = nullptr;//最小元素指针
    node* head = new node;//第一层元素的链表表头
	T MIN_VALUE;
	void LeftInsert(node* base, node* tmp)//LeftInsert:在双向循环链表中把tmp插入base左边
	{
		tmp->left = base->left;
		tmp->right = base;
		base->left->right = tmp;
		base->left = tmp;
	}
	void link(node* y, node* x)//把y插入到x下面
    {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child == nullptr)//当x没有儿子
        {
            x->child = y;
            y->left = y->right = y;
        }
        else LeftInsert(x->child, y);
        x->degree++;
        y->mark = false;//把标记清空，由于它刚刚成为子结点，仍需失去儿子结点mark才会标为true
    }
	void Consolidate()
	{
		int Dn = (int)log2(size) + 1;
		node** nodes = new node * [Dn];
		for (int i = 0; i < Dn; i++)
			nodes[i] = nullptr;
		node* ptr = head->right, * nxt;
		do
		{
			int d;
			node* x, * y;
			x = ptr;
			if (x == head) continue;
			d = x->degree;
			nxt = ptr->right;
			while (nodes[d] != nullptr)
			{
				y = nodes[d];
				if (x->data > y->data)
					std::swap(x, y);
				link(y, x);
				nodes[d] = nullptr;
				d++;
			}
			nodes[d] = x;
			ptr = nxt;
		} while (ptr != head);
		min = nullptr;
		head->left = head->right = head;
		for (int i = 0; i < Dn; i++)
		{
			if (nodes[i] != nullptr)
			{
				if (min == nullptr)
				{
					min = nodes[i];
					LeftInsert(head, min);
				}
				else
				{
					LeftInsert(head, nodes[i]);
					if (nodes[i]->data < min->data)
						min = nodes[i];
				}
			}
		}
	}
public:
	T top()//获得最小值
	{
		return min->data;
	}
	int empty()
	{
		return size==0;
	}
    void push(T data)//插入
    {
        //初始化
        node* tmp = new node;
        tmp->degree = 0;
        tmp->data = data;
        tmp->parent = tmp->child = nullptr;
        tmp->left = tmp->right = tmp;//双向循环链表需要把左右指针指向自己
        tmp->mark = false;
        if (min == nullptr)//空堆，min指针指向该结点
        {
            min = tmp;
            LeftInsert(head, min);//LeftInsert定义见上方
        }
        else
        {
            LeftInsert(min, tmp);
            if (data < min->data)//插入的结点更小，min指向新结点
                min = tmp;
        }
        size++;
    }
	FibHeap<T> Merge(FibHeap<T> H2)//合并两个斐波那契堆
	{
		node* ptr = head->right;
		do
		{
			H2.Insert(ptr->data);
			ptr = ptr->right;
		} while (ptr != head);
		if (H2.min == nullptr || (min != nullptr && min->data < H2.GetMin()))
			H2.min = min;
		return H2;
	}
    void pop()//删除最小值
    {
        node* ptr = min;
        if (ptr != nullptr)
        {
            node* tmp = min->child, * nxt;
            for (int i = 0; i < min->degree; i++)
            {
                nxt = tmp->right;
                LeftInsert(head, tmp);
                tmp = nxt;
            }//由于在LeftInsert之后tmp的链会断，所以需要提前记录下一个孩子
            ptr->left->right = ptr->right;
            ptr->right->left = ptr->left;//在第一层链表中把min去掉

            if (ptr == ptr->right)//此时堆中仅有一个元素
                min = nullptr;
            else
            {
                min = min->right;//先随意指向一个结点
                if (min == head) min = min->right;//指向表头，无意义，再指向下一个
                Consolidate();//调整堆结构
            }
            size--;
        }
    }
	void Cut(node* x, node* y)//x为子结点，y为父结点
    {
		if (y->degree == 1)
			y->child = nullptr;
		else
		{
			x->left->right = x->right;
			x->right->left = x->left;
		}
		y->degree--;
		LeftInsert(head, x);
		x->parent = nullptr;
		x->mark = false;
	}
	void CascadingCut(node* y)//对父结点尝试进行级联切断
	{
		node* z = y->parent;
		if (z != nullptr)
		{
			if (y->mark == false)
				y->mark = true;
			else
			{
				Cut(y, z);
				CascadingCut(z);
			}
		}
	}
	void DecreaseKey(node* x, T key)//给定一个结点指针，并把它的值减小，重新调整堆的结构
	{
		if (key >= x->data) return;
		x->data = key;

		node* y = x->parent;
		if (y != nullptr && x->data < y->data)
		{
			Cut(x, y);
			CascadingCut(y);
		}
		if (x->data < min->data)
			min = x;
	}
	void Delete(node* x)//删除关键字操作（前提是有指向它的指针）。MIN_VALUE需要在初始化类时给出，如int型设为INT_MIN等
	{
		DecreaseKey(x, MIN_VALUE);
		pop();
	}
};

//二叉堆实现优先队列
template<class T>
class binaryPriorityQueue
{
private:
    T* pArray = new T[MVNum];// 根节点
    //T* pArray = new T[MVNum];// 根节点
    int m_length = 0;
public:
    //上浮
    void swim(int k) {	//k为数组的id
        //若叶子节点k所对应的值大于其父节点，上浮
        while (k > 0 && pArray[k] > pArray[k / 2]) {
            swap(pArray[k], pArray[k / 2]);	//交换父子位置
            k /= 2;	//数值对应id改变
        }
    }

    //下沉
    void sink(int k) {
        while (k * 2 <= m_length) {	//循环至最后一个节点截止
            int j = 2 * k;
            if (j < m_length && (pArray[j] < pArray[j + 1])) j++;	// 这里先比较左子树和右子树的大小，将最大的那个键记录下来再和父节点比较
            if (pArray[k] > pArray[j]) break;	// 和父节点比较如果父节点比最大的子节点还要大，则直接退出循环
            swap(pArray[k], pArray[j]);	// 如果父节点比子节点小则交换
            k = j;
        }
    }

    //插入
    void push(T v) {
        pArray[m_length++] = v;
        sink(m_length);
    }

    //删除堆顶
    void pop() {
        swap(pArray[0], pArray[m_length--]);
        //delete pArray[m_length + 1];
        swim(1);
    }

    //取顶点元素
    T top() {
        return	pArray[0];
    }

    // 判断是否为空
    bool empty() {
        return m_length == 0;
    }

    int size() {
        return m_length;
    }
};

void denseCreate(AMGraph& G)//创建稠密有向图
{
    G.vexnum =100;//当前顶点数
    for (int i = 0; i < G.vexnum; ++i)//随机构造邻接矩阵：稠密图
    {
        for (int j = i; j < G.vexnum; ++j)
        {
            if (i == j)
            {
                G.arcs[i][j] = 0;
            }
            else 
            {
                G.arcs[i][j] = rand() % 10;//权值
                G.arcs[j][i] = rand() % 10;
                G.arcnum += 2;//统计弧数
                if (G.arcs[i][j] == 0)
                {
                    G.arcs[i][j] = MaxInt;//为0则当作没有弧
                    --G.arcnum;//统计弧数
                }
                if (G.arcs[j][i] == 0)
                {
                    G.arcs[j][i] = MaxInt;//为0则当作没有弧
                    --G.arcnum;//统计弧数
                }
            }
        }
    }
}

void sparseCreate(AMGraph& G)//创建稀疏有向图
{
    G.vexnum = 100;//当前顶点数
    for (int i = 0; i < G.vexnum; ++i)//随机构造邻接矩阵：稀疏图
    {
        for (int j = i + 1; j < G.vexnum; ++j)
        {
            if (i == j)
            {
                G.arcs[i][j] = 0;
            }
            else
            {
                G.arcs[i][j] = rand() % 10;//权值
                G.arcs[j][i] = rand() % 10;
                G.arcnum+=2;//统计弧数
                if (G.arcs[i][j] == 0)
                {
                    G.arcs[i][j] = MaxInt;//为0则当作没有弧
                    --G.arcnum;//统计弧数
                }
                if (G.arcs[j][i] == 0)
                {
                    G.arcs[j][i] = MaxInt;//为0则当作没有弧
                    --G.arcnum;//统计弧数
                }
            }
            
            if (j = i + 3)//保证边数不超过99+98条
                break;
        }
    }
}

bool Bellman_Ford(AMGraph& G, int S)//图的起点为G.vexs[S]
{
    int n = G.vexnum;//顶点数
    int t = G.arcnum;//边数
    //vector<int> dis(G.vexnum, MaxInt);//初始化所有顶点到源点的距离,为上界
    vector<int> backup(G.vexnum);//用来存上一次的结果
    dis[S] = 0;

    for (int k = 0; k < n-1; k++) //最多对所有边执行n-1次松弛操作
    {
        //将dis数组备份
        for (int i = 0; i < n; i++) {
            backup[i] = dis[i];
        }
        for (int i = 0; i < n; i++) {
            //双重循环，对每个边进行松弛操作
            for (int j = 0; j < n; j++)
            {
                if (dis[j] > dis[i] + G.arcs[i][j]) //i到S的距离加i到j的距离，决定是否改善j到S的距离
                {
                    dis[j] = dis[i] + G.arcs[i][j];
                }
            }
        }
        //松弛完成后检测dis数组是否有更新
        int check = 0;
        for (int i = 0; i < n; i++) {
            if (dis[i] != backup[i])
                check = 1;//数组有更新  继续循环
        }
        if (check == 0)
        {
            cout << "Bellman_Ford循环次数：" << k + 1 << endl;
            break;//如果数组不再更新就退出多余循环
            //经测验：如果有负权值 就会一直循环  没有负权值就会循环3次
        }
        //for (int i = 0; i < n; i++) {
        //    cout << dis[i] << ' ';//测试
        //}
    }
    
    int flag = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //再次对每条边进行松弛操作,检查每个节点
            if (dis[j] > dis[i] + G.arcs[i][j]) 
            {
                dis[j] = -MaxInt;//负无穷
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

node* Dijkstra(AMGraph& G, int s)//斐波那契堆实现Dijkstra/最小二叉堆实现Dijkstra
{
    //binaryPriorityQueue<node> q; //二叉堆优先队列
    FibHeap<node> q;//斐波那契堆优先队列
    node d[MVNum];      //结点集，node重定义优先级
    bool visited[MVNum]; //用于判断顶点是否已经在最短路径树中

    int n = G.vexnum;//顶点数
    for (int i = 0; i < n; i++) //初始化
    {
        d[i].vlue = i;
        d[i].key = MaxInt;      //估算距离置极大
        d[i].parent = -1;       //每个顶点都无父亲节点
        visited[i] = false;     //都未找到最短路
    }
    d[s].key = 0;               //源点到源点最短路权值为0
    q.push(d[s]);               //压入队列中
    while (!q.empty())          //队列空说明完成了操作
    {
        node cd = q.top();      //取最小顶点
        q.pop();
        int u = cd.vlue;
        if (visited[u])
            continue;
        visited[u] = true;

        //cout << "访问:" << u << " 距离:" << d[u].key << " 父结点:" << d[u].parent << "\t";

        for (int i = 0; i < n-1; i++) //松弛操作
        {
            if (!visited[i] && d[i].key > d[u].key + G.arcs[d[u].vlue][i])
            {
                d[i].parent = u;
                d[i].key = d[u].key + G.arcs[d[u].vlue][i];
                q.push(d[i]);
            }
        }
    }
    //cout << endl;//清空缓存区
    return d;
}

vector<vector<int>> Johnson(AMGraph& G,int s)
{
    if (Bellman_Ford(G,s))
        cout << "the input graph contains a negative-weight cycle" << endl;
    else
    {
        int h[MVNum];
        int i, j, k;
        vector<vector<int>> newWeight(MVNum,vector<int>(MVNum));
        //将数组h[]的值设为运行BellmanFord后取得的值，h[i]为结点s到其他点的最短路径  
        for (i = 0; i < G.vexnum; i++)
            h[i] = dis[i];
        //遍历所有的边，将边的权值重新赋值,即将所有的边的权值改为负值  
        for (i = 0; i < G.vexnum; i++)
        {
            for (j = 0; j<G.vexnum; j++)
                newWeight[i][j] = G.arcs[i][j] + h[i] - h[j];
        }       
        vector<vector<int>> d(MVNum, vector<int>(MVNum));
        //对每个结点运行dijkstra算法，求出每个点到其他点的最短路径，保存在key中
        node* key = new node[MVNum];
        for (k = 1; k < MVNum; k++)
        {
            key = Dijkstra(G,k);
            for (i = 1; i < MVNum; i++)
            {
                d[k][i] = key[i].key + h[i] - h[k];
            }
                
        }
        cout << "最后计算出各点到起点"<<s<<"的最短距离：" << endl;
        for (int k = 1; k < G.vexnum; k++)
        {
            for (int i = 1; i < G.vexnum; i++)
            {
                if (d[k][i] < 0 || d[k][i] >= 30000)//30000就是没有边  负值表示有溢出
                    d[k][i] = 30000;
                cout << d[k][i] << "\t";
            }
                
        }
        return d;
    }
}

int main()
{
    srand((int)time(0)); // 产生随机种子
    AMGraph G;
    sparseCreate(G);//创建稀疏图
    //denseCreate(G);//创建稠密图

    //for (int i = 0; i < G.vexnum; ++i)//输出邻接矩阵测试
    //{
    //    for (int j = 0; j < G.vexnum; ++j)
    //        cout << G.arcs[i][j] << "\t";
    //    cout << endl;
    //}
    cout << "弧数：" << G.arcnum << endl;

    int S = rand() % G.vexnum;//图的起点
    cout << "Bellman_Ford起点：" << S << endl;
    //bool result = Bellman_Ford(G, S);
    //if (result)
    //    cout << "此有向图存在负权回路，计算两点之间距离可能没有意义" << endl;

    //Dijkstra(G, S);
    cout << "起点" << S << "的JOHNSON算法单源最短路径" << endl;
    vector<vector<int>> d = Johnson(G, S);
    return 0;
}
