#include "rejection.hpp"

std::ostream& operator<<(std::ostream& out, const Box& B)
{
    out << B.left << " " << B.right << " " << B.height; 
    return out; 
}

std::istream& operator>>(std::istream& in, Box& B)
{
    double l, r , h; 
    in >> l >> r >> h; 
    B.left = l; 
    B.right = r; 
    B.height = h; 
    return in; 
}

bool PiecewiseConstant_function::check_ranges() const
{
    auto height_negative = [](Box B)
    {
        return B.height <= 0; 
    };
    auto compare = [](Box B) 
    {
        return B.right < B.left; 
    };
    bool test1 = std::any_of(boxes.begin(), boxes.end(), height_negative); 
    bool test2 = std::any_of(boxes.begin(), boxes.end(), compare); 
    if(test1 || test2) return false; 
    return true; 
}

bool PiecewiseConstant_function::check_disjoint() const
{
    bool rep = true; 
    for(int i = 0; i < nb_of_boxes()-1; ++i)
    {
        if(boxes[i].right > boxes[i+1].left) rep = false; 
    }
    return rep; 
}

std::ostream& operator<<(std::ostream& out, const PiecewiseConstant_function& f)
{   
    out << f.boxes.size() << "\n"; 
    for(const Box& B : f.boxes)
    {
        out << B << "\n"; 
    }
    return out; 
}

std::istream& operator>>(std::istream& in, PiecewiseConstant_function& f)
{   
    int n; 
    in >> n; 
    std::vector<Box> boites(n); 
    for(int i = 0; i < n; ++i)
    {
        Box B;
        in >> B; 
        boites[i] = B; 
    }
    f.boxes = boites; 
    return in; 
}

int PiecewiseConstant_distribution::random_box(double u) const
{
    int k = 0; 
    while(cumul_area[k] >= u)
    {
        k++; 
    }
    return k; 
}