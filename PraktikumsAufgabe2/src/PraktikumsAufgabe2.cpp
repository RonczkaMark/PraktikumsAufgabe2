//============================================================================
// Name        : PraktikumsAufgabe2.cpp
// Author      : Stefan Ronczka Sepp Mark
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "Trie.h"
#include <utility>
using namespace std;

using namespace PA2;

int main() {

	typedef string tree_type;
	typedef basic_string<char> key_type; // string=basic_string<char>
	typedef pair<const key_type, tree_type> value_type;

	Trie<tree_type> trie;
	const value_type test("abcd", "test1");
	const value_type test2("abcdef","test2");
	const value_type test3("abcdhi","test3");

	cout << test.second << "ende" << endl;

	typedef typename Trie<tree_type>::TrieIterator testIterator;

	testIterator testIter1 = trie.insert(test);
	testIterator testIter2 = trie.insert(test2);
	testIterator testIter3 = trie.insert(test3);

	const basic_string<char> testString = "abcd";
	const basic_string<char> testString2 = "abcdef";
	const basic_string<char> testString3 = "abcdhi";

	//test the begin method
	testIter1 = trie.begin();
	//testing if the begin node is an leaf
	cout<<"test2"<<static_cast<typename Trie<tree_type>::Leaf *>(*testIter1)->getData()<<endl;
	//testing iteration funktion
	++testIter2;
	++testIter2;
	cout<<static_cast<typename Trie<tree_type>::InnerNode *>(*testIter2)->getLeft()->getValue();
	//testing the erase funktion
	trie.erase(testString2);
	//test the find funktion
	trie.find(testString);
	testIter1 = trie.begin();

	//controlling the if the words insearted successfully
	cout<<"test 1"<<static_cast<typename Trie<tree_type>::Leaf *>((*testIter1))->getData()<<endl;
	testIter1 =trie.insert(test2);
	cout<<"test 2"<<static_cast<typename Trie<tree_type>::Leaf *>((*testIter1))->getData()<<endl;

	testIter1 = trie.begin();



// subprogramm to use the trie


	Trie<tree_type> trie2;
	bool out = 1;
	string ger;
	string eng;
	while(out){
		cout<<"enter the german word \t"<<endl;
		cin>> ger;
		cout<<"enter the english word \t"<<endl;
		cin>> eng;


		value_type newWordPair(ger,eng);
		trie2.insert(newWordPair);

		cout<<"end loop 0 or 1 to continue?"<<endl;
		cin>>out;
	}
	out = 1;
	while(out){
			cout<<"translate word \t"<<endl;
			cin>> ger;

			testIterator translation= trie2.find(ger);
			cout<<static_cast<typename Trie<tree_type>::Leaf *>(*translation)->getData()<<endl;

			cout<<"end loop 0 or 1 to continue?"<<endl;
			cin>>out;
		}

	out = 1;
	while(out){
			cout<<"erase the pair with key (german word) \t"<<endl;
			cin>> ger;

			trie2.erase(ger);

			cout<<"tree is Empty \t"<<trie2.empty()<<endl;


			cout<<"end loop 0 or 1 to continue?"<<endl;



			cin>>out;
		}

		out = 1;
		while(out){
				cout<<"translate word \t"<<endl;
				cin>> ger;

				testIterator translation= trie2.find(ger);
				cout<<static_cast<typename Trie<tree_type>::Leaf *>(*translation)->getData()<<endl;

				cout<<"end loop 0 or 1 to continue?"<<endl;
				cin>>out;
			}
	cout << "!!!Programm ends correctly!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

