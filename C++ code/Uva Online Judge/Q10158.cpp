#include<cstdio>
#include<cstdlib>
int n,c,x,y,S[10001];
int abs(int a)
{
	return a>=0?a:-a;
}
int fin(int a,bool isenemy)
{
	if(a<0)
	{
		a*=-1;
		isenemy^=1;
	}
	if(abs(S[a])==a) return isenemy?-a:a;
	S[a]=fin(S[a],false);
	return isenemy?-S[a]:S[a];
}
int solve(int a,int b,bool d)
{
	//printf("pass\n");
	int e=fin(a,false);
	int f=fin(b,false);
	if(abs(e)!=abs(f)) return 0;
	return d^(e==f?0:1);
}
void setS(int a,int b)
{
	if(S[a]==-b)
	{
		printf("-1\n");
		return;
	}
	S[a]=b;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) S[i]=i;
	while(scanf("%d%d%d",&c,&x,&y)==3&&(c||x||y))
	{
		x++,y++;
		switch(c)
		{
			case 1://set friend
				{
					int a=fin(x,false);
					//printf("a=%d b=%d\n",a,fin(y,false));
					if(a>0)
					{
						setS(a,fin(y,false));
					}
					else
					{
						setS(-a,-fin(y,false));
					}
				}break;
			case 2://set enemy
				{
					int a=fin(x,false);
					if(a>0)
					{
						setS(a,-fin(y,false));
					}
					else
					{
						setS(-a,fin(y,false));
					}
				}break;
			case 3://are friend
				{
					printf("%d\n",solve(x,y,true));
				}break;
			case 4://are enemy
				{
					printf("%d\n",solve(x,y,false));
				}break;
		}
		//printf("%d %d %d\n",c,x,y);
		//for(int i=1;i<=n;i++) printf(" %d",S[i]);printf("\n");
	}
	return 0;
}
