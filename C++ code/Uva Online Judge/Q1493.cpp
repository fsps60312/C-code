#include<cstdio>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1)printf("E");}
typedef long long LL;
const LL BD=4294967296LL;
void RunTimeError(){puts("Run Time Error\n");int a,b=0;while(1)a/=b;}
int N,M,Q,BASE[200][200000];
struct Sg
{
	int *bad;
	void Clear(){bad[1]=0;}
	void GetColor(int *ans)
	{
	}
}SG[100];
char LINE[10];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)SG[i].bad=BASE[i];
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
		for(int i=0;i<M;i++)SG[i].Clear();
		long long xc,yc,r,c,l,w;
		while(Q--)
		{
			if(scanf("%s",LINE)!=1)RunTimeError();
			switch(LINE[0])
			{
				case'C':
				{
					int tmp=scanf("%lld%lld%lld%lld",&xc,&yc,&r,&c);
					if(tmp!=4||xc>=BD||yc>=BD||r>=BD||c>=BD)RunTimeError();
				}break;
				case'D':
				{
					int tmp=scanf("%lld%lld%lld%lld",&xc,&yc,&r,&c);
					if(tmp!=4||xc>=BD||yc>=BD||r>=BD||c>=BD)RunTimeError();
				}break;
				case'R':
				{
					int tmp=scanf("%lld%lld%lld%lld%lld",&xc,&yc,&l,&w,&c);
					if(tmp!=5||xc>=BD||yc>=BD||l>=BD||w>=BD||c>=BD)RunTimeError();
				}break;
				case'T':
				{
					int tmp=scanf("%lld%lld%lld%lld",&xc,&yc,&w,&c);
					if(tmp!=4||xc>=BD||yc>=BD||w>=BD||c>=BD)RunTimeError();
				}break;
				default:termin("Can't handle %c\n",LINE[0]);break;
			}
		}
	}
	termin("Finish\n");
	return 0;
}
