#include<cstdio>
int N,S;
int V[100000];
void getmin(int &a,int b){if(b<a)a=b;}
int main()
{
	while(scanf("%d%d",&N,&S)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&V[i]);
		int ans=2147483647,s=0,l=0,r;
		for(r=0;r<N;r++)
		{
			s+=V[r];
			while(s-V[l]>=S)s-=V[l++];
			if(s>=S)getmin(ans,r-l+1);
		}
		printf("%d\n",ans==2147483647?0:ans);
	}
	return 0;
}
