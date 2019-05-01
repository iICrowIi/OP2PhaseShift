#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

// Include important header files needed to interface with Outpost 2
#include "..\Outpost2DLL\Outpost2DLL.h"
// Include header files to make it easier to build levels
#include "..\OP2Helper\OP2Helper.h"

// Include base layout data
// Note: Editing this file is a good way to build bases.
#include "BaseData.h"
#include "BeaconData.h"


// Note: These exports are required by Outpost2.exe from every level
//		 DLL. They give values for the map and tech trees used by the
//		 level and a description to place in the level listbox. The
//		 last export is used to define characteristics of the level.
//		 See RequiredExports.h for more details.
//		 ** Be sure to set these when you build your own level**

char MapName[] = "ohana.map";							// The .map file used for this level
char LevelDesc[]		= "2P, SR, 'Ohana - PhaseShift'";			// Description appearing in the game list box
char TechtreeName[]		= "MULTITEK.TXT";						// File to use for the tech tree
SDescBlock DescBlock	= { MultiSpaceRace, 2, 12, 0 }; // Important level details


// Note: This is the DLL entry point which is called by Windows when the
//		 DLL is first loaded into a processes address space or unloaded
//		 from the process address space. This function also be called for
//		 each thread owned by the process, but this has been disabled
//		 for efficiency reasons by the DisableThreadLibraryCalls during
//		 the first time the method is run.
// Note: You most likely do NOT need to edit this and unless you really
//		 know what you're doing you probably shouldn't.

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hinstDLL);
	}

    return TRUE;
}


// Note: The following function is called once by Outpost2.exe when the
//		 level is first initialized. This is where you want to create
//		 all the initial units and structures as well as setup any 
//		 map/level environment settings such as day and night.

int InitProc()
{
	int i;

	// Randomize which player is NW vs SE
	int nwPlayerID = TethysGame::GetRand(2), sePlayerID;
	if (nwPlayerID == 1)
		sePlayerID = 0;
	else sePlayerID = 1;

	//I want to know if PhaseShift is active, but checking this turns out to be tricky.  For now, I will just have this as a manual on/off switch.
	bool isPhaseShift = true;

	// Initialize the colony resources
	for (i = 0; i < TethysGame::NoPlayers(); i++)
	{
		_Player player = Player[i];
		switch (player.Difficulty())
		{
			case 0:		// High
				player.SetOre(5000);
				player.SetFoodStored(3000);
				player.SetWorkers(28);
				player.SetScientists(13);
				player.SetKids(15);
				break;
			case 1:		// Medium
				player.SetOre(4500);
				player.SetFoodStored(2000);
				player.SetWorkers(26);
				player.SetScientists(12);
				player.SetKids(14);
				break;
			case 2:		// Low
				player.SetOre(4000);
				player.SetFoodStored(1000);
				player.SetWorkers(24);
				player.SetScientists(11);
				player.SetKids(13);
				break;
		}

		if (player.Difficulty() < 2)
		{
			player.MarkResearchComplete(3304); // Offspring Enhancement
			player.MarkResearchComplete(3305); // Research Training Program
		}

		if (player.Difficulty() == 0)
		{
			player.MarkResearchComplete(3401); //cybernetic teleoperation
			if (TethysGame::UsesMorale())
				player.MarkResearchComplete(3406); //environmental psychology
			if (player.IsEden())
				player.MarkResearchComplete(3407); //laser
			else
			{
				if (!isPhaseShift)
					player.MarkResearchComplete(3408); //microwave
				else
					player.MarkResearchComplete(5114); //legged robots
			}
		}
	}

	//place my beacons  Arg order: type, x,	y, rare, bar, variant (-1 means random)
	//northern half of map
	TethysGame::CreateBeacon(mapMiningBeacon, 7 + 31, 5 - 1, 0, 1, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 37 + 31, 5 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 38 + 31, 22 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 58 + 31, 4 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 50 + 31, 5 - 1, 1, 1, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 47 + 31, 22 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 50 + 31, 42 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 9 + 31, 29 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 5 + 31, 37 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 6 + 31, 56 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 12 + 31, 64 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 62 + 31, 65 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 67 + 31, 64 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 76 + 31, 4 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 94 + 31, 5 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 114 + 31, 22 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 116 + 31, 32 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 93 + 31, 57 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 112 + 31, 48 - 1, 0, 1, -1);
	//rest of map
	TethysGame::CreateBeacon(mapMiningBeacon, 125 + 31, 125 - 1, 0, 1, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 95 + 31, 123 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 93 + 31, 104 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 120 + 31, 99 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 124 + 31, 91 - 1, 1, 1, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 122 + 31, 73 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 116 + 31, 65 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 108 + 31, 69 - 1, 1, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 76 + 31, 86 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 36 + 31, 70 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 19 + 31, 75 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 83 + 31, 121 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 86 + 31, 106 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 76 + 31, 123 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 57 + 31, 124 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 42 + 31, 120 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 19 + 31, 103 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 15 + 31, 94 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 20 + 31, 60 - 1, 1, 0, -1);


	TethysGame::CreateBeacon(mapFumarole, 84 + 31, 42 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 5 + 31, 17 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 5 + 31, 15 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 46 + 31, 87 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 124 + 31, 112 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 124 + 31, 110 - 1, -1, -1, -1);

	TethysGame::CreateBeacon(mapMagmaVent, 62 + 31, 48 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 68 + 31, 82 - 1, -1, -1, -1);

	//add players' starting units.
	Unit x;

	//NW player
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(27 + 31, 17 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(22 + 31, 16 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateWallOrTube(24 + 31, 16 - 1, 0, mapTube); //connects the above and below
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(26 + 31, 11 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(18 + 31, 9 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(22 + 31, 10 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapStandardLab, LOCATION(25 + 31, 14 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(9 + 31, 16 - 1), nwPlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(7 + 31, 4 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(9 + 31, 5 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(11 + 31, 6 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(13 + 31, 7 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(34 + 31, 19 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(28 + 31, 19 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(26 + 31, 19 - 1), nwPlayerID, mapNone, 0); x.DoSetLights(1);

	//wall blocking the path to the natural
	TethysGame::CreateWallOrTube(66 + 31, 4 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 4 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(68 + 31, 4 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(69 + 31, 4 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 5 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 5 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(68 + 31, 5 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(69 + 31, 5 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 6 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 6 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(68 + 31, 6 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(69 + 31, 6 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(69 + 31, 7 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(68 + 31, 7 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 7 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 7 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 8 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 8 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(68 + 31, 8 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(69 + 31, 8 - 1, 0, mapWall);

	if (Player[nwPlayerID].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapNursery, LOCATION(19 + 31, 13 - 1), nwPlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapUniversity, LOCATION(22 + 31, 13 - 1), nwPlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(34 + 31, 18 - 1), nwPlayerID, mapNone, 0);  x.DoSetLights(1);
		if(TethysGame::UsesMorale())
			TethysGame::CreateUnit(x, mapResidence, LOCATION(19 + 31, 16 - 1), nwPlayerID, mapNone, 0);
	}

	if (Player[nwPlayerID].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapVehicleFactory, LOCATION(32 + 31, 17 - 1), nwPlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(15 + 31, 8 - 1), nwPlayerID, mapNone, 0);  x.DoSetLights(1);
		TethysGame::CreateUnit(x, mapTokamak, LOCATION(9 + 31, 19 - 1), nwPlayerID, mapNone, 0);

		if (Player[nwPlayerID].IsEden() || !isPhaseShift)
		{
			TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(9 + 31, 10 - 1), nwPlayerID, mapNone, 0);
			TethysGame::CreateWallOrTube(12 + 31, 10 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(13 + 31, 10 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(14 + 31, 10 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(15 + 31, 10 - 1, 0, mapTube);
		}
		else
			TethysGame::CreateUnit(x, mapArachnidFactory, LOCATION(30 + 31, 11 - 1), nwPlayerID, mapNone, 0);
	}

	//SE Player
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(106 + 31, 112 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapStandardLab, LOCATION(107 + 31, 116 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(106 + 31, 119 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateWallOrTube(109 + 31, 112 - 1, 0, mapTube); //connecting above and below
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(111 + 31, 113 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(111 + 31, 119 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(115 + 31, 119 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(120 + 31, 112 - 1), sePlayerID, mapNone, 0);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(116 + 31, 123 - 1), sePlayerID, mapNone, 0);  x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(120 + 31, 124 - 1), sePlayerID, mapNone, 0);  x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(123 + 31, 125 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(125 + 31, 124 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(105 + 31, 114 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(107 + 31, 114 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(98 + 31, 114 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);

	//wall blocking back entrance to natural
	TethysGame::CreateWallOrTube(64 + 31, 120 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(65 + 31, 120 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 120 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 120 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(64 + 31, 121 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(65 + 31, 121 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 121 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 121 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(64 + 31, 122 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(65 + 31, 122 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 122 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 122 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(64 + 31, 123 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(65 + 31, 123 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 123 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 123 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(64 + 31, 124 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(65 + 31, 124 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(66 + 31, 124 - 1, 0, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 124 - 1, 0, mapWall);

	if (Player[sePlayerID].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapResidence, LOCATION(114 + 31, 113 - 1), sePlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapUniversity, LOCATION(111 + 31, 116 - 1), sePlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapNursery, LOCATION(114 + 31, 116 - 1), sePlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(98 + 31, 113 - 1), sePlayerID, mapNone, 0);  x.DoSetLights(1);
	}
	if (Player[sePlayerID].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapVehicleFactory, LOCATION(101 + 31, 112 - 1), sePlayerID, mapNone, 0);
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(112 + 31, 122 - 1), sePlayerID, mapNone, 0); x.DoSetLights(1);
		TethysGame::CreateUnit(x, mapTokamak, LOCATION(120 + 31, 109 - 1), sePlayerID, mapNone, 0);

		if (Player[sePlayerID].IsEden() || !isPhaseShift)
		{
			TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(121 + 31, 115 - 1), sePlayerID, mapNone, 0);
			TethysGame::CreateWallOrTube(116 + 31, 116 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(117 + 31, 116 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(118 + 31, 116 - 1, 0, mapTube);
			TethysGame::CreateWallOrTube(119 + 31, 116 - 1, 0, mapTube);
		}
		else TethysGame::CreateUnit(x, mapArachnidFactory, LOCATION(103 + 31, 119 - 1),sePlayerID, mapNone, 0);
	}

	// Misc initialization
	//TethysGame::CreateWreck(95, 63, (map_id)11999, 0); // Tech #11999 - tiger speed upgrade

	if (TethysGame::UsesDayNight())
	{
		TethysGame::SetDaylightEverywhere(0);
		TethysGame::SetDaylightMoves(1);
		GameMap::SetInitialLightLevel(64);
	}
	else
	{
		TethysGame::SetDaylightEverywhere(1);
		TethysGame::SetDaylightMoves(0);
		GameMap::SetInitialLightLevel(-32);
	}

	Player[nwPlayerID].CenterViewOn(22 + 31, 13 - 1);
	Player[sePlayerID].CenterViewOn(110 + 31, 116 - 1);

	if (TethysGame::UsesMorale())
	{
		if (isPhaseShift)
		{
			TethysGame::ForceMoralePoor(-1);
			CreateTimeTrigger(1, 0, 32, "LimitMorale");
		}
		else TethysGame::ForceMoraleGood(-1);
		
		TethysGame::FreeMoraleLevel(-1);
	}
	else TethysGame::ForceMoraleGood(-1);

	if (isPhaseShift)
		CreateTimeTrigger(1, 0, 25, "MineAlertCheck");

	//Starship OR last one standing victory trigger.
	Trigger onePlayerLeftTrig = CreateOnePlayerLeftTrigger(1, 1, "NoResponseToTrigger");
	Trigger starshipTrig = CreateCountTrigger(1, 1, -1, mapEvacuationModule, mapAny, 1, cmpGreaterEqual, "NoResponseToTrigger");
	Trigger combinedTrig = CreateSetTrigger(1, 1, 2, 1, "NoResponseToTrigger", onePlayerLeftTrig, starshipTrig);
	CreateVictoryCondition(1, 1, combinedTrig, "Launch the starship - OR - Eliminate your opponents.");

	return 1; // return 1 if OK; 0 on failure
}

SCRIPT_API void MineAlertCheck()
{
	for (int playerID = 0; playerID < 2; playerID++)
	{
		PlayerBuildingEnum commonMineEnum = PlayerBuildingEnum(playerID, mapCommonOreMine);
		Unit currentMineUnit;
		while (commonMineEnum.GetNext(currentMineUnit) != 0)
		{
			MineByUnitID myMine = MineByUnitID(currentMineUnit.unitID);
			bool sendAlert = false;

			switch (myMine.GetMineVariant())
			{
			case 0:
				if (myMine.GetNumTruckLoadsSoFar() == 70)
					sendAlert = true;
				break;
			case 1:
				if (myMine.GetNumTruckLoadsSoFar() == 75)
					sendAlert = true;
				break;
			case 2:
				if (myMine.GetNumTruckLoadsSoFar() == 50)
					sendAlert = true;
				break;
			}

			if (sendAlert)
			{
				myMine.IncrementNumTruckLoads();

				TethysGame::AddMessage(currentMineUnit, "A common mine will be depleted soon.", playerID, 33); //167
			}
		}

		//it feels bad that I have to do this code twice, but the alternative is to enumerate ALL the player's units and look for one of two options.
		PlayerBuildingEnum rareMineEnum = PlayerBuildingEnum(playerID, mapRareOreMine);
		while (rareMineEnum.GetNext(currentMineUnit) != 0)
		{
			MineByUnitID myMine = MineByUnitID(currentMineUnit.unitID);
			bool sendAlert = false;

			switch (myMine.GetMineVariant())
			{
			case 0:
				if (myMine.GetNumTruckLoadsSoFar() == 70)
					sendAlert = true;
				break;
			case 1:
				if (myMine.GetNumTruckLoadsSoFar() == 75)
					sendAlert = true;
				break;
			case 2:
				if (myMine.GetNumTruckLoadsSoFar() == 50)
					sendAlert = true;
				break;
			}

			if (sendAlert)
			{
				myMine.IncrementNumTruckLoads();

				TethysGame::AddMessage(currentMineUnit, "A rare mine will be depleted soon.", playerID, 33); //167
			}
		}

	}
}

SCRIPT_API void LimitMorale()
{
	for (int i = 0; i < 2; i++)
	{
		int maxMorale = 30;
		if (Player[i].HasTechnology(3301)) //DIRT
			maxMorale += 10;
		if (Player[i].HasTechnology(3303)) //Med Centers
			maxMorale += 15;
		if (Player[i].HasTechnology(3304)) //Nursery
			maxMorale += 5;
		if (Player[i].HasTechnology(3305)) //University
			maxMorale += 5;
		if (Player[i].HasTechnology(3306)) //Rec Facility
			maxMorale += 20;
		if (Player[i].HasTechnology(5108)) //Forum
			maxMorale += 10;
		if (Player[i].HasTechnology(5101)) //Consumer Goods
			maxMorale += 10;
		if (Player[i].HasTechnology(3302)) //GORF
			maxMorale += 5;

		//int* morale = (int*)(&Player[i] + 0x40); This doesn't work, but the below does - I guess player[i] points to some alternate data structure, rather than the underlying data.
		int* morale = (int*)(0x56EF1C + i * 0xC24 + 0x40);
		int* moraleLevel = (int*)(0x56EF1C + i * 0xC24 + 0x34);
			
		if (*morale > maxMorale)
		{
			*morale = maxMorale;
			if (*morale >= 90)
				*moraleLevel = 0;
			else if (*morale >= 70)
				*moraleLevel = 1;
			else if (*morale >= 45)
				*moraleLevel = 2;
			else if (*morale >= 25)
				*moraleLevel = 3;
			else *moraleLevel = 4;
		}
	}
}

// Note: The following function seems to be intended for use in
//		 controlling an AI. It is called once every game cycle. 
//		 Use it for whatever code needs to run on a continual basis.
// Note: The standard level DLLs released by Sierra leave this function
//		 empty and handle all AI controls through triggers.

void AIProc() 
{
}


// Note: This function is called by Outpost2.exe to obtain a description
//		 of a buffer that is saved to saved game files. Outpost2.exe
//		 calls this function and passes it a pointer to a structure
//		 which describes this buffer. This function is required to set
//		 the fields of this structure. If no buffer needs to be saved
//		 to a saved game file, then the buffer pointer needs to be set
//		 to 0, and the length should also be set to 0.
// Note: This function is called once when the DLL is first initialized.
//		 This means that all data to be saved must have space reserved
//		 ahead of time at the start of the level. (Static sized storage)
//		 In other words, there is no way to dynamically grow the size of
//		 the buffer if more space is needed than originally specified.
// Note: You can probably stretch the above limitation by saving the
//		 pointer to the buffer description passed by Outpost2.exe. This
//		 may allow you to increase the buffer size dynamically but the
//		 idea is yet untested. Keep in mind that you have no idea when
//		 a game may be saved (or just loaded). 

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}



// Note: These last two functions aren't absolutely required by a level
//		 but they found in almost all DLLs anyways.


// Note: This export usually exists, but does nothing other than return 0.
//		 It's use may have been for checking for victory/failure conditions
//		 that are not easily checked for by using triggers.

int StatusProc()
{
	return 0; // must return 0
}


// Note: This is a trigger callback function. This function is
//		 intentionally left empty and is used as the trigger
//		 callback function for triggers that don't want or need
//		 any special callback function.
// Note: The use of SCRIPT_API is used by all trigger functions
//		 to ensure they are exported correctly. (Although, 
//		 technically it's not needed in this case since this
//		 function has a function prototype defined in 
//		 RequiredExports.h which contains the SCRIPT_API macro
//		 in it. However, most other trigger callback functions
//		 won't have a function prototype anywhere (and you really
//		 don't need to declare a function prototype since you
//		 should never be calling a callback function yourself)
//		 so you should use the SCRIPT_API macro when you define
//		 the function.
//		 Might as well set a good example. =)

SCRIPT_API void NoResponseToTrigger()
{
}



