#pragma once

//the following structs are extracted from TechCor8's HFL ( https://github.com/TechCor8/OP2DotNetMissionSDK )
// OP2Unit
// Can't use bit fields on the 'char' types since the compiler will still pad to word-size
struct OP2Unit
{
	void *vtbl;
	int isLive;
	void *prevUnit;
	void *nextUnit;
	int id;
	int pixelX;
	int pixelY;
	char unknown0;
	char ownerCreator; // lower 4 bits: owner ID, upper 4 bits: creator ID
	short damage;
	char boolNewAction;
	char curCmd;
	char curAction;
	char lastAction;
	short weaponCargo; // trucks: lowest 4 bits, cargo type; next 4 bits, cargo amount
	short unknown1;
	int unknown2;
	short instanceNum;
	short unknown3;
	int unknown4;
	void *destWaypoints; // missileDestX
	int missileDestY;
	int timer;
	int unknown5;
	unsigned int flags;
	char bayWeaponCargo[6];
	char unknown6;
	char unknownCargo;
	int unknown7;
	short timerStickyfoam;
	short timerEMP;
	short timerESG;
	short unknown8;
	int unknown9;
	char unknown10;
	char bayItem[6];
	char unknown11;
	int unknown12;
	short unknown13;
	int objectOnPad;
	int launchPadCargo; // Arklon says this should be an int32. unknown15 would be int16?
	short unknown15;
};

struct BeaconData
{
	int numTruckLoadsSoFar;
	int barYield;
	int variant;
	char oreType; // [0 = common, 1 = rare]
	char unknown1;
	char unknown2;
	char surveyedBy; // [player bit vector]
};

struct MineData
{
	int beaconUnitIndex;
	int unknown1; //if I had to guess, this would be ore type.
	int numTruckLoadsSoFar;
	int variant;
	int barYield;
};

class BeaconByUnitID
{
private:
	int unitID;
	//const DWORD imageBase = 0x00400000;
	OP2Unit ** unitArray = (OP2Unit**)0x54F848;
	BeaconData* GetBeaconData();

public:
	BeaconByUnitID(int setUnitID);

	int GetNumTruckLoadsSoFar();

	int GetMineVariant();

	//to prevent an alert message from happening more than once, I'm going to artificially increment the number of truck loads past the alert level.
	void IncrementNumTruckLoads();

	~BeaconByUnitID();
};

class MineByUnitID
{
private:
	int unitID;
	//const DWORD imageBase = 0x00400000;
	OP2Unit ** unitArray = (OP2Unit**)0x54F848;
	MineData* GetMineData();

public:
	MineByUnitID(int setUnitID);

	int GetNumTruckLoadsSoFar();

	int GetMineVariant();

	//to prevent an alert message from happening more than once, I'm going to artificially increment the number of truck loads past the alert level.
	void IncrementNumTruckLoads();

	~MineByUnitID();
};