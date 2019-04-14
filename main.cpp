#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef double length_t;

struct Pair{
    length_t lenght;
    string desc;
};

struct Bar
{
    Bar( const length_t defaultLength ):m_leftLength( defaultLength ),
        m_defaultLength( defaultLength ){}
    Bar() = delete;

    bool TryAdd(const Pair& nextBar, const bool first = false)
    {
        if( first )
        {
            m_barsNumber = floor( nextBar.lenght/m_defaultLength );
            m_parts.push_back( nextBar );
            m_leftLength -= ( nextBar.lenght - ( m_barsNumber * m_defaultLength ) );
            m_barsNumber++;
            return true;
        }
        if( m_leftLength >= nextBar.lenght )
        {
            m_parts.push_back( nextBar );
            m_leftLength -= nextBar.lenght;
            return true;
        }
        else
        {
            return false;
        }
    }

    int Show( const length_t oneLength )
    {
        length_t usedLength = 0.0;
        cout << "\tlistew w zestawie: " << m_barsNumber << endl;
        for( const auto i:m_parts )
        {
            usedLength += i.lenght;
            cout << "\t\t" << i.lenght << "\t" << i.desc << endl;
        }
        length_t fullLength = oneLength;
        while( fullLength < usedLength )
        {
            fullLength += oneLength;
        }
        cout << "\tresztek w zestawie: " << fullLength - usedLength << endl;

        return m_barsNumber;
    }

    vector<Pair> m_parts;
    length_t m_leftLength;
    const length_t m_defaultLength;
    int m_barsNumber = 0;
};

int count( vector<Pair>& v, length_t oneLength )
{
    const length_t sum = accumulate( v.begin(), v.end(), 0.0, []( length_t sum, const Pair& pair ){ return sum + pair.lenght; } );
    vector<Bar> bars;
    sort( v.begin(), v.end(), []( const Pair& a, const Pair& b ) -> bool { return a.lenght > b.lenght; } );
    int currentBar = -1;
    while( v.size() )
    {
        // create new bar
        bars.push_back( Bar( oneLength ) );
        currentBar++;
        int currentVIndex = 0;
        bars[currentBar].TryAdd( v[currentVIndex], true );
        v.erase(v.begin());
        bool found = true;
        while( found )
        {
            found = false;
            for( unsigned int i=0;i<v.size();++i )
            {
                if( v[i].lenght>oneLength )
                {
                    continue;
                }
                if( bars[currentBar].TryAdd( v[i] ) )
                {
                    found = true;
                    v.erase( v.begin()+i );
                }
            }
        }
    }

    int barsNumber = 0;
    for( unsigned int i=0;i<bars.size();i++ )
    {
        cout << "paczka: " << i+1 << endl;
        barsNumber += bars[i].Show( oneLength );
    }
    cout << "niewykorzystanego materialu: " << ( barsNumber*oneLength )-sum << endl;
    return barsNumber;
}

int main()
{
    vector<Pair> v = {
        { 14.2,  "1" },
        { 51.3,  "2" },
        { 59.5,  "3" },
        { 70,    "4" },
        { 35.6,  "5" },
        { 76.1,  "6" },
        { 14.4,  "7" },
        { 21.1,  "8" },
        { 220.3, "9" },
        { 79,    "10" },
        { 13.3,  "11" },
        { 115.6, "12" },
        { 25.6,  "13" },
        { 288.4, "15" },
        { 330.4, "16" },
        { 22.6,  "18" },
        { 200.1, "24" },
        { 459.9, "25" },
        { 64.8,  "26" },
        { 17.6,  "27" },
        { 17.1,  "29" },
        { 348.6, "30" },
        { 344.3, "31" },
    };
    const length_t defaultLen = 250.0;
    cout << "Dlugosc jednej listwy: " << defaultLen << endl;
    cout << "lacznie potrzebnych listew: " << count( v, defaultLen ) << endl;
}
