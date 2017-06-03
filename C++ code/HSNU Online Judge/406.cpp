#include<bits/stdc++.h>
using namespace std;
int N;
char S[1001];
inline bool Digit(const char &c){return c>='0'&&c<='9';}
int main()
{
	while(scanf("%s",S)==1)
	{
		int i=0;
		for(;;)
		{
			while(S[i]&&!Digit(S[i]))i++;
			if(!S[i])break;
			int v=0;
			while(Digit(S[i]))v=v*10+(S[i]-'0'),i++;
			printf("%d\n",v);
		}
	}
	return 0;
}
