#include "main.h"

Engine::Engine()
{
	this->attached = false;
	this->initialized = false;

	DEBUG(DBG, 1, "Creating memory object\n");

	//Allocated memory for new mem class
	this->mem = new Memory();

	//Handle invalid allocation
	if (this->mem == nullptr) 
	{
		DEBUG(ERR, 1, "Memory object handle null\n");
		LASTERR(1);
		return;
	}

	DEBUG(SCS, 1, "Memory object allocated\n");

	DEBUG(DBG, 1, "Attaching to game\n");

	this->attached = this->mem->Attach();

	if (!this->attached)
	{
		DEBUG(ERR, 1, "Unable to attach\n");
		LASTERR(1);
		return;
	}

	DEBUG(SCS, 1, "Attached to game\n");

	this->initialized = this->mem->Init();

	if (!this->initialized) 
	{
		DEBUG(ERR, 1, "Unable to initialize\n");
		LASTERR(1);
		return;
	}

	DEBUG(SCS, 1, "Initialized\n");

	return;
}

Engine::~Engine()
{

	if (this->mem == nullptr) 
	{
		DEBUG(ERR, 1, "Memory object handle null\n");
		LASTERR(1);
		return;
	}
	
	DEBUG(DBG, 1, "Deleting memory object\n");

	delete this->mem;

	DEBUG(SCS, 1, "Memory object deleted\n");

	return;
}

/*	ToDo
 *	-Find other way to create thread to store in vector or something for easier cleanup
 *	-Better way to keep track of errors
 *	-Find better way to loop/kill threads without getting key state for each one (maybe a central controller class with callbacks on key press?)
 *	-Add more seperate classes for handling things potentially (find a way to init them too)
 */

bool Engine::Start()
{
	std::thread t1([this]() {this->Task1();});

	DEBUG(SCS, 1, "Engine started\n");

	while (!GetAsyncKeyState(VK_F4)) 
	{
		wait(100);
	}

	t1.join();

	return true;
}

void Engine::Task1()
{
	while (!GetAsyncKeyState(VK_F4)) 
	{
		this->mem->clientState = this->mem->rpm<DWORD>(this->mem->client + this->mem->clientStateOffs);
		DEBUG(DBG, 1, "[0x%08lu] %d\n", (DWORD)this->mem->client + (DWORD)this->mem->clientStateOffs, this->mem->clientState);
		wait(3000);
	}
}