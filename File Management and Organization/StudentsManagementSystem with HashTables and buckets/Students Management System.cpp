#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class three {
public:
	const char DELETE_FLAG = '*';
	const int BUCKET_SIZE = 1;
	const int RECORD_LEN = 120;
	const int HASH_ROW = 2 + (BUCKET_SIZE * (50 + 4)) + 2; //58
	const int BUCKET_LEN = 50 + 4;
	const int HASH_FILE_SIZE = HASH_ROW * 100;

	int H1(char* x) {

		return max((((int) x[0] * (int) x[1]) % 100), 1);
	}

	int H2(char* x) {
		return max((((int) x[2] * (int) x[3]) % 20), 1);
	}

	//initalize
	//vector <pair <int ,  vector < pair < string , int > > > > hash1 ( 100 );

	struct student {

		char Name[50];
		char GPA[5];
		char Address[50];
		char Mobile[12];
		char Department[3];
		//From user to struct
		string add_padding(char* s, int len) {

			string ss = s;
			for (int i = strlen(s); i < len; i++) {
				ss += ' ';
			}
			return ss;
		}
		string remove_padding(char* s, int len) {

			string ss = s;
			int i;
			for (i = len - 1; i > 0; i--) {
				if (ss[i] != ' ') {
					i++;
					break;
				}
			}
			return ss.substr(0, i);
		}

		void fillData() {
			cin.ignore();
			string temp;

			cout << "Enter Student Name: ";
			cin.getline(Name, 50);
			temp = add_padding(Name, 50);
			strcpy(Name, temp.c_str());
			Name[50 - 1] = '\0';

			//	cout << "$" << Name << "$" << endl;

			cout << "Enter Student GPA : ";
			cin.getline(GPA, 5);
			temp = add_padding(GPA, 5);
			strcpy(GPA, temp.c_str());
			GPA[5 - 1] = '\0';

			//	cout << "$" << GPA << "$" << endl;

			cout << "Enter Student Address: ";
			cin.getline(Address, 50);
			temp = add_padding(Address, 50);
			strcpy(Address, temp.c_str());
			Address[50 - 1] = '\0';

			//	cout << "$" << Address << "$" << endl;

			cout << "Enter Student Mobile: ";
			cin.getline(Mobile, 12);
			temp = add_padding(Mobile, 12);
			strcpy(Mobile, temp.c_str());
			Mobile[12 - 1] = '\0';

			//	cout << "$" << Mobile << "$" << endl;

			cout << "Enter Student Department: ";
			cin.getline(Department, 3);
			temp = add_padding(Department, 3);
			strcpy(Department, temp.c_str());
			Department[3 - 1] = '\0';

			//	cout << "$" << Department << "$" << endl;
		}
		void print_This() {
			cout << "|" << Name << "|" << strlen(Name) << endl;
			cout << "|" << GPA << "|" << strlen(GPA) << endl;
			cout << "|" << Address << "|" << strlen(Address) << endl;
			cout << "|" << Mobile << "|" << strlen(Mobile) << endl;
			cout << "|" << Department << "|" << strlen(Department) << endl;
		}
		void empty() {
			memset(Name, ' ', 50 * sizeof(char));
			memset(GPA, ' ', 4 * sizeof(char));
			memset(Address, ' ', 50 * sizeof(char));
			memset(Mobile, ' ', 12 * sizeof(char));
			memset(Department, ' ', 3 * sizeof(char));
		}

	};

	void writeToh1(char * PK, int offset) {
		int HX = H1(PK);
		int idx = HX * HASH_ROW;
		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		hfile.seekg(0, ios::end);

		hfile.seekg(idx, ios::beg);
		short counter;
		hfile.read((char*) &counter, sizeof(short));
		//cout << "COUNTER " << counter << "  IDX  " << hfile.tellg()
		//		<< "    --  " << idx << endl;

		if (counter == BUCKET_SIZE) {
			fstream over_flow("overflow.txt", ios::in | ios::out | ios::binary);
			over_flow.seekp(0, ios::end);
			int new_head = over_flow.tellg();

			hfile.seekg(BUCKET_LEN, ios::cur);
			int old_head;
			hfile.read((char*) &old_head, sizeof(old_head));
			hfile.seekg(-4, ios::cur);
			hfile.write((char*) &new_head, sizeof(new_head));
			//	cout << "NEW HEad " << new_head << endl;
			//	cout << " Over Flow ADDING FROMMMMM : " << over_flow.tellp()
			//<< endl;
			over_flow.write(PK, 50);
			over_flow.write((char*) &offset, sizeof(offset));
			over_flow.write((char*) &old_head, sizeof(old_head));
			//	cout << "Over Flow ADDING ENDSSSS : " << over_flow.tellp() << endl;
			hfile.close();
			over_flow.close();
		} else {

			//	cout << "ADDING FROMMMMM : " << hfile.tellp() << endl;
			hfile.write(PK, 50);
			hfile.write((char*) &offset, sizeof(offset));
			//	cout << "ADDING ENDSSSS : " << hfile.tellp() << endl;
			hfile.seekg(idx, ios::beg);
			counter++;
			hfile.write((char*) &counter, sizeof(short));

			hfile.close();

		}

	}

	short Readfromh1(char * PK, int mode) {
		int HX = H1(PK);
		int idx = HX * HASH_ROW;
		//int newHX = HX;
		int newIDX = idx;

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		hfile.seekg(newIDX, ios::beg);

		short counter;
		hfile.read((char*) &counter, sizeof(short));

		char temp[50];
		hfile.read(temp, 50);
		/*cout << "|" << PK << "|" << strlen(PK) << " " << strlen(temp)
		 << " |" << temp << "|" << endl;*/
		if (temp[0] == '/') {
			return -1;
		}
		if (strcmp(PK, temp) == 0) {
			int offset;
			if (mode == 1) {
				hfile.read((char*) &offset, sizeof(offset));
				return offset;
			}
		}

		hfile.seekg(4, ios::cur);
		int head;
		hfile.read((char*) &head, sizeof(head));
		cout << "ST HEAD" << head << "--" << hfile.tellg() << endl;
		if (head == -1) {
			return -1;
		}
		fstream over_flow("overflow.txt", ios::in | ios::out | ios::binary);

		while (head != -1) {
			cout << "HEAD " << head << endl;
			over_flow.seekg(head, ios::beg);
			over_flow.read(temp, 50);
			if (strcmp(PK, temp) == 0) {
				int offset;
				if (mode == 1) {
					over_flow.read((char*) &offset, sizeof(offset));
					return offset;
				}

			} else {
				over_flow.seekg(4, ios::cur);
				over_flow.read((char*) &head, sizeof(head));
			}
		}

		hfile.close();
		return -1;

	}
	void writeToFile(student s, fstream& data) {

		data.seekg(0, ios::end);

		//Add to h1 ;

		writeToh1(s.Name, data.tellg());

		data.write(s.Name, 50);
		data.write(s.GPA, 5);
		data.write(s.Address, 50);
		data.write(s.Mobile, 12);
		data.write(s.Department, 3);

		data.close();
		data.open("students.txt", ios::in | ios::out | ios::binary);

	}
	void initializeFile(fstream& ofile) {
		short counter = 0;
		short ptr = -1;
		char s = '/';
		for (int i = 0; i < 100; i++) {

			ofile.write((char*) &counter, sizeof(short));

			for (int j = 0; j < HASH_ROW - 2 - 2; j++) {
				ofile.write((char*) &s, sizeof(char));
			}
			ofile.write((char*) &ptr, sizeof(short));

		}

		ofile.flush();

	}

	void displayStudent(int offset) {

		fstream out;
		out.open("students.txt", ios::in | ios::out | ios::binary);

		out.seekg(offset, ios::beg);

		char info[51];

		cout << "Start reading from : " << out.tellg() << endl;
		//	cout << "REcord starts at : " << out.tellp() << endl;
		cout << "---------------------------------------------------\n";

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Name : \n#" << info << "#" << endl;

		out.read(info, 5);
		info[5] = '\0';
		cout << "Student GPA : \n#" << info << "#" << endl;

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Address : \n#" << info << "#" << endl;

		out.read(info, 12);
		info[12] = '\0';
		cout << "Student mobile : \n#" << info << "#" << endl;

		out.read(info, 3);
		info[3] = '\0';
		cout << "Student Department : \n#" << info << "#" << endl;
		cout << "END reading from : " << out.tellg() << endl;
		cout << endl;
		out.close();

	}
	void searchStudent(char name[], fstream& ifile) {
		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		int idx = Readfromh1(name, 1);
		if (idx == -1) {
			cout << "Not found break" << endl;
			;
			return;
		}
		displayStudent(idx);

	}

	void deleteStudent(char name[], fstream& ifile) {

		int H1_idx = Readfromh1(name, -1);
		int data_idx = Readfromh1(name, 1);

		ifile.seekg(data_idx, ios::beg);
		ifile.write((char*) &DELETE_FLAG, sizeof(DELETE_FLAG));

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		hfile.seekg(H1_idx, ios::beg);

		short counter;
		hfile.read((char*) &counter, sizeof(counter));
		counter--;
		hfile.seekg(-2, ios::cur);
		hfile.write((char*) &counter, sizeof(counter));

		char temp[50];
		hfile.read(temp, 50);
//		cout << "|" << temp << "|" << strlen(temp) << " " << strlen(name)
		//			<< " |" << name << "|" << endl;
		if (strcmp(temp, name) == 0) {
			hfile.seekg(-50, ios::cur);
			//	cout << "#########" << endl;
			char tompStone = '#';
			for (int j = 0; j < RECORD_LEN; j++) {
				hfile.write((char*) &tompStone, sizeof(tompStone));
			}
			return;
		} else {

			fstream over_flow("overflow.txt", ios::in | ios::out | ios::binary);
			//skip offset
			hfile.seekg(4, ios::cur);
			int head;
			hfile.read((char*) &head, sizeof(head));
			int prev = head;
			while (head != -1) {
				over_flow.seekg(head, ios::beg);
				over_flow.read(temp, 50);
				if (strcmp(temp, name) == 0) {
					hfile.seekg(-50, ios::cur);

					char tompStone = '#';
					for (int j = 0; j < RECORD_LEN; j++) {
						hfile.write((char*) &tompStone, sizeof(tompStone));
					}
					return;
				}
			}
		}

	}
	void TUI() {
		cout << "****************************************" << endl;
		cout << "\t Students Management System" << endl;
		cout << "****************************************" << endl;
		cout << "1)Add New Student\n" << "3)Delete Student\n"
				<< "4)Search using ID\n";
		cout << "8) Display All \n9)exit\n";
		cout << "Please Enter Your Choice : ";
	}
	double avgTime() {
		fstream Hfile("h1.txt", ios::in | ios::out | ios::binary);
		fstream data("students.txt", ios::in | ios::out | ios::binary);
		double NumOfRecs = 0;
		double times = 0.0;

		for (int i = 0; i < 100; i++) {
			//cout<<i<<" ->> "<<Hfile.tellg()<<endl;
			short counter;
			Hfile.read((char*) &counter, sizeof(counter));
			if (counter == 0) {
				Hfile.seekg(HASH_ROW - 2, ios::cur);
				continue;
			}
			for (int j = 0; j < BUCKET_SIZE; j++) {
				char temp[51];
				Hfile.read(temp, 50);
				if (temp[0] != '/' and temp[0] != '#') {
					//cout << "----" << temp << endl;
					NumOfRecs++;
					clock_t tStart = clock();
					searchStudent(temp, data);
					times += (double) (clock() - tStart) / CLOCKS_PER_SEC;
				}
				Hfile.seekg(4, ios::cur);
			}
		}
		return times / NumOfRecs;
	}
	int run() {
		student ss;
		//fstream file("students.txt", ios::in | ios::out | ios::binary);
		fstream file("students.txt",
				ios::in | ios::out | ios::binary | ios::trunc);
		fstream H1file("h1.txt", ios::in | ios::out | ios::binary | ios::trunc);

		if (file.fail() or H1file.fail()) {
			cout << "Fail!" << endl;
			return 0;
		}
		initializeFile(H1file);
		cout << "Done " << endl;
		int choice;

		while (1) {
			TUI();
			cin >> choice;
			switch (choice) {
			case 1: {
				ss.fillData();
				writeToFile(ss, file);
				break;
			}

			case 2: {
				char Tname[50];
				cout << "Enter name to search : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				searchStudent(Tname, file);

				break;
			}
			case 3: {
				char Tname[50];
				cout << "Enter name to Delete : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				deleteStudent(Tname, file);

				break;
			}
			case 8:
				cout << setprecision(9) << "Avarage time for one is : "
						<< avgTime() << endl << endl;
				break;
			case 9:
				return 0;
				break;

			default:
				continue;
			}
		}
		return 0;

	}
};

class two {
public:

	const char DELETE_FLAG = '*';
	const int BUCKET_SIZE = 2;
	const int RECORD_LEN = 120;
	const int HASH_ROW = 2 + BUCKET_SIZE * (50 + 4); //110
	const int BUCKET_LEN = 50 + 4;
	const int HASH_FILE_SIZE = HASH_ROW * 100;

	int H1(char* x) {
		return max((((int) x[0] * (int) x[1]) % 100), 1);
	}

	int H2(char* x) {
		return max((((int) x[2] * (int) x[3]) % 20), 1);
	}

	struct student {

		char Name[50];
		char GPA[5];
		char Address[50];
		char Mobile[12];
		char Department[3];
		//From user to struct
		string add_padding(char* s, int len) {

			string ss = s;
			for (int i = strlen(s); i < len; i++) {
				ss += ' ';
			}
			return ss;
		}
		string remove_padding(char* s, int len) {

			string ss = s;
			int i;
			for (i = len - 1; i > 0; i--) {
				if (ss[i] != ' ') {
					i++;
					break;
				}
			}
			return ss.substr(0, i);
		}

		void fillData() {
			cin.ignore();
			string temp;

			cout << "Enter Student Name: ";
			cin.getline(Name, 50);
			temp = add_padding(Name, 50);
			strcpy(Name, temp.c_str());
			Name[50 - 1] = '\0';

			cout << "Enter Student GPA : ";
			cin.getline(GPA, 5);
			temp = add_padding(GPA, 5);
			strcpy(GPA, temp.c_str());
			GPA[5 - 1] = '\0';

			cout << "Enter Student Address: ";
			cin.getline(Address, 50);
			temp = add_padding(Address, 50);
			strcpy(Address, temp.c_str());
			Address[50 - 1] = '\0';

			cout << "Enter Student Mobile: ";
			cin.getline(Mobile, 12);
			temp = add_padding(Mobile, 12);
			strcpy(Mobile, temp.c_str());
			Mobile[12 - 1] = '\0';

			cout << "Enter Student Department: ";
			cin.getline(Department, 3);
			temp = add_padding(Department, 3);
			strcpy(Department, temp.c_str());
			Department[3 - 1] = '\0';

		}
		void print_This() {
			cout << "|" << Name << "|" << strlen(Name) << endl;
			cout << "|" << GPA << "|" << strlen(GPA) << endl;
			cout << "|" << Address << "|" << strlen(Address) << endl;
			cout << "|" << Mobile << "|" << strlen(Mobile) << endl;
			cout << "|" << Department << "|" << strlen(Department) << endl;
		}
		void empty() {
			memset(Name, ' ', 50 * sizeof(char));
			memset(GPA, ' ', 4 * sizeof(char));
			memset(Address, ' ', 50 * sizeof(char));
			memset(Mobile, ' ', 12 * sizeof(char));
			memset(Department, ' ', 3 * sizeof(char));
		}

	};

	void writeToh1(char * PK, int offset) {
		int HX = H1(PK);
		int idx = HX * HASH_ROW;
		int HX2 = H2(PK);

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		hfile.seekg(idx, ios::beg);
		short counter;

		hfile.read((char*) &counter, sizeof(short));

		while (counter == BUCKET_SIZE) {
			cout << "Bucket correction" << endl;
			hfile.seekg(-2, ios::cur);
			int tt = hfile.tellg();
			cout << tt << " ==> " << (tt + (HX2 * HASH_ROW) % HASH_FILE_SIZE)
					<< " " << HX2 << endl;
			hfile.seekg((tt + (HX2 * HASH_ROW) % HASH_FILE_SIZE), ios::beg);
			hfile.read((char*) &counter, sizeof(short));

		}

//hfile.seekg(idx + 2, ios::beg);
		for (int i = 0; i < BUCKET_SIZE; i++) {
			char temp[50];
			hfile.read(temp, 50);

			if (temp[0] == '/' or temp[0] == '#') {
				hfile.seekg(-50, ios::cur);

				hfile.write(PK, 50);
				hfile.write((char*) &offset, sizeof(offset));

				hfile.seekg(idx, ios::beg);
				counter++;
				hfile.write((char*) &counter, sizeof(short));
				break;
			} else {
				hfile.seekg(-50, ios::cur);
				hfile.seekg(BUCKET_LEN, ios::cur);
			}

		}

		hfile.close();
	}

	short Readfromh1(char * PK, int mode) {
		int HX = H1(PK);
		int HX2 = H2(PK);
		int idx = HX * HASH_ROW;
		int newHX = HX;
		int newIDX = idx;

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		while (true) {
			hfile.seekg(newIDX % HASH_FILE_SIZE, ios::beg);
			short counter;

			hfile.read((char*) &counter, sizeof(short));

			for (int i = 0; i < BUCKET_SIZE; i++) {
				char temp[50];
				hfile.read(temp, 50);

				if (strcmp(PK, temp) == 0) {
					int offset;
					if (mode == 1) {
						hfile.read((char*) &offset, sizeof(offset));
						return offset;
					} else {
						return newIDX;
					}

				}

				if (temp[0] == '/') {
					return -1;
				}
				hfile.seekg(4, ios::cur);
			}

			newHX = (newHX + HX2) % 100;
			newIDX = newHX * HASH_ROW;

			if (newHX == HX) {
				return -1;
			}
		}

		hfile.close();
		//return -1;

	}
	void writeToFile(student s, fstream& data) {

		data.seekg(0, ios::end);

//Add to h1 ;

		writeToh1(s.Name, data.tellg());

		data.write(s.Name, 50);
		data.write(s.GPA, 5);
		data.write(s.Address, 50);
		data.write(s.Mobile, 12);
		data.write(s.Department, 3);

		data.flush();

	}
	void initializeFile(fstream& ofile) {
		short counter = 0;
		char s = '/';
		for (int i = 0; i < 100; i++) {
			cout << ofile.tellg() << endl;
			ofile.write((char*) &counter, sizeof(short));
			ofile.seekg(-2, ios::cur);
			ofile.read((char*) &counter, sizeof(short));
			cout << counter;
			for (int j = 0; j < HASH_ROW - 2; j++) {
				ofile.write((char*) &s, sizeof(char));
			}

		}

	}

	void displayStudent(int offset) {

		fstream out;
		out.open("students.txt", ios::in | ios::out | ios::binary);

		out.seekg(offset, ios::beg);

		char info[51];

		cout << "Start reading from : " << out.tellg() << endl;

		cout << "---------------------------------------------------\n";

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Name : \n#" << info << "#" << endl;

		out.read(info, 5);
		info[5] = '\0';
		cout << "Student GPA : \n#" << info << "#" << endl;

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Address : \n#" << info << "#" << endl;

		out.read(info, 12);
		info[12] = '\0';
		cout << "Student mobile : \n#" << info << "#" << endl;

		out.read(info, 3);
		info[3] = '\0';
		cout << "Student Department : \n#" << info << "#" << endl;
		cout << "END reading from : " << out.tellg() << endl;
		cout << endl;
		out.close();

	}

	void searchStudent(char name[], fstream& ifile) {
		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		int idx = Readfromh1(name, 1);
		if (idx == -1) {
			cout << "Not found break" << endl;
			;
			return;
		}
		displayStudent(idx);

	}

	void deleteStudent(char name[], fstream& ifile) {

		int H1_idx = Readfromh1(name, -1);
		int data_idx = Readfromh1(name, 1);

		ifile.seekg(data_idx, ios::beg);
		ifile.write((char*) &DELETE_FLAG, sizeof(DELETE_FLAG));

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		hfile.seekg(H1_idx, ios::beg);
		short counter;
		hfile.read((char*) &counter, sizeof(counter));
		counter--;
		hfile.seekg(-2, ios::cur);
		hfile.write((char*) &counter, sizeof(counter));
		for (int i = 0; i < BUCKET_SIZE; i++) {
			char temp[50];
			hfile.read(temp, 50);
			if (strcmp(temp, name) == 0) {
				hfile.seekg(-50, ios::cur);
				char tompStone = '#';
				for (int j = 0; j < RECORD_LEN; j++) {
					hfile.write((char*) &tompStone, sizeof(tompStone));
				}
				return;
			}
			hfile.seekg(4, ios::cur);
		}
	}
	void TUI() {
		cout << "****************************************" << endl;
		cout << "\t Students Management System" << endl;
		cout << "****************************************" << endl;
		cout << "1)Add New Student\n" << "3)Delete Student\n"
				<< "4)Search using ID\n";
		cout << "8) Display All \n9)exit\n";
		cout << "Please Enter Your Choice : ";
	}
	double avgTime() {
		fstream Hfile("h1.txt", ios::in | ios::out | ios::binary);
		fstream data("students.txt", ios::in | ios::out | ios::binary);
		double NumOfRecs = 0;
		double times = 0.0;

		for (int i = 0; i < 100; i++) {
			//cout<<i<<" ->> "<<Hfile.tellg()<<endl;
			short counter;
			Hfile.read((char*) &counter, sizeof(counter));
			if (counter == 0) {
				Hfile.seekg(HASH_ROW - 2, ios::cur);
				continue;
			}
			for (int j = 0; j < BUCKET_SIZE; j++) {
				char temp[51];
				Hfile.read(temp, 50);
				if (temp[0] != '/' and temp[0] != '#') {
					//cout << "----" << temp << endl;
					NumOfRecs++;
					clock_t tStart = clock();
					searchStudent(temp, data);
					times += (double) (clock() - tStart) / CLOCKS_PER_SEC;
				}
				Hfile.seekg(4, ios::cur);
			}
		}
		return times / NumOfRecs;
	}
	int run() {
		student ss;
		//fstream file("students.txt", ios::in | ios::out | ios::binary);
		fstream file("students.txt",
				ios::in | ios::out | ios::binary | ios::trunc);
		fstream H1file("h1.txt", ios::in | ios::out | ios::binary | ios::trunc);

		if (file.fail() or H1file.fail()) {
			cout << "Fail!" << endl;
			return 0;
		}
		initializeFile(H1file);
		cout << "Done " << endl;
		int choice;

		while (1) {
			TUI();
			cin >> choice;
			switch (choice) {
			case 1: {
				ss.fillData();
				writeToFile(ss, file);
				break;
			}

			case 2: {
				char Tname[50];
				cout << "Enter name to search : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				searchStudent(Tname, file);

				break;
			}
			case 3: {
				char Tname[50];
				cout << "Enter name to Delete : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				deleteStudent(Tname, file);

				break;
			}
			case 8:
				cout << setprecision(9) << "Avarage time for one is : "
						<< avgTime() << endl << endl;
				break;
			case 9:
				return 0;
				break;

			default:
				continue;
			}
		}
		return 0;

	}

};

class one {
public:

	const char DELETE_FLAG = '*';
	const int BUCKET_SIZE = 3;
	const int RECORD_LEN = 120;
	const int HASH_ROW = 2 + BUCKET_SIZE * (50 + 4); //164
	const int BUCKET_LEN = 50 + 4;
	const int HASH_FILE_SIZE = HASH_ROW * 100;
	int H1(char* x) {
		return max((((int) x[0] * (int) x[1]) % 100), 1);
	}

	int H2(char* x) {
		return max((((int) x[2] * (int) x[3]) % 20), 1);
	}

	//initalize
	//vector <pair <int ,  vector < pair < string , int > > > > hash1 ( 100 );

	struct student {

		char Name[50];
		char GPA[5];
		char Address[50];
		char Mobile[12];
		char Department[3];
		//From user to struct
		string add_padding(char* s, int len) {

			string ss = s;
			for (int i = strlen(s); i < len; i++) {
				ss += ' ';
			}
			return ss;
		}
		string remove_padding(char* s, int len) {

			string ss = s;
			int i;
			for (i = len - 1; i > 0; i--) {
				if (ss[i] != ' ') {
					i++;
					break;
				}
			}
			return ss.substr(0, i);
		}

		void fillData() {
			cin.ignore();
			string temp;

			cout << "Enter Student Name: ";
			cin.getline(Name, 50);
			temp = add_padding(Name, 50);
			strcpy(Name, temp.c_str());
			Name[50 - 1] = '\0';

			//	cout << "$" << Name << "$" << endl;

			cout << "Enter Student GPA : ";
			cin.getline(GPA, 5);
			temp = add_padding(GPA, 5);
			strcpy(GPA, temp.c_str());
			GPA[5 - 1] = '\0';

			//	cout << "$" << GPA << "$" << endl;

			cout << "Enter Student Address: ";
			cin.getline(Address, 50);
			temp = add_padding(Address, 50);
			strcpy(Address, temp.c_str());
			Address[50 - 1] = '\0';

			//	cout << "$" << Address << "$" << endl;

			cout << "Enter Student Mobile: ";
			cin.getline(Mobile, 12);
			temp = add_padding(Mobile, 12);
			strcpy(Mobile, temp.c_str());
			Mobile[12 - 1] = '\0';

			//cout << "$" << Mobile << "$" << endl;

			cout << "Enter Student Department: ";
			cin.getline(Department, 3);
			temp = add_padding(Department, 3);
			strcpy(Department, temp.c_str());
			Department[3 - 1] = '\0';

			//	cout << "$" << Department << "$" << endl;
		}
		void print_This() {
			cout << "|" << Name << "|" << strlen(Name) << endl;
			cout << "|" << GPA << "|" << strlen(GPA) << endl;
			cout << "|" << Address << "|" << strlen(Address) << endl;
			cout << "|" << Mobile << "|" << strlen(Mobile) << endl;
			cout << "|" << Department << "|" << strlen(Department) << endl;
		}
		void empty() {
			memset(Name, ' ', 50 * sizeof(char));
			memset(GPA, ' ', 4 * sizeof(char));
			memset(Address, ' ', 50 * sizeof(char));
			memset(Mobile, ' ', 12 * sizeof(char));
			memset(Department, ' ', 3 * sizeof(char));
		}

	};

	void writeToh1(char * PK, int offset) {
		int HX = H1(PK);
		int idx = HX * HASH_ROW;
		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		hfile.seekg(idx, ios::beg);
		short counter;
		hfile.read((char*) &counter, sizeof(short));
		//	cout << "COUNTER " << counter << endl;

		while (counter == BUCKET_SIZE) {
			hfile.seekg(-2, ios::cur);
			int tt = hfile.tellg();

			hfile.seekg(((tt * HASH_ROW) % HASH_FILE_SIZE), ios::beg);
			hfile.read((char*) &counter, sizeof(short));

		}

		//hfile.seekg(idx + 2, ios::beg);
		for (int i = 0; i < 3; i++) {
			char temp[50];
			hfile.read(temp, 50);

			if (temp[0] == '/' or temp[0] == '#') {
				hfile.seekg(-50, ios::cur);
				//		cout << "ADDING FROMMMMM : " << hfile.tellp() << endl;
				hfile.write(PK, 50);
				hfile.write((char*) &offset, sizeof(offset));
				//		cout << "ADDING ENDSSSS : " << hfile.tellp() << endl;
				hfile.seekg(idx, ios::beg);
				counter++;
				hfile.write((char*) &counter, sizeof(short));
				break;
			} else {
				hfile.seekg(-50, ios::cur);
				hfile.seekg(BUCKET_LEN, ios::cur);
			}

		}

		hfile.close();
	}

	short Readfromh1(char * PK, int mode) {
		int HX = H1(PK);
		int idx = HX * HASH_ROW;
		int newHX = HX;
		int newIDX = idx;

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);

		while (true) {

			hfile.seekg(newIDX % HASH_FILE_SIZE, ios::beg);
			short counter;
			hfile.read((char*) &counter, sizeof(short));
			//	cout << "COUNTER " << counter << endl;
			for (int i = 0; i < BUCKET_SIZE; i++) {
				char temp[50];
				hfile.read(temp, 50);
				/*cout << "|" << PK << "|" << strlen(PK) << " " << strlen(temp)
				 << " |" << temp << "|" << endl;*/
				if (strcmp(PK, temp) == 0) {
					int offset;
					if (mode == 1) {
						hfile.read((char*) &offset, sizeof(offset));
						return offset;
					} else {
						return newIDX;
					}

				}

				if (temp[0] == '/') {
					return -1;
				}
				hfile.seekg(4, ios::cur);
			}

			newHX = (newHX + 1) % 100;
			newIDX = newHX * HASH_ROW;
			if (newHX == HX) {
				return -1;
			}
		}

		hfile.close();
		//return -1;

	}
	void writeToFile(student s, fstream& data) {

		data.seekg(0, ios::end);

		//Add to h1 ;

		writeToh1(s.Name, data.tellg());

		data.write(s.Name, 50);
		data.write(s.GPA, 5);
		data.write(s.Address, 50);
		data.write(s.Mobile, 12);
		data.write(s.Department, 3);

		data.close();
		data.open("students.txt", ios::in | ios::out | ios::binary);

	}
	void initializeFile(fstream& ofile) {
		short counter = 0;
		char s = '/';
		for (int i = 0; i < 100; i++) {
			ofile.write((char*) &counter, sizeof(short));
			for (int j = 0; j < HASH_ROW - 2; j++) {
				ofile.write((char*) &s, sizeof(char));
			}

		}

	}

	void displayStudent(int offset) {

		fstream out;
		out.open("students.txt", ios::in | ios::out | ios::binary);

		out.seekg(offset, ios::beg);

		char info[51];

		cout << "Start reading from : " << out.tellg() << endl;
		//	cout << "REcord starts at : " << out.tellp() << endl;
		cout << "---------------------------------------------------\n";

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Name : \n#" << info << "#" << endl;

		out.read(info, 5);
		info[5] = '\0';
		cout << "Student GPA : \n#" << info << "#" << endl;

		out.read(info, 50);
		info[50] = '\0';
		cout << "Student Address : \n#" << info << "#" << endl;

		out.read(info, 12);
		info[12] = '\0';
		cout << "Student mobile : \n#" << info << "#" << endl;

		out.read(info, 3);
		info[3] = '\0';
		cout << "Student Department : \n#" << info << "#" << endl;
		cout << "END reading from : " << out.tellg() << endl;
		cout << endl;
		out.close();

	}
	void searchStudent(char name[], fstream& ifile) {
		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		int idx = Readfromh1(name, 1);
		if (idx == -1) {
			cout << "Not found break" << endl;
			;
			return;
		}
		displayStudent(idx);

	}

	void deleteStudent(char name[], fstream& ifile) {

		int H1_idx = Readfromh1(name, -1);
		int data_idx = Readfromh1(name, 1);

		ifile.seekg(data_idx, ios::beg);
		ifile.write((char*) &DELETE_FLAG, sizeof(DELETE_FLAG));

		fstream hfile("h1.txt", ios::in | ios::out | ios::binary);
		hfile.seekg(H1_idx, ios::beg);
		short counter;
		hfile.read((char*) &counter, sizeof(counter));
		counter--;
		hfile.seekg(-2, ios::cur);
		hfile.write((char*) &counter, sizeof(counter));
		for (int i = 0; i < BUCKET_SIZE; i++) {
			char temp[50];
			hfile.read(temp, 50);
			//cout << "|" << temp << "|" << strlen(temp) << " " << strlen(name)
			//		<< " |" << name << "|" << endl;
			if (strcmp(temp, name) == 0) {
				hfile.seekg(-50, ios::cur);
				//	cout << "#########" << endl;
				char tompStone = '#';
				for (int j = 0; j < RECORD_LEN; j++) {
					hfile.write((char*) &tompStone, sizeof(tompStone));
				}
				return;
			}
			hfile.seekg(4, ios::cur);
		}
	}
	void TUI() {
		cout << "****************************************" << endl;
		cout << "\t Students Management System" << endl;
		cout << "****************************************" << endl;
		cout << "1)Add New Student\n" << "3)Delete Student\n"
				<< "4)Search using ID\n";
		cout << "8) Display All \n9)exit\n";
		cout << "Please Enter Your Choice : ";
	}
	double avgTime() {
		fstream Hfile("h1.txt", ios::in | ios::out | ios::binary);
		fstream data("students.txt", ios::in | ios::out | ios::binary);
		double NumOfRecs = 0;
		double times = 0.0;

		for (int i = 0; i < 100; i++) {
			//cout<<i<<" ->> "<<Hfile.tellg()<<endl;
			short counter;
			Hfile.read((char*) &counter, sizeof(counter));
			if (counter == 0) {
				Hfile.seekg(HASH_ROW - 2, ios::cur);
				continue;
			}
			for (int j = 0; j < BUCKET_SIZE; j++) {
				char temp[51];
				Hfile.read(temp, 50);
				if (temp[0] != '/' and temp[0] != '#') {
					//cout << "----" << temp << endl;
					NumOfRecs++;
					clock_t tStart = clock();
					searchStudent(temp, data);
					times += (double) (clock() - tStart) / CLOCKS_PER_SEC;
				}
				Hfile.seekg(4, ios::cur);
			}
		}
		cout << NumOfRecs << endl << endl;
		return times / NumOfRecs;
	}
	int run() {
		student ss;
		//fstream file("students.txt", ios::in | ios::out | ios::binary);
		fstream file("students.txt",
				ios::in | ios::out | ios::binary | ios::trunc);
		fstream H1file("h1.txt", ios::in | ios::out | ios::binary | ios::trunc);

		if (file.fail() or H1file.fail()) {
			cout << "Fail!" << endl;
			return 0;
		}
		initializeFile(H1file);
		cout << "Done " << endl;
		int choice;

		while (1) {
			TUI();
			cin >> choice;
			switch (choice) {
			case 1: {
				ss.fillData();
				writeToFile(ss, file);
				break;
			}

			case 2: {
				char Tname[50];
				cout << "Enter name to search : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				searchStudent(Tname, file);

				break;
			}
			case 3: {
				char Tname[50];
				cout << "Enter name to Delete : ";
				cin.ignore();
				cin.getline(Tname, 50);
				string Stemp = ss.add_padding(Tname, 49);
				strcpy(Tname, Stemp.c_str());
				deleteStudent(Tname, file);

				break;
			}
			case 8:
				cout << setprecision(9) << "Avarage time for one is : "
						<< avgTime() << endl << endl;
				break;
			case 9:
				return 0;
				break;

			default:
				continue;
			}
		}
		return 0;

	}
};

int main() {

	one X1;
	X1.run();

	two X2;
	X2.run();

	three X3;
	X3.run();

}

