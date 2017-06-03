#include<cstdio>
#include<cstdlib>
int T,N,K,B,R;
int count () {
    int c = 0;
    for (int i = 0; i < B; i++) {
        if (X[i] != M && !bset.count(make_pair(X[i]+1, Y[i])))
        //(X[i]+1,Y[i]) can fill K-1 colors
            c++;
    }

    c += N;//on the last row
    for (int i = 0; i < B; i++)
        if (X[i] == 1)
            c--;
	//c=B.count+N-sum{X==1||X==M}
	//c is the sum of areas that seperated by uncolored blocks
    return mul_mod(pow_mod(K, c), pow_mod(K-1, (ll)M*N-B-c));
    //mod:
    //K^c*(K-1)^(M*N-B-c)
    //K^c: each area, the first color can print chaos
    //(K-1)^(M*N-B-c): each block remaining can print K-1 colors
}
int doit () {
    int cnt = count();

    if (cnt == R)
        return M;//M is the answer

    int c = 0;
    for (int i = 0; i < B; i++)
        if (X[i] == M)
            c++;
    //c is how many uncolored blocks are on the last row

    M++;
    cnt = mul_mod(cnt, pow_mod(K, c));
    cnt = mul_mod(cnt, pow_mod(K-1, N-c));
    //mod:
    //cnt*K^c*(K-1)^(N-c)

    if (cnt == R)
        return M;

    return log_mod(pow_mod(K-1, N), mul_mod(R, inv(cnt))) + M;
    //a is base, b is 
}
//╯俱ぱ祘Α沧程˙玱或ぃ来糶ぐ或琌酚帝稱猭恶干Ч逞祘Α絏眔TLE==
//硂┏琌ぐ或狥﹁???
//goal: query (A,B)
//initial: gcd(A,B,d,x,y)
void gcd(long long a,long long b,long long &d, long long &x,long long &y)
{
	if(b==0)
	{
		d=a;//(A,B)==d
		x=1;//WHY??
		y=0;//WHY??
	}
	else
	{
		gcd(b,a%b,d,y,x);
		y-=x*(a/b);
		//if(a%b==0) -> d==b,y==1,x==0
		//then x==0,y==1
		//d is always (A,B)
		//y==0,x==1
		//then ......
	}
}
inline ll inv (ll a) {
    ll d, x, y;
    gcd(a, MOD, d, x, y);
    //d:(a,MOD)
    //x:an integer make x*a%MOD==1
    return d == 1 ? (x+MOD)%MOD : -1;
    //if(a,MOD)==1: (x+MOD)%MOD
    //else -1
}
int log_mod (ll a, ll b) {//a is base
    ll m = (ll)sqrt(MOD+0.5), v, e = 1;
    //m: sqrt(MOD)
    //e: 1
    //v: v*a^m%MOD==1
    v = inv(pow_mod(a, m));
    map<ll, ll> g;
    g[1] = 0;//a^0==1
    for (ll i = 1; i < m; i++) {
        e = mul_mod(e, a);
        if (!g.count(e))
            g[e] = i;//a^i==e
    }
    //a^g[e]==e
    //to solve: a^x==b
    for (ll i = 0; i < m; i++) {
        if (g.count(b))
            return i*m+g[b];//a^g[b]==b
        //v*a^m%MOD==1
        b = mul_mod(b, v);
    }
    return -1;
}
int main()
{
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d%d",&N,&K,&B,&R);
		for(int i=0,j,k;i<B;i++)
		{
			scanf("%d%d",&j,&k);
		}
	}
	return 0;
}
