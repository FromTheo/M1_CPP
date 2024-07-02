#include "gamer.hpp"

void Game::wins(int p, double score)
{
    if(p == 1) 
    {
        score1 += score; 
        nb_of_turns++;
    } 
    if(p == 2) 
    {
        score2 += score; 
        nb_of_turns++;
    }
}

std::string Game::the_winner_is() const
{
    if(score1 > score2) return Player1; 
    if(score1 < score2) return Player2;
    return "Égalité"; 
}

void Game::write(std::ostream& out)
{
    if(score1 < score2) 
    {
        out << "Winner : " << Player2 <<  " " << score2 << "\n";
        out << "Loser : " << Player1 << " " << score1 << "\n";
    }
    else 
    {
        out << "Winner : " << Player1 << " " << score1 << "\n";
        out << "Loser : " << Player2 <<  " " << score2 << "\n"; 
    }
    out << "After " << turns() << " turns." << "\n"; 
}
