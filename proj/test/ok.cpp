#include<iostream>
#include<cstring>
using namespace std;
#define M 100
bool visit[10000000];
int prime[10000000];
 
 
void table()
{
	memset(visit,true,sizeof(visit));
	int num = 0;
	for (int i = 2; i <= M; ++i)
	{
		if (visit[i] == true)
		{
			num++;
			prime[num] = i;
		}
		for (int j = 1; ((j <= num) && (i * prime[j] <= M));  ++j)
		{
			visit[i * prime[j]] = false;
			if (i % prime[j] == 0) break; 
		}
	}
}
int main()
{
	memset(prime, 0, sizeof(prime));
	table();
	for(int i = 0; i <= M; ++i)
		if(prime[i])
		{
			cout<<prime[i]<<" ";
		}
		cout<<endl;
}