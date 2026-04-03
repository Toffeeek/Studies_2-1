#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

class CKComputer
{
private:
    set<char> attrSet;
    vector<pair<set<char>, char>> FDs;
    set<char> PA;
    set<char> DA;
    set<set<char>> CKs;
    set<set<char>> checkedSets;

    int CKsize() const
    {
        int minSize = INT_MAX;
        for(auto ck : CKs)
        {
            if(ck.size() < minSize)
            {
                minSize = ck.size();
            }
        }
        return minSize;
    }

    /*reads from input.txt and stores the values
    in appropriate attributes*/
    void read()
    {
        ifstream file("input.txt", ios::in);
        string firstLine;
        getline(file, firstLine);

        // forming the attribute set
        for (int i = 2; i < firstLine.size() - 1; i++)
        {
            if (firstLine[i] >= 'A' && firstLine[i] <= 'Z')
            {
                attrSet.insert(firstLine[i]);
            }
        }

        string secondLine;
        getline(file, secondLine);
        stringstream ss(secondLine);

        // reading the functional dependencies
        string _FD;
        while (getline(ss, _FD, ','))
        {
            string _indAttr, depAttr;
            stringstream ss(_FD);
            getline(ss, _indAttr, '-');
            char dummy;
            ss >> dummy;

            if (_indAttr[0] == ' ')
            {
                _indAttr.erase(_indAttr.begin());
            }

            set<char> indAttr;
            for(char attr : _indAttr)
            {
                indAttr.insert(attr);
            }

            getline(ss, depAttr);

            /*decomposing any FDs if possible*/ 
            while (depAttr.size() != 0)
            {
                char _depAttr = depAttr[0];
                depAttr.erase(depAttr.begin());
                FDs.push_back({indAttr, _depAttr});
                DA.insert(_depAttr);
            }
        }
    }

    void computeCK()
    {
        set<char> ck, determinedAttr;
        for (char attr : attrSet)
        {
            ck.insert(attr);
            determinedAttr.insert(attr);
        }

        for (auto fd : FDs)
        {
            set<char> indAttr = fd.first;
            char depAttr = fd.second;
            if(presentInCK(indAttr, ck))
            {
                for(char attr : ck)
                {
                    if(attr == depAttr)
                    {
                        cout << "Removing " << attr << " from the current ck\n";
                        ck.erase(attr);
                        break;
                    }
                }
            }
        }
        set<char> s;
        for(char attr : ck)
        {
            s.insert(attr);
            PA.insert(attr);
        }
        CKs.insert(s);

        for(char attr : s)
        {
            cout << attr;
        }
        cout << " added as a CK\n";

        auto PAnDA = PAintersectDA();

        cout << "PAnDA: {";
        for(char attr : PAnDA)
        {
            cout << attr  << ", ";
        }
        cout << "\b\b}\n";

        for(char ckAttr : ck)
        {
            // ckAttr is replaceable
            if(find(PAnDA.begin(), PAnDA.end(), ckAttr) != PAnDA.end())
            {
                set<char> newCK(ck);
                set<char> determiner = findDeterminer(ckAttr);
                newCK.erase(ckAttr);
                for(char determinerAttr : determiner)
                {
                    newCK.insert(determinerAttr);
                }
                computeCK_rec(newCK);
            }
        }


    }
    void computeCK_rec(const set<char>& currCK)
    {
        cout << "CURRENT Key: ";
        for(char ckAttr : currCK)
        {
            cout << ckAttr;
        }
        cout << endl;
        
        if(checkedSets.find(currCK) != checkedSets.end())
        {
            for(char ckAttr : currCK)
            {
                cout << ckAttr;
            }
            cout << " already checked , returning\n";
            return;
        }
        else
        {
            checkedSets.insert(currCK);
        }




        if(CKs.find(currCK) != CKs.end())
        {
            for(char ckAttr : currCK)
            {
                cout << ckAttr;
            }
            cout << " already exists in the CK set\n";
            return;
        }

        if(currCK.size() <= CKsize())
        {
            CKs.insert(currCK);
            for(char attr : currCK)
            {
                cout << attr;
            }
            cout << " added as a CK\n";
        }

        for (auto fd : FDs)
        {
            set<char> indAttr = fd.first;
            char depAttr = fd.second;
            if(presentInCK(indAttr, currCK))
            {
                for(char attr : currCK)
                {
                    if(attr == depAttr)
                    {
                        cout << "[REC FUNC] Removing " << attr << " from the current ck\n";
                        set<char> newCK(currCK);
                        newCK.erase(attr);
                        computeCK_rec(newCK);
                        break;
                    }
                }
            }
        }



        for(char ckAttr : currCK)
        {
            PA.insert(ckAttr);
        }

        auto PAnDA = PAintersectDA();

        cout << "PAnDA: {";
        for(char attr : PAnDA)
        {
            cout << attr  << ", ";
        }
        cout << "\b\b}\n";

        for(char ckAttr : currCK)
        {
            // ckAttr is replaceable
            if(find(PAnDA.begin(), PAnDA.end(), ckAttr) != PAnDA.end())
            {
                set<char> newCK(currCK);
                set<char> determiner = findDeterminer(ckAttr);
                newCK.erase(ckAttr);
                for(char determinerAttr : determiner)
                {
                    newCK.insert(determinerAttr);
                }
                computeCK_rec(newCK);
            }
        }
    }
    set<char> findDeterminer(char attr)
    {
        set<char> det;
        for(auto fd : FDs)
        {
            if(fd.second == attr)
            {
                return fd.first;
            }
        }
        return set<char>{};
    }
    bool presentInCK(const set<char>& indAttr, const set<char>& ck)
    {
        for (char attr : indAttr)
        {
            cout << attr;
        }
        cout << " ";

        for (char attr : indAttr)
        {
            if (ck.find(attr) == ck.end())
            {
                cout << "does not exist in the current CK\n";
                return false;
            }
        }

        cout << "exists in the current CK\n";
        return true;

        
    }
    set<char> PAintersectDA()
    {
        set<char> res;
        for(char attr : PA)
        {
            if(find(DA.begin(), DA.end(), attr) != DA.end())
            {
                res.insert(attr);
            }
        }
        return res;
    }

public : 
    CKComputer()
    {
        read();
        // presentInCK({"AB", 'C'}, "ABC");
        computeCK();
        
    }
    void displayAttributeSet() const
    {
        cout << "Attribute Set: {";
        for (char attr : attrSet)
        {
            cout << attr << ", ";
        }
        cout << "\b\b}\n";
    }
    void displayPA() const
    {
        cout << "Primary Attributes: {";
        for (char attr : PA)
        {
            cout << attr << ", ";
        }
        cout << "\b\b}\n";
    }
    void displayDA() const
    {
        cout << "Dependent Attributes: {";
        for (char attr : DA)
        {
            cout << attr << ", ";
        }
        cout << "\b\b}\n";
    }
    void displayFD() const
    {
        cout << "Displaying all FD's:\n";
        for (auto pair : FDs)
        {
            for(char attr : pair.first)
            {
                cout << attr;
            }
            cout << "->" << pair.second << endl;
        }
    }
    void displayCK() const
    {
        cout << "Candidate Keys: {";
        for (auto ck : CKs)
        {
            for(char attr : ck)
            {
                cout << attr;
            }
            cout << ", ";
        }
        cout << "\b\b}\n";
    }
};

int main()
{
    CKComputer c;
    c.displayAttributeSet();
    c.displayPA();
    c.displayDA();
    c.displayCK();
    

    return 0;
}