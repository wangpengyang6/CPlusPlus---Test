#pragma once
template<class K>
struct BSTreeNode
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
    bool insert(const K& key)//插入
    {
        if(_root == nullptr)
        {
            _root = new Node(key);
            return true;
        }
        Node* cur = _root;
        Node* fcur = nullptr;
        while(cur)
        {
            if(key > cur->_key)
            {
                fcur = cur;
                cur = cur->_right;
            }
            else if(key < cur->_key)
            {
                fcur = cur;
                cur = cur->_left;
            }
            else
                return false;
        }
        cur = new Node(key);
        if(fcur->_key < key)
            fcur->_right = cur;
        else
            fcur->_left = cur;
        return true;
    }

    void InOrder()//中序打印
    {
        _InOrder(_root);
    }
    void _InOrder(Node* root)
    {
        if(root == nullptr)
            return;
        _InOrder(root->_left);
        cout<<root->_key<<' ';
        _InOrder(root->_right);
    }

    bool find(const K& key)
    {
        Node* cur = _root;
        while(cur)
        {
            if(cur->_key < key)
                cur = cur->_right;
            else if(cur->_key > key)
                cur = cur->_left;
            else
                return true;
        }
        return false;
    }

    bool erase(const K& key)
    {
        Node* parent = nullptr;
        Node* cur = _root;

        while (cur)
        {
            if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                // 删除
                // 1、左为空
                if (cur->_left == nullptr)
                {
                    if (cur == _root)
                        _root = cur->_right;//更新根节点
                    else
                    {
                        if (parent->_left == cur)
                            parent->_left = cur->_right;
                        else
                            parent->_right = cur->_right;
                    }

                    delete cur;

                } // 2、右为空
                else if (cur->_right == nullptr)
                {
                    if (cur == _root)
                        _root = cur->_left;
                    else
                    {
                        if (parent->_left == cur)
                            parent->_left = cur->_left;
                        else
                            parent->_right = cur->_left;
                    }

                    delete cur;
                }
                else
                {
                    // 找右树最小节点替代，也可以是左树最大节点替代
                    Node* pminRight = cur;
                    Node* minRight = cur->_right;
                    while (minRight->_left)
                    {
                        pminRight = minRight;
                        minRight = minRight->_left;
                    }

                    cur->_key = minRight->_key;

                    if (pminRight->_left == minRight)
                        pminRight->_left = minRight->_right;
                    else
                        pminRight->_right = minRight->_right;

                    delete minRight;
                }
                return true;
            }
        }

        return false;
    }
private:
    Node* _root = nullptr;
};
