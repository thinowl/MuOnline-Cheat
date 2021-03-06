//-----------------------------------------------------------
// Project: MuOnline97d
// Hacking tool, for game MuOnline with version 97d.
//-----------------------------------------------------------
// Author: Bruno Medeiros
// Description: Developer of GameEngine and ModEngine.
// Assistance: Wolfulus
// Description: Developer of GameEngine::Cryptographer.
//-----------------------------------------------------------
#include "Includes.h"

DWORD WINAPI MainInitialization(PBOOLEAN SysRunning)
{
	// Wait stage of select char.
	while (GameEngine::StageScene != GameEngine::STAGE_CHARS)
	{ Sleep(100); }
	// Welcome Message
	GameEngine::ShowBox("Bem vindo ao CheatsUnknown v0.0.1!");
	// Wait a moment, to initialize the memory file mapping.
	Sleep(3000);
	// Initialize Controller System
	if (ModEngine::Controller::Initialize("Global\\MappingCheatsUnknown"))
	{
		// Initialize Integrator System, ex: { SpeedHacker }
		ModEngine::Integrator::Initialize();
		// Initialize AutoKill System, ex: { Auto UP }
		ModEngine::AutoKill::Initialize();
		// Initialize Battle System, ex: { OneHit, FastPot }
		ModEngine::Battle::Initialize();
		// Initialize Runtime System, ex: { Pull, Trace }
		ModEngine::Runtime::Initialize();
		// Stop when application controller has closed.
		while (SysRunning && ModEngine::Controller::Cache->KeyProtect >= GetTickCount() - 1000)
		{
			// FastPot
			ModEngine::Battle::FastPotKey = ModEngine::Controller::Cache->FastPot.Key;
			ModEngine::Battle::FastPotDelay = ModEngine::Controller::Cache->FastPot.Timer;
			ModEngine::Battle::FastPotStatus = ModEngine::Controller::Cache->FastPot.Status;
			// OneHit
			ModEngine::Battle::OneHitKey = ModEngine::Controller::Cache->OneHit.Key;
			ModEngine::Battle::OneHitDelay = ModEngine::Controller::Cache->OneHit.Timer;
			ModEngine::Battle::OneHitStatus = ModEngine::Controller::Cache->OneHit.Status;
			// AutoKill
			ModEngine::AutoKill::Range = ModEngine::Controller::Cache->AutoKill.Range;
			ModEngine::AutoKill::Timer = ModEngine::Controller::Cache->AutoKill.Timer;
			ModEngine::AutoKill::Status = ModEngine::Controller::Cache->AutoKill.Status;
			// Speed Hacker
			ModEngine::Integrator::GameAcceleration = ModEngine::Controller::Cache->GameSpeedTimer;
			// Targets
			ModEngine::Runtime::TargetsCount = ModEngine::Controller::Cache->TargetsCount;
			memcpy(&ModEngine::Runtime::Targets, ModEngine::Controller::Cache->Targets, sizeof(ModEngine::Controller::Cache->Targets));
			// Utils Functions
			ModEngine::Runtime::Pull = ModEngine::Controller::Cache->Pull;
			ModEngine::Runtime::Trace = ModEngine::Controller::Cache->Trace;
			ModEngine::Runtime::AutoTrade = ModEngine::Controller::Cache->AutoTrade;
			// Delay 50ms
			Sleep(50);
		}
	}
	// Finalize Game Instance
	ExitProcess(0);
	// Return thread result
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	// Control running system.
	static BOOLEAN Running = TRUE;
	// Processing of reasons
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			// Debug Initialize if actived
			DEBUG_INITIALIZE("[DEBUG - CheatsUnknown] MuOnline Server");
			// Disables the flags [DLL_THREAD_ATTACH, DLL_THREAD_DETACH].
			DisableThreadLibraryCalls(hModule);
			// Create Thread of Initialization
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&MainInitialization, &Running, 0, NULL);
			break;

		case DLL_PROCESS_DETACH:
			// Force main thread finalize
			Running = FALSE;
			// Terminate thread and Free Library.
			FreeLibraryAndExitThread(hModule, 0);
			break;
	}
	return TRUE;
}
