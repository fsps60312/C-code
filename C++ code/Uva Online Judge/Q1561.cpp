#include<cstdio>
int T,N,S[20];
bool Solve(const int l,const int r)
{
	if((l&1)||(r&1))return true;
	return false;
}
inline int Mod(const int a){return (a%N+N)%N;}
bool Solve()
{
	for(int i=0;i<1/*N*/;i++)
	{
		int r=i,l=Mod(i-1);
		while(S[r])r=Mod(r+1);
		while(S[l])l=Mod(l-1);
		if(Solve(Mod(i-1-l),Mod(r-i)))return true;
	}
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
