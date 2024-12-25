/*
┌────────────────────────────────────────────────────────────┐
│ THIS PROGRAM IS DEVELOPED BY UTKARSH SHARMA                │
│ GitHub   ─ https://github.com/utkarshofficial              │
│ FaceBook ─ https://fb.com/utkarshsharmaofficial            │
│ LinkedIn ─ https://www.linkedin.com/in/utkarssharma/       │
├────────────────────────────────────────────────────────────┤
│ ██╗   ██╗████████╗██╗  ██╗ █████╗ ██████╗ ███████╗██╗  ██╗ │
│ ██║   ██║╚══██╔══╝██║ ██╔╝██╔══██╗██╔══██╗██╔════╝██║  ██║ │
│ ██║   ██║   ██║   █████╔╝ ███████║██████╔╝███████╗███████║ │
│ ██║   ██║   ██║   ██╔═██╗ ██╔══██║██╔══██╗╚════██║██╔══██║ │
│ ╚██████╔╝   ██║   ██║  ██╗██║  ██║██║  ██║███████║██║  ██║ │
│  ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ │
└────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include <thread>

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
    // ANSI escape code for clearing the screen
    std::cout << "\033[?25l";
    std::cout << "\033[H"; // move cursor to (1,1)
    std::cout.flush();

    char b = 219;  // 219 = █ character

    for (int i = 0; i < maxNum; i++) {
        for (int j = 0; j < nums.size(); j++) {
            // Color the bars based on the comparison state
            if (j == currentElement) {
                std::cout << "\033[32m";  // Green text (for current element)
            } else if (j == currentCompare) {
                std::cout << "\033[31m";  // Red text (for current compare)
            } else if (ii == j || nums[j] != oldNums[j]) {
                std::cout << "\033[31m";  // Red text (for elements that changed)
            } else {
                std::cout << "\033[37m";  // White text (default)
            }

            if (maxNum - nums[j] <= i)
                std::cout << " " << b << b << " ";
            else
                std::cout << "    ";
        }
        std::cout << std::endl;
    }

    applyDelay();

    // Reset to normal text color
    std::cout << "\033[0m";  // Reset color

    // Print the actual array values at the bottom
    for (int i = 0; i < nums.size(); i++) {
        if (oldNums[i] != nums[i])
            std::cout << "\033[48;5;117m\033[97m";  // sky back white text
        std::cout << " " << std::left << std::setw(2) << std::setfill(' ') << nums[i] << " ";
        oldNums[i] = nums[i];
        std::cout << "\033[0m";  // Reset color
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
    // Sleep(delay);
    this_thread::sleep_for(chrono::milliseconds(delay));
}