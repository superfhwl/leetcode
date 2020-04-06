#include "code.h"
#include <vector>
#include "gtest/gtest.h"
#include <string>

using namespace std;

void call_code_17(){}

#define DEBUG
#ifdef DEBUG
    #define OJDBG std::cout
#else
    #define OJDBG  0 && std::cout
#endif

class Solution_17 {
public:

    vector<string> letterCombinations(string digits) {
        if (digits.empty())
        {
            return m_result;
        }

        InitDict();

        string joinchar;
        JoinChar(digits, 0, joinchar);

        return m_result;
    }

    void PrintResult()
    {
        OJDBG << "m_result = {";
        for (auto str : m_result)
        {
            OJDBG << str << ", ";
        }
        OJDBG << "}" << endl;
    }

private:
    map<int, vector<char>> m_dict;

    vector<string> m_result;

    void InitDict()
    {
        m_dict['2'] = {'a','b','c'};
        m_dict['3'] = {'d','e','f'};
        m_dict['4'] = {'g','h','i'};
        m_dict['5'] = {'j','k','l'};
        m_dict['6'] = {'m','n','o'};
        m_dict['7'] = {'p','q','r','s'};
        m_dict['8'] = {'t','u','v'};
        m_dict['9'] = {'w','x','y','z'};
    }

    void JoinChar(const string& digits, int pos, string joinchar)
    {
        if (pos >= digits.size())
        {
            OJDBG << "Error! pos = " << pos << " digits = " << digits << endl;
            return;
        }

        char key = digits.at(pos);
        auto charArray = m_dict[key];
        for (auto ch : charArray)
        {
            if (pos < digits.size() - 1)
            {
                // 未到迭代末尾，继续拼接字母
                JoinChar(digits, pos + 1, joinchar + ch);
            }
            else
            {
                // 到达迭代末尾，输出组合词
                m_result.push_back(joinchar + ch);
            }
        }
    }

    
}; 



TEST(Test_Code_17, test1)
{
    string test  = "23";
    Solution_17 sln;
    
    vector<string> result = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    auto output = sln.letterCombinations(test);

    sln.PrintResult();
    EXPECT_TRUE(output.size() == result.size());
    EXPECT_TRUE(output == result);
}