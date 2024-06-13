template <class K>
class Segment 
{
	private:
		K left;
		K right;
	public:
		Segment(K l,K r) : left(l), right(r) {} 
		bool contains(K n) const;
};

template <class K>
bool Segment<K>::contains(K n) const
{	
	if(n < left or n > right) return false;  
	return true; 
}
