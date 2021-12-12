// fb_encoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>

#include "fb_schemas\client_info_generated.h"

using namespace Aargo;
using namespace std;

/* Info to be serialized
1. {Ram, 21, 76.5, Male}
2. {FightClub, 24.5, 66, {Ram, Shayam, Raghuveer} }
*/

pair<uint8_t*, flatbuffers::uoffset_t> getClientInfos(flatbuffers::FlatBufferBuilder& builder) {
	auto ramName = builder.CreateString("Ram");
	auto age = CreateAgeT(builder, 21, AgeUnit::Years);
	auto weight = CreateWeightT(builder, 76.5F, WeightUnit::Kg);
	auto gender = Gender::Male;

	auto ram = CreatePerson(builder, ramName, age, weight, gender);

	auto groupName = builder.CreateString("FightClub");
	auto avgAge = CreateAgeT(builder, 24.5F, AgeUnit::Years);
	auto avgWeight = CreateWeightT(builder, 66, WeightUnit::Kg);
	auto listNames = builder.CreateVectorOfStrings({"Ram", "Shayam", "Raghuveer"});

	auto fightClub = CreateGroup(builder, groupName, avgAge, avgWeight, listNames);

	std::vector<uint8_t> citype_vec{ (uint8_t)Clientinfo::Person, (uint8_t)Clientinfo::Group };
	auto citypes = builder.CreateVector(citype_vec);
	std::vector<flatbuffers::Offset<void>> cidata_vec{ ram.Union(), fightClub.Union() };
	auto cidata = builder.CreateVector(cidata_vec);
	auto cis = CreateClientInfosT(builder, citypes, cidata);

	builder.Finish(cis);
	auto cinfos = builder.GetBufferPointer();
	auto cinfosize = builder.GetSize();

	return { cinfos, cinfosize };
}

int main(int argc, const char** argv)
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <PATH_TO_BIN_FILE>" << endl;
		return -1;
	}
	const char* filename = argv[1];

	flatbuffers::FlatBufferBuilder builder(1024);
	auto data = getClientInfos(builder);
	auto dptr = data.first;
	auto dsize = data.second;

	ofstream of{ filename, ios::out | ios::binary };
	of.write((char*)dptr, dsize);
	of.close();
}
