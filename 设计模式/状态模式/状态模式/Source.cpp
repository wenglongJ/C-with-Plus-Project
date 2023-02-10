#include<iostream>
#include<string>
#include<ctime>
using namespace std;

class State {
public:
	virtual ~State() {};
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
};

class Machine {
public:
	virtual void releaseBall() = 0;
	virtual void setState(State* m_state) = 0;
	virtual State* getSoldState() = 0;
	virtual State* getSoldOutState() = 0;
	virtual State* gethasQuarterState() = 0;
	virtual State* getNoQuarterState() = 0;
	virtual State* getWinnerState() = 0;
	virtual int getCount() = 0;
};

class SoldState :public State {
public:
	SoldState(Machine* m_machine) :machine(m_machine) {}
	virtual void insertQuarter() {
		cout << "Please wait we are already giving you a gumball" << endl;
	}
	virtual void ejectQuarter() {
		cout << "Sorry,you already turned the crank" << endl;
	}
	virtual void turnCrank() {
		cout << "Turning twice does not get you another gumball!" << endl;
	}
	virtual void dispense() {
		machine->releaseBall();
		if (machine->getCount() > 0) {
			machine->setState(machine->getNoQuarterState());
		}
		else {
			machine->setState(machine->getSoldOutState());
		}

	}

private:
	Machine* machine = nullptr;

};

class WinnerState :public State {
public:
	WinnerState(Machine* m_machine) :machine(m_machine) {}
	virtual void insertQuarter() {
		cout << "Please wait we are already giving you a gumball" << endl;
	}
	virtual void ejectQuarter() {
		cout << "Sorry,you already turned the crank" << endl;
	}
	virtual void turnCrank() {
		cout << "Turning twice does not get you another gumball!" << endl;
	}
	virtual void dispense() {
		cout << "You are WINNER! get two gumballs" << endl;
		machine->releaseBall();
		if (machine->getCount() > 0) {
			machine->releaseBall();
			if (machine->getCount() > 0)
				machine->setState(machine->getNoQuarterState());
			else
				machine->setState(machine->getSoldOutState());
		}
		else {
			cout << " Oops, out if gumballs!" << endl;
			machine->setState(machine->getSoldOutState());
		}

	}

private:
	Machine* machine = nullptr;

};
class SoldOutState :public State {
public:
	virtual void insertQuarter() {
		cout << "you can not insert another quarter" << endl;
	}
	virtual void ejectQuarter() {
		cout << "you can not eject, you have not inserted a quarter yet" << endl;
	}
	virtual void turnCrank() {
		cout << "you turned ,but thert are no gumballs!" << endl;
	}
	virtual void dispense() {
		cout << "there is no gumballs!!" << endl;
	}

};

class hasQuarterState :public State {
public:
	hasQuarterState(Machine* m_machine) :machine(m_machine) {
		srand((int)time(NULL));
	}
	virtual void insertQuarter() {
		cout << "you can not insert another quarter" << endl;
	}
	virtual void ejectQuarter() {
		cout << "quarter returned" << endl;
		machine->setState(machine->getNoQuarterState());
	}
	virtual void turnCrank() {
		cout << "you turned...." << endl;
		int choice = rand() % 10;
		if (choice == 1) {
			machine->setState(machine->getWinnerState());
		}
		else {
			machine->setState(machine->getSoldState());
		}
	}
	virtual void dispense() {
		cout << "No gumball dispensed" << endl;
	}

private:
	Machine* machine = nullptr;

};

class noQuarterState :public State {
public:
	noQuarterState(Machine* m_machine) :machine(m_machine) {}
	virtual void insertQuarter() {
		cout << "you inserted a quarter" << endl;
		machine->setState(machine->gethasQuarterState());
	}
	virtual void ejectQuarter() {
		cout << "you have not inserted a quarter" << endl;
	}
	virtual void turnCrank() {
		cout << "you turned,but there are no gumballs" << endl;
	}
	virtual void dispense() {
		cout << "No gumball dispensed" << endl;
	}

private:
	Machine* machine = nullptr;

};


class GumballMachine :public Machine {
private:
	State* soldstate = nullptr;
	State* soldoutstate = nullptr;
	State* hasquarterState = nullptr;
	State* noquarterState = nullptr;

	State* winnerstate = nullptr;

	State* state = soldoutstate;

	int count = 0;
public:
	GumballMachine(int m_count) :count(m_count) {
		soldstate = new SoldState(this);
		soldoutstate = new SoldOutState;
		hasquarterState = new hasQuarterState(this);
		noquarterState = new noQuarterState(this);
		winnerstate = new WinnerState(this);
		if (count > 0) {
			state = noquarterState;
		}
	}

	void insertQuarter() {
		if (state)
			state->insertQuarter();
	}
	void ejectQuarter() {
		if (state)
			state->ejectQuarter();
	}
	void turnCrank() {
		if (state)
			state->turnCrank();
	}
	void dispense() {
		if (state)
			state->dispense();
	}

	void releaseBall() {
		cout << "A gumball comes rolling out the slot...." << endl;
		if (count != 0) {
			--count;
		}
	}
	void setState(State* m_state) {
		state = m_state;
	}
	State* getSoldState() {
		return soldstate;
	}
	State* getSoldOutState() {
		return soldoutstate;
	}
	State* gethasQuarterState() {
		return  hasquarterState;
	}
	State* getNoQuarterState() {
		return noquarterState;
	}
	virtual State* getWinnerState() {
		return winnerstate;
	}

	int getCount() {
		return count;
	}

};


int main() {
	GumballMachine* machine = new GumballMachine(10);

	while (machine->getCount() > 0) {
		machine->insertQuarter();
		machine->turnCrank();
		machine->dispense();
		cout << machine->getCount() << endl << endl;
	}


	system("pause");
	return 0;
}
