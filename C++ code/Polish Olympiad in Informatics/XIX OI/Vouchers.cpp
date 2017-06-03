#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
int M,N;
map<int,int>S;
bool SOLD[1000001],VOUCHERED[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=1000000;i++)SOLD[i]=VOUCHERED[i]=false;
	scanf("%d",&M);
	for(int i=0,v;i<M;i++)scanf("%d",&v),VOUCHERED[v]=true;
	S.clear();
	scanf("%d",&N);
	vector<int>ans;
	for(int i=0,a,cid=0;i<N;i++)
	{
		scanf("%d",&a);
		int &v=S[a];
		if(v>1000000)continue;
		for(int j=0;j<a;j++)
		{
			v+=a;
			if(v>1000000)break;
			if(SOLD[v]){j--;continue;}
			SOLD[v]=true;
			cid++;
			if(VOUCHERED[v])ans.push_back(cid);
		}
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)printf("%d\n",ans[i]);
	return 0;
}
