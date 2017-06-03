#include<cstdio>
#include<vector>
using namespace std;
const double EPS=1e-9;
int N,F,S[100000];
bool Solve(const double &ave)
{
	static double sum[100001];
	sum[0]=0.0;
	for(int i=0;i<N;i++)sum[i+1]=sum[i]+(S[i]-ave);
	vector<int>deq;
	deq.push_back(0);
	for(int i=1,back=0;i<=N;i++)
	{
		if(sum[i]<sum[back])deq.push_back(back=i);
		else
		{
			int l=0,r=(int)deq.size();
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(sum[deq[mid]]<=sum[i])r=mid;
				else l=mid+1;
			}
			if(r<(int)deq.size()&&i-deq[r]>=F)return true;
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&F);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	double l=0.0,r=2000.0;
	while(r-l>EPS)
	{
		const double mid=0.5*(l+r);
		if(Solve(mid))l=mid;
		else r=mid;
	}
	printf("%d\n",(int)((0.5*(l+r)+EPS)*1000.0));
	return 0;
}
