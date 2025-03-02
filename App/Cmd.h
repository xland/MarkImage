#pragma once

#include "../Util/Eventer.h"

class Cmd:public Eventer
{
public:
	Cmd();
	~Cmd();
	void init();
private:
	void attachCmd();
};

