#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int T;
vector<int>Plus(const vector<int>&a,const vector<int>&b)
{
	vector<int>ans;
	for(int i=0;i<max(a.size(),b.size());i++)ans.push_back(0);
	for(int i=0;i<a.size();i++)ans[i]+=a[i];
	for(int i=0;i<b.size();i++)ans[i]+=b[i];
	for(int i=(int)ans.size()-1;i>=0&&ans[i]==0;i--)ans.pop_back();
	return ans;
}
vector<int>Mul(const vector<int>&a,const vector<int>&b)
{
	vector<int>ans;
	for(int i=0;i<(int)a.size()+(int)b.size()-1;i++)ans.push_back(0);
	for(int i=0;i<a.size();i++)for(int j=0;j<b.size();j++)ans[i+j]+=a[i]*b[j];
	for(int i=(int)ans.size()-1;i>=0&&ans[i]==0;i--)ans.pop_back();
	return ans;
}
vector<int>GetNumber()
{
	static char tmp[1000000];assert(scanf("%s",tmp)==1);
	vector<int>ans;
	if(tmp[0]=='n')
	{
		assert(tmp[1]=='\0');
		ans.push_back(0),ans.push_back(1);
	}
	else
	{
		for(int i=0;tmp[i];i++)assert(i<=9&&tmp[i]>='0'&&tmp[i]<='9');
		static int v;assert(sscanf(tmp,"%d",&v)==1);
		if(v!=0)ans.push_back(v);
	}
	return ans;
}
void Check(const char *a,const char *b)
{
	for(int i=0;;i++)
	{
		if(a[i]!=b[i])assert(0);
		if(!a[i])return;
	}
}
vector<int>Dfs(const int dep)
{
	static char command[1000000];
	vector<int>ans;
	for(;;)
	{
		assert(scanf("%s",command)==1);
		if(command[0]=='E'){Check(command,"END");return ans;}
		else if(command[0]=='O')Check(command,"OP"),ans=Plus(ans,GetNumber());
		else if(command[0]=='L')
		{
			Check(command,"LOOP");
			const auto tmp=GetNumber();
			ans=Plus(ans,Mul(tmp,Dfs(dep+1)));
		}
		else printf("\"%c\"\n",command[0]),assert(0);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		static char command[1000000];
		assert(scanf("%s",command)==1);
		Check(command,"BEGIN");
		vector<int>ans=Dfs(0);
		static int kase=1;
		printf("Program #%d\nRuntime = ",kase++);
		bool printed=false;
		for(int i=(int)ans.size()-1;i>=0;i--)if(ans[i])
		{
			if(ans[i]>0&&printed)putchar('+');
			else if(ans[i]<0)putchar('-');
			if(abs(ans[i])!=1||i==0)
			{
				printf("%d",abs(ans[i]));
				if(i>=1)putchar('*');
			}
			if(i>=2)printf("n^%d",i);
			else if(i==1)printf("n");
			printed=true;
		}
		puts(printed?"":"0");
		puts("");
	}
	return 0;
}
