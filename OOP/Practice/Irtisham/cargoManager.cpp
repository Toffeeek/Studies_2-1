#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <exception>
using namespace std;


enum SecurityLevels
{
    low,
    high,
    topsecret,
    unknown,
};

SecurityLevels strToSecurityLevel(const string& str)
{
    if(str == "low")                 return low;
    else if(str == "high")           return high;
    else if(str == "topsecret")      return topsecret;
    else                             return unknown;
}
string SecurityLevelToStr(SecurityLevels lvl)
{
    if(lvl == low)                 return "low";
    else if(lvl == high)           return "high";
    else if(lvl == topsecret)      return "topsecret";
    else                             return "unknown";
}

class SpaceStationException : public exception
{
public:
    SpaceStationException() {}
    virtual const char *what() const noexcept override = 0;
};

class FileCriticalException : public SpaceStationException
{
    string msg;

public:
    FileCriticalException(string msg) : msg(msg) {}
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class DataFormatException : public SpaceStationException
{
    string msg;
    string line;

public:
    DataFormatException(string msg, string line) : msg(msg), line(line) {}
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
    string getline() const
    {
        return line;
    }
};

class SecurityBreachException : public SpaceStationException
{
    string msg;

public:
    SecurityBreachException(string msg) : msg(msg) {}
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class CargoItem
{
    int crateID;
    string desc;
    double weight;
    SecurityLevels sLevel;


public:
    CargoItem(int cid=-1, const string &d="default", double w=0.0, SecurityLevels securityLevel=unknown)
        : crateID(cid), desc(d), weight(w), sLevel(securityLevel)
    {
    }
    string serialize() const
    {
        stringstream ss;
        ss << left << setw(10) << crateID << "|" 
        << left << setw(20) << desc
           << "|" << left << setw(15) << fixed << setprecision(2)
           << weight << "|" << left << setw(10) << SecurityLevelToStr(sLevel);
        return ss.str();
    }
    static CargoItem deserialize(const string &line)
    {
        stringstream ss(line);
        string _crateID, _desc, _weight, _securityLvl;
        if (!getline(ss, _crateID, '|'))
        {
            throw DataFormatException("missing pipe separation on ID", line);
        }
        if (!getline(ss, _desc, '|'))
        {
            throw DataFormatException("missing pipe separation on DESC", line);
        }
        if (!getline(ss, _weight, '|'))
        {
            throw DataFormatException("missing pipe separation on weight", line);
        }
        if (!getline(ss, _securityLvl))
        {
            throw DataFormatException("missing pipe separation on Security LVL", line);
        }

        while(!_crateID.empty() && _crateID[_crateID.size() - 1] == ' ')
        {
            _crateID.pop_back();
        }
        while(!_desc.empty() && _desc[_desc.size() - 1] == ' ')
        {
            _desc.pop_back();
        }
        while(!_weight.empty() && _weight[_weight.size() - 1] == ' ')
        {
            _weight.pop_back();
        }
        while(!_securityLvl.empty() && _securityLvl[_securityLvl.size() - 1] == ' ')
        {
            _securityLvl.pop_back();
        }
            

        size_t pos = 0;
        int cid = stoi(_crateID, &pos);
        if (pos != _crateID.size())
        {
            throw DataFormatException("Crate ID " + _crateID + " not an integer\n", line);
        }
        pos = 0;
        double weight = stod(_weight, &pos);
        if (pos != _weight.size())
        {
            throw DataFormatException("Weight " + _weight +  " not a double\n", line);
        }

        SecurityLevels lvl = strToSecurityLevel(_securityLvl);

        return CargoItem(cid, _desc, weight, lvl);
    }

    friend ostream &operator << (ostream &os, const CargoItem &item);

    static string getHeader()
    {
        stringstream ss;
        ss << left << setw(10) << "CrateID" << "|" 
        << left << setw(20) << "Description"
        << "|" << left << setw(15) << "Weight (kg)" 
        << "|" << left << setw(10) << "Security";
        return ss.str();
    }
    void display() const
    {
        cout << serialize() << endl;
    }
};

ostream &operator<<(ostream &os, const CargoItem &item)
{
    os << item.serialize();
    return os;
}
template <typename T, int CAPACITY>
class SecureVault
{
    int nItems;
    string filename;
    string logfile;
    T items[CAPACITY];

public:
    SecureVault()
    {
        nItems = 0;
        this->filename = "cargo-list.txt";
        this->logfile = "error_log.log";
        // ofstream file(filename, ios::out);
        // printHeader(file);
    }
    void printHeader(ostream& os) const
    {
        os << T::getHeader() << endl;
    }
    void save(const T &item) const
    {
        ifstream reader(filename, ios::in);
        if (reader.is_open() && !reader.fail())
        {
            int nLines = -1;
            string line;
            while (getline(reader, line))
            {
                nLines++;
            }
            if (nLines == CAPACITY)
            {
                throw FileCriticalException("Capacity Full\n");
                return;
            }
        }

        cout << "lines counted\n";

        ofstream appender(filename, ios::app);
        if (appender.is_open() && !appender.fail())
        {
            appender << item << endl;
        }
        else
        {
            throw FileCriticalException("Couldnt open " + filename + " for saving\n");
        }
    }
    void sync()
    {
        nItems = 0;
        ifstream reader(filename, ios::in);
        if (reader.is_open() && !reader.fail())
        {
            string line;
            // getline(reader, line);
            while (1)
            {
                try
                {
                    if (!getline(reader, line))
                    {
                        break;
                    }
                    items[nItems++] = T::deserialize(line);
                }
                catch (DataFormatException &e)
                {
                    cout << e.what();
                    ofstream logger(logfile, ios::app); 
                    if (logger.is_open() && !logger.fail())
                    {
                        logger << "DATAFORMATEXCEPTION >> " << e.getline() << endl;
                    }
                    else
                    {
                        throw FileCriticalException("Couldnt open " + logfile + " for logging\n");
                    }
                }
            }
        }
        else
        {
            throw FileCriticalException("Couldnt open " + filename + " for syncing\n");
        }
    }
    void display() const
    {
        printHeader(cout);
        for(int i = 0; i < nItems; i++)
        {
            cout << items[i] << endl;
        }
    }
};

int main()
{
    SecureVault<CargoItem, 3> vault;
    try
    {
        vault.save(CargoItem(5, "ABG", 80.5, topsecret));
        vault.sync(); 
        vault.display();  
    }
    catch(DataFormatException& e)
    {
        cerr << e.what();
    }
    catch(FileCriticalException& e)
    {
        cerr << e.what();
    }
    catch(SecurityBreachException& e)
    {
        cerr << e.what();
    }
    catch(...)
    {
        cerr << "something went wrong\n";
    }
    

    return 0;
}