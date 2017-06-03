#include<cstdio>
int T,VIS[27],TO[26];//,FROM[26];
char S[27];
bool dfs(int idx)
{
	for(;;idx++)
	{
		if(!(VIS[idx]&1))break;
		int i=TO[idx];
		if(VIS[i]&1)
		{
			if(TO[i]!=S[idx])return false;
		}
		else if(VIS[S[idx]]&2)
		{
			printf("error\n");
			return false;
		}
		else
		{
			VIS[i]|=1;
			VIS[S[idx]]|=2;
			bool ans=dfs(idx+1);
			VIS[i]|=~1;
			VIS[S[idx]]|=~2;
			return ans;
		}
	}
	if(idx==26)return true;
	VIS[idx]|=1;
	VIS[S[idx]]|=2;
	for(int i=0;i<26;i++)
	{
		if(i==idx)continue;
		if(!(VIS[i]&2))
		{
			VIS[i]|=2;
			TO[idx]=i;
//			FROM[i]=idx;
			if(!(VIS[i]&1))
			{
				VIS[i]|=1;
				TO[i]=S[idx];
//				FROM[S[idx]]=i;
				if(dfs(idx+1))return true;
				VIS[i]|=~1;
			}
			else if(TO[i]==S[idx])if(dfs(idx+1))return true;
			VIS[i]|=~2;
		}
	}
	VIS[idx]|=~1;
	VIS[S[idx]]|=~2;
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	VIS[26]=0;
	while(T--)
	{
		scanf("%s",S);
		for(int i=0;i<26;i++)
		{
			S[i]-='A';
			if(S[i]==i)VIS[i]=3,TO[i]=i;
			else VIS[i]=0;
		}
		printf(dfs(0)?"Yes\n":"No\n");
		for(int i=0;i<26;i++)printf(" %d",TO[i]);puts("");
	}
	return 0;
}
