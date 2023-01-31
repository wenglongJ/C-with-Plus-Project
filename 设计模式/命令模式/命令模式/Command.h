#pragma once
#include "Device.h"
//Command类
class Command {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

//空命令什么都不做
class VoidCommand :public Command {
public:
	VoidCommand() {}
	void execute()override { }
	void undo() override { }
private:
	Light* mLight;
};

class LightOnCommand :public Command {
public:
	LightOnCommand(Light* light) :mLight(light) {}
	void execute()override { mLight->on(); }
	void undo()override { mLight->off(); }
private:
	Light* mLight;
};

class LightOffCommand :public Command {
public:
	LightOffCommand(Light* light) :mLight(light) {}
	void execute()override { mLight->off(); }
	void undo()override { mLight->on(); }
private:
	Light* mLight;
};

class TVOnCommand :public Command {
public:
	TVOnCommand(TV* tv) : mTV(tv) {}
	void execute()override { mTV->on(); }
	void undo()override { mTV->off(); }
private:
	TV* mTV;
};

class TVOffCommand :public Command {
public:
	TVOffCommand(TV* tv) : mTV(tv) {}
	void execute()override { mTV->off(); }
	void undo()override { mTV->on(); }
private:
	TV* mTV;
};

class CeilingFanHighCommand :public Command 
{
public:
	CeilingFanHighCommand(CeilingFan* CeilingFan) : mCeilingFan(CeilingFan) {}
	void execute()override 
	{ 
		nSpeed = mCeilingFan->GetSpeed();
		mCeilingFan->High();
	}
	void undo()override 
	{
		switch (nSpeed)
		{
		case CeilingFan::OFF:
			mCeilingFan->off();
			break;
		case CeilingFan::LOW:
			mCeilingFan->Low();
			break;
		case CeilingFan::MEDIUM:
			mCeilingFan->Medium();
			break;
		case CeilingFan::HIGH:
			mCeilingFan->High();
			break;
		default:
			break;
		}
	}
private:
	CeilingFan* mCeilingFan;
	CeilingFan::TSpeed nSpeed;
};

class CeilingFanOffCommand :public Command
{
public:
	CeilingFanOffCommand(CeilingFan* CeilingFan) : mCeilingFan(CeilingFan) {}
	void execute()override
	{
		nSpeed = mCeilingFan->GetSpeed();
		mCeilingFan->off();
	}
	void undo()override
	{
		switch (nSpeed)
		{
		case CeilingFan::OFF:
			mCeilingFan->off();
			break;
		case CeilingFan::LOW:
			mCeilingFan->Low();
			break;
		case CeilingFan::MEDIUM:
			mCeilingFan->Medium();
			break;
		case CeilingFan::HIGH:
			mCeilingFan->High();
			break;
		default:
			break;
		}
	}
private:
	CeilingFan* mCeilingFan;
	CeilingFan::TSpeed nSpeed;
};
