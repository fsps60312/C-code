#include<cstdio>
#include<cstdlib>
int T,n;
char in[2];
struct pairtype{int x,y;};
pairtype S[20001];
pairtype newpair(int a,int b){pairtype c;c.x=a,c.y=b;return c;}
pairtype fin(int a)
{
	if(S[a].x==a)return S[a];
	pairtype b=fin(S[a].x);
	S[a].x=b.x;
	S[a].y+=b.y;
	return S[a];
}
int abs(int a){return a>=0?a:-a;}
void run()
{
	int a,b;
	for(int i=1;i<=n;i++)S[i]=newpair(i,0);
	while(scanf("%s",in)==1)
	{
		switch(in[0])
		{
			case'E':
			{
				scanf("%d",&a);
				fin(a);
				printf("%d\n",S[a].y);
			}break;
			case'I':
			{
				scanf("%d%d",&a,&b);
				S[a].x=b;
				S[a].y=abs(a-b)%1000;
			}break;
			default:return;
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		run();
	}
	return 0;
}
