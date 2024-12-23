#include<iostream>
using namespace std;
struct node {
    int data;
    node* prev;
    node* next;
    node() : data(0), prev(nullptr), next(nullptr) {};
    node(int data) : data(data), prev(nullptr), next(nullptr) {};
    ~node() {};
};
node* insertBegin(node* head, int data) {
    node* newNode = new node(data);
    newNode->next = head;
    if (head != nullptr)
    {
        head->prev = newNode;
    }
    return newNode;
}
node* insertEnd(node* head, int data)
{
    node* newNode = new node(data);
    if (head == nullptr)
    {
        head = newNode;
    }
    else if (head != nullptr)
    {
        node* curr = head;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }
    return head;
}
node* insertAtPos(node* head, int pos, int data)
{
    node* newNode = new node(data);
    if (pos == 1)
    {
        newNode->next = head;
        if (head != nullptr)
        {
            head->prev = newNode;
        }
        head = newNode;
        return head;
    }
    node* curr = head;
    for (int i = 1; i < pos - 1 && curr != nullptr; i++)
    {
        try
        {
            curr = curr->next;
            if (curr == nullptr)
            {
                throw(true);
            }
        }
        catch (bool)
        {
            cout << "Klaida!!! Elemento pozicija uz saraso ribu\n";
            delete newNode;
            return head;
        }
    }
    newNode->prev = curr;
    newNode->next = curr->next;
    curr->next = newNode;
    if (newNode->next != nullptr)
    {
        newNode->next->prev = newNode;
    }
    return head;
}
node* deleteBegin(node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    node* temp = head;
    head = head->next;
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    delete temp;
    return head;
}
node* deleteEnd(node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    node* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    if (temp->prev == nullptr)
    {
        delete temp;
        return nullptr;
    }
    temp->prev->next = nullptr;
    delete temp;
    return head;
}
node* deleteData(node* head, int data)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    node* temp = head;
    while(temp!=nullptr && temp->data !=data)
    {
        try
        {
            temp = temp->next;
            if (temp == nullptr)
            {
                throw(true);
            }
        }
        catch (bool)
        {
            cout << "Klaida!!! Elemento nera sarase\n";
            return head;
        }
    }
    if (temp->prev != nullptr)
    {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr)
    {
        temp->next->prev = temp->prev;
    }
    if (head == temp)
    {
        head = temp->next;
    }
    delete temp;
    return head;
}
int findData(node* head, int pos)
{
    if (head == nullptr)
    {
        cout << "Klaida!!! Sarasas tuscias\n";
        return NULL;
    }
    node* curr = head;
    for (int i = 1; i < pos && curr != nullptr; i++)
    {
        try
        {
            curr = curr->next;
            if (curr == nullptr)
            {
                throw(true);
            }
        }
        catch (bool)
        {
            cout << "Klaida!!! Elemento pozicija uz saraso ribu\n";
            return NULL;
        }
    }
    return curr->data;
}
int findSize(node* head)
{
    node* curr = head;
    int size=0;
    while (curr != nullptr)
    {
        curr = curr->next;
        size++;
    }
    return size;
}
node* flushList(node* head)
{
    if (head == nullptr)
    {
        return head;
    }
    node* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
        delete temp->prev;
    }
    delete temp;
    return nullptr;
}
void printList(node* head)
{
    node* curr = head;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
}
void printMenu()
{
    cout << "---------------------------------------------------";
    cout << "\nPasirinkite norima veiksma ";
    cout << "\n---------------------------------------------------";
    cout << "\n1. Prideti nauja elementa ";
    cout << "\n---------------------------------------------------";
    cout << "\n2. Pasalinti elementa ";
    cout << "\n---------------------------------------------------";
    cout << "\n3. Surasti elementa sarase pagal nurodyta vieta";
    cout << "\n---------------------------------------------------";
    cout << "\n4. Patikrinti ar sarasas tuscias ";
    cout << "\n---------------------------------------------------";
    cout << "\n5. Atspausdinti sarasa ";
    cout << "\n---------------------------------------------------";
    cout << "\n6. Parodyti saraso dydi ";
    cout << "\n---------------------------------------------------";
    cout << "\n7. Isvalyti sarasa ";
    cout << "\n---------------------------------------------------";
    cout << "\n8. Baigti darba ";
    cout << "\n---------------------------------------------------\n";
}
void addMenu()
{
    cout << "---------------------------------------------------";
    cout << "\nKur prideti elementa? ";
    cout << "\n1. I saraso pradzia ";
    cout << "\n2. I nurodyta pozicija sarase ";
    cout << "\n3. I saraso gala ";
    cout << "\n---------------------------------------------------\n";
}
void delMenu()
{
    cout << "---------------------------------------------------";
    cout << "\nIs kur pasalinti elementa? ";
    cout << "\n1. Is saraso pradzios ";
    cout << "\n2. Su nurodyta reiksme ";
    cout << "\n3. Is saraso galo ";
    cout << "\n---------------------------------------------------\n";
}
int main()
{
    char choice = NULL;
    int data=NULL, pos=NULL;
    node* head = nullptr;
    printMenu();
    while (choice != '8')
    {
        cout << "Veiksmas: ";
        cin>>choice;
        if (choice - '0' < 1 || choice - '0' > 8)
        {
            cout << "Klaida!!! Tokio veiksmo neegzistuoja.\n";
            continue;
        }
        if (choice == '1')
        {
            addMenu();
            cout << "Veiksmas: ";
            cin >> choice;
            if (choice == '1')
            {
                cout << "Elementas: ";
                cin >> data;
                head = insertBegin(head, data);
            }
            else if (choice == '2')
            {
                cout << "Naujo elemento pozcija: ";
                cin >> pos;
                cout << "Elementas: ";
                cin >> data;
                head = insertAtPos(head, pos, data);

            }
            else if (choice == '3')
            {
                cout << "Elementas: ";
                cin >> data;
                head = insertEnd(head, data);
            }
        }
        else if (choice == '2')
        {
            delMenu();
            cout << "Veiksmas: ";
            cin >> choice;
            if (choice == '1')
            {
                head = deleteBegin(head);
            }
            else if (choice == '2')
            {
                cout << "Pasalinamo elemento reiksme: ";
                cin >> data;
                head = deleteData(head, data);
            }
            else if (choice == '3')
            {
                head = deleteEnd(head);
            }
        }
        else if (choice == '3')
        {
            cout << "Elemento pozcija: ";
            cin >> pos;
            cout << "Elementas: " << findData(head, pos)<<endl;
        }
        else if (choice == '4')
        {
            if (head == nullptr)
            {
                cout << "Sarasas tuscias\n";
            }
            else if (head != nullptr)
            {
                cout << "Sarasas turi elementu\n";
            }
        }
        else if (choice == '5')
        {
            cout << "Sarasas: ";
            printList(head);
            cout << endl;
        }
        else if (choice == '6')
        {
            cout << "Saraso dydis: " << findSize(head)<<endl;
        }
        else if (choice == '7')
        {
            head = flushList(head);
        }
    }
}