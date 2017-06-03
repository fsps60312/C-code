#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
char S[1002];
int N,SA[1000];
void BuildSA()
{
	static int tmp[3][1000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int p='Z'+1;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
	for(int move=1;move<=N;move<<=1)
	{
		int idx=0;
		for(int i=N-move;i<N;i++)y[idx++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[idx++]=SA[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0;
		x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i]]!=y[SA[i-1]])x[SA[i]]=p++;
			else if((SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=p++;
			else assert(SA[i]+move<N&&SA[i-1]+move<N),x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?p-1:p++);
		}
		if(p==N)break;
	}
}
int RANK[1000],HEIGHT[1000];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,ans=0;i<N;i++)
	{
		if(ans)ans--;
		if(RANK[i]==0){HEIGHT[0]=0;continue;}
		int j=SA[RANK[i]-1];
		while(S[i+ans]==S[j+ans])ans++;
		HEIGHT[RANK[i]]=ans;
	}
}
set<int>P;
vector<int>IDX[1000];
void Erase(multiset<int,greater<int> >&s,const int v)
{
	const auto it=s.find(v);
	assert(it!=s.end());
	s.erase(it);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(fgets(S,INF,stdin))
	{
		N=-1;while(S[++N])if(S[N]=='\n'){S[N]='\0';break;}
		if(N==0)break;
		N=0;
		for(int i=0;S[i];i++)if(S[i]!=' ')S[N++]=S[i];
		S[N]='\0';
		assert(N<=1000);
		if(N==0){puts("0\n");continue;}
		for(int i=0;i<N;i++)assert(S[i]>='A'&&S[i]<='Z');
		BuildSA();
		BuildHEIGHT();
		for(int i=0;i<N;i++)IDX[i].clear();
		for(int i=1;i<N;i++)assert(HEIGHT[i]>=0&&HEIGHT[i]<N),IDX[HEIGHT[i]].push_back(i);
		P.clear();
		P.insert(0),P.insert(N);
		multiset<int,greater<int> >gap;
		gap.insert(N);
		for(int h=0,cnt=0;;h++)
		{
			for(const int idx:IDX[h])
			{
				auto it=P.upper_bound(idx);
//				assert(P.find(idx)==P.end());
				assert(it!=P.end()&&it!=P.begin());
				const int r=*it;
				const int l=*(--it);
				P.insert(idx);
				Erase(gap,r-l);
				gap.insert(idx-l),gap.insert(r-idx);
				assert(++cnt<=N-1);
			}
			if(*gap.begin()==1)break;
			printf("%d\n",*gap.begin());
		}
		puts("");
	}
	return 0;
}
