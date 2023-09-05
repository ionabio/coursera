// Convert this program to C++ 
// change to C++ io
// change to one line comments  
// change defines of constants to const
// change array to vector<> 
// inline any short function 

//It was easy to just rename sum to a regular sum, I was experimenting with templates to make it also generic which was covered
//Iterating over vector could use foreach, but I didn't use it since at this point of lecture it is not talked

#include <iostream>
#include <vector>

using namespace std;
const int N = 40;


// We don't need to pass number of vector elements, since we can enquire it using size() method
template<class T> 
inline void sum(T& p, vector<T> d)
{
    p = 0;
    for (int i = 0; i < d.size(); ++i)
        p += d[i];
}

int main()
{
    int i;
    int accum = 0;

    // To keep it closer to original implementation
    // vector is resized to N to initialise its members, 
    // and I am not using push_back as a result, since we have N members already

    vector<int> data(N);
    for (i = 0; i < N; ++i)
        data[i] = i;
    
    sum<int>(accum, data);
    cout << "sum is: " << accum << endl;
    return 0;
}