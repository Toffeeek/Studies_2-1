#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
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
        ss << id << "|" << name << "|" << price;

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
        os << "|" << setw(10) << left << id
            << "|" << setw(20) << left << name
            << "|" << setw(10) << left << fixed << setprecision(2) << price << "|" << endl;
    }
    static void printHeader(ostream &os)
    {
        os << string(44, '-') << endl;
        os << "|" << setw(10) << left << "saleID"
           << "|" << setw(20) << left << "Item"
           << "|" << setw(10) << left << "Price" << "|" << endl;
        os << string(44, '-') << endl;
    }
    
};


class SaleRecord
{
    int saleId;
    int menuId;
    int units;
    double total;
public:
    class ReadingError
    {
        string msg;
    public:
        ReadingError(string msg) : msg(msg) {}
        string what() const
        {
            return msg;
        }
    };

    SaleRecord(int sid=-1, int mid=-1, int u=0, double t=0) 
        : saleId(sid), menuId(mid), units(u), total(t) {}
    string serialize() const
    {
        stringstream ss;
        ss << saleId << "|" << menuId << "|" << units << "|" << total;
        return ss.str();
    }
    static bool deserialize(const string& line, SaleRecord& obj)
    {
        string _sid, _mid, _units, _total; 
        stringstream ss(line);

        if(!getline(ss, _sid, '|'))
        {
            return false;
        }
        if(!getline(ss, _mid, '|'))
        {
            return false;
        }
        if(!getline(ss, _units, '|'))
        {
            return false;
        }  
        if(!getline(ss, _total))
        {
            return false;
        }    

        // cout << "_ID: " << _id << endl;
        // cout << "_Name: " << _name << endl;
        // cout << "_Price: " << _price << endl;
        
        try
        {
            size_t pos = 0;
            obj.saleId = stoi(_sid, &pos);
            if(pos != _sid.size())
                throw ReadingError("Error in reading SID");

            pos = 0;
            obj.menuId = stoi(_mid, &pos);
            if(pos != _mid.size())
                throw ReadingError("Error in reading MID");

            pos = 0;
            obj.menuId = stoi(_mid, &pos);
            if(pos != _mid.size())
                throw ReadingError("Error in reading MID");

            
            pos = 0;
            obj.units = stoi(_units, &pos);
            if(pos != _units.size())
                throw ReadingError("Error in reading units");

            pos = 0;
            obj.total = stod(_total, &pos);
            if(pos != _total.size())
                throw ReadingError("Error in reading total");
                            
        }
        catch(SaleRecord::ReadingError& e)
        {
            cerr << e.what() << '\n';
            return false;
        }

        return true;
    }
    static void printHeader(ostream &os)
    {
        os << string(45, '-') << endl;
        os << "|" << setw(10) << left << "saleID"
           << "|" << setw(10) << left << "menuID"
           << "|" << setw(10) << left << "Units"
           << "|" << setw(10) << left << "Total" << "|" << endl;
        os << string(45, '-') << endl;
    }
    void printRow(ostream &os) const
    {
        os << "|" << setw(10) << left << saleId
           << "|" << setw(10) << left << menuId
           << "|" << setw(10) << left << units
           << "|" << setw(10) << left << fixed << setprecision(2) << total << "|" << endl;
    }
};

template<class T, int MAX>
class FileRepository
{
    T items[MAX];
    int currSize;
    string fileName;
public:
    class ReadingError
    {
        string msg;
    public:
        ReadingError(string msg) : msg(msg) {}
        string what() const
        {
            return msg;
        }
    };

    FileRepository(const string& fileName) 
        : fileName(fileName), currSize(0) {}
    bool add(const T& item)
    {
        if(currSize < MAX)
            items[currSize++] = item;
        else
            return false;
        return true; 
    }
    int load()
    {
        ifstream file(fileName, ios::in);
        int itemsRead = 0;
        if(file.is_open())
        {
            string line;
            while(getline(file, line))
            {
                T obj;
                T::deserialize(line, obj);
                add(obj);
                itemsRead++;
            }
        }
        else
        {
            throw ReadingError("Could not open file for reading");
        }
        return itemsRead;
    }
    void printAll(ostream& os)
    {
        T::printHeader(os);
        for(int i = 0; i < currSize; i++)
        {
            items[i].printRow(os);
        }
        os << string(45, '-') << endl;
    }
    int count() const
    {
        return currSize;
    }
};

int main()
{
    FileRepository<MenuItem, 100> menuRepo("menu.txt");

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
                menuFile << item.serialize() << endl;
            }
        }
        
    }
    catch(...)
    {
        cerr << "Error in creating menu\n";
    }

    menuRepo.load();
    menuRepo.printAll(cout);

    FileRepository<SaleRecord, 100> salesRepo("sales.txt");

    SaleRecord menu_dim(1, 2, 3, 5.0);
    SaleRecord menu_paratha(2, 4, 3, 10.5);
    SaleRecord menu_daal(3, 10, 3, 15.5);
    SaleRecord menu_bhaat(4, 1, 1, 10.0);
    SaleRecord menu_itemArr[] = {menu_dim, menu_paratha, menu_dim, menu_bhaat};

    try
    {
        ofstream menuFile("sales.txt", ios::out);
        if(menuFile.is_open())
        {
            for(auto item : menu_itemArr)
            {
                menuFile << item.serialize() << endl;
            }
        }
        
    }
    catch(...)
    {
        cerr << "Error in creating menu\n";
    }

    salesRepo.load();
    salesRepo.printAll(cout);


    return 0;

}