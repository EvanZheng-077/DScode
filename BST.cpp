#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T1,typename T2>
struct TNode{
    T1 key;
    T2 data;
    int size;
    TNode<T1,T2>* left;
    TNode<T1,T2>* right;
};

struct Node{
    int key;
    int data;
    Node* left;
    Node* right;
    int size;
    Node();
    Node(int key,int data,int N):key(key),data(data),size(N){this->left=nullptr;this->right=nullptr;}
    ~Node();
};

class BST{
    public:
        BST(){};
        int size() {return size(root);}
        int size(Node* x){
            if(!x)
                return 0;
            else
                return x->size;
        }
        int get(int key);
        void put(int key,int data);
        int getMax();
        int getMin();
        int floor(int key);//find the biggest key->element < given key
        int ceil(int key);//find the smallest key->element > given key
        int select(int k);
        int rank(int key);
        void DeleteMax();
        void DeleteMin();
        void Delete(int key);
        void InOrder();
    protected:
        int get(Node *x,int key);
        Node* put(Node* x,int key,int data);
        Node* getMax(Node *x);
        Node* getMin(Node *x);
        Node* floor(Node *x,int key);
        Node* ceil(Node *x,int key);
        Node* select(Node *x,int k);
        Node* DeleteMax(Node *x);
        Node* DeleteMin(Node *x);
        Node* Delete(Node *x,int key);
        int rank(int key,Node *x);
        void Print(Node *x);

    private:
        Node* root=nullptr;
};

int BST::get(Node* x,int key){
    if(!x)
        return -1;
    if(x->key>key){
        return get(x->left,key);
    }
    else if(x->key<key){
        return get(x->right,key);
    }
    else{
        return x->data;
    }
}

int BST::get(int key){
    return get(root,key);
}

Node* BST::put(Node *x,int key,int data){
    if(!x)
        return new Node(key,data,1);
    if(x->key>key){
        x->left=put(x->left,key,data);
    }
    else if(x->key<key){
        x->right=put(x->right,key,data);
    }
    else{
        x->data=data;
    }
    x->size=size(x->left)+size(x->right)+1;
    return x;
}

void BST::put(int key,int data){
    root=put(root,key,data);
}

Node* BST::getMax(Node* x){
    if(!x->right)
        return x;
    return getMax(x->right);
}

int BST::getMax(){
    Node* p=getMax(root);
    return p->data;
}

Node* BST::getMin(Node* x){
    if(!x->left)
        return x;
    return getMin(x->left);
}

int BST::getMin(){
    Node* p=getMin(root);
    return p->data;
}

Node* BST::floor(Node* x,int key){
    if(!x)
        return nullptr;
    if(x->key==key){
        return x;
    }
    else if(x->key>key){
        return floor(x->left,key);
    }
    else{
        Node* t=floor(x->right,key);
        if(t)
            return t;
        else
            return x;
    }
}

int BST::floor(int key){
    Node* x=floor(root,key);
    if(!x)
        return -1;
    else
        return x->key;
}

Node* BST::ceil(Node *x,int key){
    if(!x)
        return nullptr;
    if(x->key==key)
        return x;
    else if(key>x->key){
        return ceil(x->right,key);
    }
    else{
        Node* t=ceil(x->left,key);
        if(t)
            return t;
        else
            return x;
    }
}

int BST::ceil(int key){
    Node* x=ceil(root,key);
    if(!x)
        return -1;
    else
        return x->key;
}

Node* BST::select(Node *x,int k){
    if(!x)
        return nullptr;
    int t=size(x->left);
    if(t>k){
        return select(x->left,k);
    }
    else if(t<k){
        return select(x->right,k-t-1);
    }
    else{
        return x;
    }
}

int BST::select(int k){
    return select(root,k)->key;
}

int BST::rank(int key,Node* x){
    if(!x)
        return 0;
    if(key<x->key){
        return rank(key,x->left);
    }
    else if(key>x->key){
        return 1+size(x->left)+rank(key,x->right);
    }
    else{
        return size(x->left);
    }
}

int BST::rank(int key){
    return rank(key,root);
}

Node* BST::DeleteMax(Node *x){
    if(!x->right)
        return x->left;
    x->right=DeleteMax(x->right);
    x->size=size(x->left)+size(x->right)+1;
    return x;
}

void BST::DeleteMax(){
    root=DeleteMax(root);
}

Node* BST::DeleteMin(Node *x){
    if(!x->left)
        return x->right;
    x->left=DeleteMin(x->left);
    x->size=size(x->left)+size(x->right)+1;
    return x;
}

void BST::DeleteMin(){
    root=DeleteMin(root);
}

Node* BST::Delete(Node *x,int key){
    if(!x)
        return nullptr;
    if(key<x->key){
        return Delete(x->left,key);
    }
    else if(key>x->key){
        return Delete(x->right,key);
    }
    else{
        if(!x->right)
            return x->left;
        else if(!x->left)
            return x->right;
        Node *t=x;
        x=getMin(t->right);
        x->right=DeleteMin(t->right);
        x->left=t->left;
    }
    x->size=size(x->left)+size(x->right)+1;
    return x;
}

void BST::Delete(int key){
    root=Delete(root,key);
}

void BST::Print(Node *x){
    if(!x)
        return;
    Print(x->left);
    cout<<x->key<<" ";
    Print(x->right);
}

void BST::InOrder(){
    Print(root);
}

int main(){
    vector<int> data;
    int N=500;
    for(int i=0;i<N;i++){
        data.push_back(rand()%1000);
    }
    vector<int> keys=data;
    sort(keys.begin(),keys.end());

    BST* MyTree=new BST();
    for(int i=0;i<N;i++){
        MyTree->put(keys[i],data[i]);
    }
    MyTree->InOrder();
    return 0;
}
