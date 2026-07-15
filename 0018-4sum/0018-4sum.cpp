class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        sort(arr.begin(),arr.end());
        int n=arr.size();
        vector<vector<int>> ans;
        for(int i=0;i<n-3;i++){
            if(i > 0 && arr[i] == arr[i-1]) continue;
            for(int j=i+1;j<n-2;j++){
                if(j>i+1 && arr[j] == arr[j-1]) continue;
                long long sum=(long long)target-(long long)(arr[i]+arr[j]);
                int start=j+1;
                int end=n-1;
                while(start<end){
                    if(arr[start]+arr[end]==sum){
                        vector<int> temp{arr[i],arr[j],arr[start],arr[end]};
                        ans.push_back(temp);
                        start++;
                        end--;
                        while(start<end && arr[start]==arr[start-1]) start++;
                        while(start<end && arr[end]==arr[end+1]) end--;
                    }
                    else if(arr[start]+arr[end]<sum) start++;
                    else end--;
                }
            }
        }
        return ans;
    }
};