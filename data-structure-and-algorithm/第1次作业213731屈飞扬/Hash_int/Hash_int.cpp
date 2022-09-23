#include<iostream>
#include<array>
#include<vector>
using std::vector;

class HashChain
{
public:
    HashChain()//构造
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
    };//array的每个位置放一个链表

    bool insert(const int& val);//插入
    bool find(const int& val);//查找
    void outnext(const Node* next);//输出next之后的data

    void output()//输出arr[i]
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

    ~HashChain() {}//析构函数
private:
    std::array<Node*, 13> arr;//创建具有 13 个 Node* 类型元素的 array 容器

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
    if (find(val))//arr[i]恰好是要插入的值，即已经有了
    {
        return true;
    }
    pnode& point = arr[val % 13];//取出arr[i]
    Node* newPoint = new Node(val);//newPoint指向一个val初始化的Node对象
    pnode _point = nullptr;
    if (point == nullptr)
    {
        point = newPoint;//val的指针引用传递给arr
        return true;//插入成功
    }
    else
    {
        _point = point;//val的指针拷贝传递给_point，但是指针指向的仍然是arr后面的
    }
    while (_point->next)//一直往后寻找、直到为空
    {
        _point = _point->next;
    }
    _point->next = newPoint;//插入
    return true;
}

bool HashChain::find(const int& val)
{
    HashChain::Node* point = arr[val % 13];
    if (point == nullptr)
    {
        return false;//arr[i]是空的
    }
    while (point)//arr[i]有值
    {
        if (point->data == val)
            return true;//arr[i]恰好是要插入的值
        else
        {
            point = point->next;//指向下一个数的指针
        }
    }
    return false;//arr[i]不是要插入的值，指向下一个指针
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
