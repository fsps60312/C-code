#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
inline void getmax(int &a,const int b){if(a<b)a=b;}
struct Deq
{
	int S[1000000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Back(const int i)const{return S[R-i];}
	int Front(const int i)const{return S[L+i];}
	int Size()const{return R-L+1;}
	bool Empty()const{return R<L;}
}DEQ;
int N;
vector<int>QUERIES,ET[1000000];
int DEPTH[1000000],ANS[1000001],SUM[1000001],MAX_DEPTH;
void BuildDepth()
{
	for(int i=0;i<N;i++)DEPTH[i]=-1;
	queue<int>q;
	q.push(0);DEPTH[0]=1;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		MAX_DEPTH=DEPTH[u];
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			assert(DEPTH[nxt]==-1);
			DEPTH[nxt]=DEPTH[u]+1;
			q.push(nxt);
		}
	}
}
int GetA(const int i){return SUM[i+1];}
int GetB(const int i){return i;}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
int main()
{
//	freopen("in.txt","r",stdin);
	if(true)
	{
		int cnt;
		scanf("%d%d",&N,&cnt);
		QUERIES.clear();
		for(int i=0,v;i<cnt;i++)
		{
			scanf("%d",&v);
			QUERIES.push_back(v);
		}
	}
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=1,fa;i<N;i++)scanf("%d",&fa),ET[--fa].push_back(i);
	BuildDepth();
	for(int i=1;i<=MAX_DEPTH;i++)SUM[i]=0;
	for(int i=0;i<N;i++)++SUM[DEPTH[i]];
	for(int i=MAX_DEPTH-1;i>=1;i--)SUM[i]+=SUM[i+1];
	DEQ.Clear();
	for(int i=MAX_DEPTH-1;i>=0;i--)
	{
		while(DEQ.Size()>=2&&GetX(DEQ.Back(1),DEQ.Back(0))>=GetX(DEQ.Back(0),i))DEQ.PopBack();
		DEQ.PushBack(i);
	}
	for(int k=N;k>=1;k--)
	{
//		ANS[k]=0;
//		for(int i=0;i<MAX_DEPTH;i++)getmax(ANS[k],i+SUM[i+1]/k);
		//ANS[1/i]=max(j+i*SUM[j+1])
		while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<=1.0/k)DEQ.PopFront();
		const int i=DEQ.Front(0);
		ANS[k]=i+(SUM[i+1]+k-1)/k;
	}
	for(int i=0;i<(int)QUERIES.size();i++)
	{
		if(i)putchar(' ');
		const int q=QUERIES[i],ans=(q>N?MAX_DEPTH:ANS[q]);
		printf("%d",ans);
	}
	puts("");
	return 0;
}
