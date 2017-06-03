#include "reverse.h"
#include<algorithm>
std::vector<long long> reverse(const std::vector<long long> &a) {
	std::vector<long long>ans=a;
	reverse(ans.begin(),ans.end());
	return ans;
}

