#include <iostream>

using namespace std;


int main()
{	
	const int N = 100;
	int k = 0,prime[N]{};
	bool Isprime;

	for (int i = 2; i <= N; i++)
	{
		Isprime = true;
		for (int j = 0; prime[j] != 0; j++)
		{
			if (i % prime[j] == 0)
			{
				Isprime = false;
				break;
			}
		}

		if (Isprime)
		{
			cout << i << " ";
			prime[k++] = i;
		}
	}

	cout << endl;
	cout << "共有" << k << "个素数" << endl;
	return 0;
}
