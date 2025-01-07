#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class solution{
    private:
    //计算一个数的各个位上的平方和
    int getSum(int n){
        int sum = 0;
        while(n){
            sum += (n%10)*(n%10);
            n /= 10;
        }
        return sum;
    }

    public:
    void managestudents(){
    // unordered_map模拟哈希表，键是学号，值是姓名
    std::unordered_map<int, std::string> student_map;
    
    // 插入数据
    student_map[1] = "Tom";
    student_map[2] = "Jerry";
    student_map[3] = "Alice";

    // 查找数据
    int search_id = 2;
    if(student_map.find(search_id) != student_map.end()){
        std::cout << "ID: " << search_id << " Name: " << student_map[search_id] << std::endl;
    }else{
        std::cout << "ID: " << search_id << " Not Found" << std::endl;
    }

    //删除学生数据
    int delete_id = 3;
    student_map.erase(delete_id);
    std::cout << "ID: " << delete_id << " Deleted" << std::endl;


    // 遍历哈希表
    std::cout<<"\nCurrent stduent list:\n"<<std::endl;
    //auto是自动类型推断，它会根据student·map的类型推断出student的类型
    for(const auto& student : student_map){ 
        std::cout << "ID: " << student.first << " Name: " << student.second << std::endl;
    }
    }
    bool isAnagram(std::string s, std::string t){
        int record[26] = {0};
        for(int i=0;i<s.size();i++){
            record[s[i]-'a']++;
        }
        for(int i=0;i<t.size();i++){
            record[t[i]-'a']--;
        }
        for(int i=0;i<26;i++){
            if(record[i]!=0){
                return false;
                
            }
        }
        return true;
    }


    std::vector<int> intersection(std::vector<int>& firstArray, std::vector<int>& secondArray){
        // 存放结果
        std::unordered_set<int> result_set;
        std::unordered_set<int> nums_set(firstArray.begin(), firstArray.end());
        
        for(int num : secondArray){
            // 发现secondArray的元素在nums_set中存在
            if(nums_set.find(num) != nums_set.end()){
                result_set.insert(num);
            }
        }
        return std::vector<int>(result_set.begin(), result_set.end());
    }


    bool isHappy(int n){
        std::unordered_set<int> set;
        while(1){
            int sum = getSum(n);
            if(sum == 1){
                return true;
            }
            // 如果sum已经在set中(重新出现)，说明进入了循环
            if(set.find(sum) != set.end()){
                return false;
            }else{
                set.insert(sum);
            }
            n = sum;
        }

    }

    //两数之和
    std::vector<int> twoSum(std::vector<int>& nums,int target){
        std::unordered_map<int,int> record;
        for(int i = 0;i<nums.size();i++){
            //遍历当前元素，并且在map中查找是否有满足条件的元素
            auto iter = record.find(target-nums[i]);
            if(iter != record.end()){
                return {iter->second,i};
            }
            //如果没有找到，就把当前元素加入map
            record.insert(std::make_pair(nums[i],i));
        }
        return {};

    }

    //四数相加
    int fourSumCount(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, std::vector<int>& D){
        std::unordered_map<int,int> record; //key是A和B的和，value是这个和出现的次数
        for(int a : A){
            for(int b : B){
                record[a+b]++;
            }
        }
        int count = 0;
        for (int c : C){
            for(int d : D){
                if(record.find(-c-d) != record.end()){
                    count += record[-c-d];
                }
            }
        }
        return count;
    }

    //三数之和
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums){
        // 存放结果
        std::vector<std::vector<int>> result;
        //排序数组，采用升序排列
        std::sort(nums.begin(),nums.end());

        //遍历每个元素，为后续双指针法准备
        for(int i=0;i<nums.size();i++){
            //跳过重复元素
            if(i>0 && nums[i] == nums[i-1]) continue;
            int left = i + 1, right = nums.size() - 1;

            while(left<right){
                int sum = nums[i] + nums[left] + nums[right];
                if(sum < 0){
                    left++;
                }else if(sum > 0){
                    right--;
                }else{
                    result.push_back({nums[i], nums[left], nums[right]});
                    //跳过重复元素
                    while(left < right && nums[left] == nums[left + 1]) left++;
                    while(left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }
            }
        }   
        return result;
    }

    //四数之和
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums,int target){
        //存储结果
        std::vector<std::vector<int>> result;
        //排序
        std::sort(nums.begin(),nums.end());
        //准备查找
        for(int k=0;k<nums.size();k++){
            //进行适当的减枝处理
            if(nums[k]>target && (nums[k]>0 || target>0)) break;
            //去重
            if(k>0 && nums[k]==nums[k-1]) continue;
            for(int i=k+1;i<nums.size();i++){
                //接下来就和三数之和差不多了
                //适当的剪枝处理
                if(nums[k]+nums[i]>target && (nums[k]+nums[i]>0 || target>0)) break;
                //去重
                if (i>k+1 && nums[i]==nums[i-1]) continue;
                int left = i + 1, right = nums.size() - 1;
                while(left<right){
                    int sum = nums[k]+nums[i]+nums[left]+nums[right];
                    if(sum<target){
                        left++;
                    }else if(sum>target){
                        right--;
                    }else{
                        result.push_back({nums[k],nums[i],nums[left],nums[right]});
                        //对nums[left]和nums[right]进行去重
                        while(left<right && nums[left]==nums[left+1]) left++;
                        while(left<right && nums[right]==nums[right-1]) right--;

                        left++;
                        right--;
                    }
                }
            }
        }
        return result;

    }

};

class Test{
    public:
    void test_isAnagram(){
        solution sol;
        // 调用 isAnagram 函数并输出结果
        std::string str1 = "anagram";
        std::string str2 = "nagaram";
        bool result = sol.isAnagram(str1, str2);
        std::cout << "Is \"" << str1 << "\" an anagram of \"" << str2 << "\"? " << (result ? "Yes" : "No") << std::endl;
    }

    void test_intersection(){
        solution sol;
        std::vector<int> firstArray = {1,2,2,1};
        std::vector<int> secondArray = {2,1};
        std::vector<int> result = sol.intersection(firstArray, secondArray);
        std::cout << "Intersection of two arrays: ";
        for(int num : result){
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    void test_isHappy(){
        solution sol;
        int n = 19;
        bool result = sol.isHappy(n);
        std::cout << "Is " << n << " a happy number? " << (result ? "Yes" : "No") << std::endl;
    }

    void test_twoSum(){
        solution sol;
        std::vector<int> nums = {2,7,11,15};
        int target = 9;
        std::vector<int> result = sol.twoSum(nums, target);
        std::cout << "Two sum result: " << result[0] << " " << result[1] << std::endl;
    }

    void test_threeSum(){
        solution sol;
        std::vector<int> nums = {-1,0,1,2,-1,-4};
        std::vector<std::vector<int>> result = sol.threeSum(nums);
        std::cout << "Three sum results: " << std::endl;
        for(auto triplet : result){
            std::cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]" << std::endl;
        }
    }

    void test_fourSum(){
        solution sol;
        std::vector<int> nums = {1,0,-1,0,-2,2};
        int target = 0;
        std::vector<std::vector<int>> result = sol.fourSum(nums, target);
        std::cout << "Four sum results: " << std::endl;
        for(auto quadruplet : result){
            std::cout << "[" << quadruplet[0] << ", " << quadruplet[1] << ", " << quadruplet[2] << ", " << quadruplet[3] << "]" << std::endl;
        }
    }
};

int main(){
    Test test;
    // test.test_isAnagram();
    // test.test_intersection();
    // test.test_isHappy();
    // test.test_twoSum();
    // test.test_threeSum();
    test.test_fourSum();
    return 0;
}