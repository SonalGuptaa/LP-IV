#include <omp.h>
#include <iostream>

using namespace std;

int minval(int arr[], int n){
    int minval = arr[0];
    for(int i = 0; i < n; i++){
        if(arr[i] < minval) minval = arr[i];
    }
    return minval;
}

int maxval(int arr[], int n){
    int maxval = arr[0];
    for(int i = 0; i < n; i++){
        if(arr[i] > maxval) maxval = arr[i];
    }
    return maxval;
}

int sum(int arr[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int average(int arr[], int n){
    return static_cast<double>(sum(arr, n)) / n;
}

int minvalparallel(int arr[], int n){
    int minval = arr[0];
    #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
        if(arr[i] < minval) minval = arr[i];
    }
    return minval;
}

int maxvalparallel(int arr[], int n){
    int maxval = arr[0];
    #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
        if(arr[i] > maxval) maxval = arr[i];
    }
    return maxval;
}

int sumparallel(int arr[], int n){
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int averageparallel(int arr[], int n){
    return static_cast<double>(sumparallel(arr, n)) / n;
}

int main(){
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    cout << "Elements in the array: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sequential version
    cout << "Sequential Min = " << minval(arr, n) << endl;
    cout << "Sequential Max = " << maxval(arr, n) << endl;
    cout << "Sequential Sum = " << sum(arr, n) << endl;
    cout << "Sequential Average = " << average(arr, n) << endl;

    // OpenMP Parallel version
    cout << "Parallel Min = " << minvalparallel(arr, n) << endl;
    cout << "Parallel Max = " << maxvalparallel(arr, n) << endl;
    cout << "Parallel Sum = " << sumparallel(arr, n) << endl;
    cout << "Parallel Average = " << averageparallel(arr, n) << endl;

    return 0;
}
