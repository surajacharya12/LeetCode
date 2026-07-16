class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        for (int mx = 0; int& x : nums) x = gcd(x, mx = max(mx, x)); 
        ranges::sort(nums);
        return transform_reduce(  
            nums.begin(), nums.begin() + nums.size() / 2,
            nums.rbegin(), 0LL, plus{},
            [](long long a, long long b) { return gcd(a, b); }
        );
    }
};