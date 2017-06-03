#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int DJ[1000000];
int Find(int a){return DJ[a]==a?a:(DJ[a]=FInd(DJ[a]));}
bool Merge(int a,int b)
{
	if((a=Find(a))==(b=Find(b)))return false;
	DJ[a]=b;
	return true;
}
int N,M;
vector<int>ET[1000000],TYPE[1000000];
void Walk(int u,const int depth)
{
	assert(depth>=1);
	assert(ET[u].size()==1);
	int parent=u,u=ET[u][0];
	for(int i=1;i<depth;i++)
	{
		assert(ET[u].size()==2);
		assert((ET[u][0]==parent)^(ET[u][1]==parent));
		const int nxtu=ET[u][ET[u][0]==parent?1:0];
		parent=u,u=nxtu;
	}
	return u;
}
void SetSmallEnd(const int u,const int type)
{
	for(const int nxt:ET[u])
	{
		assert(ET[nxt].size()==1&&ET[nxt][0]==u);
		TYPE[nxt][0]=type;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),TYPE[i].clear(),TYPE[i].push_back(0);
		int ans=N;
		for(int a,b;M--;)
		{
			scanf("%d",&a);
			if(a==-1)printf("%d\n",ans);
			else
			{
				scanf("%d",&b),--a,--b;
				if(ans==0)continue;
				if(TYPE[a][0]<TYPE[b][0])swap(a,b);
				int &ta=TYPE[a][0],tb=TYPE[b][0];
				const bool together=(Find(a)==Find(b));
				switch(ta)
				{
					case 0:
					{
						switch(tb)
						{
							case 0:
							{
								assert(!together);
								ta=tb=1;
							}break;
							default:assert(0);break;
						}
					}break;
					case 1://<>
					{
						switch(tb)
						{
							case 0:
							{
								assert(!together);
								ta=3,tb=2;
								TYPE[Walk(a,1)][0]=2;
							}break;
							case 1:
							{
								assert(!together);
								ta=tb=3;
								TYPE[Walk(a,1)][0]=TYPE[Walk(b,1)][0]=2;
							}break;
							default:assert(0);break;
						}
					}break;
					case 2://<->
					{
						switch(tb)
						{
							case 0:
							{
								assert(!together);
								ta=3,tb=2;
							}break;
							case 1:
							{
								assert(!together);
								ta=tb=3;
								TYPE[Walk(b,1)][0]=2;
							}break;
							case 2:
							{
								if(!together)ta=tb=3;
								else
								{
									
									assert(0);
								}
							}break;
							default:assert(0);break;
						}
					}break;
					case 3://<->
					{
						switch(tb)
						{
							case 0:
							{
								ta=5;
								assert(0);
							}break;
							case 1:
							{
								assert(0);
							}break;
							case 2:
							{
								assert(0);
							}break;
							case 3:
							{
								assert(0);
							}break;
							default:assert(0);break;
						}
					}break;
					//0: one dot
					//1: end of chain, 2
					//2: end of chain, 3
					//3: body of chain, 3
					//4: end of small-fork, 4
					//5: body of small-fork, 4
					//
					default:assert(0);break;
				}
				Merge(a,b);
				ET[a].push_back(b),ET[b].push_back(a);
			}
		}
	}
	return 0;
}
