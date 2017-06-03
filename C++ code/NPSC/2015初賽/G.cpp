#include<cstdio>
#include<vector>
#include<map>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int T,N,M;
map<char,int>IDX;
vector<int>SKILL,COST;
int GetIDX(const char c)
{
	if(IDX.find(c)==IDX.end())
	{
		const int sz=IDX.size();
		return IDX[c]=sz;
	}
	return IDX[c];
}
int CntBit(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int DP[1<<12],PRE[1<<12],USE[1<<12];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		IDX.clear(),COST.clear(),SKILL.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[100];
			static int cost;
			scanf("%d%s",&cost,tmp);
			COST.push_back(cost);
			int skill=0;
			for(int i=0;tmp[i];i++)skill|=(1<<GetIDX(tmp[i]));
			SKILL.push_back(skill);
		}
		assert(SKILL.size()==N&&COST.size()==N);
		M=IDX.size();
		assert(M<=12);
		for(int i=0;i<(1<<M);i++)DP[i]=INF;
		DP[0]=0;
		for(int bitcnt=0;bitcnt<M;bitcnt++)
		{
			for(int s=0;s<(1<<M);s++)if(CntBit(s)==bitcnt&&DP[s]!=INF)
			{
				for(int i=0;i<N;i++)if((s|SKILL[i])!=s)
				{
					if(getmin(DP[s|SKILL[i]],DP[s]+COST[i]))
					{
						PRE[s|SKILL[i]]=s;
						USE[s|SKILL[i]]=i;
					}
				}
			}
		}
		assert(DP[(1<<M)-1]!=INF);
		printf("%d\n",DP[(1<<M)-1]);
		vector<int>tmp;
		tmp.push_back(USE[(1<<M)-1]);
		for(int s=PRE[(1<<M)-1];s;s=PRE[s])tmp.push_back(USE[s]);
		static bool vis[10000];
		for(int i=0;i<N;i++)vis[i]=false;
		vector<int>ans;
		for(int i=(int)tmp.size()-1;i>=0;i--)ans.push_back(tmp[i]),vis[tmp[i]]=true;
		for(int i=0;i<N;i++)if(!vis[i])ans.push_back(i);
		assert(ans.size()==N);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
} 
