#include<iostream>
#include<algorithm>
#include<vector>
using std::vector;

struct binarySearchTreeNode//节点
{
	int element;//关键字
	binarySearchTreeNode* leftChild, *rightChild;//左右子树

	//构造函数
	binarySearchTreeNode(const int& key = 0) {
		element = key;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	binarySearchTreeNode() {
		element = 0;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	binarySearchTreeNode(const int& theElement,
		binarySearchTreeNode* theLeftChild,
		binarySearchTreeNode* theRightChild)
	{
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}

};
class binarySearchTree
{
	typedef binarySearchTreeNode Node;
	typedef binarySearchTree BSTree;
public:
	//构造函数
	binarySearchTree();
	//拷贝构造
	binarySearchTree(const BSTree& t)
	{
		_root = _Copy(t._root); //拷贝t对象的二叉搜索树
	}
	//赋值运算符重载函数,不重载运算符赋值会出现读取访问权限冲突
	BSTree& operator=(BSTree t)
	{
		std::swap(_root, t._root);
		return *this; //支持连续赋值
	}
	//析构函数
	~binarySearchTree();
	//插入函数，采用子函数递归避免自己手动给函数传形参
	bool Insert(const int& key);
	//删除函数
	bool Erase(const int& key);
	//查找函数
	Node* Find(const int& key);
	//中序遍历
	void InOrder();

	friend void _Destory(Node* root);
	friend bool _Insert(Node*& root, const int& key);//便于递归实现
	friend void _InOrder(Node*& root);
	//拷贝树,树的拷贝要用循环或者递归来实现
	Node* _Copy(Node* root)
	{
		if (root == nullptr) //空树直接返回
			return nullptr;

		Node* copyNode = new Node(root->element); //拷贝根结点
		copyNode->leftChild = _Copy(root->leftChild); //拷贝左子树
		copyNode->rightChild = _Copy(root->rightChild); //拷贝右子树
		return copyNode; //返回拷贝的树
	}

private:
	Node* _root;//二叉树根节点
};

//中序遍历接口函数
//必须定义子函数以便于访问类的私有成员
void _InOrder(binarySearchTree::Node*& root)
{
	// 类外成员函数引用本对象的数据成员，不需加类名限定
	if (root != nullptr)
	{
		_InOrder(root->leftChild);
		std::cout << root->element << " ";
		_InOrder(root->rightChild);
	}
}
void binarySearchTree::InOrder()
{
	_InOrder(_root);
	std::cout << std::endl;
}

//构造函数
binarySearchTree::binarySearchTree()
{
	_root = nullptr;
}

//析构函数是不能有参数的,可以加一个子函数便于递归
void _Destory(binarySearchTree::Node* root)
{
	if (root == nullptr)
	{
		return;//空树无需释放
	}
	_Destory(root->leftChild);
	_Destory(root->rightChild);
	delete root;//释放节点
}
binarySearchTree::~binarySearchTree()
{
	_Destory(_root); //释放二叉搜索树中的结点
	_root = nullptr; //delete的作用：销毁并释放指针所指向的内存空间，指针要及时置空
	//子树已经全部被销毁，根节点指针要置空
}

bool _Insert(binarySearchTree::Node*& root, const int& key)//递归实现
{
	if (root == nullptr)
	{
		root = new binarySearchTree::Node(key);//直接申请值为key的结点作为根结点
		return true; //插入成功，返回true
	}

	if (key < root->element)
	{
		return _Insert(root->leftChild, key);
	}
	else if (key > root->element)
	{
		return _Insert(root->rightChild, key);
	}
	else {
		return false;//key的值已经在树中
	}
}
//递归实现插入
bool binarySearchTree::Insert(const int& key)
{
	return _Insert(_root, key);
}

//1.待删除结点的左右子树均为空(节点是树叶)
//2.待删除结点有一个非空子树 
//3.待删除结点有两个非空子树
bool binarySearchTree::Erase(const int& key)
{
	Node* parent = nullptr; //标记待删除结点的父结点
	Node* cur = _root; //标记待删除结点
	while (cur)
	{
		if (key < cur->element) //key值小于当前结点的值
		{
			//往该结点的左子树走
			parent = cur;
			cur = cur->leftChild;
		}
		else if (key > cur->element) //key值大于当前结点的值
		{
			//往该结点的右子树走
			parent = cur;
			cur = cur->rightChild;
		}
		else //找到了待删除结点
		{
			if (cur->leftChild == nullptr) //待删除结点的左子树为空
			{
				if (cur == _root) //待删除结点是根结点，此时parent为nullptr
				{
					_root = cur->rightChild; //二叉搜索树的根结点改为根结点的右孩子即可
				}
				else //待删除结点不是根结点，此时parent不为nullptr
				{
					if (cur == parent->leftChild) //待删除结点是其父结点的左孩子
					{
						parent->leftChild = cur->rightChild; //父结点的左指针指向待删除结点的右子树即可
					}
					else //待删除结点是其父结点的右孩子
					{
						parent->rightChild = cur->rightChild; //父结点的右指针指向待删除结点的右子树即可
					}
				}
				delete cur; //释放待删除结点
				return true; //删除成功，返回true
			}
			else if (cur->rightChild == nullptr) //待删除结点的右子树为空
			{
				if (cur == _root) //待删除结点是根结点，此时parent为nullptr
				{
					_root = cur->leftChild; //二叉搜索树的根结点改为根结点的左孩子即可
				}
				else //待删除结点不是根结点，此时parent不为nullptr
				{
					if (cur == parent->leftChild) //待删除结点是其父结点的左孩子
					{
						parent->leftChild = cur->leftChild; //父结点的左指针指向待删除结点的左子树即可
					}
					else //待删除结点是其父结点的右孩子
					{
						parent->rightChild = cur->leftChild; //父结点的右指针指向待删除结点的左子树即可
					}
				}
				delete cur; //释放待删除结点
				return true; //删除成功，返回true
			}
			else //待删除结点的左右子树均不为空
			{
				//替换法删除
				Node* minParent = cur; //标记待删除结点右子树当中值最小结点的父结点
				Node* minRight = cur->rightChild; //标记待删除结点右子树当中值最小的结点
				//寻找待删除结点右子树当中值最小的结点
				while (minRight->leftChild)
				{
					//一直往左走
					minParent = minRight;
					minRight = minRight->leftChild;
				}
				cur->element = minRight->element; //将待删除结点的值改为minRight的值
				//注意一个隐含条件：此时minRight的_left为空
				if (minRight == minParent->leftChild) //minRight是其父结点的左孩子
				{
					minParent->leftChild = minRight->rightChild; //父结点的左指针指向minRight的右子树即可
				}
				else //minRight是其父结点的右孩子
				{
					minParent->rightChild = minRight->rightChild; //父结点的右指针指向minRight的右子树即可
				}
				delete minRight; //释放minRight
				return true; //删除成功，返回true
			}
		}
	}
	return false; //没有找到待删除结点，删除失败，返回false
}

//查找函数，不用递归，直接循环也可
binarySearchTree::Node* binarySearchTree::Find(const int& key)
{
	Node* node = _root;
	while (node)//不为空
	{
		if (key > node->element)
		{
			node = node->rightChild;
		}
		else if (key < node->element)
		{
			node = node->leftChild;
		}
		else {
			return node;
		}
	}
	return nullptr; //树为空或查找失败，返回nullptr
}

int main()
{
	binarySearchTree BSTree;
	vector<int> vInt = {4, 12, 8, 16, 6, 18, 24, 2, 14, 3};
	for (auto& i : vInt)
	{
		BSTree.Insert(i);
	}
	BSTree.InOrder();

	vector<int> _vInt = { 6, 14, 16, 4 };
	for (auto& i : _vInt)
	{
		BSTree.Erase(i);
	}
	BSTree.InOrder();
}