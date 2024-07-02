#include <string> 
#include <fstream>

class Game 
{
    private : 
    std::string Player1; 
    std::string Player2; 
    double score1; 
    double score2; 
    int nb_of_turns; 

    public : 
    Game(std::string p1, std::string p2, double s1 = 0, double s2 = 0) : Player1(p1), Player2(p2), score1(s1), score2(s2), nb_of_turns(0) {}

    void wins(int p, double score); 
    std::string the_winner_is() const; 
    int turns() const {return nb_of_turns;}
    void write(std::ostream& out);
};