#include<stdio.h>
typedef long long LL;
LL SUM[1000005],DP[1000005],A,B,C;
int N;
double K(int l,int r)
{
    return double(DP[r]-DP[l]+A*(SUM[r]*SUM[r]-SUM[l]*SUM[l]))/double(SUM[r]-SUM[l]);
}
struct Deq
{
	int s[1000005],l,r;
	void clear(){l=0,r=-1;}
	void pop_front(){l++;}
	void pop_back(){r--;}
	void push_back(int v){s[++r]=v;}
	int front(int i=0){return s[l+i];}
	int back(int i=0){return s[r-i];}
	int size(){return r-l+1;}
}DEQ;
int main()
{
	freopen("in.txt","r",stdin);
    scanf("%d%lld%lld%lld",&N,&A,&B,&C);
    SUM[0]=DP[0]=0;
	for(int i=1;i<=N;i++)
	{
        scanf("%lld",&SUM[i]);
        SUM[i]+=SUM[i-1];
    }
    DEQ.clear();
    DEQ.push_back(0);
    for(int i=1;i<=N;i++)
	{
        while(DEQ.size()>=2&&K(DEQ.front(),DEQ.front(1))>=double(2*A*SUM[i]))DEQ.pop_front();
        LL sum=SUM[i]-SUM[DEQ.front()];
        DP[i]=DP[DEQ.front()]+A*sum*sum+C;
        printf("DP[%d]=%lld\n",i,DP[i]);
        while(DEQ.size()>=2&&K(DEQ.back(1),DEQ.back())<=K(DEQ.back(),i))DEQ.pop_back();
        DEQ.push_back(i);
    }
    printf("%lld\n",DP[N]+SUM[N]*B);
}
