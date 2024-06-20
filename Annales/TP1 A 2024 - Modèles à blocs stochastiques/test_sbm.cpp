#include <iostream>
#include "sbm.hpp"

using namespace std; 

int main()
{
    MatInt A(3,3); 
    A << 0, 1, 1, 1, 0, 0, 1, 0, 0; 
    VecInt Z(3); 
    Z << 0, 0, 1;
    Graph simple_graph_directed(A, true, Z), simple_graph_undirected(A, false, Z); 
    ifstream fichier("graph.txt"); 
    Graph f_graph(fichier); 
    fichier.close(); 

    cout << "simple_graph_directed : " << "\n" << simple_graph_directed << "\n"; 
    /* Output : 
    simple_graph_directed : 
    3
    1
    0 1 1 
    1 0 0 
    1 0 0 
    0 0 1 */
    cout << "simple_graph_undirected : " << "\n" << simple_graph_undirected << "\n";
    /* Output : 
    simple_graph_undirected : 
    3
    0
    0 1 1 
    1 0 0 
    1 0 0 
    0 0 1 */ 
    cout << "f_graph : " << "\n" << f_graph << "\n"; 
    /* Output : 
    f_graph : 
    10
    1
    0 1 1 0 1 1 1 0 0 0 
    1 0 1 1 1 1 1 1 1 1 
    0 1 0 1 0 0 1 0 1 0 
    0 1 0 0 0 1 1 0 0 0 
    0 1 0 0 0 0 1 0 0 0 
    1 1 0 0 0 0 1 0 0 0 
    1 1 1 1 1 1 0 1 1 1 
    1 1 0 0 0 0 1 0 1 0 
    1 1 0 0 1 0 1 0 0 0 
    0 1 0 0 0 0 1 0 1 0 
    1 0 2 1 2 2 0 2 1 2 */

    mt19937_64 G(time(nullptr)); 
    SBM my_SBM({0.5,0.3,0.2}, 0.5, true); 
    Graph graph = my_SBM.generate_graph(10, G); 

    MatInt M = f_graph.one_hot_Z();
    cout << "\n" << M << endl; 
    /* Output : 
    0 1 0
    1 0 0
    0 0 1
    0 1 0
    0 0 1
    0 0 1
    1 0 0
    0 0 1
    0 1 0
    0 0 1 */

    cout << "Pour f_graph : " << endl; 
    cout << f_graph.count_statistics_s() << endl << endl;  
    cout << f_graph.count_statistics_a() << endl << endl; 
    cout << f_graph.count_statistics_b() << endl << endl; 
    /* Output : 
    Pour f_graph : 
    2
    3
    5

    2  6 10
    6  1  5
    10  6  0

    0  0  0
    0  5 10
    0  9 20 */
    cout << "Pour simple_graph_directed : " << endl; 
    cout << simple_graph_directed.count_statistics_s() << endl << endl;  
    cout << simple_graph_directed.count_statistics_a() << endl << endl; 
    cout << simple_graph_directed.count_statistics_b() << endl << endl; 
    /* Output : 
    Pour simple_graph_directed : 
    2
    1

    2 1
    1 0 

    0 1
    1 0 */
    cout << "Pour simple_graph_undirected : " << endl; 
    cout << simple_graph_undirected.count_statistics_s() << endl << endl;  
    cout << simple_graph_undirected.count_statistics_a() << endl << endl;  
    cout << simple_graph_undirected.count_statistics_b() << endl << endl;  
    /* Output : 
    Pour simple_graph_undirected : 
    2
    1

    1 1
    1 0

    0 1
    1 0 */
    return 0; 
}