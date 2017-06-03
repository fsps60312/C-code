#include<cstdio>
#define LL long long
void termin(){int a[1];for(int i=0;;i--)a[i]=9;}
int N,M;
struct Node
{
	int pre,next;
	Node(){}
	Node(int p,int n):pre(p),next(n){}
};
Node S[100002];
bool REVERSED;
void Join(int u1,int u2)
{
	S[u1].next=u2;
	S[u2].pre=u1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&N,&M)==2)
	{
		REVERSED=false;
		for(int i=0;i<=N+1;i++)
		{
			S[i]=Node(i-1,i+1);
		}
		while(M--)
		{
			int type,x,y;
			scanf("%d",&type);
			if(REVERSED&&(type==1||type==2))type=3-type;
			switch(type)
			{
				case 1:
					{
						scanf("%d%d",&x,&y);
						Join(S[x].pre,S[x].next);
						Join(S[y].pre,x);
						Join(x,y);
					}break;
				case 2:
					{
						scanf("%d%d",&x,&y);
						Join(S[x].pre,S[x].next);
						Join(x,S[y].next);
						Join(y,x);
					}break;
				case 3:
					{
						scanf("%d%d",&x,&y);
						if(S[x].pre==y)
						{
							Join(S[y].pre,x);
							Join(y,S[x].next);
							Join(x,y);
						}
						else if(S[x].next==y)
						{
							Join(S[x].pre,y);
							Join(x,S[y].next);
							Join(y,x);
						}
						else
						{
							Node nx=S[x];
							Join(S[y].pre,x);
							Join(x,S[y].next);
							Join(nx.pre,y);
							Join(y,nx.next);
						}
					}break;
				default:
					{
						REVERSED^=1;
					}break;
			}
//			int u=S[0].next;
//			for(int i=0;u<=N;i++)
//			{
//				printf(" %d",u);
//				u=S[u].next;
//			}
//			puts("");
		}
		LL sum=0;
		if(REVERSED&&!(N&1))
		{
			int u=S[0].next,i;
			for(i=0;u!=N+1;i++)
			{
				//printf(" %d",u);
				if(i&1)sum+=u;
				u=S[u].next;
			}
			if(i!=N)
			{
				printf("%d\n",i);
				termin();
			}
		}
		else
		{
			int u=S[0].next,i;
			for(i=0;u!=N+1;i++)
			{
				//printf(" %d",u);
				if(!(i&1))sum+=u;
				u=S[u].next;
			}
			if(i!=N)
			{
				printf("%d\n",i);
				termin();
			}
		}
		//puts("");
		printf("Case %d: %lld\n",kase++,sum);
	}
	return 0;
}
