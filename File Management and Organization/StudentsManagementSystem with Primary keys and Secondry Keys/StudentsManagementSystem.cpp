#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const char DELETE_FLAG = '*';
const int FILE_HEADER_SIZE = sizeof(short);
const int MIN_RECORD_SIZE = 5;

fstream data;
fstream PK;
fstream GSK;
fstream NSK;

vector<pair<int, short> > PKV;

vector<pair<float, vector<int> > > GSKV;

vector<pair<string, vector<int> > > NSKV;

template<class T>
inline T STI(char x[]) {
	T t;
	stringstream ss;
	ss << x;
	ss >> t;
	return t;
}
template<class T>
inline const char* ITS(T x) {
	string t;
	stringstream ss;
	ss << x;
	ss >> t;
	return t.c_str();
}

template<class T, class TT>
bool pairCompare(const pair<T, TT> & firstElem, const pair<T, TT>& secondElem) {
	return firstElem.first < secondElem.first;

}

template<class T, class TT>
void print(vector<pair<T, TT> > v) {

	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << "  " << v[i].second << endl;
	}
}

void insertSorted(vector<int> &v, int value) {
	if (v.size() == 0) {
		v.push_back(value);
	//	cout << "FS!" << endl;
		return;
	}
	vector<int>::iterator it = std::lower_bound(v.begin(), v.end(), value,
			std::less<int>());
	v.insert(it, value);
}

void insertSorted(vector<pair<float, vector<int> > > & v,
		pair<float, vector<int> > value) {
	vector<pair<float, vector<int> > >::iterator it;
	it = std::lower_bound(v.begin(), v.end(), value,
			std::less<pair<float, vector<int> > >());
	v.insert(it, value);
}

void insertSorted(vector<pair<string, vector<int> > > & v,
		pair<string, vector<int> > value) {
	vector<pair<string, vector<int> > >::iterator it;
	it = std::lower_bound(v.begin(), v.end(), value,
			std::less<pair<string, vector<int> > >());
	v.insert(it, value);
}

void insertSorted(vector<pair<int, short> > & v, pair<int, short> value) {
	vector<pair<int, short> >::iterator it;
	it = std::lower_bound(v.begin(), v.end(), value,
			std::less<pair<float, vector<int> > >());
	v.insert(it, value);
}

template<class T, class TT>
void print(vector<pair<T, vector<TT> > > v) {

	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << "  ";
		cout << v[i].second.size();
		cout << " : " << endl;

		for (int j = 0; j < v[i].second.size(); j++) {
			cout << v[i].second[j] << " ";
		}
		cout << endl;
	}
}

struct student {
	char Name[50];
	int ID;
	float GPA;
	char Address[50];
	char Mobile[12];
	//From user to struct
	void fillData() {
		cin.ignore();
		cout << "Enter Student Name: ";
		cin.getline(Name, 50);
		cout << "Enter Student ID: ";
		cin >> ID;
		cout << "Enter Student GPA : ";
		cin >> GPA;
		cout << "Enter Student Address: ";
		cin.ignore();
		cin.getline(Address, 50);
		cout << "Enter Student Mobile: ";
		cin.getline(Mobile, 12);
	}

	void writeToFile(int idx) {
		//idx changes the mode of the function
		// if idx is NOT -1 it will write starting from idx
		//else it will look in the avail list normally
		// its used in the Update function where the lengths are equal
		//	fstream data;
		data.close();
		data.open("students.txt", ios::in | ios::out | ios::binary);

		short szN = strlen(Name);
		short szA = strlen(Address);
		short szM = strlen(Mobile);
		short szI = strlen(ITS<int>(ID));
		short szG = strlen(ITS<float>(GPA));
		short len = szA + szM + szN + szI + szG + (2 * 5);

		short out_of_date;
		short offset;
		data.seekg(0, ios::beg);
		data.read((char*) &out_of_date, sizeof(short));

		if (out_of_date == 1) {
			cout << "PK is not Up to date ";
			ReadVecPK(PKV, "Primary_keys.txt");
		}
		data.seekg(0, ios::end);

		cout << "Writing at : " << data.tellg() << endl;
		if (idx == -1) {
			offset = data.tellg();
			if (offset == -1) {
				data.close();
				data.open("students.txt", ios::in | ios::out | ios::binary);
				data.seekg(FILE_HEADER_SIZE, ios::beg);
		//		cout << "DID IT  now " << data.tellg() << endl;
				offset = FILE_HEADER_SIZE;

			}

		} else {
			offset = idx;
			data.seekg(idx, ios::beg);
		}

		int PK = ID;
		float SKG = GPA;
		string SKN = Name;
		//cout<<"CHAR ******* "<<SKN<<" --  "<<Name<< endl;
		//cout << "WRITING OFFSET ++" << data.tellg() << endl;
		data.write((char*) &len, sizeof(len));
		data.write((char*) &szN, sizeof(szN));
		data.write(Name, szN);

		data.write((char*) &szI, sizeof(szI));
		data.write(ITS<int>(ID), szI);

		data.write((char*) &szG, sizeof(szG));
		data.write(ITS<float>(GPA), szG);

		data.write((char*) &szA, sizeof(szA));
		data.write(Address, szA);

		data.write((char*) &szM, sizeof(szM));
		data.write(Mobile, szM);
		//cout << "Wrote\n";

		if (idx != -1) {
			data.close();
			return;
		}
		insertSorted(PKV, make_pair(PK, offset));
		//cout << "inserted\n";

		fstream flag;

		//OUT OF DATE
		flag.open("students.txt", ios::in | ios::out | ios::binary);

		flag.seekg(0, ios::beg);

		short tt = 1;
		flag.write((char*) &tt, sizeof(short));
		//cout << "wrote flag \n";
		flag.close();

		int keys = 0;
		if (writeVecPK(PKV, "Primary_keys.txt")) {
			keys++;

		} else {
			cout << "PK is not Up to date ";
			return;
			//generateIDX();

		}

		int already_in = BS(GSKV, SKG, 0, GSKV.size());
	//	cout << "already_in == " << already_in << endl;
		if (already_in < 0) {
			vector<int> tempV;
			insertSorted(GSKV, make_pair(SKG, tempV));
			//insertSorted(GSKV[GSKV.size()].second, PK);
		}
		already_in = BS(GSKV, SKG, 0, GSKV.size());
		insertSorted(GSKV[already_in].second, PK);

		if (writeVecSK(GSKV, "GPA_keys.txt")) {
		//	cout << "GSK is done\n";
			keys++;
		} else {
			cout << "GSK is not Up to date ";
			return;
			//generateIDX();

		}
	
		already_in = BSS(NSKV, SKN, 0, NSKV.size());

		if (already_in < 0) {
	
			vector<int> tempV;
			cout << NSKV.size() << endl;
			insertSorted(NSKV, make_pair(SKN, tempV));
			cout << NSKV.size() << endl;
		}
		already_in = BSS(NSKV, SKN, 0, NSKV.size());
		insertSorted(NSKV[already_in].second, PK);

		if (writeVecSK(NSKV, "NAME_keys.txt")) {
			keys++;
		} else {
			cout << "NSK is not Up to date ";
			return;

		}

		//Can check (KEYS == 3)
		flag.open("students.txt", ios::in | ios::out | ios::binary);
		flag.seekg(0, ios::beg);
		tt = 0;
		flag.write((char*) &tt, sizeof(short));
		flag.close();
		data.close();

	}

	template<class T, class TT>
	bool writeVecPK(vector<pair<T, TT> >& v, string path) {
	
		fstream f(path.c_str(), ios::out | ios::binary | ios::trunc);

		if (f.fail()) {
			cout << "Opening failed\n";
			return false;
		}
		for (int i = 0; i < v.size(); i++) {
			f.write((char*) &v[i].first, sizeof(v[i].first));
			f.write((char*) &v[i].second, sizeof(v[i].second));
		}
	
		f.close();
		return true;
	}

	
	bool writeVecSK(vector<pair<float, vector<int> > > & v, string path) {
	
		fstream f(path.c_str(), ios::out | ios::binary | ios::trunc);

		if (f.fail()) {
			cout << "Opening failed\n";
			return false;
		}
		int Vsz = v.size();
		f.write((char*) &Vsz, sizeof(Vsz));
		for (int i = 0; i < Vsz; i++) {

			f.write((char*) &(v[i].first), sizeof(v[i].first));

		
			int tmpVsz = v[i].second.size();
			f.write((char*) &tmpVsz, sizeof(int));
		
			;
			for (int j = 0; j < tmpVsz; j++) {
				f.write((char*) &v[i].second[j], sizeof(v[i].second[j]));
	
			}
		}
	
		f.close();
		return true;
	}
	bool writeVecSK(vector<pair<string, vector<int> > > & v, string path) {
	//	cout << "Here Name \n";
		fstream f(path.c_str(), ios::out | ios::binary | ios::trunc);

		if (f.fail()) {
			cout << "Opening failed\n";
			return false;
		}

		//Size of vec
		int VSZ = v.size();
		f.write((char*) &VSZ, sizeof(VSZ));

		for (int i = 0; i < VSZ; i++) {

			int sz = v[i].first.size();
			f.write((char*) &sz, sizeof(int));

			f.write(v[i].first.c_str(), sz);

	//		cout << "I'm writing char * : " << v[i].first << endl;

			int tmpVsz = v[i].second.size();
			f.write((char*) &tmpVsz, sizeof(int));

	//		cout << "I'm writing : " << tmpVsz << endl;

			for (int j = 0; j < tmpVsz; j++) {
				f.write((char*) &v[i].second[j], sizeof(v[i].second[j]));
	//			cout << " writing2 " << v[i].second[j] << endl;
			}
		}
		f.close();
	//	cout << "Done writing \n";
		return true;
	}

	bool ReadVecPK(vector<pair<int, short> >& v, string path) {
		fstream f(path.c_str(), ios::in | ios::out | ios::binary);
		if (f.fail()) {
			cout << "FailL";
			return false;
		}
		v.clear();
		while (!f.eof()) {
			int one;
			short two;
			f.read((char*) &one, sizeof(one));
			if (f.fail()) {
				cout << one << endl;
				//cout<<f.tellg()<<endl;
				cout << "ReadVecPK FAILD" << endl;
				f.close();
				break;
			}

			f.read((char*) &two, sizeof(two));

		//	cout << "I have " << one << " " << two << endl;
			v.push_back(make_pair(one, two));
		}
		f.close();
		return true;
	}

	bool ReadVecSK(vector<pair<float, vector<int> > > & v, string path) {

		fstream f(path.c_str(), ios::in | ios::out | ios::binary);
		if (f.fail()) {
			cout << "ReadVecsk F FAILeD" << endl;
			return false;
		}
		v.clear();
		int Fsz;
		f.read((char*) &Fsz, sizeof(Fsz));

		for (int ii = 0; ii < Fsz; ii++) {
			float one;
			int sz;
			vector<int> two;

			//		cout << f.tellg() << endl;

			f.read((char*) &one, sizeof(one));
			
			if (f.fail())
				break;

			f.read((char*) &sz, sizeof(sz));
			
			for (int i = 0; i < sz; i++) {

				int twotemp;
				f.read((char*) &(twotemp), sizeof(int));
				two.push_back(twotemp);
			}

			cout << "I have " << one << " with " << two.size() << "  elements"
					<< endl;
			v.push_back(make_pair(one, two));
		}
		f.close();
		return true;
	}

	bool ReadVecSK(vector<pair<string, vector<int> > > & v, string path) {

		fstream f(path.c_str(), ios::in | ios::out | ios::binary);
		if (f.fail()) {
			cout << "ReadVecsk S FAILeD" << endl;
			return false;
		}


		v.clear();

		int Fsz;
		f.read((char*) &Fsz, sizeof(Fsz));

		for (int ii = 0; ii < Fsz; ii++) {
			string one;
			int Nsz;
			int sz;
			vector<int> two;

			
			f.read((char*) &Nsz, sizeof(Nsz));
			char temp[51];
			f.read(temp, Nsz);

			if (f.fail()) {
				cout << "Fail" << endl;
				break;
			}
			temp[Nsz] = '\0';

			
			one = temp;
			

			f.read((char*) &sz, sizeof(sz));
			for (int i = 0; i < sz; i++) {
				int twotemp;
				f.read((char*) &(twotemp), sizeof(int));
				two.push_back(twotemp);
			}

			cout << "I have " << one << " with " << two.size() << "  elements"
					<< endl;
			v.push_back(make_pair(one, two));
		}
		
		f.close();
		return true;
	}

	void displayStudent(int Sid, int offset) {

		fstream out;
		out.open("students.txt", ios::in | ios::out | ios::binary);

		short namelen;
		short IDlen;
		short GPAlen;
		short addlen;
		short moblen;
		char info[51];
		short PlaceInFile;

		if (offset == -1) {
			int idx = BS(PKV, Sid, 0, PKV.size());
	//		cout << "IDX TO be Printed : " << idx << endl;
			if (idx < 0) {
				cout << "---------------------------------------------------\n";
				cout << "NOT FOUND \n";
				return;
			}
			PlaceInFile = PKV[idx].second;

		} else {
			PlaceInFile = offset;
		}
		out.seekp(PlaceInFile + 2, ios::beg);

	
		cout << "---------------------------------------------------\n";

		out.read((char*) &namelen, sizeof(namelen));
		out.read(info, namelen);
		info[namelen] = '\0';
		cout << "Student Name : \n" << info << endl;

		out.read((char*) &IDlen, sizeof(IDlen));
		out.read(info, IDlen);
		info[IDlen] = '\0';
		cout << "Student ID : \n" << info << endl;

		out.read((char*) &GPAlen, sizeof(GPAlen));
		out.read(info, GPAlen);
		info[GPAlen] = '\0';
		cout << "Student GPA : \n" << info << endl;

		out.read((char*) &addlen, sizeof(addlen));
		out.read(info, addlen);
		info[addlen] = '\0';
		cout << "Student Address : \n" << info << endl;

		out.read((char*) &moblen, sizeof(moblen));
		out.read(info, moblen);
		info[moblen] = '\0';
		cout << "Student mobile : \n" << info << endl;

		cout << endl;

	}

	void Display(fstream &f) {

		f.close();
		f.open("students.txt", ios::in | ios::out | ios::binary | ios::app);
		for (int i = 0; i < PKV.size(); i++) {
		//	cout << "SSSSSSSSSSSSSSSSSSSS" << i << endl;
			displayStudent(-1, PKV[i].second);
		}
		cout << endl;
		cout << endl;

	}

	void deleteRecord(int id) {

		fstream file("students.txt", ios::in | ios::out | ios::binary);

		int idx;
		short namelen;
		short GPAlen;
		char name[51];
		char info[20];
		float gpa;
		idx = BS(PKV, id, 0, PKV.size());
	//	cout << "IDX TO be DELETED : " << idx << endl;
		if (idx < 0) {
			cout << "---------------------------------------------------\n";
			cout << "NOT FOUND \n";
			return;
		}
		short PlaceInFile = PKV[idx].second;
	//	cout << "Place in file := " << PlaceInFile << endl;
		file.seekg(PlaceInFile + 2, ios::beg);
		file.read((char*) &namelen, sizeof(short));
		file.read(name, namelen);
		short skipper;
		file.read((char*) &skipper, sizeof(skipper));
		file.seekg(skipper,ios::cur);
		file.read((char*) &GPAlen, sizeof(short));
		file.read(info, GPAlen);
		gpa = STI<float>(info);
		
		file.seekg(PlaceInFile + 2, ios::beg);
		file.put(DELETE_FLAG);
	//	cout << "DATA FILE  IS DELETED " << endl;

//DELETE SECONDRY

		PKV.erase(PKV.begin() + idx);
	
		int GSK_idx = BS(GSKV, gpa, 0, GSKV.size());
	
		if (GSK_idx < 0) {
	
		}
		for (int GSI = 0; GSI < GSKV[GSK_idx].second.size(); GSI++) {
			if (GSKV[GSK_idx].second[GSI] == id) {
				GSKV[GSK_idx].second.erase(GSKV[GSK_idx].second.begin() + GSI);
			}
			if (GSKV[GSK_idx].second.size() == 0) {
				GSKV.erase(GSKV.begin() + GSK_idx);
				break;
			}

		}
	//	cout << "GSI FILE  IS DELETED " << endl;
		string name_str = name;
		int NSK_idx = BS(NSKV, name_str, 0, NSKV.size());
		if (NSK_idx < 0) {
	
		}
		for (int NSI = 0; NSI < NSKV[NSK_idx].second.size(); NSI++) {
			if (NSKV[NSK_idx].second[NSI] == id) {
	
				NSKV[NSK_idx].second.erase(NSKV[NSK_idx].second.begin() + NSI);
			}
			if (NSKV[NSK_idx].second.size() == 0) {
				NSKV.erase(NSKV.begin() + NSK_idx);
				break;
			}

		}
		fstream flag;
		short tt = 1;
		flag.seekg(0, ios::beg);
		flag.write((char*) &tt, sizeof(short));
		flag.close();

		if (writeVecPK(PKV, "Primary_keys.txt")) {
		
		} else {
			cout << "PK is not Up to date ";
			return;
		

		}

		if (writeVecSK(GSKV, "GPA_keys.txt")) {
		
		} else {
			cout << "GSK is not Up to date ";
		

		}
		if (writeVecSK(NSKV, "NAME_keys.txt")) {
		
		} else {
			cout << "NSK is not Up to date ";

		}
		flag.open("students.txt", ios::in | ios::out | ios::binary);
		flag.seekg(0, ios::beg);
		tt = 0;
		flag.write((char*) &tt, sizeof(short));
		flag.close();

		cout << "Student : " << id << " was Deleted successfully \n\n";
	}
	void update(int id) {
		fstream f;
		f.open("students.txt", ios::in | ios::out | ios::binary | ios::app);

		int idx = BS(PKV, id, 0, PKV.size());
	
		short oldLen;

		if (idx < 0) {
			cout << "ID not found " << endl;
			return;
		}

		f.seekg(PKV[idx].second, ios::beg);

		f.read((char*) &oldLen, sizeof(short));
		char info[50];

		short namelen;
		f.read((char*) &namelen, sizeof(short));
		f.read(info, namelen);
		info[namelen] = '\n';
		string oldName = info;

		short gpalen;
		f.read((char*) &gpalen, sizeof(short));
		f.read(info, gpalen);
		info[namelen] = '\n';
		float oldID = STI<int>(info);

		deleteRecord(oldID);

		fillData();

		short szN = strlen(Name);
		short szA = strlen(Address);
		short szM = strlen(Mobile);
		short szI = strlen(ITS<int>(ID));
		short szG = strlen(ITS<float>(GPA));
		short newLen = szA + szM + szN + szI + szG + (2 * 5);

		if ((oldLen == newLen)) {


			cout << PKV.size() << " " << GSKV.size() << " " << NSKV.size()
					<< endl;
			writeToFile(PKV[idx].second);

		} else {

	//		cout << "Done Deleting in update  ";
			writeToFile(-1);
		}

	}

	void displayByGPA(float GPA) {
		int gpa_idx = BS(GSKV, GPA, 0, GSKV.size());
		if (gpa_idx < 0) {
			cout << "NOT FOUND!" << endl;
			return;
		}
	
		for (int j = 0; j < GSKV[gpa_idx].second.size(); j++) {
			cout << j + 1 << " : \n";
			displayStudent(GSKV[gpa_idx].second[j], -1);
			cout << endl;
		}

	}

	void displayByName(string name) {
		int name_idx = BS(NSKV, name, 0, NSKV.size());
		if (name_idx < 0) {
			cout << "NOTFOUND!" << endl;
			return;
		}
	
		for (int j = 0; j < NSKV[name_idx].second.size(); j++) {
			cout << j + 1 << " : \n";
	
			displayStudent(NSKV[name_idx].second[j], -1);
			cout << endl;
		}
	}

	int BS(vector<pair<string, vector<int> > > &v, string elem, int st,
			int fn) {
		cout << st << " " << fn << endl;
		if (st >= fn or v.size() == 0) {
		

			return -2;
		}

		int mid = (st + fn) / 2;
		
		if (v[mid].first == elem) {
			return mid;

		} else if (v[mid].first > elem) {
	//		cout << ">>>>>>>>>>>>>>\n";
			//if (v.size() > 1)
			return BS(v, elem, st, mid - 1);
		} else if (v[mid].first < elem) {
	//		cout << "<<<<<<<<<<<<<<\n";
			//	if (v.size() > 1)

			return BS(v, elem, mid + 1, fn);

		}

		//return -1;
	}
	int BSS(vector<pair<string, vector<int> > > &v, string elem, int st,
			int fn) {
		for(int i =0 ; i < v.size() ; i++){
			if(v[i].first == elem ){
				return i ;
			}
		}
		return -2;
	}
	int BS(vector<pair<float, vector<int> > > &v, float elem, int st, int fn) {
		cout << st << " " << fn << endl;
		if (st > fn or v.size() == 0) {
	//		cout << "BS is returning -1" << endl;

			return -2;
		}

		int mid = (st + fn) / 2;
	//	cout << "BSS!! " << v[mid].first << " " << elem << endl;
		if (v[mid].first == elem) {
	//		cout << "returned this : " << mid << endl;
			return mid;

		} else if (v[mid].first > elem) {
	//		cout << ">>>>>>>>>>>>>>\n";
			//	if (v.size() > 1)
			return BS(v, elem, st, mid - 1);
		} else if (v[mid].first < elem) {
	//		cout << "<<<<<<<<<<<<<<\n";
			//	if (v.size() > 1)
			return BS(v, elem, mid + 1, fn);

		}

		//return -1;
	}
	int BS(vector<pair<int, short> > &v, int elem, int st, int fn) {
		cout << st << " " << fn << endl;
		if (st > fn or v.size() == 0) {
			cout << "BS is returning -1" << endl;

			return -2;
		}

		int mid = (st + fn) / 2;
		cout << "BSS!! " << v[mid].first << " " << elem << endl;
		if (v[mid].first == elem) {
			cout << "returned this : " << mid << endl;
			return mid;

		} else if (v[mid].first > elem) {
			cout << ">>>>>>>>>>>>>>\n";
			//	if (v.size() > 1)
			return BS(v, elem, st, mid - 1);
		} else if (v[mid].first < elem) {
			cout << "<<<<<<<<<<<<<<\n";
			//	if (v.size() > 1)
			return BS(v, elem, mid + 1, fn);

		}

		//return -1;
	}
	void composite_search(string name, float gpa) {
		//vector<int> IDs;

		int name_IDX = BSS(NSKV, name, 0, NSKV.size());
		int gpa_IDX = BS(GSKV, gpa, 0, GSKV.size());

		//cout<<"IDX SIZES   " <<name_IDX<<" <<>> "<<gpa_IDX<<endl;
		if(name_IDX < 0  or gpa_IDX <0){
			cout<<"NOT FOUND !"<<endl;
			return ;
		}
		int Nsz = NSKV[name_IDX].second.size();
		int Gsz = GSKV[gpa_IDX].second.size();
		//	cout << "NN " << Nsz << " " << Gsz << endl;
		for (int i = 0, j = 0; i < Nsz and j < Gsz;) {

		//		cout << "CS  : " << NSKV[name_IDX].second[i] << " "
			//			<< GSKV[gpa_IDX].second[j] << endl;
		//		cout << " I J  : " << i << " " << j << endl;
		//		cout << " SZss   : " << Nsz << " " << Gsz << endl;
			if (NSKV[name_IDX].second[i] > GSKV[gpa_IDX].second[j]) {
				j++;
			} else if (NSKV[name_IDX].second[i] < GSKV[gpa_IDX].second[j]) {
				i++;
			} else {
			//		cout << "GONAA PRINT " << endl;
				displayStudent(NSKV[name_IDX].second[i], -1);
			//		cout << "DONE PRINT " << endl;
				i++;
				j++;
			}
		}

	}
	void printALL() {
		cout << "PK : " << endl;
		ReadVecPK(PKV, "Primary_keys.txt");
		cout << "GSK : " << endl;
		ReadVecSK(GSKV, "GPA_keys.txt");
		cout << "NSK : " << endl;
		ReadVecSK(NSKV, "NAME_keys.txt");
	}
};
//Interface
void TUI() {
	cout << "****************************************" << endl;
	cout << "\t Students Management System" << endl;
	cout << "****************************************" << endl;
	cout << "1)Add New Student\n" << "2)Update Student\n"
			<< "3)Delete Student\n" << "4)Search using ID\n"
			<< "5) Search using GPA\n6)Search using Name \n7)Search using Name and GPA\n";
	cout << "8) Display All \n9)exit\n10)Display Index Files\n";
	cout << "Please Enter Your Choice : ";
}

int main() {
	student ss;
	fstream file("students.txt", ios::in | ios::out | ios::binary | ios::app);
	//fstream file("students.bin", ios::in | ios::out | ios::binary | ios::app);
	//fstream file("students.txt", ios::in | ios::out | ios::binary);
	//fstream file("students.dat", ios::in | ios::out | ios::app);

	if (file.fail()) {
		cout << "Fail!" << endl;
		return 0;
	}

	file.seekp(0, ios::end);
	if (file.tellp() == 0) {
		file.seekp(0, ios::beg);
		cout << "DONE" << endl;
		short AL = 1;
		file.write((char*) &AL, sizeof(AL));
	}
	cout << "PK : " << endl;
	ss.ReadVecPK(PKV, "Primary_keys.txt");
	cout << "GSK : " << endl;
	ss.ReadVecSK(GSKV, "GPA_keys.txt");
	cout << "NSK : " << endl;
	ss.ReadVecSK(NSKV, "NAME_keys.txt");

	int choice;

	while (1) {
		TUI();
		cin >> choice;
		switch (choice) {
		case 1:
			ss.fillData();
			ss.writeToFile(-1);
		//	print(PKV);
		//	cout << "PK are done" << endl;
		//	print(GSKV);
		//	cout << "GSK are done" << endl;
		//	print(NSKV);
			//ss.BinwriteToFile(file);
			break;
		case 2:
			int updateID;
			cout << "Enter Student ID to Be updated : ";
			cin >> updateID;
			ss.update(updateID);
			break;
		case 3:
			int deleteID;
			cout << "Enter Student ID to Be Deleted : ";
			cin >> deleteID;
			ss.deleteRecord(deleteID);
			break;
		case 4:
			int searchID;
			cout << "Enter Student ID \n";
			cin >> searchID;
			ss.displayStudent(searchID, -1);
			break;
		case 5:
			cout << "Enter GPA : ";
			float Tgpa;
			cin >> Tgpa;
			ss.displayByGPA(Tgpa);
			break;
		case 6: {
			cout << "Enter name : ";
			string Tname;
			cin >> Tname;
			ss.displayByName(Tname);
			break;
		}

		case 7: {
			string TTname;
			float TTgpa;
			cout << "Enter name : ";
			cin >> TTname;
			cout << "Enter gpa : ";
			cin >> TTgpa;
			ss.composite_search(TTname, TTgpa);
			break;
		}

		case 8:
			ss.Display(file);
			break;

		case 9:
			return 0;
			break;
		case 10:
			ss.printALL();
			break;
		default:

			continue;
		}
	}
	return 0;

}

