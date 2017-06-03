#include<cstdio>
#include<vector>
#include<map>
#include<string>
#include<cassert>
#include<algorithm>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
int T,N,CNT[26],OUT[26],DJ[26];
char LINE[21];
vector<string>TO[26][26];
void dfsprint(int u,int fa,int t)
{
	if(fa!=-1)
	{
		vector<string>&v=TO[fa][u];
		printf("%s",v[v.size()-1].c_str());
		CNT[fa]--,CNT[u]--,N--;
		v.pop_back();
		if(!N)return;
		else printf(".");
	}
	for(int i=0;i<26;i++)
	{
		vector<string>&v=TO[u][i];
		if(!v.size())continue;
		if(i==t&&CNT[i]==1&&N>1)continue;
		dfsprint(i,u,t);
		break;
	}
	if(N)termin("still has unprinted\n");
}
bool cmp(string a,string b){return a>b;}
int findDJ(int a){return DJ[a]==a?a:(DJ[a]=findDJ(DJ[a]));}
int main()
{
//	printf("%d %d\n",'a','.');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<26;i++)
		{
			for(int j=0;j<26;j++)TO[i][j].clear();
			CNT[i]=OUT[i]=0;
			DJ[i]=i;
		}
		for(int i=0;i<N;i++)
		{
			scanf("%s",LINE);
			int c1=LINE[0]-'a',c2=-1;
			while(LINE[++c2]);c2=LINE[--c2]-'a';
			TO[c1][c2].push_back(LINE);
			CNT[c1]++,CNT[c2]++;
			OUT[c1]++;
			DJ[findDJ(c1)]=findDJ(c2);
		}
		int cnt=0;
		for(int i=0,dj=-1;i<26;i++)
		{
			for(int j=0;j<26;j++)
			{
				vector<string>&v=TO[i][j];
				sort(v.begin(),v.end(),cmp);
			}
			if(CNT[i])
			{
				if(CNT[i]&1)cnt++;
				if(dj==-1)dj=findDJ(i);
				else if(findDJ(i)!=dj){cnt=3;break;}
			}
			if(abs(OUT[i]*2-CNT[i])>1){cnt=3;break;}
		}
		if(cnt>2)printf("***\n");
		else if(cnt==2)
		{
			int s=-1,t=-1;
			for(int i=0;i<26;i++)
			{
				if(CNT[i]&1)
				{
					if(s==-1)
					{
						if(!OUT[i])t=i;
						else s=i;
					}
					else t=i;
				}
			}
			if(s==-1||t==-1)termin("can't find s & t\n");
			dfsprint(s,-1,t);puts("");
		}
		if(cnt==0)
		{
			for(int i=0;i<26;i++)if(CNT[i])dfsprint(i,-1,i);
			puts("");
		}
	}
	return 0;
}
/*
25
ba cb dc ed fe gf hg ih ji kj lk ml nm on po qp rq sr ts ut vu wv xw yx zy
*/
