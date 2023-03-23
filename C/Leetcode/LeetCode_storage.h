//
// Created by Zhixu on 9/21/2022.
//

#ifndef LEETCODE_LEETCODE_STORAGE_H
#include <iostream>
#include <vector>
#define LEETCODE_LEETCODE_STORAGE_H
/*9-20
 *
 * answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
answer[i] == "Fizz" if i is divisible by 3.
answer[i] == "Buzz" if i is divisible by 5.
answer[i] == i (as a string) if none of the above conditions are true.
 */

/*class Solution1 {
public:
    std::vector<std::string> Temp_arr;
    int count=NULL;
    std::vector<std::string> fizzBuzz(int n) {
        for(int arr_index=1;arr_index<=n;arr_index++){
            if((arr_index%5)==0)//能整除5
            {
                count++;
                if(count%3==0){count=0;
                    Temp_arr.push_back("FizzBuzz");
                    continue;}//能除以5且除以3
                else{Temp_arr.push_back("Buzz");
                    continue;}//只能除以5
            } else if(arr_index%3==0){//能整除3
                Temp_arr.push_back("Fizz");
                continue;
            } else
            {
                Temp_arr.push_back(std::to_string(arr_index));
            }
        }
        return Temp_arr;
    }
};*/
/*
 * 改进：分别添加，可以除3，add Fizz
 * 可以除5，add Buzz
 * */
/*class Solution2{
public:
    std::vector<std::string> fizzBuzz(int n){
       std::vector<std::string> Temp;
       std::string temp;
        //        build the dictionary
//        std:: map<int,std::string > HashTable;
//        auto Insert_result=HashTable.insert(std::pair<int,std::string>(3,"Fizz"));
//        if(Insert_result.second)HashTable[5]="Buzz";
//        auto Hash_key =HashTable.begin();
        for (int i = 1; i <=n; ++i) {
            bool Three=i%3;
            bool Five=i%5;
            if(!Three){temp.append("Fizz");}
            if(!Five){temp.append("Buzz");}
            if(Three and Five){temp.append(std::to_string(i));}
            Temp.push_back(temp);
            temp.clear();
        }
        return Temp;

    }
};*/
class Best_Solution_9_20 {
public:
    std::vector<std::string> fizzBuzz(int n) {
        std::vector<std::string> res(n);
        res.reserve(n);

        for (int i = 1; i <= n; i++) {
            std::string s = "";
            if (i % 3 == 0) {
                s.append("Fizz");
            }
            if (i % 5 == 0) {
                s.append("Buzz");
            }
            if (s.empty()) {
                s.append(std::to_string(i));
            }
            res[i-1]=s;
        }
        return res;
    }
};

//Solution 9-21:
/*
class Solution_bad {
public:

    std::vector<int> Map_table;

    std::vector<std::string> letterCombinations(std::string& digits) {
        Map_table.resize(10);
        //Get the length
        int length_of_str=digits.length();

        std::vector<std::string > Result;
        // Result.reserve(3^length_of_str);

        //get the map table

        Map_table[1]=0;
        for(int i=1;i<=8;i++)
        {
            Map_table[i+1]=i*3;
        }//e.g. map[2]=3,map[3]=6,map[4]=9, map[9]=26
        Map_table[7]++;
        Map_table[8]++;
        Map_table[9]+=2;
        return  OutPut_str(digits,Result);


    }
    char Get_char(int digit,int times){
        return  ('a'+Map_table[digit-1]+times);
    }

    std::vector<std::string> OutPut_str(std::string str,std::vector<std::string >& Result){
        int new_digit;
        std::string temp;
        int Result_len=Result.size();
        while(!str.empty()){
            new_digit= str[0]-'0';
            str.erase(0, 1);
            // std::cout<<str<<"! and"<<str.empty()<<"new digit is:"<<new_digit<<std::endl;


//               If is the first digit
            if(Result.empty()){
                for(int times=0;times<Map_table[new_digit]-Map_table[new_digit-1];times++ ){
                    temp="";
                    temp.push_back(Get_char(new_digit,times));
                    Result.push_back(temp);
                }
                //  std::cout<<"finishing initiating"<<std::endl;
            }//END EMPTY

                //之后的digit
            else   {
                std::vector<std::string > temp_record=Result;

                //开始数字组合
                // std::cout<<"begin to combination!"<<std::endl;

                for(int times=0;times<(Map_table[new_digit]-Map_table[new_digit-1]);times++){
//如果times=0，直接插入，否则先拷贝然后插入
                    if(times==0){
                        // std::cout<<"times is:"<<times<<std::endl;
                        for(auto &j:Result){
                            j.push_back(Get_char(new_digit,times));
                            // std::cout<<"string after insert "<<j<<std::endl;
                            //                                TODO:此处可以优化
                        }
                    }
//                        先拷贝然后插入
                    else{
                        std::vector<std::string > temp_result=temp_record;
                        // std::cout<<"times is:"<<times<<std::endl;
                        //进行拷贝
                        for (auto &j :temp_result) {
                            j.push_back(Get_char(new_digit, times));
                            std::cout << "string after insert " << j << std::endl;
                        }

                        Result.insert(Result.end(), temp_result.begin(), temp_result.end());

                        //============================
                        std::cout<<"after one time combination:";
                        for(auto test:Result){
                            std::cout<<test<<"  ";
                        }
                        //============================

                    }

                }



            }
        }    //end while
        return  Result;
    }
};
class Solution {
    void solve(string *digits, vector<string> &ans, string * const output, int index, string* mapping) {
        if(index >= (*digits).length()) {
            ans.push_back(*output);
            return;
        }

        int number = (*digits)[index] -'0';
        string value = mapping[number];

        for(int i=0; i<value.length(); i++) {
            (*output).push_back(value[i]);
            solve(digits, ans, output, index+1, mapping);
            (*output).pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        string output = "";
        if(digits.length() == 0) {
            return ans;
        }
        int index=0;
        string mapping[10] = {" ", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        solve(&digits, ans, &output, index, mapping);
        return ans;

    }
};*/


//Solution_10_1
/*class Solution_10_1 {
public:
    vector<int> nextGreaterElements(vector<int>& A) {
        int n = A.size();
        int maxv=0;
        vector<int> stack, res(n, -1);//直接预设成-1
        for (int i = 0; i < n * 2; ++i) {
            while (stack.size() && A[stack.back()] < A[i % n]) {
                res[stack.back()] = A[i % n];
                stack.pop_back();
            }
            if(i>=n and maxv==A[i%n]){ break;}
            stack.push_back(i % n);
            maxv=max(A[i%n],maxv);
        }
        return res;
    }


};*/
//倒叙
/*

class Solutio0_10_1 {

public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> s;
        int n = nums.size();
        vector<int> result(n);

        for(int i=nums.size()*2-1;i>=0;--i){
            int num =nums[i%n];
            while(!s.empty() && num>=s.top()){
                s.pop();
            }
            result[i%n]=s.empty()?-1:s.top();
            s.push(num);
        }
        return result;
    }
};
*/
//Solution_10_1_907
/*class Solution_10_1 {
public:
    void NGE_PGE(vector<int> &A,vector< long > &nLE,vector<long>&pLE){//直接预设成-1 {
        int n = A.size();

        stack<int>s;
        for (int i = n-1; i>=0; --i) {
            while (s.size() && A[s.top()]>=A[i]) {
                pLE[s.top()] = i;
                s.pop();
            }

            s.push(i);

        }
        while (s.size()){s.pop();}
        for (int i = 0; i<n; ++i) {
            while (s.size() && A[s.top()]>A[i]) {
                nLE[s.top()] = i;
                s.pop();
            }

            s.push(i);

        }

    }

//先找上下界，也就是跑两遍PGE、NGE
    int sumSubarrayMins(vector<int>& a) {
        int n=a.size();
        vector< long> nLE(n, -1),pLE(n,-1);//直接预设成-1
        NGE_PGE(a,nLE,pLE);
*//*        for (auto i:nLE) {
            cout<<i<<endl;

        }
cout<<"----------------"<<endl;
        for (auto i:pLE) {
            cout<<i<<endl;

        }*//*
        long pre,next;
        long lLen,rLen;
        long cnt=0;
        for (int k= 0; k < n; ++k) {
            pre=pLE[k];
            next=nLE[k];

            if( pre==-1){lLen=k-0;}
            else{lLen=k-pre-1;}
            if(next==-1){rLen=n-1-k;}
            else{rLen=next-k-1;}
            cnt+=(lLen+rLen+rLen*lLen+1)*a[k];
            cnt=cnt%(1000000007);
        }

        cout<<cnt;
        return cnt;
    }
};*/
/*
class Solution_most_fast {
public:
    int sumSubarrayMins(vector<int>& arr) {
        long mod = 1000000007, n = arr.size(), result = 0, x;
        std::vector<long> left;
//        使用pair可能更快
        std::vector<std::pair<long,long>> bounds;
        bounds.push_back({-1,-1});
//左边界
        for (long i = 0; i < n; ++i) {
            x = arr[i];
            while (true) {
                const std::pair<long, long> &p = bounds.back();
                if (p.first < x) {
//                    预置的{-1,-1}，让代码更简洁
                    left.push_back(p.second);
                    break;
                }
                bounds.pop_back();
            }
            bounds.push_back({x,i});
        }


        bounds.clear();
//        右边界
        bounds.push_back({-1,n});

        for (long i = n - 1; i >= 0; --i) {
            x = arr[i];
            while (true) {
                const std::pair<long, long> &p = bounds.back();
                if (p.first <= x) {
//                    找出右边界直接计算
                    result = (result + x*(i-left[i])*(p.second-i)) % mod;
                    break;
                }
                bounds.pop_back();
            }
            bounds.push_back({x,i});
        }


        return (int)result;
    }

    // *** need this constructor to boost the speed ***
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
    }
};
*/




/*class 9_28_Solution {
public:
    string intToRoman(int num) {
        int thousand=num/1000;
        int hundred=(num%1000)/100;
        int decimal=(num%100)/10;
        int last=(num%10);
        string output;
        for(int i=0;i<thousand;i++){
            output.append("M");
        }

        string a,b,c;
        a="C";
        b="D";
        c="M";
        vector<string>h{"",a,a+a,a+a+a,a+b,b,b+a,b+a+a,b+a+a+a,a+c};

        a="X";
        b="L";
        c="C";
        vector<string>d{"",a,a+a,a+a+a,a+b,b,b+a,b+a+a,b+a+a+a,a+c};
        a="I";
        b="V";
        c="X";
        vector<string>l{"",a,a+a,a+a+a,a+b,b,b+a,b+a+a,b+a+a+a,a+c};
        output.append(h[hundred]);
        output.append(h[decimal]);
        output.append(h[last]);
        cout<<output;
    }
};

class 9_28_faster_Solution {
public:
    string intToRoman(int num) {
        string table[4][10] = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                               {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                               {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                               {"", "M", "MM", "MMM"}
        };
        string result;
        int count = 0;
        while(num > 0){
            int temp = num % 10;
            result = table[count][temp] + result;
            num /= 10;
            count++;
        }
        return result;
    }
};*/
/*

class 9_30Solution {
public:
    int  combinationSum4(vector<int>& nums, int target) {

        vector<unsigned>dp(target+1,0);

        for(auto j:nums){
            if(target<j){ continue;}
            dp[j]=1;
        }

        for (int i = 1; i <=target; ++i) {
            for (auto k:nums) {
                if(target<k){ continue;}
                if(i<k){ continue;}
                dp[i]+=dp[i-k];
            }
        }
//    cout<<dp[target];
        return dp[target];

    }
};
*/


//10-4
/*class Solution_10_4 {
public:
    long int D(unsigned d1,unsigned d2){

        if(d1<d2){return 0;}
        if(d1==d2){return 1;}
        int pre=d2;
        long unsigned tmp=d2;
        int cnt=0;
        while (d1>tmp){
            pre=tmp;
            tmp=tmp+tmp;

            cnt++;
        }
        if(cnt!=0){cnt--;}
        return pow(2,cnt)+D((d1-pre),d2);

    }
    int divide(int d1, int d2) {
        int flag=1;
        if((d1<0 and d2>0) or d1>0 and d2<0) {flag=-1;}
        unsigned D1,D2;
        D1=abs(d1);
        D2=abs(d2);
        unsigned ret=D(D1,D2 );
        if (ret>pow(2,31)-1 and flag+1){ret=pow(2,31)-1;}
        if(ret>pow(2,31) and flag-1){ret=pow(2,31);}
        return flag*ret;

    }
};

class Solution_10_4_Fastest {
public:
    int divide(int dividend, int divisor) {
        if(divisor==-1 && dividend == INT_MIN)
            return INT_MAX;
        bool sign = (dividend>=0) == (divisor>=0) ? true : false;
        long int did = abs(dividend);
        long int div = abs(divisor);
        long int result=0;
        // int count=0, temp=divisor;
        while(did - div >= 0){
            int count=0;
            while((did - (div<<1<<count))>=0)
                count++;
            result += 1<<count;
            did -= div<<count;
        }
        return sign ? result : -result;
    }
};*/

#endif //LEETCODE_LEETCODE_STORAGE_H
