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


    std::cout << "This code will power on the leach and apply the clock and bias voltages.\n"
              << "Then it will perform an erase procedure.\n"
              << "The process starts in 10 seconds. Please ensure that the Leach is switched ON.\n";

    std::this_thread::sleep_for(std::chrono::seconds(10));


	LeachController _ThisRunControllerInstance("config/FirstTest.ini");

	/*First, check if the settings file has changed in any way*/
	std::cout<<"Checking for new settings and loading them.\n";
	_ThisRunControllerInstance.LoadCCDSettingsFresh();

	/*Startup the CCD*/
	std::cout<<"Starting up the controller.\n";
    _ThisRunControllerInstance.StartupController();

	/*Apply biases and clocks*/
	std::cout<<"Applying biases and clocks.\n";
	_ThisRunControllerInstance.ApplyAllBiasVoltages(_ThisRunControllerInstance.CCDParams, _ThisRunControllerInstance.BiasParams);
	_ThisRunControllerInstance.ApplyAllCCDClocks(_ThisRunControllerInstance.CCDParams, _ThisRunControllerInstance.ClockParams);


	/*Erase procedure*/
	std::cout<<"Set IDLE clocks to ON and then start erase procedure in 5 seconds.\n";
    _ThisRunControllerInstance.IdleClockToggle();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _ThisRunControllerInstance.PerformEraseProcedure();


    std::cout<<"Leach system is now ready to take data.\n";


}

