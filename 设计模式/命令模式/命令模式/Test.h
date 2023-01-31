#pragma once
#include "Command.h"

//调用者，遥控器类
class RemoteControl {
public:
	RemoteControl()
	{
		for (int i = 0; i < 7; i++)
		{
			onCommands[i] = new VoidCommand();//初始化为空命令。
			offCommands[i] = new VoidCommand();//初始化为空命令。
		}
	}
	~RemoteControl()
	{
		for (int i = 0; i < 7; i++)
		{
			delete onCommands[i];
			onCommands[i] = nullptr;
			delete offCommands[i];
			offCommands[i] = nullptr;
		}
		delete undoCommand;
		undoCommand = NULL;
	}


	void setCommand(int slot, Command* onCommand, Command* offCommand)
	{
		delete onCommands[slot];
		onCommands[slot] = onCommand;
		delete offCommands[slot];
		offCommands[slot] = offCommand;
	}

	void onButtonWasPushed(int slot)
	{
		onCommands[slot]->execute();
		undoCommand = onCommands[slot];
	}

	void offButtonWasPushed(int slot)
	{
		offCommands[slot]->execute();
		undoCommand = offCommands[slot];
	}

	void undoButtonWasPushed()
	{
		undoCommand -> undo();
	}
private:
	Command* onCommands[7];
	Command* offCommands[7];
	Command* undoCommand;
};
