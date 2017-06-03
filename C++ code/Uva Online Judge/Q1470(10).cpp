#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Deq
{
	vector<int>s;
	void clear(){s.clear();l=0,r=-1;}
	void push_back(const int v){s.push_back(v),r++;}
	void pop_back(){s.pop_back(),r--;}
	void pop_front(){s.pop_front(),l++;}
	int front()const{return s[l];}
	int back()const{return s[r];}
	bool empty()const{return r<l;}
}DEQ;
int T,N;
vector<char>S;
vector<int>DP;
set
int Solve()
{
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+DP[mx]-1>i)DP[i]=min(DP[mx-(i-mx)],mx+DP[mx]-1-i+1);
		else DP[i]=1;
		while(i-DP[i]>=0&&i+DP[i]<N&&S[i-DP[i]]==S[i+DP[i]])DP[i]++;
	}
	DEQ.clear();
	for(int i=0;i<N;i+=2)
	{
		while(!DEQ.empty())
	}
}
int main()
{
	static char tmp[300002];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
	while(T--)
	{
		assert(fgets(tmp,INF,stdin));
		S.clear(),S.push_back('\0');
		N=-1;
		while(tmp[++N])
		{
			if(tmp[N]=='\n')break;
			S.push_back(tmp[N]),S.push_back('\0');
		}
		N=S.size();
		DP.resize(N);
		printf("%d\n",Solve());
	}
	return 0;
}
