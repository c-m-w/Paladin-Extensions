#pragma once

class Engine
{
public:
	Engine();
	~Engine();

private:
	Memory *mem;

	bool attached;
	bool initialized;

public:
	bool Start();

private:
	void Task1();
};