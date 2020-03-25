#include "code.h"
#include <vector>
#include "gtest/gtest.h"

#include <map>
#include <utility>
#include <limits.h>

using namespace std;

void call_code_296(){}

class Solution_296 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if (grid.size() <= 0)
        {
            return 0;
        }

        // 1. 从矩阵中心出发，检查周边八个格子的距离，取最小距离
        // 2. 迭代向最小距离移动，每次检查周边八个格子的距离
        // 3. 直到周边八个格子距离都比中心点大，则此为矩阵质心

        // 计算矩阵中心
        pair<int, int> gridCenter;
        gridCenter.first = (grid.size() % 2 == 0) ? (grid.size() / 2) : (grid.size() / 2 + 1);
        gridCenter.second = (grid[0].size() % 2 == 0) ? (grid[0].size() / 2) : (grid[0].size() / 2 + 1);

        // 逐渐向质心移动
        pair<int, int> center;
        center = gridCenter;
        for (int i = 0; i < gridCenter.first + gridCenter.second; i++) 
        {
            auto newCenter = FindCenter(center, grid);
            if (newCenter == center)
            {
                return m_knownDistance[center];
            }
            else
            {
                center = newCenter;
            }
        }

        // 到这里就出错了
        cout << "Error! can't find center." << endl;
        return 0;
    }




private:
    map<pair<int,int>, int> m_knownDistance;  //用来记录所有计算过的距离，避免重复计算

    /**
     * 传入一个中心点，计算周边八个点的距离，以及自己的距离，然后返回距离最小那个点
     */
    pair<int, int> FindCenter(pair<int, int> center, vector<vector<int>>& grid)
    {

        // 计算9个点的距离，如果算过可以不用从新算
        vector<pair<int, int>> points;
        pair<int ,int> point;
        point.first = center.first; point.second = center.second; points.push_back(point);
        point.first = center.first; point.second = center.second - 1; points.push_back(point);
        point.first = center.first; point.second = center.second + 1; points.push_back(point);
        point.first = center.first - 1; point.second = center.second; points.push_back(point);
        point.first = center.first - 1; point.second = center.second - 1; points.push_back(point);
        point.first = center.first - 1; point.second = center.second + 1; points.push_back(point);
        point.first = center.first + 1; point.second = center.second; points.push_back(point);
        point.first = center.first + 1; point.second = center.second - 1; points.push_back(point);
        point.first = center.first + 1; point.second = center.second + 1; points.push_back(point);

        int minDistance = INT_MAX;
        pair<int, int> newCenter;
        int fmax = grid.size() - 1;
        int smax = grid[0].size() - 1;
        for (auto point : points)
        {
            if (point.first < 0 || point.second < 0 || point.first > fmax || point.second > smax)
            {
                continue;
            }

            // 迭代更新，取距离最小的那个点
            int distance = CountDistance(point, grid);
            if (minDistance > distance)
            {
                minDistance = distance;
                newCenter = point;
            }
        }

        return newCenter;
    }

    int CountDistance(pair<int, int> point, vector<vector<int>>& grid)
    {
        auto itr = m_knownDistance.find(point);
        if (itr != m_knownDistance.end())
        {
            return (*itr).second;
        }

        // 没有计算过的，现算一把
        int dstSum = 0;
        for (int first = 0; first < grid.size(); first++)
        {
            for (int second = 0; second < grid[0].size(); second++)
            {
                if (grid[first][second] == 1)
                {
                    dstSum += abs(point.first - first);
                    dstSum += abs(point.second - second);
                }
            }
        }

        m_knownDistance[point] = dstSum;

        PirntKnownDistance();

        return dstSum;
    }

    void PirntKnownDistance()
    {
        cout << "{";
        for (auto itr = m_knownDistance.begin(); itr != m_knownDistance.end(); ++itr)
        {
            cout << " [" << (*itr).first.first << "," << (*itr).first.second << "]=" << (*itr).second;
        }
        cout << "}" << endl;
    }
    
}; 



TEST(Test_Code_296, test1)
{
    vector<vector<int>> grid = {{1, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}};
    Solution_296 sln;
    EXPECT_EQ(sln.minTotalDistance(grid), 6);
}

TEST(Test_Code_296, test2)
{
    vector<vector<int>> grid = {{1, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}};
    Solution_296 sln;
    EXPECT_EQ(sln.minTotalDistance(grid), 11);
}