#include <iostream>
#include <fstream>
#include <vector>
#include<map>
#include<list>
using namespace std;

 void solve(int n)
{   cout<<n<<" ";
  for(int i=0;i<3;i++)
    { 
      if(i==2)
      {
 
        return;
      }
      solve(i);
      
    }


  
}

int main()
{ 

solve(1);
  
  
  return 0; 
}
