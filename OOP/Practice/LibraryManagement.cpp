#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Person
{
protected:
    string name;
    int nBorrows;
    int maxBorrows;
public:
    Person(string name, int maxBorrows) 
        : name(name), nBorrows(0), maxBorrows(maxBorrows) {}
    virtual ~Person() = default;
    string getName() const
    {
        return name;
    }
    int getNBorrows() const
    {
        return nBorrows;
    }
    int getMaxBorrows()
    {
        return maxBorrows;
    }
    void incrementNBorrows()
    {
        nBorrows++;
    }
    void decrementNBorrows()
    {
        nBorrows--;
    }
    virtual string getType() const = 0;
};

class Student : public Person
{
public:
    Student(string name) : Person(name, 3) {}
    string getType() const override
    {
        return "Student";
    }
};

class Faculty : public Person
{
public:
    Faculty(string name) : Person(name, 5) {}
    string getType() const override
    {
        return "Faculty";
    }
};


class Library;

class LibraryItem
{
protected:
    Library* ptrLib;
    string ID;
    string title;
    bool borrowed;
    Person* borrower;
public:
    LibraryItem(Library* ptrLib=nullptr, string ID="0000", string title="", string type="unknown")
        : ptrLib(ptrLib), ID(ID), title(title), borrowed(false), borrower(nullptr)
    {}
    virtual ~LibraryItem() = default;
    string getLibraryName() const;
    bool borrowItem(Person* borrower)
    {
        if(borrowed == false && borrower->getNBorrows() < borrower->getMaxBorrows())
        {
            borrowed = true;
            this->borrower = borrower;
            borrower->incrementNBorrows();
            cout << "Item borrowed\n";
            return true;
        }
        else
        {
            cout << "Return failed\n";
            return false;
        }
    }
    bool returnItem()
    {
        if(borrowed == true)
        {
            borrower->decrementNBorrows();

            borrowed = false;
            this->borrower = nullptr;
            cout << "Item returned\n";
            return true;
        }
        else
        {
            cout << "Return failed\n";
            return false;
        }
    }
    bool isBorrowed() const
    {
        return borrowed;
    }
    string getID() const
    {
        return ID;
    }
    string getTitle() const
    {
        return title;
    }

    virtual int getLoanPeriod() const = 0;
    virtual void display() const = 0;

};

class Book : public LibraryItem
{
    string author;
public:
    Book(Library* ptrLib=nullptr, string ID="0000", string title="", string author="default") 
        : LibraryItem(ptrLib, ID, title), author(author)
    {

    }
    virtual ~Book () = default;

    int getLoanPeriod() const override;
    
    void display() const override
    {
        cout << "BOOK INFO <" << ID << "|"
        << title << "|" << author << "|";
        borrowed ? cout << "borrowed" : cout << "unborrowed";
        borrowed ? cout << "|" << this->borrower->getName() << ">\n" : cout << "|unborrowed>\n";
    }
};

class Magazine : public LibraryItem
{
    string issueNo;
public:
    Magazine(Library* ptrLib=nullptr, string ID="0000", string title="title", string issueNo="default") 
        : LibraryItem(ptrLib, ID, title), issueNo(issueNo)
    {

    }
    virtual ~Magazine () = default;

    int getLoanPeriod() const override;
    
    void display() const override
    {
        cout << "MAGAZINE INFO <" << ID << "|"
        << title << "|" << issueNo << "|";
        borrowed ? cout << "borrowed" : cout << "unborrowed";
        borrowed ? cout << "|" << this->borrower->getName() << ">\n" : cout << "|unborrowed>\n";
    }
};

class DVD : public LibraryItem
{
    int length;
    string genre;
public:
    DVD(Library* ptrLib=nullptr, string ID="0000", string title="", int length=0, string genre="default") 
        : LibraryItem(ptrLib, ID, title), length(length), genre(genre)
    {

    }
    virtual ~DVD () = default;

    int getLoanPeriod() const override;
    
    void display() const override
    {
        cout << "DVD INFO <" << ID << "|"
        << title << "|" << length << "|" << genre << "|";
        borrowed ? cout << "borrowed" : cout << "unborrowed";
        borrowed ? cout << "|" << this->borrower->getName() << ">\n" : cout << "|unborrowed>\n";
    }
};

class Library
{
    string name;
    LibraryItem** items;  // array of LibraryItem pointers
    int size;
    int nItems;
    int loanPeriod[3] = {30, 20, 10};
public:
    Library(string name, int size)
        : name(name), size(size), nItems(0)
    {
        items = new LibraryItem*[size];
        for(int i = 0; i < size; i++)
        {
            items[i] = nullptr;
        }
    }
    virtual ~Library()
    { 
        for(int i = 0; i < nItems; i++)
        {
            delete items[i];
        }
        delete[] items;
    }
    string getName() const
    {
        return name;
    }
    bool addItem()
    {   
        // Book(Library* ptrLib=nullptr, string ID=0, string title="") 
        // : ptrLib(ptrLib), ID(ID), title(title), borrowed(false), borrowerName("unborrowed")
        if(nItems < size)
        {
            int idx;
            cout << "1. Book\n2. Magazine\n3. DVD\nItem to create: ";
            cin >> idx;
            switch(idx)
            {
                case 1:
                {
                    LibraryItem* item = new Book(this, "0001", "Harry Potter", "JKRowling");
                    items[nItems++] = item;
                    break;   
                }
                case 2:
                {
                    LibraryItem* item = new Magazine(this, "0002", "MAG", "012A");
                    items[nItems++] = item;
                    break;   
                }
                case 3:
                {
                    LibraryItem* item = new DVD(this, "0003", "Shrek", 120, "Animation");
                    items[nItems++] = item;
                    break;     
                }
                default : return false;
            }

            return true;
        }
        return false;
    }
    void displayAllItems() const
    {
        for(int i = 0; i < nItems; i++)
        {
            items[i]->display();
        }
    }
    int getLoanPeriod(int idx) const
    {
        return loanPeriod[idx];
    }
    bool borrowById(string id, Person* borrower)
    {
        for(int i = 0; i < nItems; i++)
        {
            if(items[i]->getID() == id)
            {
                bool res = items[i]->borrowItem(borrower);
                return res ? true : false;
            }
        }
        return false;
    }
    bool returnById(string id)
    {
        for(int i = 0; i < nItems; i++)
        {
            if(items[i]->getID() == id)
            {
                bool res = items[i]->returnItem();
                return res ? true : false;
            }
        }
        return false;
    }
    LibraryItem* findById(string id)
    {
        for(int i = 0; i < nItems; i++)
        {
            if(items[i]->getID() == id)
            {
                return items[i];
            }
        }
        return nullptr;
    }
    int countBorrowed() const
    {
        int count = 0;
        for(int i = 0; i < nItems; i++)
        {
            if(items[i]->isBorrowed())
            {
                count++;
            }
        }
        return count;
    }
    int countBooks()
    {
        int count = 0;
        for(int i = 0; i < nItems; i++)
        {
            if(dynamic_cast<Book*>(items[i]) != nullptr)
            {
                count++;
            }
        }
        return count;
    }
};

string LibraryItem::getLibraryName() const
{
    return ptrLib ? ptrLib->getName() : "no library\n";
}
int Book::getLoanPeriod() const
{
    return ptrLib->getLoanPeriod(0);
}
int Magazine::getLoanPeriod() const
{
    return ptrLib->getLoanPeriod(1);
}
int DVD::getLoanPeriod() const
{
    return ptrLib->getLoanPeriod(2);
}


int main()
{
    Person* std = new Student("tawfiq");
    Person* fac = new Faculty("KH");


    Library lib("londu library", 10);
    lib.addItem();
    lib.addItem();
    lib.addItem();
    lib.addItem();
    lib.borrowById("0002", std);
    lib.borrowById("0001", fac);
    lib.returnById("0002");


    lib.displayAllItems();

    cout << lib.countBooks() << endl;

    delete std; delete fac;
    
    return 0;
}