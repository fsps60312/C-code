#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
int N,BONE[24];
char STR[1000000];
void getmax(int &a,int b){if(b>a)a=b;}
map<int,vector<int> > MAX;
int main()
{
	while(scanf("%d",&N)==1)
	{
		MAX.clear();
		for(int i=0;i<N;i++)
		{
			scanf("%s",STR);
			BONE[i]=0;
			for(int j=0;STR[j];j++)
			{
				BONE[i]^=1<<(STR[j]-'A');
			}
		}
		int hn=N/2;
		vector<int> cnt,ans;
		for(int i=0,v=0;i<(1<<hn);i++,v=0)
		{
			cnt.clear();
			for(int j=0;j<hn;j++)if(i&(1<<j))v^=BONE[j],cnt.push_back(j);
			if(MAX.find(v)==MAX.end())MAX[v]=cnt;
			else if(MAX[v].size()<cnt.size())MAX[v]=cnt;
		}
		int r=N-hn;
		for(int i=0,v=0;i<(1<<r);i++,v=0)
		{
			cnt.clear();
			for(int j=hn;j<N;j++)if(i&(1<<j-hn))v^=BONE[j],cnt.push_back(j);
			if(MAX.find(v)!=MAX.end()&&MAX[v].size()+cnt.size()>ans.size())
			{
				ans.clear();
				vector<int> &m=MAX[v];
				for(int i=0;i<m.size();i++)ans.push_back(m[i]);
				for(int i=0;i<cnt.size();i++)ans.push_back(cnt[i]);
			}
		}
		printf("%d\n",ans.size());
		sort(ans.begin(),ans.end());
		for(int i=0;i<ans.size();i++)
		{
			if(i>0)printf(" ");
			printf("%d",ans[i]+1);
		}
		printf("\n");
	}
	return 0;
}
