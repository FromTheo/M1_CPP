#include <iostream>

#include "rejection.hpp"

using namespace std;

int main()
{
    ifstream file_in("source.txt"); 
    ofstream file_out("target.txt"); 
    PiecewiseConstant_function f; 
    file_in >> f; 
    file_out << f; 
    file_in.close(); 
    file_out.close(); 
    return 0; 
}