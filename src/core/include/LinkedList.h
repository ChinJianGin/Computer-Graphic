#pragma once
#include"Core.h"

namespace CustomSpace
{
    template<typename T>
    class LinkedList;

    template<typename T>
    class SinglyLinkedList;

    template<typename T>
    class Node
    {
        public:
        Node(T d) 
        {
            data = d;
            previous = nullptr;
            next = nullptr;
        }
        ~Node()
        {
            if(previous != next)
            {
                delete previous;
            }
            delete next;
        }

        T get() { return this->data; }

        friend class LinkedList<T>;
        friend class SinglyLinkedList<T>;
        private:
        T data;
        Node<T>* previous;
        Node<T>* next;
    };

    template<typename T>
    class LinkedList
    {
        public:
        LinkedList()
        {
            count = 0;
            first = nullptr;
            last = nullptr;
        }
        virtual ~LinkedList()
        {
            if(first != last)
            {
                delete first;
            }
            delete last;
        }

        int size()
        {
            return count;
        }

        Node<T>* front()
        {
            return first;
        }

        Node<T>* back()
        {
            return last;
        }

        virtual void push_front(T value) = 0;
        virtual void push_back(T value) = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual void erase(Node<T>* node) = 0;
        virtual void clear() = 0;

        class Iterator
        {
            public:
            Iterator()
            {
                current = first;
            }

            Iterator(Node<T>* node)
            {
                current = node;
            }

            Iterator& operator=(Node<T>* node)
            {
                this->current = node;
                return *this;
            }

            Iterator* operator++()
            {
                if(current)
                    current = current->next;
                return this;
            }

            Iterator operator++(int)
            {
                Node<T>* preNode = current;
                current = current->next;
                return Iterator(preNode);
            }

            bool operator!=(const Iterator& it) const
            {
                return current != it.current;
            }

            T& operator*() const
            {
                return current->get();
            }

            Node<T>* get_current_node() { return this->current; }

            T getdata() { return current->get(); }
            private:
            Node<T>* current;
        };

        Iterator begin()
        {
            return Iterator(first);
        }

        Iterator end()
        {
            return Iterator(nullptr);
        }
        protected:
        int count;
        Node<T>* first;
        Node<T>* last;
    };

    template<typename T>
    class SinglyLinkedList : public LinkedList<T>
    {
        public:
        void push_front(T value) override
        {
            Node<T>* node = new Node<T>(value);
            if(this->count == 0)
                this->last = node;
            else
                node->next = this->first;
            this->first = node;
            ++(this->count);
        }

        void push_back(T value) override
        {
            Node<T>* node = new Node<T>(value);
            if(this->count == 0)
                this->first = node;
            else
                this->last->next = node;
            this->last = node;
            ++(this->count);
        }

        void pop_front() override
        {
            if(this->count == 0)
                throw std::out_of_range("empty list");
            else if(this->count == 1)
            {
                this->first = nullptr;
                this->last = nullptr;
            }
            else
            {
                Node<T>* node = this->first->next;
                this->first->next = nullptr;
                this->first = node;
            }
            --(this->count);
        }

        void pop_back() override
        {
            if(this->count == 0)
                throw std::out_of_range ("empty list");
            else if(this->count == 1)
            {
                this->first = nullptr;
                this->last = nullptr;
            }
            else
            {
                Node<T>* node = find_previous_node(this->last);
                node->next = nullptr;
                this->last = node;
            }
            --(this->count);
        }

        void erase(Node<T>* node) override
        {
            if(node == this->first)
                pop_front();
            else if(node == this->last)
                pop_back();
            else
            {
                Node<T>* preNode = find_previous_node(node);
                if(preNode == nullptr)
                    throw std::out_of_range("node not in list");
                preNode->next = node->next;
                node->next = nullptr;
                --(this->count);
            }
        }

        void clear() override
        {
            while(this->first != nullptr)
            {
                Node<T>* current = this->first;
                this->first = this->first->next;
                delete current;
                current = nullptr;
            }
        }

        private:

        Node<T>* find_previous_node(Node<T>* node)
        {
            Node<T>* preNode = this->first;
            while (preNode != nullptr)
            {
                if(node == preNode->next)
                    break;
                preNode = preNode->next;
            }
            return preNode;
        }
    };
}