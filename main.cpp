#pragma warning(disable : 4996)

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <algorithm>
#include <sstream>
#include <memory>
#include <string_view>
#include <cstdint>
#include <string>
#include <cmath>
#include <thread>
#include <xstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <xmmintrin.h>
#include <intrin.h>

#include "xor.h"
#include "1xor.h"
#include "mem_driver/hello.h"
#include "math/math.h"
#include "settings.h"
#include "sdk/offsets.h"

uintptr_t GWorld = 0, GName = 0;

std::string GetNameById(uint32_t actor_id)
{
	char pNameBuffer[256];
	int TableLocation = (unsigned int)(actor_id >> 0x10);
	uint16_t RowLocation = (unsigned __int16)actor_id;
	uint64_t GNameTable = DbdBaseAddress + GName;

	uint64_t TableLocationAddress = mem_read(GNameTable + 0x10 + TableLocation * 0x8, uint64_t) + (unsigned __int32)(4 * RowLocation);

	uint64_t sLength = (unsigned __int64)(mem_read(TableLocationAddress + 4, uint16_t)) >> 1;

	if (sLength < 128)
	{
		drv::read_memory(drv::sock, oPID, (TableLocationAddress + 6), (uintptr_t)pNameBuffer, sLength);
		return std::string(pNameBuffer);
	}
	return std::string(XorStr("NULL"));
}

void Aura(uintptr_t obj, uint32_t addr, float color[3]) {

	if (!obj)
		return;

	auto outLine = mem_read(obj + addr, uintptr_t);
	if (!outLine)
		return;

	mem_write(outLine + 0x3B4, color[0]);
	mem_write(outLine + 0x3B8, color[1]);
	mem_write(outLine + 0x3BC, color[2]);
	mem_write(outLine + 0x3C0, 1.f);
}
 

enum class EPalletState : char
{
	Up = 0,
	Falling = 1,
	Fallen = 2,
	Destroyed = 3,
	EPalletState_MAX = 4,
};

namespace Cache {

	class Object {
	public:

		Object(uintptr_t o) {
			Obj = o;
 		}

		uintptr_t GetObj() {

			if (!this)
				return 0;

			return Obj;
		}


	private:
		uintptr_t Obj;
 	};

	std::vector<Object*> Players = {};
	std::vector<Object*> Killers = {};
	std::vector<Object*> Chests = {};
	std::vector<Object*> Hooks = {};
	std::vector<Object*> Exits = {};
	std::vector<Object*> Windows = {};
	std::vector<Object*> Gens = {};
	std::vector<Object*> Pallets = {};
	std::vector<Object*> Hatch = {};
	std::vector<Object*> Traps = {};
}

void Loop() {

 
	auto World = mem_read(DbdBaseAddress + GWorld, uintptr_t);
	if (!World) 
		return;

	static bool StoreObjects = true;
  
	auto WorldName = mem_read(World + 0x18, EngineUtils::FName);
	if (GetNameById(WorldName.GetDisplayIndex()).find(XorStr("Lobby")) != std::string::npos || GetAsyncKeyState(VK_F2) & 1) {
		StoreObjects = true;
		return;
	}

	if (StoreObjects) {

		Cache::Players.clear();
		Cache::Killers.clear();
		Cache::Chests.clear();
		Cache::Pallets.clear();
		Cache::Gens.clear();
		Cache::Hooks.clear();
		Cache::Windows.clear();
	

		auto Levels = mem_read(World + O::UWorld::Level, uintptr_t);
		if (!Levels)
			return;

 		for (int i = 0; i < mem_read(World + O::UWorld::LevelSize, int); i++) {

			auto Level = mem_read(Levels + i * 8, uintptr_t);
			if (!Level)
				continue;

			auto Actors = mem_read(Level + O::ULevel::ActorArray, uintptr_t);
			if (!Actors)
				continue;

			for (int j = 0; j < mem_read(Level + O::ULevel::ActorCount, int); j++) {

				auto Actor = mem_read(Actors + j * 8, uintptr_t);
				if (!Actor)
					continue;

				auto Name = mem_read(Actor + 0x18, EngineUtils::FName);
				auto NameByID = GetNameById(Name.GetDisplayIndex());

				if (NameByID.find(XorStr("BP_CamperFemale")) != std::string::npos || NameByID.find(XorStr("BP_CamperMale")) != std::string::npos) 
					Cache::Players.push_back(new Cache::Object(Actor));

				if (NameByID.find(XorStr("BP_Slasher")) != std::string::npos)
					Cache::Killers.push_back(new Cache::Object(Actor));

				if (NameByID.find(XorStr("BP_Chest")) != std::string::npos) 
					Cache::Chests.push_back(new Cache::Object(Actor));


				if (NameByID.find(XorStr("BP_Pallet")) != std::string::npos) 
					Cache::Pallets.push_back(new Cache::Object(Actor));


				if (NameByID.find(XorStr("WindowStandard")) != std::string::npos) 
					Cache::Windows.push_back(new Cache::Object(Actor));


				if (NameByID.find(XorStr("GeneratorStandard")) != std::string::npos || NameByID.find(XorStr("GeneratorNoPole")) != std::string::npos) 
					Cache::Gens.push_back(new Cache::Object(Actor));

				if (NameByID.find(XorStr("BP_MeatHook")) != std::string::npos) 
					Cache::Hooks.push_back(new Cache::Object(Actor));

			}

		}

		StoreObjects = false;
	}
	else {
		auto IterateDefObj = [](std::vector<Cache::Object*> objects, uint32_t addr, float auraCol[3]) {

			for (int i = 0; i < objects.size(); i++) {

				auto obj = objects[i];
				if (!obj)
					continue;

				Aura(obj->GetObj(), addr, auraCol);
			}

		};

		static float SurvColor[3] = { 0.f,1.f, 0.f };
		IterateDefObj(Cache::Players, O::SurvivorDBDOutline, SurvColor);
		 
		static float KillerColor[3] = { 1.f,0.f, 0.f };
		IterateDefObj(Cache::Killers, O::KillerDBDOutline, KillerColor);

		static float ChestColor[3] = { 33.f / 255.f, 77.f / 255.f, 191.f / 255.f };
		IterateDefObj(Cache::Chests, O::ChestDBDOutline, ChestColor);
		 
		IterateDefObj(Cache::Gens, O::GeneratorDBDOutline, KillerColor);

 
 		static float HookColor[3] = { 1.f,1.f, 1.f};

		IterateDefObj(Cache::Hooks, O::MeatHookDBDOutline, HookColor);

		for (int i = 0; i < Cache::Pallets.size(); i++) {

			auto obj = Cache::Pallets[i]->GetObj();
			if (!obj)
				continue;

			auto PalletState = mem_read(obj + O::APallet::PalletState, EPalletState);

			float PalletColor[3] = { 125.f /255.f ,114.f / 255.f, 84.f / 255.f };

			if (PalletState == EPalletState::Destroyed) {

				PalletColor[0] = 1.f;
				PalletColor[1] = 0.f;
				PalletColor[3] = 0.f;
			}

			Aura(obj, O::PalletDBDOutline, PalletColor);
		}


		for (int i = 0; i < Cache::Windows.size(); i++) {

			auto obj = Cache::Windows[i]->GetObj();
			if (!obj)
				continue;

			float WindowColor[3] = { 250.f / 255.f, 157.f / 255.f, 7.f / 255.f };

			auto blockComp = mem_read(obj + 0x430, uintptr_t);
			if (blockComp) {
				if (mem_read(blockComp + 0xd0, uintptr_t) != 0) {
					WindowColor[0] = 1.f;
					WindowColor[1] = 0.f;
					WindowColor[2] = 0.f;
				}

			}
  

			Aura(obj, O::WindowDBDOutline, WindowColor);
		}

	}


}

std::string CurrentProc = "";
HWND hwnd = 0;
void init_overlay( ) {	
	
	while (!hwnd)
	{
 		hwnd = FindWindowA(XorStr("UnrealWindow").c_str(), 0);
 		Sleep(100);
	}

	oPID = get_process_id(CurrentProc);
	if (!oPID) {
		std::cout << XorStr("PID") << std::endl;
		Sleep(3000);
		exit(0);
	}

 	DbdBaseAddress = drv::get_process_base_address(oPID);
  	if (!DbdBaseAddress) {
		std::cout << XorStr("invalid module") << std::endl;
		Sleep(3000);
		exit(0);
	}

	while (true) {
		
		if (FindWindowA(XorStr("UnrealWindow").c_str(), 0) == 0) {
			exit(0);
			break;
		}

		Loop();
	}

}

int main() {

	std::cout << XorStr("1 - steam, 2 - epic games, 3 - microsoft store").c_str() << std::endl;
	int res = 0;
	std::cin >> res;

 
	switch (res)
	{
		case 1:
 			GWorld = 0xA7E7E30;
			GName = 0xA58F880;
			CurrentProc = XorStr("DeadByDaylight-Win64-Shipping.exe");
		break;
		case 2:
 			GWorld = 0xA2A6140;
			GName = 0xA0613C0;
			CurrentProc = XorStr("DeadByDaylight-EGS-Shipping.exe");
			break;
		case 3:
 			GWorld = 0xA690180;
			GName = 0xA437E80;
			CurrentProc = XorStr("DeadByDaylight-WinGDK-Shipping.exe");
			break;
	default:
		std::cout << XorStr("invalid input") << std::endl;
		Sleep(1000);
		exit(0);
		break;
	}

	init_overlay();
}