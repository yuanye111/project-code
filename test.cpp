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
