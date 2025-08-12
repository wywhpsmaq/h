//快速排序
#include <iostream>

template<typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void quickSort(T arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 示例使用
int main() {
    int arr[999] ;
    int n ;
    std::cin>>n;
    for(int i = 0; i < n; i++)
        std::cin>>arr[i];

    quickSort(arr, 0, n-1);

    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    
    return 0;
}