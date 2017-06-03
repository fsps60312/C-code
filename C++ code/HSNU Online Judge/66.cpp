#include<cstdio>
typedef long long LL;
const int INF=1147483647;
int N,M,X,Y,L[5000001],R[5000001];
struct Deq
{
	int s[5000001],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int &v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int front(){return s[l];}
	int back(){return s[r];}
	int size(){return r-l+1;}
	bool empty(){return r<l;}
}MN,MX;
LL Cnt(const int &h,const int &w)
{
	MN.clear(),MX.clear();
	MN.push_back(0),MX.push_back(0);
	LL ans=0LL;
	for(int i=1;i<=M;i++)
	{
		while(!MX.empty()&&L[i]>=L[MX.back()])MX.pop_back();
		while(!MN.empty()&&R[i]<=R[MN.back()])MN.pop_back();
		MX.push_back(i),MN.push_back(i);
		while(MX.front()<=i-h)MX.pop_front();
		while(MN.front()<=i-h)MN.pop_front();
		if(L[MX.front()]<=R[MN.front()]-w)
		{
			ans+=R[MN.front()]-L[MX.front()]-w+1LL;
//			printf("(%d,%d):%d:%d\n",w,h,i,R[MN.front()]-L[MX.front()]-w+1);
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d",&N,&M,&X,&Y);
	L[0]=INF,R[0]=-INF;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&L[i],&R[i]);
		R[i]+=L[i];
	}
	LL ans;
	if(X!=Y)ans=Cnt(X,Y)+Cnt(Y,X);
	else ans=Cnt(X,Y);
	printf("%lld\n",ans);
	return 0;
}
