#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const char DELETE_FLAG = '*';
const int FILE_HEADER_SIZE = sizeof(short);
const int MIN_RECORD_SIZE = 5;

/*
from char[] to T converter
*/
template<class T>
inline T STI(char x[]) {
	T t;
	stringstream ss;
	ss << x;
	ss >> t;
	return t;
}

/*
from T to char[] converter
*/
template<class T>
inline const char* ITS(T x) {
	string t;
	stringstream ss;
	ss << x;
	ss >> t;
	return t.c_str();
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

	void writeToFile(fstream &w, int idx) {
		//idx changes the mode of the function
		// if idx is NOT -1 it will write starting from idx
		//else it will look in the avail list normally
		// its used in the Update function where the lengths are equal

		w.close();
		w.open("students.txt", ios::in | ios::out | ios::binary);

		short szN = strlen(Name);
		short szA = strlen(Address);
		short szM = strlen(Mobile);
		short szI = strlen(ITS<int>(ID));
		short szG = strlen(ITS<float>(GPA));
		short len = szA + szM + szN + szI + szG + (2 * 5);

		short head;
		short longestDel;

		bool addedToAvail = 0;

		if (idx != -1) {
			// Update record with same length
			w.seekg(idx, ios::beg);

		} else {
			//Normal write to file

			w.seekg(0, ios::beg);

			w.read((char*) &head, sizeof(short));

			if (head != -1) {
				//there is deleted

				w.seekg(head, ios::beg);
				w.read((char*) &longestDel, sizeof(short));
				// The avail list is kept sorted with the largest index at the head
				

				if (longestDel >= len) {
				
					//can insert at avail list
					w.seekg(head, ios::beg);
					// indecates should i add left space or not
					addedToAvail = 1;
				} else {
					//add at the end
					w.seekg(0, ios::end);
				}
			}

			else {
				// no deleted .. add at the end
				w.seekg(0, ios::end);
			}
		}
		short diffrance = longestDel - len;

		
		if (addedToAvail and diffrance < MIN_RECORD_SIZE) {
			
			w.seekg(2, ios::cur);
		} else {
			
			w.write((char*) &len, sizeof(len));
		}

		w.write((char*) &szN, sizeof(szN));
		w.write(Name, szN);

		w.write((char*) &szI, sizeof(szI));
		w.write(ITS<int>(ID), szI);

		w.write((char*) &szG, sizeof(szG));
		w.write(ITS<float>(GPA), szG);

		w.write((char*) &szA, sizeof(szA));
		w.write(Address, szA);

		w.write((char*) &szM, sizeof(szM));
		w.write(Mobile, szM);

		if (addedToAvail and (diffrance > MIN_RECORD_SIZE)) {
			//write deleted record length and *
			w.write((char*) &diffrance, sizeof(diffrance));
			w.put(DELETE_FLAG);

			// send the deleted space to the delete function with flags
			//to indecate only adding the space to the avail list without deleteing
			deleteRecord(-1, w.tellp(), diffrance - 2 - 1);
		}

		w.close();
		w.open("students.txt", ios::in | ios::out | ios::binary | ios::app);

	}
	// writes the whole struct
	void BinwriteToFile(fstream &writer) {
		writer << this;
	}

	short searchByID(int Sid) {

		fstream out("students.txt",
				ios::in | ios::out | ios::binary | ios::app);
		out.seekg(FILE_HEADER_SIZE, ios::beg);

		short Rlen;
		short namelen;
		short IDlen;
		int id;
		short placeInFile = -1;

		while (!out.eof()) {

			out.read((char*) &Rlen, sizeof(Rlen));
			
			if (out.fail())
				break;
			char c;
			out.get(c);
			out.seekg(-1, ios::cur);
			

			if (c == DELETE_FLAG) {
				// Skip this record
				out.seekg(Rlen, ios::cur);
				continue;
			}

			//read name and ID
			out.read((char*) &namelen, sizeof(namelen));
			out.seekg(namelen, ios::cur);
			
			out.read((char*) &IDlen, sizeof(IDlen));
			
			char temp[IDlen];
			out.read(temp, IDlen);
			id = STI<int>(temp);

			if (id == Sid) {
				// id is found .. get the start of the record
				out.seekg(-(namelen + 2 + IDlen + 2), ios::cur);
				placeInFile = out.tellg();
				break;
			}
			//Not found .. return to the start of the record and skip it
			out.seekg(-(namelen + 2 + IDlen + 2), ios::cur);
			out.seekg(Rlen, ios::cur);
		}

		out.close();
		return placeInFile;
	}

	void displayStudent(int Sid) {

		fstream out;
		out.open("students.txt", ios::in | ios::out | ios::binary);
		out.seekg(FILE_HEADER_SIZE, ios::beg);

		short namelen;
		short IDlen;
		short GPAlen;
		short addlen;
		short moblen;
		char info[51];

		//get index by id
		short idx = searchByID(Sid);

		
		if (idx == -1) {

			cout << "---------------------------------------------------\n";
			cout << "NOT FOUND \n";

			return;
		}

		out.seekp(idx, ios::beg);

		
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

	void deleteRecord(int id, int st, int len) {

		//st and len are mode changers
		// if they both equal -1 it will delete a normal record by adding * and the length
		//if the != -1 it will treat this range as a deleted record
		//and ONLY adds it to the avail list
		// its used in the insert to add fragmented record back to the avail list

		fstream file("students.txt", ios::in | ios::out | ios::binary);

		short firstDeletedRecord;
		short prev;
		short Rlen;
		short idx;
		short headLen;

		char ignoreflag;
		//get the first idx

		file.seekg(0, ios::beg);
		file.read((char*) &firstDeletedRecord, FILE_HEADER_SIZE);
		//Normal delete
		if (st == -1 and len == -1) {
			idx = searchByID(id);
			
			if (idx == -1) {
				cout << "---------------------------------------------------\n";
				cout << "NOT FOUND \n";
				return;
			}

			if (firstDeletedRecord != -1) {
				// get the length of the first deleted
				file.seekg(firstDeletedRecord, ios::beg);
				file.read((char*) &headLen, sizeof(headLen));

			} else {
				//there is no deleted
				headLen = -1;
			}
			
			//prev keeps the deleted reord before the current

			prev = firstDeletedRecord;
			file.seekp(idx - 2, ios::beg);

			file.read((char*) &Rlen, sizeof(Rlen));
			file.seekp(idx, ios::beg);
			//Delete the decord
			

			file.put(DELETE_FLAG);

			file.seekg(-1, ios::cur);

		} else {
			//Other mode
			// the deleted record starts at st and its length is len

			idx = st;
			Rlen = len;
		}

//////////////////////////////////////////////////
// From here we only need the idx and the length
//////////////////////////////////////////////////

		// we have a fragment from the insert and we only want to add it to the avail list
		if (headLen < Rlen) {
			// the deleted record is larger that the head .. make it the new head
			file.seekp(idx + 1, ios::beg);
		
			file.write((char*) &firstDeletedRecord, sizeof(short));
			file.seekp(0, ios::beg);

		
			idx -= 2;
			file.write((char*) &idx, FILE_HEADER_SIZE);
			idx += 2;
			prev = firstDeletedRecord;

		} else {
			short thisLen;
			// add the deleted record in the SORTED avail list
			while (firstDeletedRecord != -1 and file.tellp() != -1) {
			

				file.seekg(firstDeletedRecord, ios::beg);
				file.read((char*) &thisLen, sizeof(thisLen));

			

				if (thisLen <= Rlen) {
					// found the right place
				
					// make prev-> next as idx
					file.seekg(prev + 3, ios::beg);
					idx -= 2;
					file.write((char*) &idx, sizeof(idx));
					idx += 2;
					file.seekg(idx + 1, ios::beg);
					file.write((char*) &firstDeletedRecord,
							sizeof(firstDeletedRecord));
					break;
				} else if (file.tellp() > -1) {
					//Move to next deleted record
				

					file.get(ignoreflag);

					prev = firstDeletedRecord;
				

					file.read((char*) &firstDeletedRecord,
							sizeof(firstDeletedRecord));

				
				}
				// reached end of avail list without being added
				// means its the smallest record
				//add at the end
				if (firstDeletedRecord == -1) {
					
					
					file.seekp(prev + 3, ios::beg);
					
					idx -= 2;
					file.write((char*) &idx, sizeof(idx));
					idx += 2;
					file.seekp(idx + 1, ios::beg);
					short temp = -1;
					
					
					file.write((char*) &temp, sizeof(temp));
					break;

				}
			}
		}

		

		cout << "Student : " << id << " was Deleted successfully \n\n";
	}

// Desplay the DEleted records
// NOT WORKING 
	void DisplayD(fstream &f) {
		f.close();
		f.open("students.txt", ios::in | ios::out | ios::binary | ios::app);
		short DelIdx;
		f.read((char*) &DelIdx, sizeof(DelIdx));

		while (!(f.eof()) and (DelIdx != -1)) {

			cout << "WE R AT " << DelIdx << endl;
			f.seekg(DelIdx, ios::beg);
			if (f.fail())
				break;
			short Rlen;
			f.read((char*) &Rlen, sizeof(Rlen));
			cout << "RRRRRRRRRLENN" << Rlen << endl;
			char c;
			f.get(c);

			if (c == DELETE_FLAG) {

				cout << "THERE is a deleted record AT : " << DelIdx
						<< " and its size is : " << Rlen << endl;

			}

			//cout<<"Gonna read deleted at " <<f.tellg()<<endl;
			f.read((char*) &DelIdx, sizeof(DelIdx));

		}
	}

	//Display NOT deleted records
	void Display(fstream &f) {

		f.close();
		f.open("students.txt", ios::in | ios::out | ios::binary | ios::app);
		short Rlen;
		short namelen;
		short IDlen;
		short GPAlen;
		short addlen;
		short moblen;
		char info[51];
		char c;
		f.seekg(FILE_HEADER_SIZE, ios::beg);
		//read all file
		while (!(f.eof()) and (Rlen != -1)) {

			f.read((char*) &Rlen, sizeof(Rlen));
			
			if (f.fail())
				return;

			

			f.get(c);
			
					<< endl;
			f.seekg(-1, ios::cur);
			// IF not deleted
			if (c != DELETE_FLAG) {
				int st = f.tellp();
				f.read((char*) &namelen, sizeof(namelen));
				f.read(info, namelen);
				info[namelen] = '\0';
				cout << "Student Name : \n" << info << endl;

				f.read((char*) &IDlen, sizeof(IDlen));
				f.read(info, IDlen);
				info[IDlen] = '\0';
				cout << "Student ID : \n" << info << endl;

				f.read((char*) &GPAlen, sizeof(GPAlen));
				f.read(info, GPAlen);
				info[GPAlen] = '\0';
				cout << "Student GPA : \n" << info << endl;

				f.read((char*) &addlen, sizeof(addlen));
				f.read(info, addlen);
				info[addlen] = '\0';
				cout << "Student Address : \n" << info << endl;

				f.read((char*) &moblen, sizeof(moblen));
				f.read(info, moblen);
				info[moblen] = '\0';
				cout << "Student mobile : \n" << info << endl;

				f.seekg( st , ios::beg);
				f.seekg(  Rlen , ios::cur);
				cout << endl;
				cout << endl;
			}
			//get to the start of the record
			// skip the record
			else{

				f.seekg(Rlen, ios::cur);
			}


		}

	}
	void update(short id) {
		fstream f;
		f.open("students.txt", ios::in | ios::out | ios::binary | ios::app);
		short idx = searchByID(id);

		if (idx == -1) {
			cout << "ID not found " << endl;
			return;
		}
		//NEW data
		fillData();

		short oldLen;

		short szN = strlen(Name);
		short szA = strlen(Address);
		short szM = strlen(Mobile);
		short szI = strlen(ITS<int>(ID));
		short szG = strlen(ITS<float>(GPA));
		short newLen = szA + szM + szN + szI + szG + (2 * 5);

		idx -= 2;

		f.read((char*) &oldLen, sizeof(short));

		if (oldLen == newLen) {
			//At the same place
			//using idx as a mode for the writeToFile function
			writeToFile(f, idx);
		} else {
			//from the avail list
			deleteRecord(id, -1, -1);
			writeToFile(f, -1);
		}

	}

	void compact() {
		fstream f("students.txt", ios::in | ios::out | ios::binary | ios::app);
		f.seekg(FILE_HEADER_SIZE, ios::beg);
		short st;
		short len;
		char flag;
		while (!f.eof()) {
			short Rlen;
			f.read((char*) &Rlen, sizeof(Rlen));
			if (f.fail()) {
			
				break;
			}
			f.get(flag);
			
			if (flag == DELETE_FLAG) {
				f.seekg(-1, ios::cur);
				st = f.tellg() - 2;
				len += Rlen + 2;
				short count = 1;
				f.seekg(Rlen, ios::cur);
				while (!(f.eof())) {

					short NewRlen;
					char NewFlag;
					f.read((char*) &NewRlen, sizeof(NewRlen));
					if (f.fail()) {

						break;
					}
					f.get(NewFlag);
							<< NewFlag << endl;
					if (NewFlag != DELETE_FLAG) {
						break;
					}
					count++;
							<< endl;
					len += NewRlen + 2;
					f.seekg(-1, ios::cur);
							<< endl;
					f.seekg(NewRlen, ios::cur);

				}
				if (count > 1) {
					f.seekg(-1 - 2, ios::cur);

				} else {
					f.seekg(Rlen, ios::cur);
				}
			} else {
				f.seekg(-1, ios::cur);

				f.seekg(Rlen, ios::cur);
			}
		}
	}
};
//Interface
void TUI() {
	cout << "****************************************" << endl;
	cout << "\t Students Management System" << endl;
	cout << "****************************************" << endl;
	cout << "1)Add New Student\n" << "2)Update Student\n"
			<< "3)Delete Student\n" << "4)Display Student\n"
			<< "5)Compact Available Records List\n6)Display\n7)Exit\n";
	cout << "8) Display deleted \n";
	cout << "Please Enter Your Choice : ";
}

int main() {

	fstream file("students.txt", ios::in | ios::out | ios::binary | ios::app);

	if (file.fail()) {
		cout << "Fail!" << endl;
		return 0;
	}

	file.seekp(0, ios::end);
	if (file.tellp() == 0) {
		file.seekp(0, ios::beg);
		short AL = -1;
		file.write((char*) &AL, sizeof(AL));
	}
	int choice;
	student ss;
	while (1) {
		TUI();
		cin >> choice;
		switch (choice) {
		case 1:
			ss.fillData();
			ss.writeToFile(file, -1);
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
			ss.deleteRecord(deleteID, -1, -1);
			break;
		case 4:
			int searchID;
			cout << "Enter Student ID \n";
			cin >> searchID;
			ss.displayStudent(searchID);
			break;
		case 5:
			ss.compact();
			break;
		case 6:
			ss.Display(file);
			break;
		case 7:
			file.close();
			return 0;
			break;
		case 8:
			ss.DisplayD(file);
			break;
		default:
			continue;
		}
	}

	return 0;

}

