#include<iostream>
#include<algorithm>
#include<vector>
using std::vector;

struct binarySearchTreeNode//�ڵ�
{
	int element;//�ؼ���
	binarySearchTreeNode* leftChild, *rightChild;//��������

	//���캯��
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
	//���캯��
	binarySearchTree();
	//��������
	binarySearchTree(const BSTree& t)
	{
		_root = _Copy(t._root); //����t����Ķ���������
	}
	//��ֵ��������غ���,�������������ֵ����ֶ�ȡ����Ȩ�޳�ͻ
	BSTree& operator=(BSTree t)
	{
		std::swap(_root, t._root);
		return *this; //֧��������ֵ
	}
	//��������
	~binarySearchTree();
	//���뺯���������Ӻ����ݹ�����Լ��ֶ����������β�
	bool Insert(const int& key);
	//ɾ������
	bool Erase(const int& key);
	//���Һ���
	Node* Find(const int& key);
	//�������
	void InOrder();

	friend void _Destory(Node* root);
	friend bool _Insert(Node*& root, const int& key);//���ڵݹ�ʵ��
	friend void _InOrder(Node*& root);
	//������,���Ŀ���Ҫ��ѭ�����ߵݹ���ʵ��
	Node* _Copy(Node* root)
	{
		if (root == nullptr) //����ֱ�ӷ���
			return nullptr;

		Node* copyNode = new Node(root->element); //���������
		copyNode->leftChild = _Copy(root->leftChild); //����������
		copyNode->rightChild = _Copy(root->rightChild); //����������
		return copyNode; //���ؿ�������
	}

private:
	Node* _root;//���������ڵ�
};

//��������ӿں���
//���붨���Ӻ����Ա��ڷ������˽�г�Ա
void _InOrder(binarySearchTree::Node*& root)
{
	// �����Ա�������ñ���������ݳ�Ա������������޶�
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

//���캯��
binarySearchTree::binarySearchTree()
{
	_root = nullptr;
}

//���������ǲ����в�����,���Լ�һ���Ӻ������ڵݹ�
void _Destory(binarySearchTree::Node* root)
{
	if (root == nullptr)
	{
		return;//���������ͷ�
	}
	_Destory(root->leftChild);
	_Destory(root->rightChild);
	delete root;//�ͷŽڵ�
}
binarySearchTree::~binarySearchTree()
{
	_Destory(_root); //�ͷŶ����������еĽ��
	_root = nullptr; //delete�����ã����ٲ��ͷ�ָ����ָ����ڴ�ռ䣬ָ��Ҫ��ʱ�ÿ�
	//�����Ѿ�ȫ�������٣����ڵ�ָ��Ҫ�ÿ�
}

bool _Insert(binarySearchTree::Node*& root, const int& key)//�ݹ�ʵ��
{
	if (root == nullptr)
	{
		root = new binarySearchTree::Node(key);//ֱ������ֵΪkey�Ľ����Ϊ�����
		return true; //����ɹ�������true
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
		return false;//key��ֵ�Ѿ�������
	}
}
//�ݹ�ʵ�ֲ���
bool binarySearchTree::Insert(const int& key)
{
	return _Insert(_root, key);
}

//1.��ɾ����������������Ϊ��(�ڵ�����Ҷ)
//2.��ɾ�������һ���ǿ����� 
//3.��ɾ������������ǿ�����
bool binarySearchTree::Erase(const int& key)
{
	Node* parent = nullptr; //��Ǵ�ɾ�����ĸ����
	Node* cur = _root; //��Ǵ�ɾ�����
	while (cur)
	{
		if (key < cur->element) //keyֵС�ڵ�ǰ����ֵ
		{
			//���ý�����������
			parent = cur;
			cur = cur->leftChild;
		}
		else if (key > cur->element) //keyֵ���ڵ�ǰ����ֵ
		{
			//���ý�����������
			parent = cur;
			cur = cur->rightChild;
		}
		else //�ҵ��˴�ɾ�����
		{
			if (cur->leftChild == nullptr) //��ɾ������������Ϊ��
			{
				if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
				{
					_root = cur->rightChild; //�����������ĸ�����Ϊ�������Һ��Ӽ���
				}
				else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
				{
					if (cur == parent->leftChild) //��ɾ��������丸��������
					{
						parent->leftChild = cur->rightChild; //��������ָ��ָ���ɾ����������������
					}
					else //��ɾ��������丸�����Һ���
					{
						parent->rightChild = cur->rightChild; //��������ָ��ָ���ɾ����������������
					}
				}
				delete cur; //�ͷŴ�ɾ�����
				return true; //ɾ���ɹ�������true
			}
			else if (cur->rightChild == nullptr) //��ɾ������������Ϊ��
			{
				if (cur == _root) //��ɾ������Ǹ���㣬��ʱparentΪnullptr
				{
					_root = cur->leftChild; //�����������ĸ�����Ϊ���������Ӽ���
				}
				else //��ɾ����㲻�Ǹ���㣬��ʱparent��Ϊnullptr
				{
					if (cur == parent->leftChild) //��ɾ��������丸��������
					{
						parent->leftChild = cur->leftChild; //��������ָ��ָ���ɾ����������������
					}
					else //��ɾ��������丸�����Һ���
					{
						parent->rightChild = cur->leftChild; //��������ָ��ָ���ɾ����������������
					}
				}
				delete cur; //�ͷŴ�ɾ�����
				return true; //ɾ���ɹ�������true
			}
			else //��ɾ������������������Ϊ��
			{
				//�滻��ɾ��
				Node* minParent = cur; //��Ǵ�ɾ���������������ֵ��С���ĸ����
				Node* minRight = cur->rightChild; //��Ǵ�ɾ���������������ֵ��С�Ľ��
				//Ѱ�Ҵ�ɾ���������������ֵ��С�Ľ��
				while (minRight->leftChild)
				{
					//һֱ������
					minParent = minRight;
					minRight = minRight->leftChild;
				}
				cur->element = minRight->element; //����ɾ������ֵ��ΪminRight��ֵ
				//ע��һ��������������ʱminRight��_leftΪ��
				if (minRight == minParent->leftChild) //minRight���丸��������
				{
					minParent->leftChild = minRight->rightChild; //��������ָ��ָ��minRight������������
				}
				else //minRight���丸�����Һ���
				{
					minParent->rightChild = minRight->rightChild; //��������ָ��ָ��minRight������������
				}
				delete minRight; //�ͷ�minRight
				return true; //ɾ���ɹ�������true
			}
		}
	}
	return false; //û���ҵ���ɾ����㣬ɾ��ʧ�ܣ�����false
}

//���Һ��������õݹ飬ֱ��ѭ��Ҳ��
binarySearchTree::Node* binarySearchTree::Find(const int& key)
{
	Node* node = _root;
	while (node)//��Ϊ��
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
	return nullptr; //��Ϊ�ջ����ʧ�ܣ�����nullptr
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