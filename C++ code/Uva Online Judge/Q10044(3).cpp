#include<cstdio>
#include<map>
#include<string>
#include<vector>
//#include<cassert>
#include<queue>
using namespace std;
const int STRLEN=10000000;
void assert(bool valid){if(valid)return;while(1)puts("E");}
int T,P,N;
char LINE[STRLEN];
map<string,int>IDX;
vector<int>ERDO;
vector<bool>INQ;
vector<vector<int> >ET;
int GetIdx(const string &s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		ERDO.push_back(-1);
		ET.push_back(vector<int>());
		INQ.push_back(false);
		return IDX[s]=sz;
	}
	return IDX[s];
}
void fgets()
{
	fgets(LINE,STRLEN,stdin);
	int i=-1;while(LINE[++i])assert(i<STRLEN);i--;
	if(LINE[i]=='\n')LINE[i]='\0';
}
int main()
{
//	freopen("in.txt","r",stdin);
	fgets();
	assert(sscanf(LINE,"%d",&T)==1);
	while(T--)
	{
		fgets();
		assert(sscanf(LINE,"%d%d",&P,&N)==2);
		IDX.clear(),ERDO.clear(),ET.clear(),INQ.clear();
		GetIdx("Erdos, P.");
		for(int i=0;i<P;i++)
		{
			fgets();
			int idx=0;
			vector<int>v;
			int b=-1;
			for(int i=0;;)
			{
				assert(i<STRLEN);
				while(LINE[idx]==' ')idx++;i=idx;
				while(LINE[i]!=' '&&LINE[i-1]!=':')i++;
				char c=LINE[i-1];
				if(c==':')goto bookname;
				while(LINE[i]==' ')i++;
				while(LINE[i]!=' '&&LINE[i-1]!=':')i++;
				c=LINE[i-1];LINE[i-1]='\0';
//				printf("s=\"%s\"\n",LINE+idx);
				v.push_back(GetIdx(LINE+idx));
				bookname:;
				idx=i;
				if(c==':')
				{
					while(LINE[idx]==' ')idx++;
					b=GetIdx(LINE+idx);
//					printf("b=\"%s\"\n",LINE+idx);
					break;
				}
			}
			assert(b!=-1);
			for(int i=0;i<v.size();i++)
			{
				ET[b].push_back(v[i]);
				ET[v[i]].push_back(b);
			}
		}
		queue<int>q;
		q.push(0);
		INQ[0]=true;
		ERDO[0]=0;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			INQ[u]=false;
			for(int &i:ET[u])
			{
				if(ERDO[i]==-1||ERDO[u]+1<ERDO[i])
				{
					ERDO[i]=ERDO[u]+1;
					if(!INQ[i])
					{
						q.push(i);
						INQ[i]=true;
					}
				}
			}
		}
//		int sz=IDX.size();
//		printf("sz=%d\n",sz);
//		for(auto &p:IDX)printf("%d:%s\n",p.second,p.first.c_str());
		static int kase=1;
		printf("Scenario %d\n",kase++);
		for(int i=0;i<N;i++)
		{
			fgets();
			printf("%s ",LINE);
			if(IDX.find(LINE)==IDX.end()||ERDO[IDX[LINE]]==-1)puts("infinity");
			else printf("%d\n",ERDO[IDX[LINE]]>>1);
		}
	}
	return 0;
}
