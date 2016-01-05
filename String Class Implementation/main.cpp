/*
 Omar Ibrahim Saber
 20130316
 G12

 Mohammad Al Sayed
 20130187
 G7
 */

#include "String.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
	String slen = "data structure course";
	cout << "Length() : " << slen.Length() << endl;
	cout << "------------------------------------------" << endl;
	cout << "substring( 5 , 6 ) : " << slen.substring(5, 6) << endl;
	cout << "------------------------------------------" << endl;
	String sapp = "ali-ahmed";
	String other = "-Mohammed";
	cout << " ali-ahmed.append(-Mohammed) : " << sapp.append(other) << endl;
	cout << "------------------------------------------" << endl;
	String sfind = "can you open this can for me?";
	other = "can";
	cout << "can you open this can for me? .find(can) : " << sfind.find(other)
			<< endl;
	cout << "------------------------------------------" << endl;
	String srep = "ahmed ali ahmed mostafa";
	String old = "ahmed";
	String New = "Hassan";
	cout << "ahmed ali ahmed mostafa . replace(ahmed,Hassan) :" << endl
			<< srep.replace(old, New) << endl;
	;
	cout << "------------------------------------------" << endl;
	String sarr[] = { "Ali", "Sameh", "Ahmed", "Mohammed" };

	cout << "Before sort : " << endl;
	for (int i = 0; i < 4; i++) {
		cout << sarr[i] << " ";
	}
	cout << endl;
	String::sort(sarr, 4);

	cout << "After sort : " << endl;
	for (int i = 0; i < 4; i++) {
		cout << sarr[i] << " ";
	}
	cout << endl;
	cout << "------------------------------------------" << endl;

	String srev = "To be reversed";
	cout << srev << "  :: reversed :: ";
	srev.reverse();
	cout << srev << endl;
	cout << "------------------------------------------" << endl;
	String sup = "Ahmed Hosam";
	cout << sup << " :: toUpper :: ";
	sup.toUpper();
	cout << sup << endl;
	cout << "------------------------------------------" << endl;
	String sdown = "DON’T WRITE UPPER CASE LETTERS";
	cout << sup << " :: toLower :: ";
	sdown.toLower();
	cout << sdown << endl;
	cout << "------------------------------------------" << endl;
	String sget = "New semester";
	try {
		cout << sget << " char at 2 : " << sget.getAt(2) << endl;
	} catch (string& e) {
		cout << sget << " char at 2 : " << -1 << endl;
	}
	try {
		cout << sget << " char at 20 : " << sget.getAt(20) << endl;
	} catch (string& e) {
		cout << sget << " char at 20 : " << -1 << endl;
	}
	cout << "------------------------------------------" << endl;
	cout << "isEmpty() : " << sget.IsEmpty() << endl;
	cout << "------------------------------------------" << endl;
	String sc1 = "Ahmed", sc2 = "Ali", sc3 = "Sameh";
	cout << "compare (" << sc1 << " , " << sc2 << " )   : " << sc1.compare(sc2)
			<< endl;
	cout << "compare (" << sc1 << " , " << sc1 << " )   : " << sc1.compare(sc1)
			<< endl;
	cout << "compare (" << sc3 << " , " << sc2 << " )   : " << sc3.compare(sc2)
			<< endl;
	sdown =
			"Make the following assumptions: the English phrase consists of words separated by blanks , there are no punctuation marks and all words have two or more letters. Create aprogram that inputs a string from the user and translates it into pig Latin.";
	cout << endl;
	cout << "------------------------------------------" << endl;
	sdown.align(String::left);
	cout << endl;
	cout << "------------------------------------------" << endl;
	sdown.align(String::right);
	cout << endl;
	cout << "------------------------------------------" << endl;
	sdown.align(String::justify);
	cout << endl;
	return 0;
}

/*
 int main() {
 ////////////////////////////////////////////////
 //   Test cases for each function separately  //
 ////////////////////////////////////////////////


 //the getline and the cout overloading
 cout<<"Enter a string : "<<endl;
 string getx;
 getline(cin, getx);
 cout << getx << endl;

 String ss = "who are you";

 ss.Sort();
 cout << "Sorted : " << ss << endl;

 String f = "aaaaa aaBBBa abbb aaaaa";
 cout << "found at pos : " << f.Find("bbb") << endl;
 ;

 // 0 for left 1 for right 2 for middle
 String x = "Align me !";
 x.Display(0);
 cout << endl;
 cout
 << "--------------------------------------------------------------------------------";
 cout << endl;
 x.Display(1);
 cout << endl;
 cout
 << "--------------------------------------------------------------------------------";
 cout << endl;
 x.Display(2);
 cout << endl;
 cout
 << "--------------------------------------------------------------------------------";
 cout << endl;

 String ss1 = "Hello ";
 String ss2 = "World !";
 ss1 += ss2;
 cout << ss1 << endl;

 String s1 = "This is string one";

 String s2 = "This is string two";

 s1.Reverse();
 cout << s1 << endl;

 s2.Substitute("s", "z");
 cout << s2 << endl;

 cout << s1.Compare(s2) << endl;

 s2.Erase(4, 1);
 cout << s2 << endl;

 String s3 = s2.substring(4, 4);
 cout << s3 << endl;

 cout << s2.WordCount() << endl;

 s2.Swap(s1);
 cout << s1 << endl;
 cout << s2 << endl;

 cout << s1.Find("o") << endl;
 cout << s1.Find("H") << endl;

 s2.Insert("AAA", 3);
 cout << s2 << endl;

 cout << s2[0] << " " << s2[1] << endl;

 cout << s1.Toupper() << endl;

 return 0;
 }
 */


