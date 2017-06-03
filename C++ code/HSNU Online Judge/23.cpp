#include "interactive/23.h"
#include<bits/stdc++.h>
using namespace std;
int N,G,X;
int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}
int main()
{
	GetN(N);
	Get(G);
	for(int i=1;i<N;i++)
	{
		Get(X);
		G=gcd(X,G);
		Report(G);
	}
	Bye();
	return 0;
}
