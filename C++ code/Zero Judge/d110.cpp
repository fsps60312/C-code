#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Djset
{
	int s[2000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	void find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
}DJ;
struct Deq
{
	int s[1000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int back()const{return s[r];}
	int front()const{return s[l];}
	bool empty(){return r<l;}
}DEQ;
int N,S[1001];
int RIGHT[1000],RIGHT_J[1000],RIGHT_I[1000];
void GetRIGHT()
{
	S[N]=INF;
	DEQ.clear(),DEQ.push_back(N);
	for(int i=N-1;i>=0;i--)
	{
		while(!DEQ.empty()&&S[i]>S[DEQ.back()])DEQ.pop_back();
		RIGHT[i]=DEQ.back();
		DEQ.push_back(i);
	}
	RIGHT_I[0]=0,RIGHT_J[0]=RIGHT[0];
	for(int i=1;i<N;i++)
	{
		if(RIGHT_J[i-1]<=RIGHT[i])RIGHT_I[i]=RIGHT_I[i-1],RIGHT_J[i]=RIGHT_J[i-1];
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		//i<j<k,S[k]<S[i]<S[j]
		GetRIGHT();
		for(int i=0;i<N;i++)
		{
			
		}
	}
	return 0;
}
