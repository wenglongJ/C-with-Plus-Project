#pragma once
#include <iostream>
//¼Òµç×°ÖÃ£¬receiver
class Light {
public:
	void on() {
		std::cout << "Light on!" << std::endl;
	}
	void off() {
		std::cout << "Light off!" << std::endl;
	}
};

class TV {
public:
	void on() {
		std::cout << "TV on!" << std::endl;
	}
	void off() {
		std::cout << "TV off!" << std::endl;
	}
};

class CeilingFan {
public:
	enum TSpeed { OFF, LOW, MEDIUM, HIGH };
public:
	void High()
	{
		nSpeed = HIGH;
		std::cout << "CeilingFan High Speed!" << std::endl;
	}
	void Medium()
	{
		nSpeed = MEDIUM;
	}
	void Low()
	{
		nSpeed = LOW;
	}
	void off()
	{
		nSpeed = OFF;
		std::cout << "CeilingFan off!" << std::endl;
	}
	TSpeed GetSpeed()
	{
		return nSpeed;
	}

private:
	TSpeed nSpeed;
};

class GarageDoor {
public:
	void on() {
		std::cout << "GarageDoor on!" << std::endl;
	}
	void off() {
		std::cout << "GarageDoor off!" << std::endl;
	}
};

class StereOnWithCD {
public:
	void on() {
		std::cout << "StereOnWithCD on!" << std::endl;
	}
	void off() {
		std::cout << "StereOnWithCD off!" << std::endl;
	}
};
