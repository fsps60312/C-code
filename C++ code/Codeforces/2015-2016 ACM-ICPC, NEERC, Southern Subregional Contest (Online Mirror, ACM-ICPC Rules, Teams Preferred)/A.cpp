#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
int N;
map<string,vector<string> >S;
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&N)==1);
	for(int i=0;i<N;i++)
	{
		static char a[101],b[101];
		assert(scanf("%s",a)==1);
		int j=0,at=-1;
		bool ated=false;
		for(int i=0;a[i];i++)
		{
			if(!ated)
			{
				if(a[i]=='+')for(;a[i]!='@';i++);
				if(a[i]=='@')ated=true;
				else if(a[i]=='.')continue;
			}
			if(a[i]=='@')at=j;
			if(a[i]>='A'&&a[i]<='Z')b[j++]=a[i]-'A'+'a';
			else b[j++]=a[i];
		}
		b[j]='\0';
		static char special[11]="@bmail.com";
		bool found=true;
		for(int i=0;i<11;i++)if(special[i]!=b[at+i]){found=false;break;}
//		printf("@(%d)=%s\n",at,b+at);
		if(!found)
		{
//			printf("rebuild\n");
			j=0;
			//ated=false;
			for(int i=0;a[i];i++)
			{
//				if(!ated)
//				{
//					if(a[i]=='@')ated=true;
//					else if(a[i]=='.')continue;
//				}
				if(a[i]>='A'&&a[i]<='Z')b[j++]=a[i]-'A'+'a';
				else b[j++]=a[i];
			}
			b[j]='\0';
		}
//		printf("b=%s\n",b);
		S[b].push_back(a);
	}
	printf("%d\n",S.size());
	for(map<string,vector<string> >::iterator it=S.begin();it!=S.end();it++)
	{
		vector<string> &v=it->second;
		printf("%d",v.size());
		for(int i=0;i<v.size();i++)printf(" %s",v[i].c_str());
		puts("");
	}
	return 0;
}
