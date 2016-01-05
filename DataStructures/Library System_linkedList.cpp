#include <bits/stdc++.h>
using namespace std;

class book {

public:
	string name;
	string auth;
	int count;
	book() {
		name = "";
		auth = "";
		count = -1;
	}
	book(string n, string a, int c) {

		name = n;
		auth = a;
		count = c;
		cout << "Creating Book " << endl;
	}
};

struct node {
	book info;
	node *next = NULL;
	node *prev = NULL;
};

class double_llist {
public:
	node * start;

	double_llist() {
		start = NULL;
	}
	void create_list(book value) {
		node *s, *temp;
		temp = new node;
		temp->info = value;
		temp->next = NULL;
		if (start == NULL) {
			temp->prev = NULL;
			start = temp;
		} else {
			s = start;
			while (s->next != NULL)
				s = s->next;
			s->next = temp;
			temp->prev = s;
		}
	}

	node* search_list(node *head, string item) {
		item[0] = toupper(item[0]);

		while (head != NULL) {

			if (head->info.name == item) {

				return head;
			}

			head = head->next;
		}

		return NULL;

	}

	void add_begin(book value) {

		if (start == NULL) {
			cout << "First Create the list." << endl;
			create_list(value);

			return;
		}
		node * already_in = search_list(start, value.name);
		if (already_in != NULL) {
			already_in->info.count = value.count;
			return;
		}

		node *temp;
		temp = new node;
		temp->prev = NULL;
		temp->info = value;
		temp->next = start;
		start->prev = temp;
		start = temp;
		cout << "Element Inserted" << endl;
	}

	void add_after(book value, int pos) {
		if (start == NULL) {
			cout << "First Create the list." << endl;
			create_list(value);
			return;
		}
		struct node *tmp, *q;
		int i;
		q = start;
		for (i = 0; i < pos - 1; i++) {
			q = q->next;
			if (q == NULL) {
				cout << "There are less than ";
				cout << pos << " elements." << endl;
				return;
			}
		}
		tmp = new (struct node);
		tmp->info = value;
		if (q->next == NULL) {
			q->next = tmp;
			tmp->next = NULL;
			tmp->prev = q;
		} else {
			tmp->next = q->next;
			tmp->next->prev = tmp;
			q->next = tmp;
			tmp->prev = q;
		}
		cout << "Element Inserted" << endl;
	}

	void display_dlist() {
		struct node *q;
		if (start == NULL) {
			cout << "List empty,nothing to display" << endl;
			return;
		}
		q = start;
		cout << "The Doubly Link List is :" << endl;
		while (q != NULL) {
			cout << " ( " << q->info.name << " & " << q->info.count << " ) "
					<< " <-> ";
			q = q->next;
		}
		cout << "NULL" << endl;
	}
	void display_one() {
		struct node *q;
		if (start == NULL) {
			cout << "List empty,nothing to display" << endl;
			return;
		}
		q = start;
		while (q != NULL) {
			cout << "books name : " << q->info.name << endl;
			cout << "books author : " << q->info.auth << endl;
			cout << "num of copies : " << q->info.count << endl;
			cout << "--------------------------------------------" << endl;
			q = q->next;
		}

	}
	int count() {
		struct node *q = start;
		int cnt = 0;
		while (q != NULL) {
			q = q->next;
			cnt++;
		}
		return cnt;
	}

};

class borrowAction {
public:
	string book_name;
	string borrower_name;

	borrowAction() {
		book_name = "";
		borrower_name = "";
	}
	borrowAction(string n1, string n2) {
		book_name = n1;
		borrower_name = n2;
	}
};

class List {
public:
	int size;
	int cap;
	borrowAction * data;
	List() {
		size = 0;
		cap = 2;
		data = new borrowAction[2];
	}
	void increase_size() {
		cap *= 2;
		borrowAction * temp = new borrowAction[cap];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = new borrowAction[cap];
		for (int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
		delete[] temp;
		return;

	}
	void insert(borrowAction value) {
		if (size == cap) {
			increase_size();
		}
		int place = size;
		for (int i = 0; i < size; i++) {

			if (data[i].book_name < value.book_name) {
				continue;
			} else {
				place = i;

				break;
			}
		}

		for (int i = size; i > place; i--) {
			data[i] = data[i - 1];
		}
		cout<<place<<endl;
		data[place] = value;
		size++;
	}

	void display() {
		for (int i = 0; i < size; i++) {
			cout<<size<<endl;
			cout << "books name : " << data[i].book_name << endl;
			cout << "borrower_name : " << data[i].borrower_name << endl;
			cout << "--------------------------------------------" << endl;
		}
	}
	void display_by_book(string s) {
		for (int i = 0; i < size; i++) {
			if (data[i].book_name == s) {
				cout << "books name : " << data[i].book_name << endl;
				cout << "borrower_name : " << data[i].borrower_name << endl;
				cout << "--------------------------------------------" << endl;
			}
		}
	}
	void display_one(int i) {

		cout << "books name : " << data[i].book_name << endl;
		cout << "borrower_name : " << data[i].borrower_name << endl;

	}

	int search(string bk_name, string br_name) {
		for (int i = 0; i < size; i++) {
			if (data[i].book_name == bk_name
					and data[i].borrower_name == br_name) {
				return i;
			}
		}
		return -1;
	}

	void remove(int idx) {
		if (size == 1) {
			size = 0;
			return;
		}
		for (int i = idx + 1; i < size; i++) {
			data[i - 1] = data[i];
		}
		size--;
	}
};

void interface() {
	cout << "*******************************************" << endl;
	cout << "*             Library System              *" << endl;
	cout << "*******************************************" << endl;
	cout
			<< "1-add book \n2-Borrow book \n3-Restore book \n4-Display library status \n5-Display borrows \n6-Search\n";

}
int lib_idx(char c) {
	c = toupper(c);
	return ((int) c) - 'A';
}

class library {
public:
	double_llist *libraryBooks[26];
	List Borrows;
	library() {
		for (int i = 0; i < 26; i++) {
			libraryBooks[i] = new double_llist;
		}
	}

	void addBook(book Tbook) {
		int idx = lib_idx(Tbook.name[0]);
		cout << idx << endl;
		libraryBooks[idx]->add_begin(Tbook);
	}
	void Borrow(string bookN, string borN) {
		int idx = lib_idx(bookN[0]);

		node * temp_found = libraryBooks[idx]->search_list(
				libraryBooks[idx]->start, bookN);

		if (temp_found == NULL or temp_found->info.count == 0) {
			cout << "Book Not found or there is no copies avalible ! \n";
			return;
		}
		temp_found->info.count--;
		cout << "borrowed" << endl;
		borrowAction temp_borrow(bookN, borN);
		Borrows.insert(temp_borrow);
	}
	void Restore(string bookN, string borN) {
		int bor_idx = Borrows.search(bookN, borN);
		if (bor_idx == -1) {
			cout << "borrow action not found \n";
			return ;
		}
		int idx = lib_idx(bookN[0]);
		node * temp_found = libraryBooks[idx]->search_list(
				libraryBooks[idx]->start, bookN);
		temp_found->info.count++;
		Borrows.remove(bor_idx);
	//	libraryBooks[idx]->display_dlist();
		//cout << temp_found->info.count << endl;
		cout << endl;
	}
	void display_status() {
		for (int i = 0; i < 26; i++) {
			if (libraryBooks[i]->count() > 0) {
				cout << (char) ('A' + i) << " : " << endl;
				libraryBooks[i]->display_one();
			}

		}
	}
	void display_borrows() {
		cout << "Borrows : " << endl;
		for (int i = 0; i < Borrows.size; i++) {
			Borrows.display_one(i);

			int idx = lib_idx(Borrows.data[i].book_name[0]);
			node * temp_found = libraryBooks[idx]->search_list(
					libraryBooks[idx]->start, Borrows.data[i].book_name);
			cout << "Units in stock : ";
			cout << temp_found->info.count << endl;
			cout << "--------------------------------------------" << endl;
		}
	}
	void search(string bookN) {
		int idx = lib_idx(bookN[0]);

		node * temp_found = libraryBooks[idx]->search_list(
				libraryBooks[idx]->start, bookN);
		if (temp_found == NULL) {
			cout << "Book not found \n";
			return ;
		}
		cout << endl << " - book info - " << endl;
		libraryBooks[idx]->display_one();
		cout << endl << " - borrowers info - " << endl;
		Borrows.display_by_book(bookN);
	}
};
int main() {
	library L;
	while (1) {
		interface();
		int choise;
		cin >> choise;
		switch (choise) {
		case 1: {
			string Tn, Ta;
			int Ti;
			cout << "enter books name : ";
			cin >> Tn;
			cout << "enter books Author : ";
			cin >> Ta;
			cout << "enter books count : ";
			cin >> Ti;
			Tn[0] = toupper(Tn[0]);
			Ta[0] = toupper(Ta[0]);
			book Tbook(Tn, Ta, Ti);

			L.addBook(Tbook);

			break;
		}

		case 2: {
			string borN, bookN;
			cout << "Enter the books name : ";
			cin >> bookN;
			cout << "Enter borrowers name : ";
			cin >> borN;
			L.Borrow(bookN, borN);
			break;
		}

		case 3: {
			string borN, bookN;
			cout << "Enter book Name : ";
			cin >> bookN;
			cout << "Enter borrowers Name : ";
			cin >> borN;
			L.Restore(bookN, borN);
			//	Borrows.display();

		}

			break;
		case 4:
			L.display_status();
			break;
		case 5:
			L.display_borrows();
			break;
		case 6: {
			string bookN;
			cout << "Enter Books name : \n";
			cin >> bookN;
			L.search(bookN);
			break;
		}

		default:
			break;
		}
	}

	return 0;
}

