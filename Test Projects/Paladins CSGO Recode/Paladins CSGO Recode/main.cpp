#include "main.h"



int main()
{

	DEBUG(DBG, 1, "Creating engine object\n");

	Engine *eng = new Engine();

	if (eng == nullptr) 
	{
		DEBUG(ERR, 1, "Engine object handle null\n");
		LASTERR(1);
		return false;
	}

	DEBUG(DBG, 1, "Starting engine\n");

	if (!eng->Start()) 
	{
		DEBUG(ERR, 1, "Unable to start engine\n");
		return false;
	}

	//ToDo: Something maybe? idk. Might not need to.

	DEBUG(DBG, 1, "Deleting engine object\n");

	delete eng;

	DEBUG(SCS, 1, "Engine object deleted\n");

	DEBUG(DBG, 1, "Closing\n");

	return 0;
}