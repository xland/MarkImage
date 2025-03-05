#pragma once
class Cmd
{
public:
	Cmd();
	~Cmd();
	static void init();
private:
	static void attachCmd();
};