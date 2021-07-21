//小扣在秋日市集选择了一家早餐摊位，一维整型数组 `staple`
//中记录了每种主食的价格，一维整型数组 `drinks`
//中记录了每种饮料的价格。小扣的计划 选择一份主食和一款饮料，且花费不超过 `x`
//元。请返回小扣共有多少种购买方案。
//
//注意：答案需要以 `1e9 + 7 (1000000007)`
//为底取模，如：计算初始结果为：`1000000008`，请返回 `1`
//
//**示例 1：**
//>输入：`staple = [10,20,5], drinks = [5,5,2], x = 15`
//>
//>输出：`6`
//>
//>解释：小扣有 6 种购买方案，所选主食与所选饮料在数组中对应的下标分别是：
//>第 1 种方案：staple[0] + drinks[0] = 10 + 5 = 15；
//>第 2 种方案：staple[0] + drinks[1] = 10 + 5 = 15；
//>第 3 种方案：staple[0] + drinks[2] = 10 + 2 = 12；
//>第 4 种方案：staple[2] + drinks[0] = 5 + 5 = 10；
//>第 5 种方案：staple[2] + drinks[1] = 5 + 5 = 10；
//>第 6 种方案：staple[2] + drinks[2] = 5 + 2 = 7。
//
//**示例 2：**
//>输入：`staple = [2,1,1], drinks = [8,9,5,1], x = 9`
//>
//>输出：`8`
//>
//>解释：小扣有 8 种购买方案，所选主食与所选饮料在数组中对应的下标分别是：
//>第 1 种方案：staple[0] + drinks[2] = 2 + 5 = 7；
//>第 2 种方案：staple[0] + drinks[3] = 2 + 1 = 3；
//>第 3 种方案：staple[1] + drinks[0] = 1 + 8 = 9；
//>第 4 种方案：staple[1] + drinks[2] = 1 + 5 = 6；
//>第 5 种方案：staple[1] + drinks[3] = 1 + 1 = 2；
//>第 6 种方案：staple[2] + drinks[0] = 1 + 8 = 9；
//>第 7 种方案：staple[2] + drinks[2] = 1 + 5 = 6；
//>第 8 种方案：staple[2] + drinks[3] = 1 + 1 = 2；
//
//**提示：**
//+ `1 <= staple.length <= 10^5`
//+ `1 <= drinks.length <= 10^5`
//+ `1 <= staple[i],drinks[i] <= 10^5`
//+ `1 <= x <= 2*10^5` Related Topics 数组 双指针 二分查找 排序
// 👍 51 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <algorithm>
#include <vector>
using std::vector;

/// 前缀和+桶排序
class Solution {
 public:
  int breakfastNumber(vector<int>& staple, vector<int>& drinks, int x) {
    // 前缀和数组，记录 staple 价格 的食物数量的前缀和，按照价格从低到高排序
    vector<int> prefix_sum(x + 1, 0);
    // 桶排序，记录 staple 价格和数量
    for (int i = 0; i < staple.size(); ++i) {
      if (staple[i] <= x) {
        prefix_sum[staple[i]]++;
      }
    }

    // 计算前缀和
    for (int j = 1; j < prefix_sum.size(); ++j) {
      prefix_sum[j] += prefix_sum[j - 1];
    }
    // 使用 uint64 防止越界
    uint64_t res = 0;
    // 统计 drinks 数量
    for (int i = 0; i < drinks.size(); ++i) {
      if (drinks[i] <= x) {
        res += prefix_sum[x - drinks[i]];
      }
    }
    return res % (1000000007);
  }
};
// leetcode submit region end(Prohibit modification and deletion)
