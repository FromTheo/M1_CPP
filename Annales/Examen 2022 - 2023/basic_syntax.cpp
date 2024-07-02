#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std; 

int main()
{
    vector<int> numbers(100); 
    iota(numbers.begin(), numbers.end(), 1); 
    vector<double> numbers_transformed(100); 
    transform(numbers.begin(), numbers.end(), numbers_transformed.begin(), [](int& i)
    {
        return 1/(double)(i*i); 
    }); 
    for(int i = 0; i<100; ++i)
    {
        cout << numbers[i] << "\t" << numbers_transformed[i] << "\n"; 
    }   
    cout << accumulate(numbers_transformed.begin(), numbers_transformed.end(), 0.0, [](double acc, const double &d)
    {
        return acc+d;
    }) << "\n"; 
    /* Output : 
    1	1
    2	0.25
    3	0.111111
    4	0.0625
    5	0.04

    ... 

    95	0.000110803
    96	0.000108507
    97	0.000106281
    98	0.000104123
    99	0.00010203
    100	0.0001
    1.63498 */
    return 0; 
}