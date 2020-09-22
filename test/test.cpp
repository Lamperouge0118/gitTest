#include <iostream>
#include<cstring>
#define N 100

using namespace std;
bool isprime;
int prime[10000000];


int main()
{
    memset(prime, 0, sizeof(prime));
    int i,j,k=0;

    for(i=2;i<=N;i++)
    {
        isprime = true;
        for(j=0;prime[j] != 0;j++)
        {
            if(i % prime[j] == 0)
            {
                isprime = false;
                break;
            }
        }
        if(isprime)
        {
            prime[k]=i;
            cout << prime[k++]<<" ";
        }

    }
    cout<<endl;

}
