/*
 * @lc app=leetcode.cn id=81 lang=cpp
 *
 * [81] 搜索旋转排序数组 II
 */

//已知存在一个按非降序排列的整数数组 nums ，数组中的值不必互不相同。
//
// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了
// 旋转 ，使数组变为 [nums[k], nums
//[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始
//计数）。例如， [0,1, 2,4,4,4,5,6,6,7] 在下标 5 处经旋转后可能变为
// [4,5,6,6,7,0,1,2,4,4] 。
//
// 给你 旋转后 的数组 nums 和一个整数 target
// ，请你编写一个函数来判断给定的目标值是否存在于数组中。如果 nums
// 中存在这个目标值 targ
// et ，则返回 true ，否则返回 false 。
//
//
//
// 示例 1：
//
//
//输入：nums = [2,5,6,0,0,1,2], target = 0
//输出：true
//
//
// 示例 2：
//
//
//输入：nums = [2,5,6,0,0,1,2], target = 3
//输出：false
//
//
//
// 提示：
//
//
// 1 <= nums.length <= 5000
// -104 <= nums[i] <= 104
// 题目数据保证 nums 在预先未知的某个下标上进行了旋转
// -104 <= target <= 104
//
//
//
//
// 进阶：
//
//
// 这是 搜索旋转排序数组 的延伸题目，本题中的 nums 可能包含重复元素。
// 这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？
//
// Related Topics 数组 二分查找
// 👍 443 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <vector>
using std::vector;

/// 二分法
class Solution {
 public:
  bool search(vector<int>& nums, int target) {
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
      } else if (nums[m] < nums[r]) {
        r = m;
      } else {
        // nums[m] == nums[r]
        // 实际上，当出现 nums[m] = nums[r] 时，一定有区间 [i, m]
        // 内所有元素相等 或 区间 [m, r]
        // 内所有元素相等（或两者皆满足）。
        // [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]
        // 2
        // [2,2,2,3,2,2,2]
        // 3
        for (int i = l + 1; i <= r; ++i) {
          if (nums[i] < nums[i - 1]) l = i;
        }
        break;
      }
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
        return true;
    }
    return false;
  }
};
// leetcode submit region end(Prohibit modification and deletion)
