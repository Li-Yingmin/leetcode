/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */

//实现获取 下一个排列
//的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
//
// 如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
//
// 必须 原地 修改，只允许使用额外常数空间。
//
//
//
// 示例 1：
//
//
//输入：nums = [1,2,3]
//输出：[1,3,2]
//
//
// 示例 2：
//
//
//输入：nums = [3,2,1]
//输出：[1,2,3]
//
//
// 示例 3：
//
//
//输入：nums = [1,1,5]
//输出：[1,5,1]
//
//
// 示例 4：
//
//
//输入：nums = [1]
//输出：[1]
//
//
//
//
// 提示：
//
//
// 1 <= nums.length <= 100
// 0 <= nums[i] <= 100
//
// Related Topics 数组
// 👍 1161 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <algorithm>
#include <vector>
using std::vector;

/// 数论 + 排序
// 使用两趟扫描，第一趟 [4,5,2,6,3,1] 从右向左找到第一个 a[i] < a[i+1]
// 的元素，即 a[2] = 2；此时 a[i+1...] 一定为降序序列
// 第二趟 从右向左找到第一个满足 a[j] > a[i] 的元素 a[j]；即 a[4] = 3；
// swap(a[i], a[j]) ：[4,5,3,6,2,1]，此时 a[i+1...] 仍是降序序列；
// 将 a[i+1...] 反转，即得到下一个排列：[4,5,3,1,2,6]
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    // i 将指向第一个 a[i] < a[i+1]
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      i--;
    }
    // 如果 i < 0，说明序列已经是最大序列，直接反转即可
    if (i >= 0) {
      int j = nums.size() - 1;
      // j 指向 a[i] < a[j]
      while (j >= 0 && nums[i] >= nums[j]) {
        j--;
      }
      std::swap(nums[i], nums[j]);
    }
    // 反转 a[i+1...]
    std::reverse(nums.begin() + i + 1, nums.end());
  }
};
// leetcode submit region end(Prohibit modification and deletion)
