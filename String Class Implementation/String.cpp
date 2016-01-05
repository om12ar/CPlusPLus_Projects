#include "String.h"

//Max initial input array size
const int _MAX = 1000;
//Console width for the display function
const int CONSOLE_SIZE = 80;

String::String() {

	arr = NULL;
	size = 0;
}

String::String(char* s) {

	int l = 0;
	while (s[l] != '\0')
		l++;

	size = l;
	arr = new char[size];

	for (int i = 0; i < size; i++) {
		arr[i] = s[i];
	}
}

String::String(const String& other) {

	size = other.size;
	arr = new char[size];

	for (int i = 0; i < size; i++) {
		arr[i] = other.arr[i];
	}

}

String::String(int n) {
	size = n;
	arr = new char[n];
}

String::String(char*a, int s) {
	size = s;
	arr = new char[size];
	for (int i = 0; i < size; i++) {
		arr[i] = a[i];
	}

}

String::~String() {
	delete[] arr;
}

int String::Length() {
	return size;
}

void String::Clear() {
	size = 0;
}

bool String::IsEmpty() {
	return (size == 0);
}

void String::sort(String arr[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i].compare(arr[j]) == 1) {
				String temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

}

int String::WordCount() {
	int counter = 0;
	if ((arr[0] >= 'A' && arr[0] <= 'Z') || (arr[0] >= 'a' && arr[0] <= 'z'))
		counter++;
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] == ' ') {
			if ((arr[i + 1] >= 'A' && arr[i + 1] <= 'Z')
					|| (arr[i + 1] >= 'a' && arr[i + 1] <= 'z'))
				counter++;
		}
	}

	return counter;
}
//Return -1 if not found else it returns the index
int String::find(String other) {
	bool found = 0;
	for (int i = 0; i < size; i++) {
		if (other.arr[0] == arr[i]) {
			found = 1;
			for (int j = i; j - i < other.size; j++) {
				if (other.arr[j - i] != arr[j]) {
					found = 0;
					break;
				}
			}
			if (found) {
				return i;
			}
		}
	}
	return -1;
}

String String::replace(String old, String New) {
	int idx = find(old);
	while (idx != -1) {
		Erase(idx, old.size);
		Insert(New, idx);
		idx = find(old);
	}
	return *this;
}

void String::Copy(String& other, int start, int interval) {
	other = substring(start, interval);
}

//Not required
String& String::Insert(const String& other, int index) {

	if (index >= 0 && index <= size) {
		int newsize = size + other.size;
		char*newarr = new char[newsize];

		for (int ni = 0, ai = 0, si = 0; ni < newsize; ni++) {
			if (ni >= index && ni < index + other.size) {
				newarr[ni] = other.arr[si++];
			} else {
				newarr[ni] = arr[ai++];
			}
		}

		delete[] arr;
		size = newsize;
		arr = new char[size];
		for (int i = 0; i < size; i++)
			arr[i] = newarr[i];
		delete[] newarr;

	}
	return *this;
}
//Not required
String& String::Erase(int start, int interval) {
	if (OutOfBounds(start) != true) {
		if (interval > size)
			interval = size;

		int newsize = size - interval;
		char* newarr = new char[newsize];
		for (int ni = 0, ai = 0; ai < size; ai++) {
			if (ai >= start && ai < start + interval)
				continue;
			else {
				newarr[ni] = arr[ai];
				ni++;
			}
		}
		delete[] arr;
		size = newsize;
		arr = new char[size];
		for (int i = 0; i < size; i++)
			arr[i] = newarr[i];
		delete[] newarr;
	}
	return *this;
}

String String::substring(int starting_position, int length) {
	if ((starting_position + length) >= 0
			&& (starting_position + length) <= size) {
		String other;
		other.size = length;
		other.arr = new char[other.size];

		for (int ni = 0, ai = starting_position; ni < other.size; ni++, ai++) {
			other.arr[ni] = arr[ai];
		}

		return other;
	}
	cout << "Error: Out of Bounds\n";
	return *this;
}

void String::toUpper() {
	for (int i = 0; i < size; i++) {
		if (arr[i] >= 'a' && arr[i] <= 'z') {
			arr[i] -= 32;
		}
	}
}

void String::toLower() {
	for (int i = 0; i < size; i++) {
		if (arr[i] >= 'A' && arr[i] <= 'Z') {
			arr[i] += 32;
		}
	}
}

bool String::OutOfBounds(int i) {
	if (i < 0 || i >= size) {
		cout << "Error: Out of Bounds\n";
		return true;
	}

	else
		return false;
}

String String::append(String other) {
	Insert(other, size);
	return *this;
}

//Not required
void String::Swap(String &other) {
	String temp = other;
	other = *this;
	*this = temp;
}

void String::reverse() {
	char*temp = new char[size];
	int last = size - 1;
	int tempi = 0;
	for (int i = last; i >= 0; i--) {
		if (arr[i] == ' ') {
			for (int j = i + 1; j <= last; j++, tempi++)
				temp[tempi] = arr[j];

			temp[tempi] = ' ';
			tempi++;
			last = i - 1;
		}

		if (i == 0) {
			for (int j = i; j <= last; j++, tempi++)
				temp[tempi] = arr[j];
			last = 0;
		}
	}

	for (int i = 0; i < size; i++) {
		arr[i] = temp[i];
	}

	delete[] temp;
}

//Not required
char String::operator[](int i) {
	if (OutOfBounds(i) != true)
		return arr[i];
	else {
		cout << -1;
		return ' ';
	}

}

char String::getAt(int index) {
	if (OutOfBounds(index) != true)
		return arr[index];
	else {
		string e = "out of bounds";
		throw e;
	}

}

//Not required
String& String::operator=(const String &other) {
	size = other.size;
	delete[] arr;
	arr = new char[size];
	for (int i = 0; i < size; i++) {
		arr[i] = other.arr[i];
	}
	return *this;
}

//Not required
String& String::operator+=(const String &other) {
	Insert(other, size);
	return *this;
}

ostream& operator<<(ostream& out, const String& s) {
	for (int i = 0; i < s.size; i++) {
		out << s.arr[i];
	}

	return out;
}

istream& operator>>(istream& in, String& s) {

	char*input = new char[_MAX];
	//char*input= new char;
	in >> input;

	String temp(input);
	s = temp;
	delete[] input;
	return in;

}

// returns 1 if this string is bigger
// returns -1 if the other string is bigger
// returns 0 if they are equal
int String::compare(String other) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < other.size; j++) {
			if (arr[i] > other.arr[i])
				return -1;
			else if (arr[i] < other.arr[i])
				return 1;
		}
	}
	return 0;
}
//Not required
String& String::SortWords() {
	int wordNum = this->WordCount();
	int adder = 0;
	String * temp = new String[wordNum];
	//Separate words into array items
	int st = 0;
	for (int i = 0; i < this->size; i++) {

		int fn = this->size;
		for (int j = st + 1; j < this->size; j++) {
			if (arr[j] == ' ') {
				fn = j;
				break;
			}
		}

		i = fn;
		temp[adder++] = this->substring(st, fn - st);
		st = fn + 1;

	}
	// Sort the array
	for (int i = 0; i < wordNum; i++) {
		for (int j = 0; j < wordNum; j++) {

			if (temp[i].compare(temp[j]) == -1) {
				temp[i].Swap(temp[j]);
			}
		}
	}
	//get words back to a string
	String sorted = "";
	for (int i = 0; i < wordNum; i++) {
		sorted += temp[i];
		if (i != wordNum - 1) {
			sorted += " ";
		}
	}

	*this = sorted;

	return *this;

}

//Not required
istream& getline(istream& in, String& str) {
	char temp[_MAX];
	str.Clear();
	cin.getline(temp, _MAX);
	int sss = strlen(temp);
	String ss(temp, sss);
	str = ss;
	return in;
}

int String::prevSpace(int start) {
	for (int i = start; i >= 0; i--) {
		if (arr[i] == ' ') {
			return i;
		}
	}
	return 0;
}

void String::Mid() {
	if (size < CONSOLE_SIZE) {
		int side = (CONSOLE_SIZE - size) / 2;
		for (int i = 0; i < side; i++) {
			cout << " ";
		}
		cout << *this;
	} else {
		int tsize = size;
		int charsLeft = 0;
		while (tsize > CONSOLE_SIZE) {
			for (int i = charsLeft; i < charsLeft + CONSOLE_SIZE; i++) {
				cout << arr[i];
			}
			cout << endl;
			charsLeft += CONSOLE_SIZE;
			tsize -= CONSOLE_SIZE;
		}
		charsLeft = (CONSOLE_SIZE - tsize) / 2;
		for (int i = 0; i < charsLeft; i++) {
			cout << " ";
		}
		for (int i = size - tsize; i < size; i++) {
			cout << arr[i];
		}

	}
}

void String::align(AlignType choice)
{
    if (choice == 0)
    {
        int index = 0;
    int start, last;
    if (size > 80)
    {   int j = size/80;
         while (j!=0)
        {
        start = index;
        last = index + 80;
        int counter = 0;
        if (arr[last]==' ')
           {
            for (int i=start; i<last; i++)
            cout << arr[i];
            index += 80;
           }
        else if (arr[last] != ' ')
        {
            for (int i=last-1; arr[i]!=' ';i--)
                counter++;

         index = last-counter;

        for (int i=start; i<index; i++)
            {
                cout << arr[i];
                if (arr[i] == ' ' && counter!=0)
                {
                    cout << ' ';
                    counter--;
                }
            }
        }
        j--;
        }
    int start = index;
    for (int i = start ; i<size; i++)
        cout << arr[i];
    }
    }
 if (choice == 1)
 {
    int index = 0;
    int start, last;
    if (size < 80)
    {

    for (int i=0; i<80-size; i++)
        cout << ' ';
        Printless80();
    }
   else if (size > 80)
    {   int j = size/80;
         while (j!=0)
        {
        start = index;
        last = index + 80;
        int counter = 0;
        if (arr[last]==' ')
           {
            for (int i=start; i<last; i++)
            cout << arr[i];
            index += 80;
           }
        else if (arr[last] != ' ')
        {
            for (int i=last-1; arr[i]!=' ';i--)
                counter++;

         index = last-counter;
        for (int i=0; i<counter+1; i++)
            cout << ' ';
        for (int i=start; i<index-1; i++)
            cout << arr[i];
        }
        j--;
        }
    int start = index;
    for(int i=0; i<80-(size-start); i++)cout<<" ";
    for (int i = start; i<size; i++)
    {
        cout << arr[i];


    }
    }

else if (size == 80)
 Printless80 ();

 }
 if (choice == 2)
 {
     int index = 0;
    int start, last;
    if (size < 80)
    {
        Printless80();
    }
   else if (size > 80)
    {   int j = size/80;
         while (j!=0)
        {
        start = index;
        last = index + 80;
        int counter = 0;
        if (arr[last]==' ')
           {
            for (int i=start; i<last; i++)
            cout << arr[i];
            index += 80;
           }
        else if (arr[last] != ' ')
        {
            for (int i=last-1; arr[i]!=' ';i--)
                counter++;

         index = last-counter;


      for (int i=start; i<index-1; i++)
            cout << arr[i];
            for (int i=0; i<counter+1; i++)
            cout << ' ';
        }
        j--;
        }}


    start = index;
    int spaces=80-(size-start-1);
    int spacesin=0;

    for (int i = start ; i<size; i++)if(arr[i]==' ')spacesin++;

    int divisionrem=spaces%spacesin;
    int division=spaces/spacesin;
    bool first=true;
    for (int i = start ; i<size; i++)
        {
            if(arr[i]==' '  && divisionrem ==0){cout<<arr[i]; for(int s=0; s<division;s++)cout<<" ";}
            else if (arr[i]==' '  && divisionrem !=0){cout<<arr[i]; if(first==true){cout<<" "; first=false;} for(int s=0; s<division;s++)cout<<" ";}
            else cout<<arr[i];

        }



    }
else if (size == 80)
Printless80 ();
 }


void String::Printless80()
{
    for (int i=0; i<size; i++)
        {
            cout << arr[i];
        }
        cout << endl;
}

