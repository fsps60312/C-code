#include<cstdio>
int N,X[1000000],Y[1000000];
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
}DEQ;//store up->down lowbound
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d%d",&X[i],&Y[i]);
	int ans=0;
	for(int i=0,l=0;i<N;i++)
	{
		while(!DEQ.empty()&&X[i]>=X[DEQ.back()])DEQ.pop_back();
		while(!DEQ.empty()&&X[DEQ.front()]>Y[i])l=DEQ.front()+1,DEQ.pop_front();
		DEQ.push_back(i);
		if(i-l+1>ans)ans=i-l+1;
	}
	printf("%d\n",ans);
	return 0;
}
