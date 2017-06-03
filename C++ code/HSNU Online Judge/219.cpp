#include<bits/stdc++.h>
using namespace std;
int N,HEAD;
vector<vector<int> >ET,FA;
vector<int>DEP;
void GetFA(const int &u)
{
	for(int i=0,n=FA[u][0];i<FA[n].size();i++)
	{
		FA[u].push_back(n=FA[n][i]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
//		static int kase=1;printf("Case %d:\n",kase++);
		int d=0;
		ET.clear(),FA.clear(),DEP.clear();
		HEAD=0;
		ET.push_back(vector<int>()),FA.push_back(vector<int>()),DEP.push_back(0);
		for(int cnt=0;cnt<N;cnt++)
		{
			static char type[2];
			scanf("%s",type);
			switch(type[0])
			{
				case'a':
				{
					static int u,i;
					scanf("%d",&u);u-=d,u--;
					i=ET.size();
					ET.push_back(vector<int>());
					FA.push_back(vector<int>());
					DEP.push_back(DEP[u]+1);
					ET[u].push_back(i);
					FA[i].push_back(u);
					GetFA(i);
				}break;
				case'r':
				{
					static int u;
					scanf("%d",&u);u-=d,u--;
//					printf("r u=%d\n",u);
					HEAD=u;
				}break;
				case'q':
				{
					static int u,k;
					scanf("%d%d",&u,&k);u-=d,k-=d,u--;
					int a=u,b=HEAD;
					if(a==b){printf("%d\n",++a);d=a;break;}
					int da=0,db=0;
					if(DEP[a]<DEP[b])
					{
						int dif=DEP[b]-DEP[a];
						for(int i=0;(1<<i)<=dif;i++)if(dif&(1<<i))b=FA[b][i],db+=(1<<i);
					}
					else
					{
						int dif=DEP[a]-DEP[b];
						for(int i=0;(1<<i)<=dif;i++)if(dif&(1<<i))a=FA[a][i],da+=(1<<i);
					}
//					puts("a");
//					printf("a=%d,b=%d,da=%d,db=%d\n",a,b,da,db);
					assert(DEP[a]==DEP[b]);
					while(a!=b)
					{
						int i=0;
						for(;i+1<FA[a].size()&&FA[a][i+1]!=FA[b][i+1];i++);
						a=FA[a][i],b=FA[b][i];
						da+=1<<i,db+=1<<i;
					}
//					puts("b");
//					printf("a=%d,b=%d,da=%d,db=%d\n",a,b,da,db);
					k%=(da+db)<<1;
					if(k>da+db)k=((da+db)<<1)-k;
//					printf("k=%d\n",k);
					static int o;
					if(k<=da)o=u;
					else k=da+db-k,o=HEAD;
					for(int i=0;(1<<i)<=k;i++)if(k&(1<<i))o=FA[o][i];
//					puts("c");
					printf("%d\n",++o);
					d=o;
				}break;
				default:assert(0);
			}
		}
		break;
	}
	return 0;
}
