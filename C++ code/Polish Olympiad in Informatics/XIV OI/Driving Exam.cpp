#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
struct Street
{
	int X,Y;
	Street(){}
	Street(const int _X,const int _Y):X(_X),Y(_Y){}
};
bool CmpL(const Street &a,const Street &b)
{
	return a.X!=b.X?a.X<b.X:a.Y<b.Y;
}
bool CmpR(const Street &a,const Street &b)
{
	return a.X!=b.X?a.X>b.X:a.Y<b.Y;
}
bool CmpE(const Street &a,const Street &b)
{
	return a.X==b.X&&a.Y==b.Y;
}
int N,M,P,K;
vector<Street>L,R;
int LS[100001],RS[100001]; 
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&P,&K)==4)
	{
		L.clear(),R.clear();
		for(int i=0,x,y,d;i<P;i++)
		{
			scanf("%d%d%d",&x,&y,&d);
			(d==1?L:R).push_back(Street(x,y));
		}
//		printf("%d,%d\n",(int)L.size(),(int)R.size());
		sort(L.begin(),L.end(),CmpL),L.resize(unique(L.begin(),L.end(),CmpE)-L.begin());
		sort(R.begin(),R.end(),CmpR),R.resize(unique(R.begin(),R.end(),CmpE)-R.begin());
//		printf("%d,%d\n",(int)L.size(),(int)R.size());
		static int dp[100001];
		for(int i=0;i<=N;i++)LS[i]=RS[i]=0;
		for(int i=0,ans=0;i<(int)L.size();i++)
		{
			const Street &s=L[i];
			int l=0,r=ans;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(s.Y<=dp[mid])l=mid+1;
				else r=mid;
			}
			dp[r]=s.Y;
			if(r==ans)++ans;
			getmax(LS[s.X+1],ans);
//			printf("(%d,%d)\n",s.X,s.Y);
		}
		for(int i=0,ans=0;i<(int)R.size();i++)
		{
			const Street &s=R[i];
			int l=0,r=ans;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(s.Y<=dp[mid])l=mid+1;
				else r=mid;
			}
			dp[r]=s.Y;
			if(r==ans)++ans;
			getmax(RS[s.X],ans);
//			printf("(%d,%d)\n",s.X,s.Y);
		}
		for(int i=2;i<=N;i++)getmax(LS[i],LS[i-1]);
		for(int i=N-1;i>=1;i--)getmax(RS[i],RS[i+1]);
//		for(int i=1;i<=N;i++)printf(" %d",LS[i]);puts("");
//		for(int i=1;i<=N;i++)printf(" %d",RS[i]);puts("");
		int ans1=0,ans2=0;
		for(int l=1,r=0;l<=N;l++)
		{
			while(r+1<=N&&((N-l)-RS[l])+((r+1-1)-LS[r+1])<=0)++r;
			if(((N-l)-RS[l])+((r-1)-LS[r])<=0)getmax(ans2,r-l+1);
		}
		for(int l=1,r=0;l<=N;l++)
		{
			while(r+1<=N&&((N-l)-RS[l])+((r+1-1)-LS[r+1])<=K)++r;
//			printf("l=%d,r=%d,%d,%d\n",l,r,((N-l)-RS[l])+((r-1)-LS[r]),K);
			if(((N-l)-RS[l])+((r-1)-LS[r])<=K)getmax(ans1,r-l+1);
		}
		printf("%d\n",ans1-ans2);
	}
	return 0;
}
