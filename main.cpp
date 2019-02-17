#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Bar
{
public:
    Bar(double defaultLength):leftLength(defaultLength),
        defaultLength(defaultLength){}
    Bar() = delete;

    bool TryAdd(double nextBar, bool first = false)
    {
        if(first)
        {
            barsNumber = floor(nextBar/defaultLength);
            parts.push_back(nextBar);
            leftLength -= (nextBar - (barsNumber * defaultLength));
            barsNumber++;
            return true;
        }
        if(leftLength >= nextBar)
        {
            parts.push_back(nextBar);
            leftLength -= nextBar;
            return true;
        }
        else
        {
            return false;
        }
    }

    int Show()
    {
        cout << "listew w zestawie: " << barsNumber << endl;
        for(auto i:parts)
        {
            cout << "   " << i << endl;
        }
        return barsNumber;
    }

    vector<double> parts;
    double leftLength;
    double defaultLength;
    int barsNumber = 0;
};

int count(vector<double>& v, double oneLength)
{
    vector<Bar> bars;
    sort(v.begin(), v.end(), std::greater<double>());
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
                if(v[i]>oneLength)
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
        barsNumber += bars[i].Show();
    }
    return barsNumber;
}

int main()
{
    vector<double> v = {
        //salon
        3.49,
        0.67,
        4.69,
        3.47,
        2.01,
        0.23,
        1.16,
        0.15,
        0.88,
        2.21,
        0.21,
        0.14,
        0.81,
        0.37,
        0.7 ,
        0.62,
        0.54,
        0.15,
        // sypialnia1
        2.91,
        3.35,
        3.35,
        1.87,
        //sypialnia2
        3.35,
        0.26,
        2.73,
        2.91
    };
    const double defaultLen = 2.5;
    cout << "Dlugosc jednej listwy: " << defaultLen << endl;
    cout << "lacznie potrzebnych listew: " << count(v, defaultLen) << endl;
}
