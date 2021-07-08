//给你一个由若干括号和字母组成的字符串 s
//，删除最小数量的无效括号，使得输入的字符串有效。
//
// 返回所有可能的结果。答案可以按 任意顺序 返回。
//
//
//
// 示例 1：
//
//
//输入：s = "()())()"
//输出：["(())()","()()()"]
//
//
// 示例 2：
//
//
//输入：s = "(a)())()"
//输出：["(a())()","(a)()()"]
//
//
// 示例 3：
//
//
//输入：s = ")("
//输出：[""]
//
//
//
//
// 提示：
//
//
// 1 <= s.length <= 25
// s 由小写英文字母以及括号 '(' 和 ')' 组成
// s 中至多含 20 个括号
//
// Related Topics 广度优先搜索 字符串 回溯
// 👍 459 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <string>
#include <vector>
using std::string;
using std::vector;

/// 回溯 + 剪枝
class Solution {
 public:
  vector<string> ans;  //此时不会重复搜索 无重复方案 直接存即可
  void dfs(string &s, int u, string res, int cnt, int l,
           int r) {
    // cnt 为当前[左-右]的值 l 为需要删除的左括号数量 r 为右
    if (u == s.size()) {
      if (!cnt) ans.push_back(res);
      return;
    }
    if (s[u] == '(') {  //在合法的条件下考虑删除 对于连续的k个'(' 只需考虑一次性
                        //删 i个(0<=i<=k) 则可从2^k降到 k
      int k = u;
      while (k < s.size() && s[k] == '(') k++;  //找到最后一个连续的'('的右边
      l -= k - u;  //假设将这些连续的'('全部删除
      for (int i = k - u; i >= 0; i--) {        // i为删除后的位置
        if (l >= 0) dfs(s, k, res, cnt, l, r);  //可删时
        res += '(', cnt++, l++;
      }
    } else if (s[u] == ')') {  //在合法的条件下考虑删除
      int k = u;
      while (k < s.size() && s[k] == ')') k++;  //找到最后一个连续的'('的右边
      r -= k - u;  //假设将这些连续的'('全部删除
      for (int i = k - u; i >= 0; i--) {  // i为删除后的位置
        if (cnt >= 0 && r >= 0) dfs(s, k, res, cnt, l, r);  //可删时
        res += ')', cnt--, r++;
      }
    } else
      dfs(s, u + 1, res + s[u], cnt, l, r);
  }
  vector<string> removeInvalidParentheses(string s) {
    int l = 0, r = 0;  // l为当前左括号-右括号的值 r为需要删掉的右括号的值
    for (auto v : s) {
      if (v == '(')
        l++;
      else if (v == ')') {
        if (l <= 0)
          r++;  //此时无效 右括号 必删
        else
          l--;  //右括号+1 则左-右的值需要--
      }
    }
    //此时的l为需要删除的左括号数量 r为需要删除的右括号数量
    dfs(s, 0, "", 0, l, r);
    return ans;
  }
};
// leetcode submit region end(Prohibit modification and deletion)
