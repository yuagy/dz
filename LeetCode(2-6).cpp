#include <iostream>
#include <vector>
#include <cmath>

// Задача 2
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int k = 0;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[k]) {
            ++k;
            nums[k] = nums[i];
        }
    }
    return k + 1;
}

// Задача 3
std::vector<int> sortedSquares(std::vector<int>& nums) {
    std::vector<int> result(nums.size());
    int left = 0, right = nums.size() - 1;
    int pos = nums.size() - 1;
    
    while (left <= right) {
        if (abs(nums[left]) > abs(nums[right])) {
            result[pos] = nums[left] * nums[left];
            ++left;
        } else {
            result[pos] = nums[right] * nums[right];
            --right;
        }
        --pos;
    }
    return result;
}

// Задача 4
void moveZeroes(std::vector<int>& nums) {
    int k = 0;
    
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            nums[k] = nums[i];
            ++k;
        }
    }
    
    while (k < nums.size()) {
        nums[k] = 0;
        ++k;
    }
}

// Задача 5
std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        int index = abs(nums[i]) - 1;
        if (nums[index] > 0) {
            nums[index] = -nums[index];
        }
    }
    
    std::vector<int> missing;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            missing.push_back(i + 1);
        }
    }
    return missing;
}

// Задача 6
std::vector<int> productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1);
    
    int leftProduct = 1;
    for (int i = 0; i < n; ++i) {
        result[i] = leftProduct;
        leftProduct *= nums[i];
    }
    
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    
    return result;
}

int main() {
    std::cout << "Testing LeetCode Solutions (2-6):\n\n";
    
    // Тест задачи 2
    {
        std::vector<int> nums = {1, 1, 2, 2, 3, 4, 4, 5};
        std::cout << "task 2:\n";
        std::cout << "Source array: ";
        for (int n : nums) std::cout << n << " ";
        
        int k = removeDuplicates(nums);
        std::cout << "\nUnique elements:" << k << "\n";
        std::cout << "Array after: ";
        for (int i = 0; i < k; ++i) std::cout << nums[i] << " ";
        std::cout << "\n\n";
    }
    
    // Тест задачи 3
    {
        std::vector<int> nums = {-4, -1, 0, 3, 10};
        std::cout << "Task 3::\n";
        std::cout << "Source array: ";
        for (int n : nums) std::cout << n << " ";
        
        std::vector<int> result = sortedSquares(nums);
        std::cout << "\nResult: ";
        for (int n : result) std::cout << n << " ";
        std::cout << "\n\n";
    }
    
    // Тест задачи 4
    {
        std::vector<int> nums = {0, 1, 0, 3, 12};
        std::cout << "Nask 4:\n";
        std::cout << "Source array: ";
        for (int n : nums) std::cout << n << " ";
        
        moveZeroes(nums);
        std::cout << "\nResult: ";
        for (int n : nums) std::cout << n << " ";
        std::cout << "\n\n";
    }
    
    // Тест задачи 5
    {
        std::vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
        std::cout << "Task 5:\n";
        std::cout << "Source array: ";
        for (int n : nums) std::cout << n << " ";
        
        std::vector<int> result = findDisappearedNumbers(nums);
        std::cout << "\nMissing numbers: ";
        for (int n : result) std::cout << n << " ";
        std::cout << "\n\n";
    }
    
    // Тест задачи 6
    {
        std::vector<int> nums = {1, 2, 3, 4};
        std::cout << "Task 6\n";
        std::cout << "source array: ";
        for (int n : nums) std::cout << n << " ";
        
        std::vector<int> result = productExceptSelf(nums);
        std::cout << "\nResult: ";
        for (int n : result) std::cout << n << " ";
        std::cout << "\n\n";
    }
    
    return 0;
}