#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

class MenuItem
{
private:

    int id;
    string name;
    double price;
public:

    class readingError 
    {
        string msg;
    public:
        readingError(string msg) : msg(msg) {}
        string what() const 
        {
            return msg;
        }
    };
    class writingError 
    {
        string msg;
    public:
        writingError(string msg) : msg(msg) {}
        string what() const 
        {
            return msg;
        }
    };

    MenuItem(int id=0, string name="def", double price=0.0) :
        id(id), name(name), price(price) {}

    int getID() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    double getPrice() const
    {
        return price;
    }
    
    string serialize() const
    {
        stringstream ss;
        ss << id << "|" << name << "|" << price << endl;

        return ss.str();
    }
    static bool deserialize(const string& line, MenuItem& obj)
    {
        string _id, _name, _price; 
        stringstream ss(line);

        if(!getline(ss, _id, '|'))
        {
            return false;
        }
        if(!getline(ss, _name, '|'))
        {
            return false;
        }
        if(!getline(ss, _price, '|'))
        {
            return false;
        }   

        // cout << "_ID: " << _id << endl;
        // cout << "_Name: " << _name << endl;
        // cout << "_Price: " << _price << endl;
        
        try
        {
            size_t pos = 0;
            obj.id = stoi(_id, &pos);
            if(pos != _id.size())
                throw readingError("Error in reading ID");

            obj.name = _name; 

            pos = 0;
            obj.price = stod(_price, &pos);
            if(pos != _price.size())
                throw readingError("Error in reading price");
                
        }
        catch(MenuItem::readingError e)
        {
            cerr << e.what() << '\n';
            return false;
        }

        return true;
    }

    // the ostream class can take both cout and ofstream as input
    // so depending on the parameter passed, this function prints the row
    // in either the console or in a file
    void printRow(ostream &os) const
    {
        os << "|" << setw(5) << left << id
            << "|" << setw(15) << left << name
            << "|" << setw(8) << left << fixed << setprecision(2) << price << "|" << endl;
    }
    static void printHeader(ostream &os)
    {
        os << string(42, '-') << endl;
        os << "|" << setw(5) << left << "saleID"
           << "|" << setw(15) << left << "Item"
           << "|" << setw(8) << left << "Units"
           << "|" << setw(8) << "Total" << "|" << endl;
        os << string(42, '-') << endl;
    }
    
};

bool recordSale(const string& salesFile, int saleID, const MenuItem& item, int units)     
{
    ofstream file(salesFile, ios::app);
    if(file.is_open())
    {
        file << "|" << setw(6) << left << saleID
            << "|" << setw(15) << left << item.getName()
            << "|" << setw(8) << left << units
            << "|" << setw(8) << left << fixed << setprecision(2) << item.getPrice() * units << "|" << endl;
        file.close();
    }
    else
    {
        throw MenuItem::writingError("Sales.txt opening for recording failed\n");
        return false;
    }
    return true;
}

int loadMenu(const string &menuFile, MenuItem itemArr[], int maxCount)
{
    ifstream file(menuFile, ios::in);
    int count = 0;

    if(file.is_open())
    {
        string line;
        for(int i = 0; i < maxCount && getline(file, line); i++) 
        {
            MenuItem::deserialize(line, itemArr[i]);
            count++;
        }   
        file.close();
    }
    else
    {
        throw MenuItem::readingError("Error loading menu\n");
    }
    return count;
}



int main()
{
    MenuItem dim(1, "Dim", 5.0);
    MenuItem paratha(2, "Paratha", 10);
    MenuItem daal(3, "Daal", 10);
    MenuItem bhaat(4, "Bhaat", 10.0);
    MenuItem itemArr[] = {dim, paratha, dim, bhaat};

    try
    {
        ofstream menuFile("menu.txt", ios::out);
        if(menuFile.is_open())
        {
            for(auto item : itemArr)
            {
                menuFile << item.serialize();
            }
        }
        
    }
    catch(...)
    {
        cerr << "Error in creating menu\n";
    }

    MenuItem itemArr2[10];

    try
    {
        loadMenu("menu.txt", itemArr2, 10);
    }
    catch(const MenuItem::readingError& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    for(int i = 0; i < 4; i++)
    {
        cout << "ID: " << itemArr2[i].getID() << endl;
        cout << "Name: " << itemArr2[i].getName() << endl;
        cout << "Price: " << itemArr2[i].getPrice() << endl;
    }
    
    // ios::app for appending
    // ios::out for writing
    ofstream sales("sales.txt", ios::out);
    MenuItem::printHeader(cout);
    sales.close();
    
    recordSale("sales.txt", 1, dim, 1);
    recordSale("sales.txt", 2, paratha, 2);
    recordSale("sales.txt", 3, daal, 1);

    




    return 0;
}