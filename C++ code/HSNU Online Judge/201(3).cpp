#include<bits/stdc++.h>
using namespace std;
int K,N,H[300000];
bool VIS[300000];
char T[300000];
struct Building{int h,cnt,t,sum;};
vector<Building>B;
int Sum(int l,int r){return B[r].sum-(l?B[l-1].sum:0);}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		K--;
		B.clear();
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		scanf("%s",T);
		for(int i=0,j;i<N;)
		{
			Building b;
			b.h=H[i];
			b.t=b.cnt=0;
			for(j=i;j<N&&H[j]==H[i];j++,b.cnt++)b.t|=(T[j]=='T');
			b.sum=j;
			B.push_back(b);
			i=j;
		}
		for(int i=0;i<B.size();i++)if(K<B[i].sum){K=i;break;}
		int l,r,ans=0,texist=B[K].t;
		for(r=K+1;r<B.size()&&B[r].h<B[r-1].h;r++)texist|=B[r].t;r--;
		ans=max(ans,Sum(K,r));
		for(l=K-1;l>=0&&B[l].h<B[l+1].h;l--)texist|=B[l].t;l++;
		ans=max(ans,Sum(l,K));
		if(texist)
		{
			int mx=0;
			for(int i=0;i<B.size();i++)VIS[i]=false;
			for(int i=0,j;i<B.size();i++)
			{
				if(B[i].t)
				{
					VIS[i]=true;
					for(j=i-1;j>=0&&B[j].h>B[j+1].h;j--)VIS[j]=true;
					for(j=i+1;j<B.size()&&B[j].h>B[j-1].h;j++)VIS[j]=true;
				}
			}
			for(int i=0,j;i<B.size();i++)
			{
				if(B[i].t)
				{
					for(j=i-1;j>=0&&!VIS[j]&&B[j].h<B[j+1].h;j--);j++;mx=max(mx,Sum(j,i-1));
					for(j=i+1;j<B.size()&&!VIS[j]&&B[j].h<B[j-1].h;j++);j--;mx=max(mx,Sum(i+1,j));
				}
				else if(!VIS[i]&&(i==0||B[i-1].h<B[i].h)&&(i==B.size()-1||B[i+1].h<B[i].h))
				{
					for(j=i-1;j>=0&&!VIS[j]&&B[j].h<B[j+1].h;j--);j++;mx=max(mx,Sum(j,i));
					for(j=i+1;j<B.size()&&!VIS[j]&&B[j].h<B[j-1].h;j++);j--;mx=max(mx,Sum(i,j));
				}
			}
			int ta=0;
			for(int i=0;i<B.size();i++)if(VIS[i])ta+=B[i].cnt;
			ans=max(ans,ta+mx);
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}
