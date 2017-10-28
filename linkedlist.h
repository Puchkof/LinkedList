#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

#include "memory.h"
template <class T>
void Swap_T(T* pThis, const T& R) // template for assignment operator
{
    char sBuff[sizeof(T)];//buffer for current condition of object to destroy object in future
    T Temp(R);//temporary object, copied from R. It`s on stack to call destructor of present object after function ending
    memcpy(sBuff, pThis, sizeof(T));
    memcpy(pThis, &Temp, sizeof(T));
    memcpy(&Temp, sBuff, sizeof(T));
}

template<class T>
class LinkedList
{
    struct Node//structure for linking the list
    {
        T mnValue;//the value
        Node* mpNext;//pointer to the next value
        Node(T nValue):mnValue(nValue)//constructor for the structure
        {}
    };

    Node* mpBeg;//pointer to the beginning of the list
    Node* mpEnd;//pointer to the end of the list

public:
    LinkedList():mpBeg(0), mpEnd(0)//creates the empty list with pointers equal to 0
    {
        cout << "LinkedList at " << this << endl;//some diagnostics
    }

    ~LinkedList()//destructor
    {
        Node* pCur = mpBeg;
        Node* pBuf;
        while (pCur != 0)
        {
            pBuf = pCur->mpNext;
            delete pCur;
            pCur = pBuf;
        }

        cout << "Deleting LinkedList at " << this << endl;
    }

    LinkedList(const LinkedList& R):mpBeg(0), mpEnd(0)//copy constructor
    {
        Node* pCur = R.mpBeg;
        while (pCur != 0)
        {
            push_back(pCur->mnValue);
            pCur = pCur->mpNext;
        }

        cout << "Copying from " << &R << " to " << this << endl;
    }

    LinkedList& operator =(const LinkedList& R)//assignment operator
    {
        if (this != &R)
            Swap_T(this,R);

        return *this;
    }

    void push_back(T nValue)//inserts value to the end of the list
    {
        Node* pTemp = new Node(nValue);
        if (mpBeg == 0)
            mpBeg = mpEnd = pTemp;
        else
        {
            mpEnd->mpNext = pTemp;
            mpEnd = pTemp;
            mpEnd->mpNext = 0;
        }
    }

    void Show()//outputs the list to the console
    {
        Node* pCur = mpBeg;
        while (pCur != 0)
        {
            cout << pCur->mnValue << ' ';
            pCur = pCur->mpNext;
        }
        cout << endl;
    }

    void Sort()//sorts the list
    {
        Node* pCur = mpBeg;
        if (pCur == 0)
            return;
        int pCurInd = 0, nSize = 1;
        T* pAr = new T[nSize];
        while (pCur != 0)
        {
            pAr[pCurInd++] = pCur->mnValue;
            if (pCurInd >= nSize)
            {
                T* pBuf = new T[nSize*2];
                memcpy(pBuf, pAr, sizeof(T) * pCurInd);
                delete []pAr;
                pAr = pBuf;
                nSize *= 2;
            }
            pCur = pCur->mpNext;
        }
        T nBuf;
        for (int i = 0; i < pCurInd-1; ++i)
        {
            for (int j = 0; j < pCurInd-i-1; ++j)
            {
                if (pAr[j] > pAr[j+1])
                {
                    nBuf = pAr[j];
                    pAr[j] = pAr[j+1];
                    pAr[j+1] = nBuf;
                }
            }
        }
        LinkedList Temp;
        for(int i = 0; i < pCurInd; ++i)
            Temp.push_back(pAr[i]);
        *this = Temp;
        delete []pAr;
    }

    void Delete(T nValue)//search for the value and, if it`s found, deletes it
    {
        Node* pBuf;
        Node* pCur = mpBeg;
        if (pCur->mnValue == nValue)
        {
            mpBeg = mpBeg->mpNext;
            delete pCur;
            return;
        }
        pBuf = pCur;
        pCur = pCur->mpNext;
        while (pCur != 0)
        {
            if (pCur->mnValue == nValue)
            {
                pBuf->mpNext=pCur->mpNext;
                delete pCur;
                break;
            }
            pBuf=pCur;
            pCur=pCur->mpNext;
        }
        if (pCur==0)
        {
            cout << "No such an element: " << nValue << endl;
        }
    }

    class Iterator//iterator to move through the list
    {
        Node* mpCur;//pointer to the current Node of the list
    public:
        Iterator():mpCur(0)//creates iterator with pointer to 0
        {
            cout << "Iterator at " << this << endl;
        }

        ~Iterator()//destructor
        {
            cout << "Deleting iterator-object at " << this << endl;
        }

        Iterator(const Iterator& R)//copy constructor;
        {
            mpCur = R.mpCur;
            cout << "Copying from " << &R << " to " << this << endl;
        }

        Iterator& operator =(const Iterator &R)//assignment operator
        {
            if (this != &R)
                Swap_T(this,R);

            return *this;
        }

        void put_to_the_begin(LinkedList& List)//puts the iterator to the beginning of the List
        {
            mpCur=List.mpBeg;
        }

        void put_to_the_end(LinkedList& List)//puts the iterator to the next pointer after the end of the List
        {
            mpCur=List.mpEnd->mpNext;
        }

        const Iterator& operator ++()//overloaded operator ++
        {
            if (mpCur!=0)
                mpCur=mpCur->mpNext;

            return *this;
        }

        bool operator !=(const Iterator &R)//overloaded operator !=
        {
            return (mpCur!=R.mpCur);
        }

        T& operator *()//overloaded operator *
        {
            return (mpCur->mnValue);
        }
    };
};

#endif // LINKEDLIST_H
