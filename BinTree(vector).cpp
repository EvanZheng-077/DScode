#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
template<typename T>
struct BinNode
{
    T data;
    BinNode<T>* parent;
    BinNode<T>* left;
    BinNode<T>* right;
    int height;

    BinNode();
    BinNode(const T& e,BinNode<T>* p=nullptr,BinNode<T>* l=nullptr,BinNode<T>* r=nullptr,int h = 0):data(e),parent(p),left(l),right(r),height(h){}
    ~BinNode();

    BinNode<T>* insertAsLeft(T const& e){
        return left=new BinNode(e,this);
    }

    BinNode<T>* insertAsRight(T const& e){
        return right=new BinNode(e,this);
    }

    int size();

    bool operator<(BinNode<T> const& e){
        return this->data<e->data;
    }

    bool operator=(BinNode<T> const& e){
        return this->data==e->data;
    }

};

template<typename T>
class BinTree{
    protected:
        int _size;
        BinNode<T>* _root;
        virtual int upDateHeight(BinNode<T>* x);
        void upDateHeightAbove(BinNode<T>* x);
    public:
        BinTree():_size(0),_root(nullptr){}
        ~BinTree(){if(_size>0)  remove(_root);}
        int size() const{return _size;}
        bool empty() const{return !_root;}
        BinNode<T>* root() const{return _root;}
        BinNode<T>* insertAsRoot(T const& e);
        BinNode<T>* insertAsLeft(BinNode<T>* root,T const& e);
        BinNode<T>* insertAsRight(BinNode<T>* root,T const& e);
        BinNode<T>* attachAsLeft(BinNode<T>* root,BinNode<T>* &sub);
        BinNode<T>* attachAsRight(BinNode<T>* root,BinNode<T>* &sub);
        int remove(BinNode<T>* x);
        void travPre(BinNode<T>* root){
            if(!root)
                return;
            cout<<root->data<<endl;
            travPre(root->left);
            travPre(root->right);
        }

};

template<typename T>
int BinTree<T>::upDateHeight(BinNode<T>* x){
    return x->height=1+max(x->left?x->left->height:-1,x->right?x->right->height:-1);
}

template<typename T>
void BinTree<T>::upDateHeightAbove(BinNode<T>* x){
    while(x){
        upDateHeight(x);
        x = x->parent;
    }
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const &e){
    this->_size=1;
    return this->_root=new BinNode<T>(e);
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLeft(BinNode<T>* x,T const &e){
    _size++;
    x->insertAsLeft(e);
    upDateHeightAbove(x);
    return x->left;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRight(BinNode<T>* x,T const &e){
    _size++;
    x->insertAsRight(e);
    upDateHeightAbove(x);
    return x->right;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLeft(BinNode<T>* x,BinNode<T>* &s){
    if(x->left=s->_root){
        x->left->parent=x;
    }
    _size+=s->_size;
    upDateHeightAbove(x);
    s->_root=nullptr;
    s->_size=0;
    s=nullptr;
    return x;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRight(BinNode<T>* x,BinNode<T>* &s){
    if(x->right=s->_root){
        x->right->parent=x;
    }
    _size+=s->_size;
    upDateHeightAbove(x);
    s->_root=nullptr;
    s->_size=0;
    s=nullptr;
    //release(s);
    return x;
}

template<typename T>
static int removeAt(BinNode<T>* x){
    if(!x)
        return 0;
    int n = 1 + removeAt(x->left) + removeAt(x->right);
    //release(x->data);release(x);
    return n;
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x){
    if(x==_root){
        x=nullptr;
    }
    else if(x->parent->left==x){
        x->parent->left=nullptr;
    }
    else{
        x->parent->right=nullptr;
    }
    upDateHeightAbove(x->parent);
    int n=removeAt(x);
    _size-=n;
    return n;
}

int partition(int lo,int hi,vector<int>& _elem){
	swap(_elem[lo],_elem[lo+rand()%(hi-lo+1)]);
	int pivot=_elem[lo];
	int mi=lo;
	for(int k=lo+1;k<=hi;k++){
		if(_elem[k]<pivot){//only need to swap when...
			swap(_elem[++mi],_elem[k]);//k++->greater than pivot-->no need to do...
		}
	}
	swap(_elem[lo],_elem[mi]);// ? L--mi--G partition complete
	return mi;
}

void quickSort(int lo,int hi,vector<int>& arr){
	if(hi-lo<2)
		return;
	int mi=partition(lo,hi-1,arr);
	quickSort(lo,mi,arr);
	quickSort(mi+1,hi,arr);
}

int main(){
    vector<int> test={1,2,3};
    BinTree<int> Tree;
    BinNode<int>* root=Tree.insertAsRoot(1);
    Tree.root()->insertAsLeft(2);
    Tree.root()->insertAsRight(3);
    Tree.travPre(root);
    return 0;
}
