#include <vector>
#include <iostream>
#include <iterator>
using namespace std;
int sa[10]; 
class Solution {
public:
    class ito
    {
      int x;
      int y;
    } ;
   
};

int main()
{
    std::vector<int> input;
	  istream_iterator<int> in_iter(cin);
    istream_iterator<int> end;
    while(in_iter != end)
         input.push_back(*in_iter++);
    for(auto i:input)
      cout<<" "<<i;
}
