#include "BeaconData.h"



BeaconByUnitID::BeaconByUnitID(int setUnitID)
{
	unitID = setUnitID;
}

BeaconData* BeaconByUnitID::GetBeaconData()
{
	return (BeaconData*)((int)(*unitArray) + (unitID * 120) + 0x58);
}

//this function has been altered slightly from TechCor's HFL original so it doesn't depend on the HFL init
int BeaconByUnitID::GetNumTruckLoadsSoFar()
{
	return GetBeaconData()->numTruckLoadsSoFar;
}

int BeaconByUnitID::GetMineVariant()
{
	return GetBeaconData()->variant;
}

void BeaconByUnitID::IncrementNumTruckLoads()
{
	GetBeaconData()->numTruckLoadsSoFar++;
}

BeaconByUnitID::~BeaconByUnitID()
{
}


MineByUnitID::MineByUnitID(int setUnitID)
{
	unitID = setUnitID;
}

MineData* MineByUnitID::GetMineData()
{
	return (MineData*)((int)(*unitArray) + (unitID * 120) + 0x60);
}

//this function has been altered slightly from TechCor's HFL original so it doesn't depend on the HFL init
int MineByUnitID::GetNumTruckLoadsSoFar()
{
	return GetMineData()->numTruckLoadsSoFar;
}

int MineByUnitID::GetMineVariant()
{
	return GetMineData()->variant;
}

void MineByUnitID::IncrementNumTruckLoads()
{
	GetMineData()->numTruckLoadsSoFar++;
}

MineByUnitID::~MineByUnitID()
{
}

