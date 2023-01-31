#include "Test.h"

int main()
{
	RemoteControl remoteControl;
	//实例化接收者对象和命令对象
	Light light;
	LightOnCommand lightOnCommand(&light);
	LightOffCommand lightOffCommand(&light);

	remoteControl.setCommand(0, &lightOnCommand, &lightOffCommand);
	remoteControl.onButtonWasPushed(0);
	remoteControl.undoButtonWasPushed();
	remoteControl.offButtonWasPushed(0);

	TV tv;
	TVOnCommand tvOnCommand(&tv);
	TVOffCommand tvOffCommand(&tv);

	remoteControl.setCommand(1, &tvOnCommand, &tvOffCommand);
	remoteControl.onButtonWasPushed(1);
	remoteControl.undoButtonWasPushed();
	remoteControl.offButtonWasPushed(1);

	CeilingFan ceilingFan;
	CeilingFanHighCommand ceilingFanHighCommand(&ceilingFan);
	CeilingFanOffCommand ceilingFanOffCommand(&ceilingFan);

	remoteControl.setCommand(2, &ceilingFanHighCommand, &ceilingFanOffCommand);
	remoteControl.onButtonWasPushed(2);
	remoteControl.undoButtonWasPushed();
	remoteControl.offButtonWasPushed(2);
	getchar();
	return 0;
}