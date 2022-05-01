#pragma once
#include"Core.h"
namespace CustomSpace
{
    template<typename T>
    class LinkList;

    template<typename T>
    class ListNode
    {
        public:
        T getData();
        private:
        T data;
        ListNode<T>* next;
        public:
        ListNode() : data(nullptr), next(nullptr) {};
        ListNode(T a) : data(a), next(nullptr) {};

        friend std::ostream &operator<<( std::ostream &out, const ListNode<T> &node)
        {
            out << typeid(node.data).name() << std::endl;
            return out;
        }

        friend class LinkList<T>;
    };

    template<typename T>
    T ListNode<T>::getData()
    {
        return data;
    }

    template<typename T>
    class LinkList
    {
    private:
        ListNode<T>* first;
    public:
        LinkList() : first(nullptr) {};
        void PrintList();
        void Push_Front(T x);
        void Push_back(T x);
        void Delete(T x);
        void Clear();
        void Reverse();
        void Pop_Front();

        int size();

        T front();

        class Iterator;

        Iterator begin()
        {
            return Iterator(first);
        }

        Iterator end()
        {
            return Iterator(nullptr);
        }

        template<typename Q>
        friend std::ostream &operator<<(std::ostream &out, LinkList<T> &obj)
        {
            ListNode<Q> *temp = obj.first;
            while(temp != nullptr)
            {
                out << *temp->getData() << std::endl;
                temp = temp->next;
            }
            std::cout << std::endl;
            return out;
        }

        class Iterator
        {
            public:
            Iterator() : current(first) {}

            Iterator(ListNode<T>* node) : current(node) {}

            T Get() { return current->getData(); }

            Iterator& operator=(ListNode<T>* node)
            {
                this->current = node;
                return *this;
            }

            Iterator& operator++()
            {
                if(current)
                    current = current->next;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator iterator = *this;
                ++*this;
                return iterator;
            }

            bool operator!=(const Iterator& iterator)
            {
                return current != iterator.current;
            }

            T operator*()
            {
                return current->getData();
            }

            private:
            ListNode<T>* current;
        };
    };

    template<typename T>
    void LinkList<T>::PrintList()
    {
        if(first == nullptr)
        {
            std::cout << "List is empty.\n";
            return;
        }

        ListNode<T>* current = first;
        while(current != nullptr)
        {
            std::cout << typeid(current->data).name() << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    template<typename T>
    void LinkList<T>::Push_Front(T x)
    {
        ListNode<T>* newNode = new ListNode<T>(x);
        newNode->next = first;
        first = newNode;
    }

    template<typename T>
    void LinkList<T>::Push_back(T x)
    {
        ListNode<T>* newNode = new ListNode<T>(x);
        if(first == nullptr)
        {
            first = newNode;
            return;
        }
        ListNode<T>* current = first;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    template<typename T>
    void LinkList<T>::Delete(T x)
    {
        ListNode<T>* current = first, *previous = nullptr;
        while (current != nullptr && current->data != x)
        {
            previous = current;
            current = current->next;
        }

        if(current == nullptr)
        {
            std::cout << "There is no " << x << "in list.\n";
        }
        else if(current == first)
        {
            first = current->next;
            delete current;
            current = nullptr;
        }
        else
        {
            previous->next = current->next;
            delete current;
            current = nullptr;
        }
    }

    template<typename T>
    void LinkList<T>::Clear()
    {
        while (first != nullptr)
        {
            ListNode<T>* current = first;
            first = first->next;
            delete current;
            current = nullptr;
        }
    }

    template<typename T>
    void LinkList<T>::Reverse()
    {
        if(first == nullptr || first->next == 0)
        {
            return;
        }
        ListNode<T>* previous = nullptr, *current = first, *preceding = first->next;
        while(preceding != nullptr)
        {
            current->next = previous;
            previous = current;
            current = preceding;
            preceding = preceding->next;
        }
        current->next = previous;
        first = current;
    }

    template<typename T>
    void LinkList<T>::Pop_Front()
    {
        ListNode<T>* current = first;
        if(current == nullptr)
        {
            std::cout << "The list is empty.\n";
            return;
        }
        first = first->next;
        delete current;
        current = nullptr;
    }

    template<typename T>
    int LinkList<T>::size()
    {
        if(first == nullptr)
        {
            std::cout << "List is empty\n";
            return 0;
        }

        ListNode<T>* temp = first;
        int NodeCounter = 0;
        while(temp != nullptr)
        {
            NodeCounter += 1;
            temp = temp->next;
        }
        return NodeCounter;
    }

    template<typename T>
    T LinkList<T>::front()
    {
        if(first == nullptr)
        {
            std::cout << "List is empty\n";
            return nullptr;
        }

        return first->getData();
    }
}