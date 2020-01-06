<<<<<<< HEAD
#include <vector>
#include <iostream>
using namespace std;
int sa[10]; 
int main()
{
	int ia[10];
	for(auto i : ia)
		cout<<i<<endl;
	for(auto i : sa)
		cout<<i<<endl;
	string input;
	std::vector<string> v(4);
	//cout<<v.begin()<<" "<<v.end()<<endl;
	/*for(auto it = v.begin();it != v.end();it++)
		{
		 cin>>input;
            *it = input;//.push_back(input);
        for(auto s = (*it).begin();s!=(*it).end();s++)
        	*s = toupper(*s);	
		}
     for(auto i : v)
     	cout<<i<<endl;*/
		
}
=======
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int size = digits.size();
        int end = size-1;
        int n = end;
       int Cal(vector<int>& digits,int n) 
       {
           if(n==0)
               return digits[n]+1;
           if(digits[n]+1 == 10)
               Cal(digits,n-1);
       }
        while(n>1)
        {
            mohui = digits[n]+1;
            if(mowei==10)
            {
                digits[n-1] = digits[n-1]+1;
                continue;
            }
            else
               break;
            
                
        }
    }
};
>>>>>>> 2a9c9133b5baa4d275d93520b5c78c01e1a30529
