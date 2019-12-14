#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

void bubbleSort(double* myArray, int size)
{
    for(int i = 0; i<size;++i)
    {
        int temp = 0;
        for(int j = 0; j<size-1; ++j)
        {
            if(myArray[j] > myArray[j+1])
            {
                temp = myArray[j+1];
                myArray[j+1] = myArray[j];
                myArray[j] = temp;
            }
        }
    }
}

void selectionSort(double* arr, int n)
{
    int i,j,minIndex;
    double temp;
    for(i = 0; i < n-1; ++i)
    {
        minIndex = i;
        for(j = i+1; j<n;j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void insertionSort(double* arr,int size)
{
    for(int j = 1; j < size; ++j)
    {
        double temp = arr[j];
        int k = j;
        while(k > 0 && arr[k-1] >= temp)
        {
            arr[k] = arr[k-1];
            --k;
        }
        arr[k] = temp;
    }
}

double* mergeSort(double* arr, int size)
{
    double* arr1;
    double* arr2;
    int arr1Size;
    int arr2Size;
    if(size <= 1)
    {
        return arr;
    }
    else
    {
        int mid = size/2;
        if(size%2 == 0)
        {
            arr1 = new double[mid];
            arr2 = new double[mid];
            arr1Size = mid;
            arr2Size = mid;
        }
        else{
            arr1 = new double[mid];
            arr2 = new double[mid+1];
            arr1Size = mid;
            arr2Size = mid + 1;
        }
        for(int i = 0; i < size; ++i)
        {
            if(i<mid)
            {
                arr1[i] = arr[i];
            }
            else{
                arr2[i-mid] = arr[i];
            }
        }
        mergeSort(arr1, arr1Size);
        mergeSort(arr2, arr2Size);
        int i = 0;
        int j = 0;
        int count = 0;
        while(i < arr1Size || j < arr2Size)
        {
            //cout << "merge sort merging" << count++ << endl;
            if(i >= arr1Size)
            {
                arr[i+j] = arr2[j];
                j++;
                continue;
            }
            if(j >= arr2Size)
            {
                arr[i+j] = arr1[i];
                i++;
                continue;
            }
            if(arr1[i] < arr2[j])
            {
                arr[i+j] = arr1[i];
                i++;
            }
            if(arr1[i] > arr2[j])
            {
                arr[i+j] = arr2[j];
                j++;
            }
        }
        delete arr1;
        delete arr2;
    }
    return arr;
}

void GenTestFile(int num)
{
    ofstream outFile;
    outFile.open("srobbins.out");
    outFile << num << endl;
    for(int i = 0; i < num; ++i)
    {
        outFile << rand() << endl;
    }
    outFile.close();
}


int main(int argc, char** argv)
{
    string fname = argv[1];
    int size;
    double* myArray; 
    double* myArray1;
    double* myArray2;
    double* myArray3;


    ifstream myFile(fname);
    if(myFile.is_open())
    {
        string line;
        myFile >> line;
        size = atoi(line.data());
        myArray = new double[size];
        myArray1 = new double[size];
        myArray2 = new double[size];
        myArray3 = new double[size];
        int i = 0;
        while(myFile)
        {
            myFile >> line;
            double num = atof(line.data());
            myArray[i] = num;
            myArray1[i] = num;
            myArray2[i] = num;
            myArray3[i] = num;
            i++;
        }
        myFile.close();
    }

    
    cout << "Merge Sort Started" << endl;
    auto start = high_resolution_clock::now();
    mergeSort(myArray, size);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << " ms"<< endl;

    cout << "insertion sort started" << endl;
    start = high_resolution_clock::now();
    insertionSort(myArray1, size);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << " ms"<< endl;

    cout << "selection sort started" << endl;
    start = high_resolution_clock::now();
    selectionSort(myArray2, size);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << " ms"<< endl;

    cout << "bubble Sort started" << endl;
    start = high_resolution_clock::now();
    bubbleSort(myArray3, size);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << " ms"<< endl;

    ofstream outfile;
    outfile.open("srobbinsResults.txt");

    outfile << "Merge Sort: " << endl;
    for(int i = 0; i < size; i++)
    {
        outfile<< myArray[i] << endl;
    }

    outfile << "Insertion Sort:" << endl;
    for(int i = 0; i < size; i++)
    {
        outfile<< myArray1[i] << endl;
    }

    outfile << "Selection Sort: " << endl;
    for(int i = 0; i < size; i++)
    {
        outfile<< myArray2[i] << endl;
    }

    outfile << "Bubble Sort: " << endl;
    for(int i = 0; i < size; i++)
    {
        outfile<< myArray3[i] << endl;
    }
    outfile.close();
    return -1;
}




