#include <iostream>
using namespace std;

template<typename T>
struct Node
{
    T data;
    Node* next = nullptr;
};

template<typename T>
class List
{
public:
    Node<T>* head_ref = NULL;

    List(Node<T>* node = NULL)
    {
        this->head_ref = node;
    }

    void append(T new_data) 
    {
        Node<T>* new_node = new Node<T>();
        Node<T>* last = this->head_ref;
        new_node->data = new_data;
        if (this->head_ref == NULL)
        {
            this->head_ref = new Node<T>();
            this->head_ref->data = new_data;
            this->head_ref->next = new_node;
            this->count++;
            return;
        }

        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new_node;

        this->count++;
        return;
    }

    void display() 
    {
        Node<T>* temp = this->head_ref;
        bool nfirst = false;
        while (temp != NULL)
        {
            if (nfirst)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            else
            {
                nfirst = true;
            }

        }
        cout << endl;
        return;
    }

    void displayCount()
    {
        cout << this->count << endl;
        return;
    }

private:
    int count = 0;
};


void separateListByX(List<int>* base, int x, List<int>*& lower, List<int>*& greater)
{   
    Node<int>* temp = base->head_ref->next;
    Node<int>* last = base->head_ref;

    while (temp != nullptr)
    {
        if (temp->data < x)
        {
            if (lower->head_ref == NULL)
            {
                lower->head_ref = temp;
                last->next = last->next->next;
                lower->head_ref->next = nullptr;
            }
            else
            {
                Node<int>* tmpl = lower->head_ref;
                while (tmpl->next != nullptr)
                {
                    tmpl = tmpl->next;
                }
                tmpl->next = temp;
                last->next = last->next->next;
                tmpl->next->next = nullptr;
            }

        }
        else
        {
            if (greater->head_ref == NULL)
            {
                greater->head_ref = temp;
                last->next = last->next->next;
                greater->head_ref->next = nullptr;
            }
            else
            {
                Node<int>* tmpg = greater->head_ref;
                while (tmpg->next != nullptr)
                {
                    tmpg = tmpg->next;
                }
                tmpg->next = temp;
                last->next = last->next->next;
                tmpg->next->next = nullptr;
            }
        }

        temp = last->next;
    }
}


int asdmain()
{
    int x;
    cin >> x;
    List<int>* based = new List<int>();
    based->append(9);
    based->append(3);
    based->append(6);
    based->append(8);
    based->append(13);
    based->append(6);
    based->append(9);
    based->append(33);
    based->append(6);
    based->append(2);
    based->append(5);
    based->append(2);
    based->append(12);
    based->append(4);
    based->append(10);

    List<int>* lowerValues = new List<int>();
    List<int>* greaterValues = new List<int>();

    separateListByX(based, x, lowerValues, greaterValues);

    lowerValues->display();
    greaterValues->display();

    delete based;
    delete lowerValues;
    delete greaterValues;
    return 0;
}