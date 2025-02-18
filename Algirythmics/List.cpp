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
    Node<T>* headRef = NULL;

    List(Node<T>* node = NULL)
    {
        this->headRef = node;
    }

    ~List() {
        if (!this->headRef) return;

        Node<T>* current = this->headRef;
        Node<T>* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != nullptr);
    }

    void append(T new_data) 
    {
        Node<T>* new_node = new Node<T>();
        Node<T>* last = this->headRef;
        new_node->data = new_data;
        if (this->headRef == NULL)
        {
            this->headRef = new Node<T>();
            this->headRef->data = new_data;
            this->headRef->next = new_node;
            return;
        }

        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new_node;

        return;
    }

    void display() 
    {
        if (this->headRef == nullptr)
        {
            cout << "Empty";
            return;
        }
        Node<T>* temp = this->headRef;
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
};


void separateListByX(List<int>* base, int x, List<int>*& lower, List<int>*& greater)
{   
    Node<int>* temp = base->headRef->next;
    Node<int>* last = base->headRef;

    while (temp != nullptr)
    {
        if (temp->data < x)
        {
            if (lower->headRef == NULL)
            {
                lower->headRef = temp;
                last->next = last->next->next;
                lower->headRef->next = nullptr;
            }
            else
            {
                Node<int>* tmpl = lower->headRef;
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
            if (greater->headRef == NULL)
            {
                greater->headRef = temp;
                last->next = last->next->next;
                greater->headRef->next = nullptr;
            }
            else
            {
                Node<int>* tmpg = greater->headRef;
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