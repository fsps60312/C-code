#include<bits/stdc++.h>
using namespace std;
int K,N,H[300000];
bool VIS[300000];
char T[300000];
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<=300000;i++)VIS[i]=0;
	while(scanf("%d%d",&N,&K)==2)
	{
		K--;
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		scanf("%s",T);
		int l,r,ans=0;
		for(l=K-1;l>=0&&H[l]==H[l+1];l--);l++;
		for(r=K+1;r<N&&H[r]<=H[r-1];r++);r--;
		ans=max(ans,r-l+1);
		for(r=K+1;r<N&&H[r]==H[r-1];r++);r--;
		for(l=K-1;l>=0&&H[l]<=H[l+1];l--);l++;
		ans=max(ans,r-l+1);
		
	}
	return 0;
}
