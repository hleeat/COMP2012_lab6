#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class BiLNode {
public:
    T data {};
    BiLNode<T> *next {nullptr};
    BiLNode<T> *prev {nullptr};
    BiLNode(T input) {
        data = input;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Deque {
private:
    BiLNode<T> *head {nullptr};
    BiLNode<T> *tail {nullptr};
    int size {0};
public:
    Deque() = default;
    ~Deque() {
        BiLNode <T>* tmp = head;
        while(tmp != nullptr) {
            tmp = tmp->next;
            delete head;
            head = tmp;
        }
    }

    void push_back(const T& value) {
        if(head == nullptr) {
            head = new BiLNode<T> (value);
            tail = head;
        } else {
            BiLNode<T> *tmp = new BiLNode<T> (value);
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        size++;
    }

    void push_front(const T& value) {
        if(head == nullptr) {
            head = new BiLNode<T> (value);
            tail = head;
        } else {
            BiLNode<T> *tmp = new BiLNode<T> (value);
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
        }
        size++;
    }

    T pop_back() {
        if (head == nullptr) {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr) {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = tail->data;
        BiLNode<T> *bftail = tail->prev;
        delete tail;
        tail = bftail;
        tail->next = nullptr;
        size--;
        return tmp;
    }

    T pop_front() {
        if (head == nullptr) {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr) {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = head->data;
        BiLNode<T> *afhead = head->next;
        delete head;
        head = afhead;
        head->prev = nullptr;
        size--;
        return tmp;
    }

    void clear() {
        while(size>0) this->pop_back();
    }

    // TODO 1: overload operator==
    bool operator==(const Deque<T> &d)
    {
        if(this->size==d.size)
        {
            BiLNode<T> *h=this->head;
            BiLNode<T> *h1=d.head;
            if(h==nullptr && h1==nullptr) return true;
            while(h!=nullptr && h1!=nullptr)
            {
                if(h->data!=h1->data) return false;
                h=h->next;
                h1=h1->next;
            }
            return true;
        }
        else return false;
    }
    // TODO 2: overload operator=
    const Deque<T>& operator=(const Deque<T>& d)
    {
        if(this!=&d)
        {
            BiLNode<T> *temp;
            this->clear();
            if(d.size==0)
            {
                this->size=0;
                this->head=nullptr;
                this->tail=nullptr;
            }
            else
            {
                BiLNode<T> *tmp=this->head;
                BiLNode<T> *tmp1 = d.head;
                while(tmp1!=nullptr)
                {
                    this->push_back(tmp1->data);
                    tmp1=tmp1->next;
                }
                this->size=d.size;
            }
        }
        return *this;
    }
    // TODO 3: overload operator+
    Deque<T> operator+(const Deque<T> & d)
    {
        Deque<T> tmp;
        tmp=*this;
        BiLNode<T> *d1=d.head;
        while(d1!=nullptr)
        {
            tmp.push_back(d1->data);
            d1=d1->next;
        }
        return tmp;
    }
    // TODO 4: overload operator<<
    template <typename T1>
    friend ostream& operator<<(ostream& os, const Deque<T1>& d);
    // template <typename T1,typename T2>
    // friend ostream& operator<<(ostream& os, const Deque<pair<T1,T2>>& d);
};
template <typename T>
ostream& operator<<(ostream& os, const Deque<T>& d)
{
    BiLNode<T>* tmp;
    tmp=d.head;
    os<<"[";
    while(tmp!=d.tail)
    {
        os<<tmp->data<<"<-->";
        tmp=tmp->next;
    }
    os<<tmp->data<<"]";
    return os;
}
// template <typename T1,typename T2>
// ostream& operator<<(ostream& os, const Deque<pair<T1,T2>>& d)
// {
//     d.head->data.first
//     BiLNode<T>* tmp;
//     tmp=d.head;
//     os<<"[";
//     while(tmp!=d.tail)
//     {
//         os<<tmp->data<<"<-->";
//     }
//     os<<tmp->data<<"]"<<endl;
//     return os;
// }
#endif