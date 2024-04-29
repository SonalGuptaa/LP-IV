#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
void merge(int arr[], int s, int e) {
    int i = s;
    int k = s;
    int m = (s + e) / 2;
    int j = m + 1;

    int temp[e - s + 1]; // Size of the temporary array

    while (i <= m && j <= e) {
        if (arr[i] < arr[j]) {
            temp[k - s] = arr[i]; // Adjust index for temporary array
            i++;
        } else {
            temp[k - s] = arr[j]; // Adjust index for temporary array
            j++;
        }
        k++;
    }
    while (i <= m) {
        temp[k - s] = arr[i]; // Adjust index for temporary array
        i++;
        k++;
    }
    while (j <= e) {
        temp[k - s] = arr[j]; // Adjust index for temporary array
        j++;
        k++;
    }

    // Copy back elements from temp to original array
    for (int idx = s; idx <= e; idx++) {
        arr[idx] = temp[idx - s]; // Adjust index for temporary array
    }
}


void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, high);
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high);
    }
}

int main() {
    int n;
    cout << "Enter the size of array: ";
    cin >> n;
    int arr[n];

    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
     
    //Perform Sequential merge sort
    cout<<"Sequential Merge Sort";
    mergeSort(arr, 0, n - 1);
    for(int i=0;i<n;i++)
    {
        cout<<arr[i] << " ";
    }
    cout<<endl;

    // Perform parallel merge sort
    cout << "Parallel Merge Sort: ";
    parallelMergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}


   
    // Measure Sequential Time
    // start_time = omp_get_wtime(); 
    // mergeSort(arr, 0, n - 1);
    // end_time = omp_get_wtime(); 
    // cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";

  
    //  Measure Parallel time
    // start_time = omp_get_wtime(); 
    // parallelMergeSort(arr, 0, n - 1);
    // end_time = omp_get_wtime(); 
    // cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds";
