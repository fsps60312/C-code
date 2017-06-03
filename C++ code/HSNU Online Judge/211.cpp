#include<cstdio>
int abs(const int &a,const int &b){return a>=b?a-b:b-a;}
int N,M,K;
int main()
{
	scanf("%d%d%d",&N,&M,&K);
	int dif,v;
	scanf("%d",&v);
	dif=abs(K,v);
	for(int i=1;i<M;i++)
	{
		scanf("%d",&v);
		v=abs(K,v);
		if(v==dif)puts("Same");
		else if(v<dif)puts("Hotter");
		else puts("Colder");
		dif=v;
	}
	return 0;
}
