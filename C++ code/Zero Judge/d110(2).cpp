#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Djset
{
	int s[2000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
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
	int size()const{return r-l+1;}
	bool empty()const{return r<l;}
	int operator[](const int i)const{return s[l+i];}
}DEQ;
int N,S[1000];
int RIGHT_LOWER[1000];
void GetRIGHT()
{
	S[N]=INF;
	DEQ.clear(),DEQ.push_back(N);
	for(int i=N-1;i>=0;i--)
	{
		if(S[i]>S[DEQ.back()])
		{
			int l=0,r=DEQ.size()-1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(S[DEQ[mid]]<S[i])r=mid;
				else l=mid+1;
			}
			assert(S[DEQ[r]]<S[i]);
			RIGHT_LOWER[i]=DEQ[r];
		}
		else DEQ.push_back(i),RIGHT_LOWER[i]=N;
	}
}
vector<int>ET[1000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		//i<j<k,S[k]<S[i]<S[j]
		GetRIGHT();
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(S[i]<S[j])
		{
			if(RIGHT_LOWER[i]>j)
		}
	}
	return 0;
}
