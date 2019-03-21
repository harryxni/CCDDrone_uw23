#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>

#include "LeachController.hpp"
#include <chrono>
#include <thread>


// ------------------------------------------------------
//  Main program
// ------------------------------------------------------
int main( int argc, char **argv )
{


    std::cout << "This code apply new settings on the the clock and bias voltages.\n";
    

	LeachController _ThisRunControllerInstance("config/FirstTest.ini");

	std::cout<<"Checking for new settings and loading them.\n";
	//_ThisRunControllerInstance.LoadCCDSettingsFresh();
	bool config, sequencer;
	int _CCDSettingsStatus = _ThisRunControllerInstance.LoadAndCheckForSettingsChange(config, sequencer);


	/*Apply biases and clocks*/
	std::cout<<"Applying biases and clocks.\n";
	_ThisRunControllerInstance.ApplyAllBiasVoltages(_ThisRunControllerInstance.CCDParams, _ThisRunControllerInstance.BiasParams);
	_ThisRunControllerInstance.ApplyAllCCDClocks(_ThisRunControllerInstance.CCDParams, _ThisRunControllerInstance.ClockParams);

	if (sequencer){
		std::cout<<"Applying new sequencer.\n";
		_ThisRunControllerInstance.ApplyNewSequencer(_ThisRunControllerInstance.CCDParams.sTimFile);
	}

	_ThisRunControllerInstance.CopyOldAndStoreFileHashes();

	std::cout<<"Set IDLE clocks to ON.\n";
    _ThisRunControllerInstance.IdleClockToggle();


    std::cout<<"New settings have been uploaded to the Leach system.\n";

	return 0;
}

