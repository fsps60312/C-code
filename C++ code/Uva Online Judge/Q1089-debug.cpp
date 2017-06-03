#include <stdio.h> 
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;

const int MAXS = 25;
const int MAXR = 105;
const int MAXN = 512;
map<string, int> IDX[MAXS];
vector<string> RI[MAXS];
set< pair<string, string> > RULE;
void addNode(string s)
{
	int len = s.length(), label;
	if (!IDX[len].count(s))
	{
		label = IDX[len].size();
		IDX[len][s] = label;
		RI[len].push_back(s);
		assert(label < MAXN);
	}
}
long long DIST[MAXN][MAXN], preDIST[MAXN][MAXN];
const long long INF = 1LL<<61;
int main()
{
	freopen("in.txt","r",stdin);
	string A, B, x, y;
	int M, N, cases = 0;
	while (cin >> A >> B >> M)
	{
		if (A == ".")return 0;
		RULE.clear();
		for(int i=0;i<MAXS;i++)IDX[i].clear(),RI[i].clear();
		for (int i=0;i<M;i++)
		{
			cin >> x >> y;
			RULE.insert(make_pair(x, y));
			for (int j = 0; j < x.length(); j++)
			{
				string s1=x.substr(j),s2=y.substr(j);
				addNode(s1),addNode(s2);
			}
		}
		
		N = A.length();
		for (int i = 0; i < N; i++)
		{
			string s1 = A.substr(i), s2 = B.substr(i);
			addNode(s1), addNode(s2);
		}
		
		for (int len = 1; len <= N; len++)
		{
			int sz = IDX[len].size();
			for (int i = 0; i < sz; i++)
			{
				for (int j = 0; j < sz; j++)
				{
					if (i == j){DIST[i][j] = 0;continue;}
					else
					{
						DIST[i][j] = INF;
						if (RULE.count(make_pair(RI[len][i],RI[len][j])))DIST[i][j]=1LL;
						if (len > 1 && RI[len][i][0] == RI[len][j][0])
						{ // node Aaaaaa -> Abbbbb, cost aaaaa -> bbbbb
							int pi = IDX[len-1][RI[len][i].substr(1)];
							int pj = IDX[len-1][RI[len][j].substr(1)];
							DIST[i][j] = min(DIST[i][j], preDIST[pi][pj]);
						}
					}
				}
			}
			
			// floyd algorithm
			for (int k = 0; k < sz; k++) 
				for (int i = 0; i < sz; i++)
					for (int j = 0; j < sz; j++)
						DIST[i][j] = min(DIST[i][j], DIST[i][k] + DIST[k][j]);
			
			// copy for next loop
			for (int i = 0; i < sz; i++)
				for (int j = 0; j < sz; j++)
					preDIST[i][j] = DIST[i][j];
		}
		int st = IDX[N][A], ed = IDX[N][B];
		printf("Case %d: ", ++cases);
		if (DIST[st][ed] >= INF)printf("No solution\n");
		else printf("%lld\n", DIST[st][ed]);
	}
	return 0;
}
/*
AAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBB 20
ABBBBBBBBBBBBBBBBBBB BAAAAAAAAAAAAAAAAAAA
ABBBBBBBBBBBBBBBBBB  BAAAAAAAAAAAAAAAAAA 
ABBBBBBBBBBBBBBBBB   BAAAAAAAAAAAAAAAAA  
ABBBBBBBBBBBBBBBB    BAAAAAAAAAAAAAAAA   
ABBBBBBBBBBBBBBB     BAAAAAAAAAAAAAAA    
ABBBBBBBBBBBBBB      BAAAAAAAAAAAAAA     
ABBBBBBBBBBBBB       BAAAAAAAAAAAAA      
ABBBBBBBBBBBB        BAAAAAAAAAAAA       
ABBBBBBBBBBB         BAAAAAAAAAAA        
ABBBBBBBBBB          BAAAAAAAAAA         
ABBBBBBBBB           BAAAAAAAAA          
ABBBBBBBB            BAAAAAAAA           
ABBBBBBB             BAAAAAAA            
ABBBBBB              BAAAAAA             
ABBBBB               BAAAAA              
ABBBB                BAAAA               
ABBB                 BAAA                
ABB                  BAA                 
AB                   BA                  
A                    B   
*/
