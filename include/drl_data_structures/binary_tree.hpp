#include <deque>
#include <iostream>
#include <vector>



#ifndef DRL_BINARY_TREE
#define DRL_BINARY_TREE
namespace drl
{
    template <class T>
    class binary_tree_base
    {
     public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type &;
        using pointer = value_type *;

     public:
        virtual ~binary_tree_base(){};
        virtual bool empty() = 0;
        virtual size_t size() = 0;
        template <class FUNC>
        void preOrder(const FUNC &y, size_type begin = 0);

        template <class FUNC>
        void inOrder(const FUNC &y, size_type begin = 0);

        template <class FUNC>
        void postOrder(const FUNC &y, size_type begin = 0);

        template <class FUNC>
        void levelOrder(const FUNC &y, size_type begin = 0);
    };


    template <class T>
    class array_binary_tree : public binary_tree_base<T>
    {
     public:
        using iterator = typename binary_tree_base<T>::pointer;
        using const_iterator = const typename binary_tree_base<T>::pointer;
        iterator begin()
        {
            return elements;
        }
        iterator end()
        {
            return elements + cur_size;
        }
        const_iterator cbegin()
        {
            return elements;
        }
        const_iterator cend()
        {
            return elements + cur_size;
        }

     private:
        typename binary_tree_base<T>::pointer elements;
        typename binary_tree_base<T>::size_type max_size;
        typename binary_tree_base<T>::size_type cur_size;
        void alloc_memory()
        {
            typename binary_tree_base<T>::pointer *ep = new typename binary_tree_base<T>::value_type[max_size * 2];
            for (size_t i = 0; i < max_size; i++)
                ep[i] = elements[i];
            delete[] elements;
            elements = ep;
            max_size *= 2;
            // ps:没有让cur_size加一
        }

     public:
        array_binary_tree(typename binary_tree_base<T>::pointer pointer = nullptr,
                          typename binary_tree_base<T>::size_type size = 0)
        {
            if (pointer && size)
            {
                elements = new T[size * 2];
                for (size_t i = 0; i < size; i++)
                {
                    elements[i] = pointer[i];
                }
                cur_size = size;
                max_size = size * 2;
            }
            else
            {
                max_size = 0;
                cur_size = 0;
                elements = nullptr;
            }
        }
        ~array_binary_tree()
        {
            max_size = 0;
            cur_size = 0;
            delete[] elements;
        }
        typename binary_tree_base<T>::size_type size()
        {
            return cur_size;
        }
        bool empty()
        {
            return !!cur_size;
        }
        template <class FUNC>
        void preOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin = 0);

        template <class FUNC>
        void inOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin = 0);

        template <class FUNC>
        void postOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin = 0);

        template <class FUNC>
        void levelOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin = 0);
    };

    template <class T>
    class tree_node
    {
     public:
        tree_node<T> *left;
        tree_node<T> *right;
        tree_node<T> *parent;
        T element;
        tree_node(const T &x, tree_node<T> *parent = nullptr, tree_node<T> *left = nullptr, tree_node<T> *right = nullptr)
            : left(left), right(right), parent(parent), element(x) {}
        tree_node(const tree_node<T> &x) : element(x.element), parent(parent), left(x.left), right(x.right) {}
        void make_lchild(const tree_node<T> &x)
        {
            left = new tree_node<T>(x.element, this);
        }
        void make_rchild(const tree_node<T> &x)
        {
            right = new tree_node<T>(x.element, this);
        }
    };

    template <class T>
    class linked_binary_tree : public binary_tree_base<tree_node<T>>
    {
     public:
        using size_type = typename binary_tree_base<tree_node<T>>::size_type;
        using value_type = typename binary_tree_base<tree_node<T>>::value_type;
        value_type *elements;
        bool emptyed;
        size_type size__;
        ~linked_binary_tree()
        {
            std::deque<tree_node<T> *> qu1;
            qu1.push_back(elements);
            tree_node<T> *pcur;
            while (1)
            {
                if (qu1.size())
                {
                    pcur = qu1.front();
                }
                else
                    break;
                if (pcur->left)
                {
                    qu1.push_back(pcur->left);
                }
                if (pcur->right)
                {
                    qu1.push_back(pcur->right);
                }
                {
                    delete pcur;
                }
                qu1.pop_front();
            }
        }
        linked_binary_tree(T *ele = nullptr, size_type size_ = 0)
        {
            if (ele && size_)
            {
                bool right = false;
                std::deque<tree_node<T> *> qu1;
                elements = new value_type(ele[0]);
                tree_node<T> *cur_node = elements;
                qu1.push_back(cur_node);
                for (size_type i = 1; i < size_; i++)
                {
                    if (!right)
                    {
                        cur_node->left = new tree_node<T>(ele[i]);
                        qu1.push_back(cur_node->left);
                    }
                    else
                    {
                        cur_node->right = new tree_node<T>(ele[i]);
                        qu1.push_back(cur_node->right);
                        qu1.pop_front();
                        cur_node = qu1.front();
                    }
                    right = !right;
                }
                emptyed = false;
                size__ = size_;
            }
            else
            {
                elements = nullptr;
                emptyed = true;
            }
        }

        template <class FUNC>
        void preOrder(const FUNC &y);

        template <class FUNC>
        void inOrder(const FUNC &y);

        template <class FUNC>
        void postOrder(const FUNC &y);

        template <class FUNC>
        void levelOrder(const FUNC &y);
        virtual bool empty()
        {
            return emptyed;
        }
        virtual size_type size()
        {
            return size__;
        }
    };
} // namespace drl

#pragma region array_binary_begin
template <class T>
template <class FUNC>
void drl::array_binary_tree<T>::preOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin)
{
    if (begin >= max_size)
        return;
    y(elements[begin]);
    preOrder(y, begin + begin + 1);
    preOrder(y, begin + begin + 2);
}
template <class T>
template <class FUNC>
void drl::array_binary_tree<T>::inOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin)
{
    preOrder(y, begin + begin + 1);
    if (begin >= max_size)
        return;
    y(elements[begin]);
    preOrder(y, begin + begin + 2);
}
template <class T>
template <class FUNC>
void drl::array_binary_tree<T>::postOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin)
{
    preOrder(y, begin + begin + 1);
    preOrder(y, begin + begin + 2);
    if (begin >= max_size)
        return;
    y(elements[begin]);
}
template <class T>
template <class FUNC>
void drl::array_binary_tree<T>::levelOrder(const FUNC &y, typename binary_tree_base<T>::size_type begin)
{
    for (typename binary_tree_base<T>::size_type i = begin; i < cur_size; i++)
        y(elements[i]);
}
#pragma endregion
template <class T>
template <class FUNC>
void drl::linked_binary_tree<T>::preOrder(const FUNC &y)
{
    y(*elements);
    if (elements->left)
        preOrder(elements->left);
    if (elements->right)
        preOrder(elements->right);
}
template <class T>
template <class FUNC>
void drl::linked_binary_tree<T>::inOrder(const FUNC &y)
{
    if (elements->left)
        preOrder(elements->left);
    y(*elements);
    if (elements->right)
        preOrder(elements->right);
}
template <class T>
template <class FUNC>
void drl::linked_binary_tree<T>::postOrder(const FUNC &y)
{
    if (elements->left)
        preOrder(elements->left);
    if (elements->right)
        preOrder(elements->right);
    y(*elements);
}
template <class T>
template <class FUNC>
void drl::linked_binary_tree<T>::levelOrder(const FUNC &y)
{
    std::deque<tree_node<T> *> qu1;
    qu1.push_back(elements);
    tree_node<T> *pcur;
    while (pcur)
    {
        if (qu1.size())
        {
            pcur = qu1.front();
        }
        else
            break;
        if (pcur->left)
        {
            qu1.push_back(pcur->left);
        }
        if (pcur->right)
        {
            qu1.push_back(pcur->right);
        }
        y(*pcur);
        qu1.pop_front();
    }
}

#endif