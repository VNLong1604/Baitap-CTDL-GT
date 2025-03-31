#include <stdio.h>

// Hàm in mảng
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 1. Sắp xếp đổi chỗ trực tiếp (Interchange Sort)
void interchangeSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// 2. Sắp xếp chọn trực tiếp (Selection Sort)
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// 3. Sắp xếp chèn trực tiếp (Insertion Sort)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Sắp xếp nổi bọt (Bubble Sort)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {39, 8, 5, 1, 3, 6, 9, 12, 4, 7, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Mang ban dau: ");
    printArray(arr, n);

    int arr1[n], arr2[n], arr3[n], arr4[n];
    for(int i = 0; i < n; i++){
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        arr4[i] = arr[i];
    }

    interchangeSort(arr1, n);
    printf("Mang sau khi sap xep doi cho truc tiep: ");
    printArray(arr1, n);

    selectionSort(arr2, n);
    printf("Mang sau khi sap xep chon truc tiep: ");
    printArray(arr2, n);

    insertionSort(arr3, n);
    printf("Mang sau khi sap xep chen truc tiep: ");
    printArray(arr3, n);

    bubbleSort(arr4, n);
    printf("Mang sau khi sap xep noi bot: ");
    printArray(arr4, n);

    return 0;
}