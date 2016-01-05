#include <bits/stdc++.h>

using namespace std;
class Restaurant {
private:
	string name;
	int rating;
	double distance;
public:
	Restaurant(string n, int r, double d) {
		name = n;
		rating = r;
		distance = d;
	}
	Restaurant() {
		name = "";
		rating = -1;
		distance = -1;
	}
	static void sortRestaurants(Restaurant ** arr, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (arr[i]->rating > arr[j]->rating) {
					Restaurant * temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = i + 1;
					(j < size) and (arr[j]->rating == arr[i]->rating); j++) {
				if (arr[i]->distance > arr[j]->distance) {
					Restaurant * temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

	}

	double getDistance() const {
		return distance;
	}

	void setDistance(double distance) {
		this->distance = distance;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	int getRating() const {
		return rating;
	}

	void setRating(int rating) {
		this->rating = rating;
	}
};

int main() {

	Restaurant ** arr = new Restaurant*[8];
	for (int i = 0; i < 8; i++) {
		arr[i] = new Restaurant;
	}

/*

	Restaurant Rest0("A", 2, 30.1), Rest1("B", 4, 30.8), Rest2("C", 5, 60.2),
			Rest3("D", 2, 50.1), Rest4("E", 3, 60.6), Rest5("F", 5, 50.8),
			Rest6("G", 4, 70.1), Rest7("H", 2, 10.1);
	arr[0] = &Rest0;
	arr[1] = &Rest1;
	arr[2] = &Rest2;
	arr[3] = &Rest3;
	arr[4] = &Rest4;
	arr[5] = &Rest5;
	arr[6] = &Rest6;
	arr[7] = &Rest7;
*/




	for(int i =0 ;i < 8 ; i++ ){
		string name;
		int rate ;
		float dist;
		cout<<"Enter Restaurant name :";
		cin>>name;
		cout<<"Enter Restaurant rate :";
		cin>>rate;
		cout<<"Enter Restaurant distance :";
		cin>>dist;
		Restaurant *temp = new Restaurant(name, rate ,dist);
		cout<<name;
		arr[i]=temp;
	}


	Restaurant::sortRestaurants(arr, 8);

	for (int i = 0; i < 8; i++) {
		cout << "Rest (" << arr[i]->getName() << " , " << arr[i]->getRating()
				<< " , " << arr[i]->getDistance() << " ) " << endl;
	}
	delete[] arr ;
}

