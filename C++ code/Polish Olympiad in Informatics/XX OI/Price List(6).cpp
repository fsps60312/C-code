#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
bool Contains(const vector<int>&s,const int val){return lower_bound(s.begin(),s.end(),val)!=upper_bound(s.begin(),s.end(),val);}
vector<int>ET[100000];
int N,M,K,A,B,DIST[100000],ANS[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d%d",&N,&M,&K,&A,&B);
	K--;
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b);a--;b--;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	for(int i=0;i<N;i++)DIST[i]=INF;
	queue<int>q;q.push(K);
	DIST[K]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<(int)ET[u].size();i++)if(DIST[ET[u][i]]==INF)
		{
			const int nxt=ET[u][i];
			DIST[nxt]=DIST[u]+1;
			q.push(nxt);
		}
	}
	if(B>=A*2)for(int i=0;i<N;i++)ANS[i]=DIST[i]*A;
	else
	{
		for(int i=0;i<N;i++)ANS[i]=(DIST[i]%2)*A+(DIST[i]/2)*B;
		static vector<int>E2[100000];
		for(int i=0;i<N;i++)DIST[i]=INF,sort(ET[i].begin(),ET[i].end()),E2[i]=ET[i];
		q.push(K);
		DIST[K]=0;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<(int)ET[u].size();i++)
			{
				const int nxt=ET[u][i];
				vector<int>te2;
				for(int j=0;j<(int)E2[nxt].size();j++)if(DIST[E2[nxt][j]]==INF)
				{
					const int oxt=E2[nxt][j];
					if(Contains(ET[u],oxt))te2.push_back(oxt);
					else
					{
						DIST[oxt]=DIST[u]+1;
						q.push(oxt);
					}
				}
				E2[nxt].swap(te2);
			}
		}
		for(int i=0;i<N;i++)if(DIST[i]!=INF)getmin(ANS[i],DIST[i]*B);
	}
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
	return 0;
}
