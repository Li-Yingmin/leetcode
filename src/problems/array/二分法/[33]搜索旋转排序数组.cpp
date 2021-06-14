/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */

//整数数组 nums 按升序排列，数组中的值 互不相同 。
//
// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了
// 旋转，使数组变为 [nums[k], nums[
// k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始
// 计数）。例如， [0,1,2 ,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2]
//。
//
// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target
// ，则返回它的下标，否则返回 -1 。
//
//
//
// 示例 1：
//
//
//输入：nums = [4,5,6,7,0,1,2], target = 0
//输出：4
//
//
// 示例 2：
//
//
//输入：nums = [4,5,6,7,0,1,2], target = 3
//输出：-1
//
// 示例 3：
//
//
//输入：nums = [1], target = 0
//输出：-1
//
//
//
//
// 提示：
//
//
// 1 <= nums.length <= 5000
// -10^4 <= nums[i] <= 10^4
// nums 中的每个值都 独一无二
// 题目数据保证 nums 在预先未知的某个下标上进行了旋转
// -10^4 <= target <= 10^4
//
//
//
//
// 进阶：你可以设计一个时间复杂度为 O(log n) 的解决方案吗？
// Related Topics 数组 二分查找
// 👍 1399 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <vector>
using std::vector;

/// 二分法
// 此题和 lcof-11 类似
// 由于数组被划分为两个有序端，左端所有元素应该 >= 右端最大值 num[r]
// 二分思路：记左侧为 l， 右侧位 r，二分中点为 mid，[l...r]
// 1. 如果 nums[mid] > nums[r], 则 mid 一定属于左端序列，因此 l = mid + 1
// 2. 如果 nums[mid] < nums[r], 则 mid 一定属于右端序列，因此 r = mid, [l...r]
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    // [l...r]
    // 循环结束后
    // 1.如果没有发生旋转，l 指向 0
    // 2.发生旋转，nums[l] 为右侧起点
    while (l < r) {
      int m = l + (r - l) / 2;
      if (nums[m] > nums[r]) {
        l = m + 1;
      } else
        r = m;
    }
    // 默认从左端序列 [0...l-1] 找
    int left = 0, right = l - 1;
    r = nums.size() - 1;
    // 如果没有发生旋转 或者 target <= nums[r]
    if (l == 0 || target <= nums[r]) {
      // 从整个序列 [l...r] 寻找 target
      // 从右端序列 [l...r] 寻找 target
      left = l, right = r;
    }
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else
        return mid;
    }
    return -1;
  }
};
// leetcode submit region end(Prohibit modification and deletion)
