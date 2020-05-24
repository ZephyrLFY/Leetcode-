#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int,int>> h;
        multiset<int> m; //自带排序，本题关键
        vector<vector<int>> res;

        //1、将每一个建筑分成“两个部分”，例如:[2,9,10]可以转换成[2，-10][9,10]，我们用负值来表示左边界
        for(const auto& b : buildings)
        {
            h.push_back(make_pair(b[0], -b[2]));
            h.push_back(make_pair(b[1], b[2]));
        }

        //2、根据x值对分段进行排序
        sort(h.begin(),h.end());
        int pre = 0, cur = 0;
        m.insert(0);

        //3、遍历
        for (auto i : h)
        {
            if (i.second < 0) m.insert(-i.second);  //左端点，高度入堆
            else m.erase(m.find(i.second));         //右端点，高度出堆
            cur = *m.rbegin();                      //当前最大高度高度
            if (cur != pre) {                      //当前最大高度不等于最大高度perv表示这是一个转折点
                res.push_back({i.first, cur});      //添加坐标
                pre = cur;                         //更新最大高度
            }
        }
        return res;
    }
};