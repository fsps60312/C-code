#include<cstdio>
int N,K,S[1000000];
struct Deq
{
	int s[1000000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int &v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int front(){return s[l];}
	int back(){return s[r];}
	bool empty(){return r<l;}
}DEQ;
int main()
{
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		DEQ.clear();
		for(int i=0;i<N;i++)
		{
			while(!DEQ.empty()&&S[i]<=S[DEQ.back()])DEQ.pop_back();
			DEQ.push_back(i);
			while(DEQ.front()<=i-K)DEQ.pop_front();
			if(i==K-1)printf("%d",S[DEQ.front()]);
			else if(i>=K)printf(" %d",S[DEQ.front()]);
		}
		puts("");
		DEQ.clear();
		for(int i=0;i<N;i++)
		{
			while(!DEQ.empty()&&S[i]>=S[DEQ.back()])DEQ.pop_back();
			DEQ.push_back(i);
			while(DEQ.front()<=i-K)DEQ.pop_front();
			if(i==K-1)printf("%d",S[DEQ.front()]);
			else if(i>=K)printf(" %d",S[DEQ.front()]);
		}
		puts("");
	}
	return 0;
}
