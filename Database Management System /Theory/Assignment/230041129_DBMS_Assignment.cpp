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
    set<set<char>> shortestCKs;

    /*reads from input.txt and stores the values in appropriate attributes*/
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
    void write() const
    {
        ofstream output("output.txt", ios::out);
        output << "There are a total of " << CKs.size() << " possible CK's. They are given below:\n";
        int i = 1;
        for(const auto& ck : CKs)
        {
            output << i++ << ". " << set_str(ck) << endl; 
        }
        i = 1;
        output << "The shortest CK(s) are:\n";
        for(const auto& sck : shortestCKs)
        {
            output << i++ << ". " << set_str(sck) << endl; 
        }
        output.close();
    }
    // function that returns the minimum size of the CKs in the current CK set
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
    /* takes a set of attributes of as input and returns a vector of every combination of proper subsets within the input set */
    vector<set<char>> getAllCombinations(const set<char>& s)
    {
        vector<char> elems(s.begin(), s.end());
        int n = elems.size();
        int total = 1 << n;
        
        vector<set<char>> result;
        
        for (int mask = 0; mask < total; mask++)
        {
            set<char> subset;
            
            for (int i = 0; i < n; i++)
            {
                if (mask & (1 << i))
                {
                    subset.insert(elems[i]);
                }
            }

            result.push_back(subset);
        }

        return result;
    }
    /* this function acts as the initial iteration for the computation, in the sense that it finds the first CK for the given set and calls the recursive version of it (computeCK_rec()) that recurisely checks for full closure for every combination of the current iteration's CK and adds them to the CK set until all possible CKs are visited */
    void computeCK()
    {
        set<char> sk, determinedAttr;
        for (char attr : attrSet)
        {
            sk.insert(attr);
            determinedAttr.insert(attr);
        }

        for (auto fd : FDs)
        {
            set<char> indAttr = fd.first;
            char depAttr = fd.second;
            if(inSet(sk, indAttr))
            {
                for(char attr : sk)
                {
                    if(attr == depAttr)
                    {
                        // cout << "Removing " << attr << " from the current sk. ";
                        sk.erase(attr);
                        // cout << "curr sk: " << set_str(sk) << endl;
                        break;
                    }
                }

            }
        }


        vector<set<char>> allPSS = getAllCombinations(sk);
        for(const auto& s: allPSS)
        {
            if(isSK(s))
            {
                this->CKs.insert(s);
                computeCK_rec(s);
            }
        }

        set<char> s;
        for(char attr : sk)
        {
            s.insert(attr);
            PA.insert(attr);
        }
        CKs.insert(s);

        // cout << set_str(sk) << " added as a CK\n";

        auto PAnDA = PAintersectDA();

        // cout << "PAnDA: {";
        // for(char attr : PAnDA)
        // {
        //     cout << attr  << ", ";
        // }
        // cout << "\b\b}\n";

        for(char ckAttr : sk)
        {
            // ckAttr is replaceable
            if(find(PAnDA.begin(), PAnDA.end(), ckAttr) != PAnDA.end())
            {
                set<char> newCK(sk);
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
    /* checks for full closure of the current CK and its proper subsets and calls itself for every replaceable attribute for the current CK */
    void computeCK_rec(const set<char>& currCK)
    {
        // cout << "CURRENT Key: " << set_str(currCK) << endl;
        
        
        if(checkedSets.find(currCK) != checkedSets.end())
        {
            for(char ckAttr : currCK)
            {
                cout << ckAttr;
            }
            // cout << " already checked , returning\n";
            return;
        }
        else
        {
            checkedSets.insert(currCK);
        }

        vector<set<char>> allPSS = getAllCombinations(currCK);
        for(const auto& s: allPSS)
        {
            if(isSK(s))
            {
                this->CKs.insert(s);
                // cout << set_str(s) << "added as a ck\n";
            }
        }




        if(CKs.find(currCK) != CKs.end())
        {
            // cout << set_str(currCK) << " already exists in the CK set\n";
            return;
        }

        if(currCK.size() <= CKsize())
        {
            CKs.insert(currCK);
            // cout << set_str(currCK) << " added as a CK\n";
        }

        for (auto fd : FDs)
        {
            set<char> indAttr = fd.first;
            char depAttr = fd.second;
            if(inSet(currCK, indAttr))
            {
                for(char attr : currCK)
                {
                    if(attr == depAttr)
                    {
                        // cout << "[REC FUNC] Removing " << attr << " from the current ck\n";
                        set<char> newCK(currCK);
                        newCK.erase(attr);

                        // cout << "curr ck: " << set_str(newCK) << endl;
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

        // cout << "PAnDA: {";
        // for(char attr : PAnDA)
        // {
        //     cout << attr  << ", ";
        // }
        // cout << "\b\b}\n";

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
    /* function that stores the shortest candidate key(s) in the set shortestCKs once all the possible CKs are identified*/
    void setShortestCK()
    {
        int shortest_length = INT_MAX;
        for(const auto& ck : CKs)
        {
            if(ck.size() < shortest_length)
            {
                shortest_length = ck.size();
            }
        }
        for(const auto& ck : CKs)
        {
            if(ck.size() == shortest_length)
            {
                shortestCKs.insert(ck);
            }
        }
    }
    /* helper function that takes a detrmined attribute and returns the set of attributes that determines it; used to replace attributes from the current iteration and get the attributes for the next iteration */
    set<char> findDeterminer(char attr) const
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
    /* helper function that returns the result of PA intersection DA as a set of characters; used to find which attributes are replaceable in the current CK */
    set<char> PAintersectDA() const
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
    /* helper function that checks for full closure of the input set of attributes */
    bool isSK(const set<char>& attrs) const
    {
        if(attrs.empty())
            return false;

        // cout << "Checking " << set_str(attrs) << " for full closure \n"; 

        set<char> closure;
        for(char attr : attrs)
        {
            closure.insert(attr);
        }

        bool newAdds = true;

        while(newAdds)
        {
            newAdds = false;
            for(const pair<set<char>, char>& p : FDs)
            {
                if(inSet(closure, p.first))
                {
                    auto [it, inserted] = closure.insert(p.second);
                    if (inserted)
                        newAdds = true;
                }
            }
        }

        
        // cout << set_str(attrs);

        if (closure.size() == attrSet.size())
        {
            // cout << " is an SK\n";
            return true;
        }
        else
        {
            // cout << " is NOT an SK\n";
            return false;
        }
        

    }
    /* helper function that checks if every element of the targetSet is present within the destSet */
    bool inSet(const set<char>& destSet, const set<char>& targetSet) const
    {
        for (char c : targetSet)
        {
            if (destSet.find(c) == destSet.end())
                return false;
        }
        return true;
    }
    /* helper function that takes a set of characters, s, and returns the formatted string representation of the set */
    string set_str(const set<char>& s) const
    {
        int n = s.size();

        if(n == 0)
            return "{}";

        int i = 0;
        stringstream ss;
        ss << "{";
        for(char ch : s)
        {
            ss << ch;
            if(i++ != n-1)
                ss << ", ";
        }
        ss << "}";
        return ss.str();
    }

public : 
    CKComputer()
    {
        read();
        computeCK();
        setShortestCK();
        write();
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
    void displayShortestCK() const
    {
        cout << "Shortest Candidate Keys: {";
        for (auto ck : shortestCKs)
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
    c.displayShortestCK();
    

    return 0;
}