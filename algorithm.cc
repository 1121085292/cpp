#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> res;
    res.resize(m+n);
    int i = 0, j = 0, k = 0;
    while(i < m || j < n){
      if(i == m){
        res[k++] = nums2[j++];
      } else if(j == n){
        res[k++] = nums1[i++];
      } else if(nums1[i] <= nums2[j]) {
            res[k++] = nums1[i++];
        } else {
            res[k++] = nums2[j++];
        } 
    }
    for(const auto& val : res){
    std::cout << "val: " << val << std::endl;
  }
    // nums1 = res;
}

int main(){
  vector<int> nums1 = {1,2,3,0,0,0};
  vector<int> nums2 = {2,5,6};
  int m = 3, n = 3;
  merge(nums1, m, nums2, n);
  // for(const auto& val : nums1){
  //   std::cout << "val: " << val << std::endl;
  // }
}