// fb_decoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "fb_schemas\client_info_generated.h"

using namespace Aargo;
using namespace std;


/* Info to be printed
1. {Ram, 21, 76.5, Male}
2. {FightClub, 24.5, 66, {Ram, Shayam, Raghuveer} }
*/
void printClientInfos(const ClientInfosT* ci) {
	if (nullptr == ci) {
		return;
	}

	auto citvec = ci->client_infos_type();
	auto civec = ci->client_infos();

	for (int i = 0; i < citvec->size(); ++i) {
		cout << "{";

		auto ctype = (Clientinfo)citvec->Get(i);
		auto ci = civec->Get(i);
		if (ctype == Clientinfo::Person) {
			auto person = static_cast<const Person*>(ci);
			cout << person->name()->str() << ", " << person->age()->value() << ", " << person->weight()->value() << ", " << EnumNameGender(person->gender());
		}
		else if (ctype == Clientinfo::Group) {
			auto group = static_cast<const Group*>(ci);
			cout << group->name()->str() << ", " << group->avg_age()->value() << ", " << group->avg_weight()->value() << ", ";
			cout << "{";
			auto nameList = group->list_names();
			for (int i = 0; i < nameList->size(); ++i) {
				cout << nameList->Get(i)->str() << (i == nameList->size() - 1 ? "" : ", ");
			}
			cout << "}";
		}
		cout << "}\n";
	}
}



int main(int argc, const char** argv)
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <PATH_TO_BIN_FILE>" << endl;
		return -1;
	}
	const char* filename = argv[1];
	vector<char> buff;

	ifstream fin{ filename, ios::binary };
	while (fin) {
		char ch;
		fin.get(ch);
		buff.push_back(ch);
	}

	const char* bdata = buff.data();
	auto cis = GetClientInfosT(bdata);
	printClientInfos(cis);
}

