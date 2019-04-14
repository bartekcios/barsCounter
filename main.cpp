#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair{
    double lenght;
    string desc;
};

struct Bar
{
    Bar(double defaultLength):leftLength(defaultLength),
        defaultLength(defaultLength){}
    Bar() = delete;

    bool TryAdd(Pair nextBar, bool first = false)
    {
        if(first)
        {
            barsNumber = floor(nextBar.lenght/defaultLength);
            parts.push_back(nextBar);
            leftLength -= (nextBar.lenght - (barsNumber * defaultLength));
            barsNumber++;
            return true;
        }
        if(leftLength >= nextBar.lenght)
        {
            parts.push_back(nextBar);
            leftLength -= nextBar.lenght;
            return true;
        }
        else
        {
            return false;
        }
    }

    int Show(const double oneLength)
    {
        double usedLength = 0.0;
        cout << "\tlistew w zestawie: " << barsNumber << endl;
        for(auto i:parts)
        {
            usedLength += i.lenght;
            cout << "\t\t" << i.lenght << "\t" << i.desc << endl;
        }
        double fullLength = oneLength;
        while(fullLength < usedLength)
        {
            fullLength += oneLength;
        }
        cout << "\tresztek w zestawie: " << fullLength - usedLength << endl;

        return barsNumber;
    }

    vector<Pair> parts;
    double leftLength;
    double defaultLength;
    int barsNumber = 0;
};

int count(vector<Pair>& v, double oneLength)
{
    double sum = accumulate(v.begin(), v.end(), 0.0, [](double sum, const Pair& pair){return sum + pair.lenght;});
    vector<Bar> bars;
    sort(v.begin(), v.end(), [](const Pair& a, const Pair& b) -> bool {return a.lenght > b.lenght;});
    int currentBar = -1;
    while(v.size())
    {
        // create new bar
        bars.push_back(Bar(oneLength));
        currentBar++;
        int currentVIndex = 0;
        bars[currentBar].TryAdd(v[currentVIndex], true);
        v.erase(v.begin());
        bool found = true;
        while(found)
        {
            found = false;
            for(unsigned int i=0;i<v.size();++i)
            {
                if(v[i].lenght>oneLength)
                {
                    continue;
                }
                if(bars[currentBar].TryAdd(v[i]))
                {
                    found = true;
                    v.erase(v.begin()+i);
                }
            }
        }
    }

    int barsNumber = 0;
    for(unsigned int i=0;i<bars.size();i++)
    {
        cout << "paczka: " << i+1 << endl;
        barsNumber += bars[i].Show(oneLength);
    }
    cout << "niewykorzystanego materialu: " << (barsNumber*oneLength)-sum << endl;
    return barsNumber;
}

int main()
{
    vector<Pair> v = {
        {14.2,  "1" },
        {51.3,  "2" },
        {59.5,  "3" },
        {70,    "4" },
        {35.6,  "5" },
        {76.1,  "6" },
        {14.4,  "7" },
        {21.1,  "8" },
        {220.3, "9" },
        {79,    "10" },
        {13.3,  "11" },
        {115.6, "12" },
        {25.6,  "13" },
        {288.4, "15" },
        {330.4, "16" },
        {22.6,  "18" },
        {200.1, "24" },
        {459.9, "25" },
        {64.8,  "26" },
        {17.6,  "27" },
        {17.1,  "29" },
        {348.6, "30" },
        {344.3, "31" },
    };
    const double defaultLen = 250.0;
    cout << "Dlugosc jednej listwy: " << defaultLen << endl;
    cout << "lacznie potrzebnych listew: " << count(v, defaultLen) << endl;
}
