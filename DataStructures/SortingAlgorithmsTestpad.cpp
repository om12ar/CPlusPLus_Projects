#include <bits/stdc++.h>
using namespace std;

enum Type {
	Random, Sorted, NearlySorted,
};

class ArrayList{
    private:
        int* arr;
        int sz;
        int cap;
    public:
        ArrayList(){
            arr = new int[1];
            cap = 1;
            sz=0;
        }
        ~ArrayList(){
            delete[] arr;
        }
        ArrayList(const ArrayList& other){
            sz = other.sz;
            cap = other.cap;
            delete[] arr;
            arr = new int[sz];
            copy(other.arr, other.arr+sz, arr);
        }
        int size(){
            return sz;
        }
        int insert(int element){
            if(sz == cap){
                cap*=2;
                int* tmp = new int[cap];
                copy(arr,arr+sz ,tmp);
                delete[] arr;
                arr = tmp;
            }
            int place;
            for(place=0; place<sz ; place++){
                if(arr[place]<element)
                    break;
            }
            for(int i = sz ; i>place ;i--){
                arr[i] = arr[i-1];
            }
            arr[place] = element;
            sz++;
        }
        int& operator[](int ind){
            return arr[ind];
        }

};

class sorter {
public:
	virtual void Sort(int* data, int size)=0;
	virtual ~sorter() {
	}
};
class InsertionSort: public sorter {
public:
	void Sort(int* data, int size) {
		for (int i = 1; i < size; i++) {
			if (data[i - 1] > data[i]) {
				int tmp = data[i];
				int j = i;
				do {
					data[j] = data[j - 1];
					j--;
				} while (j > 0 && data[j - 1] > tmp);
				data[j] = tmp;
			}
		}
	}
};
class ShellSort1: public sorter {
private:
	void intervalInsertion(int* data, int size, int gap) {
		for (int i = gap; i < size; i++) {
			if (data[i - gap] > data[i]) {
				int tmp = data[i];
				int j = i;
				do {
					data[j] = data[j - gap];
					j -= gap;
				} while (j >= gap && data[j - gap] > tmp);
				data[j] = tmp;
			}
		}
	}
	void shell(int* data, int size) {
		for (int gap = size; gap > 0; gap /= 2)
			intervalInsertion(data, size, gap);

	}
public:
	void Sort(int* data, int size) {
		shell(data, size);
	}
};

class ShellSort2: public sorter {
private:
    ArrayList prattgaps(int max_size){
        ArrayList patt;
        int p2=1, p3=1;
        while(p3 <= max_size){
            p2 = p3;
            while(p2 <= max_size){
                patt.insert(p2);
                p2 *= 2;
            }
            p3 *= 3;
        }

        return patt;
    }
	void intervalInsertion(int* data, int size, int gap) {
		for (int i = gap; i < size; i++) {
			if (data[i - gap] > data[i]) {
				int tmp = data[i];
				int j = i;
				do {
					data[j] = data[j - gap];
					j -= gap;
				} while (j >= gap && data[j - gap] > tmp);
				data[j] = tmp;
			}
		}
	}
	void shell(int* data, int size) {

	    ArrayList pratt = prattgaps(size);

		for (int gap = 0; gap<pratt.size(); gap++)
			intervalInsertion(data, size, pratt[gap]);
	}
public:
	void Sort(int* data, int size) {
		shell(data, size);
	}
};


class MergeSort: public sorter {

	void merge(int a[], const int low, const int mid, const int high) {
		// Variables declaration.
		int * b = new int[high + 1 - low];
		int h, i, j, k;
		h = low;
		i = 0;
		j = mid + 1;
		// Merges the two array's into b[] until the first one is finish
		while ((h <= mid) && (j <= high)) {
			if (a[h] <= a[j]) {
				b[i] = a[h];
				h++;
			} else {
				b[i] = a[j];
				j++;
			}
			i++;
		}
		// Completes the array filling in it the missing values
		if (h > mid) {
			for (k = j; k <= high; k++) {
				b[i] = a[k];
				i++;
			}
		} else {
			for (k = h; k <= mid; k++) {
				b[i] = a[k];
				i++;
			}
		}
		// Prints into the original array
		for (k = 0; k <= high - low; k++) {
			a[k + low] = b[k];
		}
		delete[] b;
	}

	void merge_sort(int a[], const int low, const int high)	// Recursive sort ...
			{
		int mid;
		if (low < high) {
			mid = (low + high) / 2;
			merge_sort(a, low, mid);
			merge_sort(a, mid + 1, high);
			merge(a, low, mid, high);
		}
	}

public:
	void Sort(int* data, int size) {
		merge_sort(data, 0, size);
	}

};

class CountSort: public sorter {
	void sort(int* arr, int len) {
		int mi, mx, z = 0;
		findMinMax(arr, len, mi, mx);
		int nlen = (mx - mi) + 1;
		int* temp = new int[nlen];
		memset(temp, 0, nlen * sizeof(int));

		for (int i = 0; i < len; i++)
			temp[arr[i] - mi]++;

		for (int i = mi; i <= mx; i++) {
			while (temp[i - mi]) {
				arr[z++] = i;
				temp[i - mi]--;
			}
		}

		delete[] temp;
	}

	void findMinMax(int* arr, int len, int& mi, int& mx) {
		mi = INT_MAX;
		mx = 0;
		for (int i = 0; i < len; i++) {
			if (arr[i] > mx)
				mx = arr[i];
			if (arr[i] < mi)
				mi = arr[i];
		}
	}

public:
	void Sort(int* data, int size) {
		sort(data, size);
	}

};
class Test_bed {
public:
	int* data;
	Test_bed() {
		data = NULL;
	}
	void generateRandomList(int Min, int Max, int Size) {
		delete[] data;
		data = new int[Size];
		srand(time(NULL));
		for (int i = 0; i < Size; i++)
			data[i] = rand() % (Max - Min + 1) + Min;
	}
	void generateNearlySortedList(int Min, int Max, int Size) {
		delete[] data;
		data = new int[Size];
		srand(time(NULL));
		for (int i = 0; i < Size; i++)
			data[i] = rand() % (Max - Min + 1) + Min;

		for (int gap = Size / 2; gap >= 100; gap /= 2) {
			for (int i = gap; i < Size; i++) {
				if (data[i - gap] > data[i]) {
					int tmp = data[i];
					int j = i;
					do {
						data[j] = data[j - gap];
						j -= gap;
					} while (j >= gap && data[j - gap] > tmp);
					data[j] = tmp;
				}
			}
		}
	}
	void generateReverseOrderedList(int Min, int Max, int Size) {
		delete[] data;
		data = new int[Size];
		int j = Max;
		for (int i = 0; i < Size; i++) {
			data[i] = j;
			if (j-- == Min)
				j = Max;
		}
	}
	float runOnce(sorter* Sorter, int size) {
		clock_t beginTime = clock();
		Sorter->Sort(data, size);
		return float(clock() - beginTime) / CLOCKS_PER_SEC;
	}
	float runAndAverage(sorter* Sorter, Type type, int minRange, int MaxRange,
			int size) {
		int Number_of_runs = 5;
		float totalTime = 0;
		if (type == Random) {
			for (int i = 0; i < Number_of_runs; i++) {
				generateRandomList(minRange, MaxRange, size);
				totalTime += runOnce(Sorter, size);
			}
		} else if (type == NearlySorted) {
			for (int i = 0; i < Number_of_runs; i++) {
				generateNearlySortedList(minRange, MaxRange, size);
				totalTime += runOnce(Sorter, size);
			}
		} else if (type == Sorted) {
			for (int i = 0; i < Number_of_runs; i++) {
				generateReverseOrderedList(minRange, MaxRange, size);
				totalTime += runOnce(Sorter, size);
			}
		}
		return totalTime / Number_of_runs;
	}
	float* runExperiemnt(sorter* Sorter, Type type, int minRange, int maxRange,
			int maxSize, int step) {
		float* times = new float[maxSize / step];

		for (int i = step, ind = 0; i <= maxSize; i += step, ind++) {
			cout << i << endl;
			times[ind] = runAndAverage(Sorter, type, minRange, maxRange, i);
		}
		return times;
	}

};
int main() {
	Test_bed t;
	string type;

    /*
    //[[[ Testing the sorting functions ]]]
    int arr[] = {9,3,4,2,1,6,5,1000,-100};
    sorter* s = new InsertionSort;
    s->Sort(arr, 9);
    int arr1[] = {9,3,4,2,1,6,5,1000,-100};
    s = new ShellSort1();
    s->Sort(arr1, 9);
    int arr3[] = {9,3,4,2,1,6,5,1000,-100};
    s = new ShellSort2();
    s->Sort(arr3, 9);

    int arr4[] = {9,3,4,2,1,6,5,1000,-100};
    s = new MergeSort();
    s->Sort(arr4, 9);

    int arr5[] = {9,3,4,2,1,6,5,1000,-100};
    s = new CountSort();
    s->Sort(arr5, 9);
    for(int i=0; i<9; i++){
        cout<<arr[i]<<" "<<arr1[i]<<" "<<arr3[i]<<" "<<arr4[i]<<" "<<arr5[i]<<endl;
    }
    */

	 float* f1 = t.runExperiemnt(new InsertionSort, Random, 1, 1000000, 100000,5000);
	 float* f2 = t.runExperiemnt(new ShellSort1 , Random, 1, 1000000, 100000, 5000);
	 float* f3 = t.runExperiemnt(new ShellSort2, Random, 1, 1000000, 100000, 5000);
	 float* f4 = t.runExperiemnt(new MergeSort, Random, 1, 1000000, 100000, 5000);
	 float* f5 = t.runExperiemnt(new CountSort, Random, 1, 1000000, 100000, 5000);


	ofstream file("experiment.csv", ios::out);
	file<< "Data size , Insertion Sort , Original Shell sort , Shell Sort (pratt) , merge sort , Count sort \n";
	for (int i = 0 , sz = 5000; i < 20; i++ , sz+=5000) {
		//file<<f1[i]<<","<<f2[i]<<","<<f3[i]<<","<<f4[i]<<","<<f5[i]<<"\n";
		file<<sz<<","<<f1[i]<<","<<f2[i]<<","<<f3[i]<<","<<f4[i]<<","<<f5[i]<<"\n";
	}
	file.close();

	return 0;
}
