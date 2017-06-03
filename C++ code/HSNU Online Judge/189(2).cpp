#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
struct MinPair//query max between min values of pairs
{
	map<int,int>DATA[2];
	int bc_dis[2],c[2];
	vector<int>bc[2];//values for B+C-bc_dis
	void clear(){for(int d=0;d<2;d++)DATA[d].clear(),bc_dis[d]=c[d]=0,bc[d].clear();}
	void AddB(const int _d){bc_dis[_d]++;}//all values of B+C add 1
	void AddC(const int _d)
	{
		bc[_d].push_back((++c[_d])-bc_dis[_d]);
		if(bc[_d].size()<=bc[_d^1].size())//a new pair is available
		{
			const int i=(int)bc[_d].size()-1;
			for(int d=0;d<=1;d++)
			{
				//if d=0, take effect when bc0-bc1<=dif, the max of min values become bc0+bc_dis0
				const int dif=bc[d][i]-bc[d^1][i];
				const int val=bc[d][i];
				auto it=DATA[d].lower_bound(dif);//query the max before val insert to dif
				if(it==DATA[d].end()||(it->second)<val)//the val is useful when at dif
				{//since val increases the max value at current dif
					it=DATA[d].upper_bound(dif);
					//check if those x<dif become worse case after val insert to dif
					vector<int>to_erase;
					while(it!=DATA[d].begin()&&((--it)->second)<=val)to_erase.push_back(it->first);
					for(const int &tmp:to_erase)DATA[d].erase(tmp);
					DATA[d][dif]=val; 
				}
			}
		}
	}
	int GetMaxMinValue(){return max(GetMaxMinValue(0),GetMaxMinValue(1));}
	int GetMaxMinValue(const int _d)
	{
		const int dif=bc_dis[_d]-bc_dis[_d^1];
		const auto it=DATA[_d].lower_bound(dif);
		if(it==DATA[_d].end())return 0;
		return (it->second)+bc_dis[_d];
	}
}MP;
char S[2][200001];
int N[2];
stack<int>A[2];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%s%s",S[0],S[1]);
		for(int d=0;d<=1;d++){while(!A[d].empty())A[d].pop();A[d].push(-1);}
		for(int d=0;d<=1;d++)for(int &i=N[d]=0;S[d][i];i++)if(S[d][i]=='A')A[d].push(i);
		for(int d=0;d<=1;d++)while(A[d].size()>A[d^1].size())A[d].pop();
		int ans=-INF;
		MP.clear();
		for(int i[2]={N[0]-1,N[1]-1};!A[0].empty();)
		{
			for(int d=0;d<=1;d++)
			{
				while(i[d]>A[d].top())
				{
					switch(S[d][i[d]])
					{
						case'B':MP.AddB(d);break;
						case'C':MP.AddC(d);break;
						default:
//							assert(0);
							break;
					}
					i[d]--;
				}
				A[d].pop(),i[d]--;
			}
			assert(A[0].size()==A[1].size());
			ans=max(ans,(int)A[0].size()+MP.GetMaxMinValue());
		}
		printf("%d\n",ans);
	}
	return 0;
}
