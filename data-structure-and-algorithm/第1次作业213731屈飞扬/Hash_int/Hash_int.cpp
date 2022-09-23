#include<iostream>
#include<array>
#include<vector>
using std::vector;

class HashChain
{
public:
    HashChain()//����
    {
        for (int i = 0; i < 13; i++)
        {
            arr[i] = nullptr;
        }
    }

    struct Node {
        Node(int val) :data(val), next(nullptr) {}
        int data;
        struct Node* next;
    };//array��ÿ��λ�÷�һ������

    bool insert(const int& val);//����
    bool find(const int& val);//����
    void outnext(const Node* next);//���next֮���data

    void output()//���arr[i]
    {
        for (int i = 0; i < 13; i++)
        {
            std::cout << "arr[" << i << "]-> ";
            if (this->arr[i] == nullptr)
            {
                std::cout << "nullptr" << std::endl;
            }
            else {
                std::cout << this->arr[i]->data;
                if (this->arr[i]->next != nullptr)
                {
                    std::cout << "->";
                    this->outnext(this->arr[i]->next);
                }
                else {
                    std::cout << std::endl;
                }
            }
        }
    }

    typedef Node* pnode;

    ~HashChain() {}//��������
private:
    std::array<Node*, 13> arr;//�������� 13 �� Node* ����Ԫ�ص� array ����

};

void HashChain::outnext(const Node* next)
{
    std::cout << next->data;
    if (next->next != nullptr)
    {
        std::cout << "->";
        HashChain::outnext(next->next);
    }
    else {
        std::cout << "->nullptr" << std::endl;
    }
}
bool HashChain::insert(const int& val)
{
    if (find(val))//arr[i]ǡ����Ҫ�����ֵ�����Ѿ�����
    {
        return true;
    }
    pnode& point = arr[val % 13];//ȡ��arr[i]
    Node* newPoint = new Node(val);//newPointָ��һ��val��ʼ����Node����
    pnode _point = nullptr;
    if (point == nullptr)
    {
        point = newPoint;//val��ָ�����ô��ݸ�arr
        return true;//����ɹ�
    }
    else
    {
        _point = point;//val��ָ�뿽�����ݸ�_point������ָ��ָ�����Ȼ��arr�����
    }
    while (_point->next)//һֱ����Ѱ�ҡ�ֱ��Ϊ��
    {
        _point = _point->next;
    }
    _point->next = newPoint;//����
    return true;
}

bool HashChain::find(const int& val)
{
    HashChain::Node* point = arr[val % 13];
    if (point == nullptr)
    {
        return false;//arr[i]�ǿյ�
    }
    while (point)//arr[i]��ֵ
    {
        if (point->data == val)
            return true;//arr[i]ǡ����Ҫ�����ֵ
        else
        {
            point = point->next;//ָ����һ������ָ��
        }
    }
    return false;//arr[i]����Ҫ�����ֵ��ָ����һ��ָ��
}

int main()
{
    HashChain hashtable;
    vector<int> vInt{ 7,42,25,70,14,38,8,21,34,11 };
    for (auto i : vInt)
    {
        hashtable.insert(i);
    }
    hashtable.output();
    return 0;
}
