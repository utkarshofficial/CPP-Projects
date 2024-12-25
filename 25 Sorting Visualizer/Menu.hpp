#include "Histogram.hpp"
#include "SortingAlgorithm.hpp"
#include <random>

class Menu {
private:
    vector<int> arr;
    int delay;

    void generateRandomArray(int size) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 32);
        
        arr.clear();
        for (int i = 0; i < size; ++i) {
            arr.push_back(dis(gen));
        }
    }

    void takeArrayInput() {
        int size;
        cout << "Enter the number of elements (1 to 50): ";
        cin >> size;
        if (size < 1 || size > 50) {
            cout << "Invalid size! Size must be between 1 and 50.\n";
            return;
        }
        
        arr.resize(size);
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }
    }

    void showArray(const string& message) {
        cout << message << ": ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }

    void showSortingMenu() {
        Histogram histogram(arr, delay);
        
        cout << "\nChoose Sorting Algorithm:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Merge Sort\n";
        cout << "5. Quick Sort\n";
        cout << "6. Heap Sort\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        SortingAlgorithm* sorter = nullptr;
        
        switch (choice) {
            case 1:
                sorter = new BubbleSort(arr, histogram);
                break;
            case 2:
                sorter = new SelectionSort(arr, histogram);
                break;
            case 3:
                sorter = new InsertionSort(arr, histogram);
                break;
            case 4:
                sorter = new MergeSort(arr, histogram);
                break;
            case 5:
                sorter = new QuickSort(arr, histogram);
                break;
            case 6:
                sorter = new HeapSort(arr, histogram);
                break;
            default:
                cout << "Invalid choice! Exiting...\n";
                return;
        }

        sorter->sort();
        delete sorter;
    }

    void showSpeedMenu() {
        cout << "\nSelect Speed for Animation (in milliseconds):\n";
        cout << "1. Slow (500ms)\n";
        cout << "2. Medium (200ms)\n";
        cout << "3. Fast (100ms)\n";
        cout << "4. Custom\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                delay = 500;
                break;
            case 2:
                delay = 200;
                break;
            case 3:
                delay = 100;
                break;
            case 4:
                cout<< "Enter custom delay (in milliseconds): ";
                cin >> delay;
                if(delay < 0){
                    cout << "Invalid delay! Defaulting to Medium speed.\n";
                    delay = 200;
                }
                break;
            default:
                cout << "Invalid choice! Defaulting to Medium speed.\n";
                delay = 200;
                break;
        }
    }

public:
    void showMainMenu() {
        system("cls");
        std::cout << "\033[?25h";
        
        while (true) {
            system("cls");
            cout << "\n*** Main Menu ***\n";
            cout << "1. Generate Random Array\n";
            cout << "2. Generate Increasing Array\n";
            cout << "3. Generate Increasing Random Array\n";
            cout << "4. Input Array Manually\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int size;
                cout << "Enter the size of the array (1 to 50): ";
                cin >> size;
                if (size < 1 || size > 50) {
                    cout << "Invalid size! Size must be between 1 and 50.\n";
                    continue;
                }
                generateRandomArray(size);
                showArray("Generated Random Array");
            } else if (choice == 2) {
                int size;
                cout << "Enter the size of the array (1 to 50): ";
                cin >> size;
                if (size < 1 || size > 50) {
                    cout << "Invalid size! Size must be between 1 and 50.\n";
                    continue;
                }
                arr.resize(size);
                iota(arr.begin(), arr.end(), 1);
                showArray("Generated Increasing Array");
                
            } else if (choice == 3) {
                arr = {5,4,7,8,1,6,9,2,3,10,13,21,11,20,16,17,19,32,23,15,28,29,31,12,18,26,14,22,30,27,25,24};
                showArray("Generated Increasing Random Array");

            } else if (choice == 4) {
                takeArrayInput();
                showArray("User Input Array");
            } else if (choice == 5) {
                cout << "Exiting...\n";
                return;
            } else {
                cout << "Invalid choice! Please try again.\n";
                continue;
            }

            showSpeedMenu();
            showSortingMenu();

            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
};

