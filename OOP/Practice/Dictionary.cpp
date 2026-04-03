#include <iostream>
using namespace std;

class element
{
private:
    char key;
    int count;

public:
    // Constructors
    element()
    {
        key = '\0';
        count = 0;
    }

    element(char k, int c)
    {
        key = k;
        count = c;
    }

    // Getters
    char getKey() const
    {
        return key;
    }

    int getCount() const
    {
        return count;
    }

    // Setters
    void setKey(char k)
    {
        key = k;
    }

    void setCount(int c)
    {
        count = c;
    }
};

class dictionary
{
private:
    element *arr; // dynamic array of element objects
    int size;     // current number of elements
    int capacity; // maximum capacity

    int findIndex(char key) const
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getKey() == key)
                return i;
        }
        return -1;
    }

public:
    // Constructor
    dictionary(int cap = 100)
    {
        capacity = cap;
        size = 0;
        arr = new element[capacity];
    }

    // Destructor
    ~dictionary()
    {
        delete[] arr;
    }

    // Copy constructor
    dictionary(const dictionary &other)
    {
        capacity = other.capacity;
        size = other.size;
        arr = new element[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    // Copy assignment operator
    dictionary &operator=(const dictionary &other)
    {
        if (this != &other)
        {
            delete[] arr;
            capacity = other.capacity;
            size = other.size;
            arr = new element[capacity];
            for (int i = 0; i < size; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    // Check if key exists
    bool hasElement(char key)
    {
        return findIndex(key) != -1;
    }

    // Add using element object
    bool addElement(element elm)
    {
        if (hasElement(elm.getKey()))
            return false;

        if (size == capacity)
            return false;

        arr[size] = elm;
        size++;
        return true;
    }

    // Add using key and count
    bool addElement(char key, int count)
    {
        if (hasElement(key))
            return false;

        if (size == capacity)
            return false;

        arr[size] = element(key, count);
        size++;
        return true;
    }

    // Remove using element object
    bool removeElement(element elm)
    {
        int idx = findIndex(elm.getKey());
        if (idx == -1)
            return false;

        for (int i = idx; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;
        return true;
    }

    // Remove using key
    bool removeElement(char key)
    {
        int idx = findIndex(key);
        if (idx == -1)
            return false;

        for (int i = idx; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;
        return true;
    }

    // Increase count
    bool increaseCount(char key)
    {
        int idx = findIndex(key);
        if (idx == -1)
            return false;

        arr[idx].setCount(arr[idx].getCount() + 1);
        return true;
    }

    // Decrease count
    bool decreaseCount(char key)
    {
        int idx = findIndex(key);
        if (idx == -1)
            return false;

        int newCount = arr[idx].getCount() - 1;

        if (newCount <= 0)
        {
            removeElement(key);
        }
        else
        {
            arr[idx].setCount(newCount);
        }
        return true;
    }

    // Print all elements
    void printElements()
    {
        cout << "Existing elements:\n";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i].getKey() << " : " << arr[i].getCount() << endl;
        }
    }
};

class Test
{
public:
    static int foo() {cout << "hi\n"; return 0;};
};

int main()
{

    Test t;
    t.foo();
    Test::foo();

    // char addingList[] = "ABACB";
    // char deleteList[] = "BCCGG";

    // dictionary dict;

    // for (int i = 0; i < 5; i++)
    // {
    //     if (!dict.addElement(addingList[i], 1))
    //         dict.increaseCount(addingList[i]);
    // }

    // for (int i = 0; i < 5; i++)
    // {
    //     dict.decreaseCount(deleteList[i]);
    // }

    // dict.printElements();

    return 0;
}