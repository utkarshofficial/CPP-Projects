using namespace std;

class SortingAlgorithm
{
protected:
    vector<int> &nums;
    Histogram &histogram;

public:
    SortingAlgorithm(vector<int> &nums, Histogram &histogram)
        : nums(nums), histogram(histogram) {}

    virtual void sort() = 0;
};

class SelectionSort : public SortingAlgorithm
{
public:
    SelectionSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        histogram.showHisto();
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                histogram.showHisto(i, j);
                if (nums[j] < nums[i])
                {
                    swap(nums[j], nums[i]);
                    histogram.showHisto();
                }
            }
        }
        histogram.showHisto();
    }
};

class BubbleSort : public SortingAlgorithm
{
public:
    BubbleSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        histogram.showHisto();
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < nums.size() - i; j++)
            {
                histogram.showHisto(j, j + 1);
                if (nums[j] > nums[j + 1])
                {
                    swap(nums[j], nums[j + 1]);
                    histogram.showHisto();
                }
            }
        }
        histogram.showHisto();
    }
};

class InsertionSort : public SortingAlgorithm
{
public:
    InsertionSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        for (int i = 1; i < nums.size(); i++)
        {
            int temp = nums[i];
            int j = i - 1;
            histogram.showHisto(i, j);
            while (j >= 0 && nums[j] > temp)
            {
                nums[j + 1] = nums[j];
                histogram.showHisto(j + 1, j);
                j--;
            }
            nums[j + 1] = temp;
            histogram.showHisto(i, j + 1);
        }
        histogram.showHisto();
    }
};

class MergeSort : public SortingAlgorithm
{
private:
    void merge(int l, int mid, int r)
    {
        int i = l, j = mid + 1, k = 0;
        vector<int> temp(r - l + 1);

        while (i <= mid && j <= r)
        {
            histogram.showHisto(i, j);
            if (nums[i] < nums[j])
            {
                temp[k++] = nums[i++];
            }
            else
            {
                temp[k++] = nums[j++];
            }
        }
        while (i <= mid)
            temp[k++] = nums[i++];
        while (j <= r)
            temp[k++] = nums[j++];

        for (k = l; k <= r; k++)
        {
            nums[k] = temp[k - l];
            histogram.showHisto(-1, -1, k);
        }
        histogram.showHisto();
    }

    void mergesort(int l, int r)
    {
        if (l < r)
        {
            int mid = (r + l) / 2;
            mergesort(l, mid);
            mergesort(mid + 1, r);
            merge(l, mid, r);
        }
    }

public:
    MergeSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        mergesort(0, nums.size() - 1);
    }
};

class QuickSort : public SortingAlgorithm
{
private:
    int partition(int low, int high)
    {
        int pivot = nums[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            histogram.showHisto(j, high);
            if (nums[j] < pivot)
            {
                i++;
                swap(nums[i], nums[j]);
                histogram.showHisto();
            }
        }
        swap(nums[i + 1], nums[high]);
        histogram.showHisto();
        return i + 1;
    }

    void quicksort(int low, int high)
    {
        if (low < high)
        {
            int pi = partition(low, high);
            quicksort(low, pi - 1);
            quicksort(pi + 1, high);
        }
    }

public:
    QuickSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        quicksort(0, nums.size() - 1);
    }
};

class HeapSort : public SortingAlgorithm
{
private:
    void heapify(int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && nums[l] > nums[largest])
        {
            largest = l;
        }
        if (r < n && nums[r] > nums[largest])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(nums[i], nums[largest]);
            histogram.showHisto();
            heapify(n, largest);
        }
    }

public:
    HeapSort(vector<int> &nums, Histogram &histogram)
        : SortingAlgorithm(nums, histogram) {}

    void sort() override
    {
        for (int i = nums.size() / 2 - 1; i >= 0; i--)
        {
            heapify(nums.size(), i);
        }
        for (int i = nums.size() - 1; i > 0; i--)
        {
            swap(nums[0], nums[i]);
            histogram.showHisto();
            heapify(i, 0);
        }
        histogram.showHisto();
    }
};
