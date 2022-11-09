#ifndef ALIST_H_
#define ALIST_H_

#include <cstdint>
#include <iomanip>

namespace alist
{
    template <typename T>
    class ListNode
    {
    public:
        uint32_t key;
        T val;
        ListNode *prev, *next;
        int count;
        explicit ListNode<T>(uint32_t k = 0, T v = 0, ListNode *p = nullptr, ListNode *n = nullptr, int c = 0) : key(k), val(v), prev(p), next(n), count(c) {}
    };

    template <typename T>
    class Alist
    {
    private:

        uint32_t strat = 0;

        ListNode<T> Head = ListNode<T>(), *Headptr = &Head;

        int Pos = 0, ListLength = 0;

        bool BoundCheck(bool type, int pos)
        {
            //type = 0 Insert, type = 1 Erase
            const std::string Type[2] = {"insertion", "erasing"};
            if(pos > ListLength - type)
            {
                std::cout << "Warning: no " << Type[type] << ", pos " << pos << " is out of bound" << std::endl;
                return false;
            }
            return true;
        }

        bool IsEmpty(bool type)
        {
            //type = 0 功能函数,  type = 1 Pop back
            if (type && !ListLength) {std::cout << "Error: pop_back fails, the list is empty" << std::endl; exit(1);}
            return !ListLength;
        }

        ListNode<T> *Find(int type, int k)
        {
            //type = 0 查重, type = 1 Get value, type = 2 Remove, type = 3 Get pos
            ListNode<T> *Node = Headptr;
            for(int i = 0; i < ListLength; i++)
            {
                Node = Node->next;
                if(Node->key == k)
                {
                    Pos = i;
                    if(!type) std::cout << "Warning: key " << k <<" is already in the list" << std::endl;
                    return Node;
                }
            }
            const std::string Type[3] = {"Error: get_value fails, ", "Warning: no removing, ", "Error: get_pos fails, " };
            if(type) {std::cout << Type[type-1] << "key " << k << " is not found" << std::endl;}
            if(type == 1 || type == 3) exit(1);
            return nullptr;
        }

        ListNode<T> *ReachPos(int pos)
        {
            ListNode<T> *tmp = Headptr;
            for (int i = 0; i <= pos; i++)
            {
                tmp = tmp->next;
            }
            return tmp;
        }

        void Renew(ListNode<T> *Node, bool type)
        {
            //type = 0 更新插入, type = 1 更新删除
            if (Node->prev != nullptr) Node->prev->next = (type? Node->next: Node);
            if (Node->next != nullptr) Node->next->prev = (type? Node->prev: Node);
        }

        void Delete(ListNode<T> *Node)
        {
            Renew(Node, 1);
            delete Node;
            ListLength--;
        }

        void AlterPos(int pos, ListNode<T> *Node)
        {
            insert(pos, Node->key, Node->val, Node->count, 1);
            Delete(Node);
        }

    public:

        //I.基本函数

        Alist(uint32_t size, const uint32_t *k_list, const T *v_list)
        {
            for(int i = 0; i < size; i++)
            {
                push_back(k_list[i], v_list[i]);
            }
        }

        ~Alist()
        {
            clear();
        }

        //II.基本操作

        bool push_back(uint32_t k, const T &v)
        {
            return insert(ListLength, k, v);
        }

        bool insert(uint32_t pos, uint32_t k, const T &v, int count = 0, bool type = false)
        {
            //type = 0 正常插入, type = 1 功能函数（reverse）
            if(!type && (!BoundCheck(0, pos) || Find(0, k) != nullptr)) return false;
            ListNode<T> *tmp = ReachPos(pos-1), *NewNode = new ListNode<T>(k, v, tmp, tmp->next, count);
            Renew(NewNode, 0);
            ListLength++;
            return true;
        }

        bool erase(uint32_t pos)
        {
            if(!BoundCheck(1, pos)) return false;
            ListNode<T> *Node = ReachPos(pos);
            Delete(Node);
            return true;
        }

        bool remove(uint32_t k)
        {
            ListNode<T> *Node = Find(2, k);
            if(Node == nullptr) return false;
            Delete(Node);
            return true;
        }

        bool clear()
        {
            if(IsEmpty(0)) return false;
            while(!IsEmpty(0))
            {
                Delete(Headptr->next);
            }
            return true;
        }

        T pop_back()
        {
            IsEmpty(1);
            ListNode<T> *Node = ReachPos(ListLength-1);
            T val = Node->val;
            Delete(Node);
            return val;
        }

        T get_value(uint32_t k)
        {
            ListNode<T> *Node = Find(1, k);
            T val = Node->val;
            switch(strat)
            {
                case 0://FRONT
                {
                    AlterPos(0, Node);
                    break;
                }
                case 1://SWAP
                {
                    if(Pos==0) break;
                    AlterPos(Pos-1, Node);
                    break;
                }
                case 2://COUNT
                {
                    Node->count++;
                    //std::cout << Node->count << ' ' << Node->key << std::endl;
                    ListNode<T> *Nodetmp;
                    uint32_t _pos = Pos;
                    while(_pos && Node->count >= Node->prev->count)
                    {
                        Nodetmp = Node->prev;
                        AlterPos(--_pos, Node);
                        Node = Nodetmp->prev;
                    }
                    break;
                }
                case 3://OWN STRATEGY
                {
                    AlterPos(Pos/2, Node);
                    break;
                }
                case 2022040129:
                {
                    std::cout << "硬核防伪标签" << std::endl;
                    break;
                }
                default: break;
            }
            return val;
        }

        void show()
        {
            ListNode<T> *tmp = Headptr;
            for(int i = 0; i < ListLength; i++)
            {
                tmp = tmp->next;
                std::cout << '(' << tmp->key << ',' << std::fixed << std::setprecision(2) << tmp->val << ')' << ' ';
            }
            std::cout << std::endl;
        }

        //III.进阶操作

        bool set_strategy(uint32_t strategy = 0)
        {
            strat = strategy;
            return true;
        }// strategy: 0 for Forward, 1 for Swap, 2 for Counter, 3 for YourStrategy, default is 0;

        int get_pos(uint32_t k)
        {
            Find(3, k);
            return Pos;
        } // with key error

        bool reverse()
        {
            for(int i = 0; i < ListLength; i++)
            {
                AlterPos(ListLength - i, Headptr->next);
            }
            return true;
        }

    };
}

#endif // ALIST_H_