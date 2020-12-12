#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct BiNode
{
    char data;
    BiNode *lchild;
    BiNode *rchild;
};

/*用于后序遍历的结构*/
struct element
{
    BiNode *ptr;
    int flag;
};

class BiTree
{
public:
    friend void Create(BiNode *&root);
    friend void CreateBinTree(istream &in, BiNode *&BT);

public:
    BiTree();
    BiTree(int i);
    BiTree(BiNode *&bn);
    ~BiTree();

public:
    void PreOrder();
    void PreOrder(BiNode *root);
    void PreOrder2();
    //先序的另外一种方法
    void PreOrder3();

    void InOrder();
    void InOreder2();

    void PostOrder();
    void PostOrder2();

    void LevelOrder();

private:
    BiNode *root;

    void release(BiNode *&r);
};

/*递归调用：先序*/

// void BiTree::PreOrder(BiNode *root)
// {
//     if (root == NULL)
//         return;
//     else
//     {
//         cout << root->data;
//         PreOrder(root->lchild);
//         PreOrder(root->rchild);
//     }
// }

//这个不是成员函数，传入根节点直接遍历
void PreOrder(BiNode *root)
{
    stack<BiNode *> s;

    while (root != nullptr || !s.empty()) //当且仅当root为空或栈不空的情况下循环终止；即root本身为空的情况下
    {
        while (root != nullptr)
        {
            s.push(root);
            cout << root->data;
            root = root->lchild;
        }
        if (!s.empty())
        {
            root = s.top();
            s.pop();
            root = root->rchild;
        }
    }
}

//先序遍历非递归调用
void BiTree::PreOrder()
{
    BiNode *s[50], *tmp = root;
    int top = -1; //顺序栈

    while (top != -1 || tmp != NULL)
    {
        while (tmp != NULL)
        {
            cout << tmp->data;
            s[++top] = tmp;
            tmp = tmp->lchild;
        }
        if (top != -1)
        {
            tmp = s[top--];
            tmp = tmp->rchild;
        }
    }
}

void BiTree::PreOrder2()
{
    BiNode *s[30], *tmp = root;
    int top = -1;

    while (top != -1 || tmp != nullptr)
    {
        while (tmp != nullptr)
        {
            cout << tmp->data;
            s[++top] = tmp;
            tmp = tmp->lchild;
        } //结束后，栈顶应该是最左下的叶节点

        if (top != -1) //栈不空
        {
            tmp = s[top--]; //出栈+取元素二合一
            tmp = tmp->rchild;
        }
    }
}

void BiTree::PreOrder3()
{
    BiNode *s[20], *p = root;
    int top = -1;

    while (p != nullptr)
    {
        cout << p->data;
        if (p->rchild != nullptr)
            s[++top] = p->rchild;
        if (p->lchild != nullptr)
            p = p->lchild;
        else
        {
            p = top == -1 ? nullptr : s[top--]; //检查top是否为-1
        }
    }
}

/*递归调用：中序
***************************************
void BiTree::InOrder(BiNode *root)
{
    if(root == NULL) return;
    else
    {
        InOrder(root->lchild);
        cout << root->data;
        InOrder(root->rchild);
    }   
}
****************************************
*/
void BiTree::InOrder()
{
    BiNode *s[50];
    int top = -1;

    while (root != NULL || top != -1)
    {
        while (root != NULL)
        {
            s[++top] = root;
            root = root->lchild;
        }
        if (top != -1)
        {
            root = s[top--];
            cout << root->data;
            root = root->rchild;
        }
    }
}

void BiTree::InOreder2()
{
    BiNode *s[20], *p = root;
    int top = -1;

    while (top != -1 || p != nullptr)
    {
        while (p != nullptr)
        {
            s[++top] = p;
            p = p->lchild;
        }
        if (top != -1)
        {
            p = s[top--];
            cout << p->data << flush;
            p = p->rchild;
        }
    }
}
/*递归调用：后序
***************************************
void BiTree::PostOrder(BiNode *root)
{
    if(root == NULL) return;
    else
    {
        InOrder(root->lchild);
        InOrder(root->rchild);
        cout << root->data;
    }   
}
****************************************
*/
void BiTree::PostOrder()
{
    int top = -1;
    element s[50];
    ++top;
    s[top].ptr = root;
    s[top].flag = 1; //若栈顶结点为1则说明左结点被遍历了，即刻将其flag设置为2，并遍历右结点；若栈顶结点为2则说明左右结点均被遍历
    root = root->lchild;
    while (top != -1) //栈不空
    {
        while (root != NULL)
        {
            ++top;
            s[top].ptr = root;
            s[top].flag = 1; //若栈顶结点为1则说明左结点被遍历了，即刻将其flag设置为2，并遍历右结点；若栈顶结点为2则说明左右结点均被遍历
            root = root->lchild;
        }
        while (top != -1 && s[top].flag == 2)
        {
            root = s[top--].ptr;
            cout << root->data;
        }
        if (top != -1)
        {
            s[top].flag = 2;
            root = s[top].ptr->rchild;
        }
    }
}

void BiTree::LevelOrder()
{
    int front = 0, rear = 0;
    BiNode *Q[50], *q; //初始化队列Q
    if (root == NULL)
        return;
    Q[++rear] = root; //首先存入根节点
    while (front != rear)
    {
        q = Q[++front];
        cout << q->data; //结点入队后立即打印相关信息

        if (q->lchild != NULL)
            Q[++rear] = q->lchild;
        if (q->rchild != NULL)
            Q[++rear] = q->rchild;
    }
}

void levelorder(BiNode *root)
{
    int front = 0, rear = 0;
    BiNode *Q[50], *q, *tmp = root; //初始化队列Q
    if (tmp == NULL)
        return;
    Q[++rear] = tmp; //首先存入根节点
    while (front != rear)
    {
        q = Q[++front];
        cout << q->data; //结点入队后立即打印相关信息

        if (q->lchild != NULL)
            Q[++rear] = q->lchild;
        if (q->rchild != NULL)
            Q[++rear] = q->rchild;
    }
}

void levelorder_version2(BiNode *root)
{
    int front = 0, rear = 0;
    BiNode *Q[50], *q; //初始化队列Q
    if (root == NULL)
        return;
    Q[++rear] = root; //首先存入根节点
    cout << root->data;
    while (front != rear)
    {
        q = Q[++front];

        if (q->lchild != NULL)
        {
            Q[++rear] = q->lchild;
            cout << q->lchild->data;
        }
        if (q->rchild != NULL)
        {
            Q[++rear] = q->rchild;
            cout << q->rchild->data;
        }
    }
}

void Create(BiNode *&r)
{
    char c;

    cin >> c;

    if (c == '#')
        r = NULL;
    else
    {
        r = new BiNode;
        r->data = c;
        cout << c << " is in." << endl;
        Create(r->lchild);
        Create(r->rchild);
    }
}

/*带参构造函数的递归实现*/
BiTree::BiTree()
{
    Create(root);
}

BiTree::BiTree(BiNode *&b)
{
    root = b;
}

void BiTree::release(BiNode *&r)
{
    if (r == NULL)
        return;
    else
    {
        release(r->lchild);
        release(r->rchild);
        delete r;
    }
}

BiTree::~BiTree()
{
    release(root);
}

void CreateBinTree(istream &in, BiNode *&BT)
{
    char input;
    stack<BiNode *> s;
    in >> input;
    BT = new BiNode{input, nullptr, nullptr};
    BiNode *cur = BT;
    bool isright = 0;
    //左括号向左下展开并且入栈，遇到逗号读栈顶的右结点，遇到右括号出栈
    while (in >> input)
    {
        switch (input)
        {
        case '(':
            s.push(cur);
            isright = 0; //设置向左遍历的标志
            break;
        case ')':
            s.pop();
            break;
        case ',':
            cur = s.top();
            isright = 1; //设置向右遍历的标志
            break;
        case '#':
            in.setstate(in.badbit); //输入流结束
            break;
        default:                                             //为大写英文字母
            BiNode *p = new BiNode{input, nullptr, nullptr}; //默认两个孩子结点指向nullptr
            if (isright)
            {
                cur->rchild = p;
                cur = cur->rchild;
            }
            else
            {
                cur->lchild = p;
                cur = cur->lchild;
            }
            // s.push(p);
            break;
        }
    }
    in.clear();
}

int depth(BiNode *root)
{
    if (root == nullptr)
        return 0;
    else
    {
        int i = depth(root->lchild);
        int j = depth(root->rchild);
        return i < j ? j + 1 : i + 1;
    }
}

int main()
{
    // fstream f("input.txt");
    string input("A(B(D, E(G, )), C( , F))#");
    istringstream in(input);
    BiNode *bn;
    CreateBinTree(in, bn);
    BiTree b(bn);
    b.PreOrder();
    return 0;
}