#include <vector>
#include <fstream>

template <class Field,int d> class LinearForm;
template <class Field,int d> std::istream & operator>> ( std::istream & is, LinearForm<Field,d> & f);

template <class Field,int d>
class LinearForm {
    private:
        std::vector<Field> coeff;
    public:
        LinearForm();
        LinearForm(std::vector<Field> v) : coeff(v) {} 
        Field operator () (const std::vector<Field> & v) const; 
};

template <class Field,int d>
Field LinearForm<Field, d>::operator () (const std::vector<Field> & v) const
{
    Field resultat = 0; 
    for(int i = 0; i < v.size(); ++i)
    {
        resultat += v[i]*coeff[i]; 
    }
    return resultat; 
}
