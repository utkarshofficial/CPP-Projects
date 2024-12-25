#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;

class Histogram {
private:
    vector<int> &nums;
    vector<int> oldNums;
    int maxNum;
    int delay; // Speed control for histogram updates

public:
    // Constructor
    Histogram(vector<int>& nums, int delay = 100)
        : nums(nums), oldNums(nums.size()), delay(delay) 
    {
        getMax();
    }

    // Method to update the array dynamically
    void setNums(const vector<int>& nums) {
        this->nums = nums;
        this->oldNums.resize(nums.size());
        getMax();
    }

    // Method to set delay
    void setDelay(int delayTime) {
        delay = delayTime;
    }

    // Static method to show the histogram
    void showHisto(int ii, int currentCompare, int currentElement);

    // Non-static utility methods
    void ShowConsoleCursor(bool showFlag);
    void getMax();
    void updateOldNums();
    void applyDelay();
};

void Histogram::getMax() {
    if (!nums.empty()) {
        maxNum = *max_element(nums.begin(), nums.end());
    } else {
        maxNum = 0;  // If nums is empty, set maxNum to 0
    }
}

void Histogram::showHisto(int ii = -1, int currentCompare = -1, int currentElement = -1) {
    // Reset the cursor position and hide the cursor
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    ShowConsoleCursor(false);

    char b = 219;  // 219 = █ character

    for (int i = 0; i < maxNum; i++) {
        for (int j = 0; j < nums.size(); j++) {
            // Color the bars based on the comparison state
            if (j == currentElement) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  // green text
            } else if (j == currentCompare) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // red text
            } else if (ii == j || nums[j] != oldNums[j]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // red text
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // white text
            }

            if (maxNum - nums[j] <= i)
                cout << " " << b << b << " ";
            else
                cout << "    ";
        }
        cout << endl;
    }

    applyDelay();

    // Print the actual array values at the bottom
    for (int i = 0; i < nums.size(); i++) {
        if (oldNums[i] != nums[i])
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16);  // light gray
        cout << " " << left << setw(2) << setfill(' ') << nums[i] << " ";
        oldNums[i] = nums[i];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // reset to white
    }
}

void Histogram::ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;  // set cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Histogram::updateOldNums() {
    oldNums = nums;
}

void Histogram::applyDelay() {
    // Apply delay in milliseconds
    Sleep(delay);
}