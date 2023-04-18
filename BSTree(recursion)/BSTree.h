#pragma once

template<class K>
struct BSTreeNode//结点
{
    BSTreeNode<K>* _left;
    BSTreeNode<K>* _right;
    K _key;
    BSTreeNode(const K& key)
            :_left(nullptr)
            ,_right(nullptr)
            ,_key(key)
    {}
};

template<class K>
class BSTree
{
    typedef BSTreeNode<K> Node;
public:
    ~BSTree()
    {
        Destory(_root);
        _root = nullptr;
    }

    BSTree() = default; // 制定强制生成默认构造

    BSTree<K>& operator= (BSTree t)
    {
        swap(_root,t._root);
        return *this;
    }

    BSTree(const BSTree<K>& t)
    {
        _root = Copy(t._root);
    }

    bool insert(const K& key)//插入
    {
        return _insert(_root,key);
    }

    void InOrder()//中序打印
    {
        _InOrder(_root);
    }

    bool find(const K& key)
    {
        return _find(_root,key);
    }

    bool erase(const K& key)
    {
        return _erase(_root,key);
    }

protected:

    Node* Copy(Node* root)
    {
        if(root == nullptr)
            return nullptr;
        Node* newroot = new Node(root->_key);
        newroot->_left = Copy(root->_left);
        newroot->_right = Copy(root->_right);
        return newroot;
    }

    void Destory(Node* root)
    {
        if(root == nullptr)
            return;
        Destory(root->_left);
        Destory(root->_right);
        delete root;
    }

    void _InOrder(Node* root)
    {
        if(root == nullptr)
            return;
        _InOrder(root->_left);
        cout<<root->_key<<' ';
        _InOrder(root->_right);
    }

    bool _insert(Node*& root,const K& key)
    {
        if(root == nullptr)
        {
            root = new Node(key);
            return true;
        }
        if(root->_key > key)
            return _insert(root->_left,key);
        else if(root->_key < key)
            return _insert(root->_right,key);
        else
            return false;
    }

    bool _find(Node* root,const K& key)
    {
        if(root == nullptr)
            return false;
        if(root->_key == key)
            return true;
        if(root->_key < key)
            return _find(root->_right,key);
        else
            return _find(root->_left,key);
    }

    bool _erase(Node*& root,const K& key)
    {
        if(root == nullptr)
            return false;
        if(root->_key < key)
            return _erase(root->_right,key);
        else if(root->_key > key)
            return _erase(root->_left,key);
        else
        {
            //通过引用直接删除
            Node* del = root;
            if(root->_left == nullptr)
                root = root->_right;
            else if(root->_right == nullptr)
                root = root->_left;
            else
            {
                Node* MaxLeft = root->_left;
                while(MaxLeft->_right)
                    MaxLeft = MaxLeft->_right;
                swap(root->_key,MaxLeft->_key); //只能交换
                return _erase(root->_left,key); //转换成子树问题去删除，之后只可能走if/else if
            }
            delete del;
            return true;
        }
    }
private:
    Node* _root = nullptr;
};
