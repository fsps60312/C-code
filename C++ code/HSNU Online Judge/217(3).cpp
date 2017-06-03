#include<cstdio>
#include<vector>
using namespace std;
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
const int INF=2147483647;
int T,N,K,A,B;
char LINE[5001];
int S[5000],DP[500][5000],PRE[500][5000];
struct State
{
	int idx,score;
	State(){}
	State(const int &i,const int &s):idx(i),score(s){}
};
struct Deq
{
	vector<State>v;
	int l,r;
	void clear(){v.clear();l=0,r=-1;}
	State &front(){return v[l];}
	State &back(){return v[r];}
	void push_back(const int &i,const int &s){r++;v.push_back(State(i,s));}
	void pop_back(){r--;v.pop_back();}
	void pop_front(){l++;}
	bool empty(){return r<l;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&K,&A,&B);
		scanf("%s",LINE);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<K;i++)for(int j=0;j<N;j++)DP[i][j]=-INF;
		for(int i=A-1;i<B;i++)DP[0][i]=S[i];
		for(int k=1;k<K;k++)
		{
			static Deq deq;
			deq.clear();
			for(int i=A;i<N;i++)
			{
				while(!deq.empty()&&deq.front().idx<i-B)deq.pop_front();
				while(!deq.empty()&&deq.back().score<=DP[k-1][i-A])deq.pop_back();
				deq.push_back(i-A,DP[k-1][i-A]);
				DP[k][i]=deq.front().score;
				if(DP[k][i]!=-INF)DP[k][i]+=S[i]*(k+1);
//				printf("(%d,%d):%d\n",k,i,DP[k][i]);
				PRE[k][i]=deq.front().idx;
			}
		}
		static int kase=1;
		printf("Case #%d:\n",kase++);
		if(DP[K-1][N-1]==-INF)puts("Sorry, you're milk cheese.");
		else
		{
			printf("%d\n",DP[K-1][N-1]);
			vector<int>ans;
			for(int i=K-1,pre=N-1;i>=0;i--)
			{
				ans.push_back(pre);
				pre=PRE[i][pre];
			}
			for(int i=ans.size()-1,idx=0;i>=0;i--)
			{
				int &v=ans[i];
				for(;idx<=v;idx++)printf("%c",LINE[idx]);
				puts("");
			}
		}
	}
	return 0;
}
