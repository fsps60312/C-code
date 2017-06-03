#include<cstdio>
int T,VIS[27],TO[26],FROM[26];
char S[27];
bool canbuild(int a,int b,int &t)
{
	if(VIS[a]&1)
	{
		if(TO[a]!=b)
		{
			t=-1;
			return false;
		}
		t=1;
		return true;
	}
	else if(VIS[b]&2)
	{
		t=-1;
		return false;
	}
	t=0;
	TO[a]=b;
	FROM[b]=a;
	VIS[a]|=1,VIS[b]|=2;
	return true;
}
void unbuild(int a,int b,int &t)
{
	if(t)return;
	VIS[a]&=~1,VIS[b]&=~2;
}
bool dfs(int idx)
{
	int t1,t2;
	for(int b1;VIS[idx]&1;idx++)
	{
		b1=canbuild(TO[idx],S[idx],t1);
		unbuild(TO[idx],S[idx],t1);
		if(!b1)return false;
	}
	if(idx==26)return true;
//	if(VIS[S[idx]]&2)
//	{
//		if(canbuild(idx,FROM[S[idx]],t1)&&dfs(idx+1))return true;
//		unbuild(idx,FROM[S[idx]],t1);
//		return false;
//	}
	for(int i=0,b1,b2;i<26;i++)
	{
		b1=canbuild(idx,i,t1),b2=canbuild(i,S[idx],t2);
		if(b1&&b2&&dfs(idx+1))return true;
		unbuild(idx,i,t1);
		unbuild(i,S[idx],t2);
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	VIS[26]=0;
	while(T--)
	{
		scanf("%s",S);puts(S);
		for(int i=0;i<26;i++)
		{
			S[i]-='A';
			if(S[i]==i)VIS[i]=3,TO[i]=i,FROM[i]=i;
			else VIS[i]=0;
		}
		printf(dfs(0)?"Yes\n":"No\n");
		for(int i=0;i<26;i++)printf("%c",'A'+i);puts("");
		for(int i=0;i<26;i++)printf("%c",'A'+TO[i]);puts("");
		for(int i=0;i<26;i++)printf(" %d",VIS[i]);puts("");puts("");
	}
	return 0;
}
