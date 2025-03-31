#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Hàm tính tổng các chữ số của một số nguyên
int tinhTongChuSo(int n) {
    int tong = 0;
    n = abs(n); // Xử lý số âm
    while (n > 0) {
        tong += n % 10;
        n /= 10;
    }
    return tong;
}

// Hàm kiểm tra số nguyên tố
bool laSoNguyenTo(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
// Hàm tìm vị trí k phần tử lớn nhất trong mảng
vector<int> timViTriKPhanTuLonNhat(const vector<int>& arr, int k) {
    vector<int> mangSaoChep = arr;
    sort(mangSaoChep.begin(), mangSaoChep.end(), greater<int>());
    vector<int> kPhanTuLonNhat(mangSaoChep.begin(), mangSaoChep.begin() + k);

    vector<int> viTri;
    for (int phanTuLonNhat : kPhanTuLonNhat) {
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] == phanTuLonNhat) {
                viTri.push_back(i);
                break;
            }
        }
    }
    return viTri;
}

// Hàm sắp xếp theo tổng chữ số
vector<int> sapXepTheoTongChuSo(vector<int> arr) {
    sort(arr.begin(), arr.end(), [](int a, int b) {
        return tinhTongChuSo(a) < tinhTongChuSo(b);
    });
    return arr;
}

// Hàm xóa số nguyên tố
vector<int> xoaSoNguyenTo(const vector<int>& arr) {
    vector<int> filteredArr;
    for (int element : arr) {
        if (!laSoNguyenTo(element)) {
            filteredArr.push_back(element);
        }
    }
    return filteredArr;
}

int main() {
    int n, k;

    cout << "Nhập số lượng phần tử của dãy: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Nhập dãy số nguyên, cách nhau bởi dấu cách: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Nhập k: ";
    cin >> k;

    vector<int> positions = timViTriKPhanTuLonNhat(arr, k);
    cout << "Vị trí của " << k << " phần tử lớn nhất: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;

    vector<int> sortedArr = sapXepTheoTongChuSo(arr);
    cout << "Dãy số sau khi sắp xếp theo tổng chữ số: ";
    for (int num : sortedArr) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> filteredArr = xoaSoNguyenTo(arr);
    cout << "Dãy số sau khi xóa các số nguyên tố: ";
    for (int num : filteredArr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
