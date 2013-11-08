#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     HiTeGyro,       sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     driveLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     conveyorTurn,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     conveyorDrive, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     hangRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     hangLeft,      tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drive.h"
#include "drive.c"
#include "conveyor.h"
#include "conveyor.c"
#include "hang.h"
#include "hang.c"
#include "gyro.h"
gyroSys gyr;
#include "gyro.c"

DriveSys drive;
ConvSys conv;
HangSys hang;


void initializeRobot()
{
	drive.Left = driveLeft;
	drive.Right = driveRight;

	conv.driveMotor = conveyorDrive;
	conv.turnMotor = conveyorTurn;

	hang.leftRaise = hangLeft;
	hang.rightRaise = hangRight;

	gyr.gyroscope = HiTeGyro;
	initGyroSys(gyr, 1000);
	StartTask(findHeading);
	return;
}

task main(){

	initializeRobot();

	#ifdef COMPETITION
	waitForStart();   // wait for start of tele-op phase
	#endif

	while (true){
		//getJoystickSettings(joystick);

		updateGyroSys(gyr);
		if(gyr.currentHeading == 0.0){
			writeDebugStreamLine("%f", gyr.rotationsHeading);
		}
		updateDriveSys(drive, joystick.joy1_y1 * (100.0/128.0), joystick.joy1_y2 * (100.0/128.0));

		updateConvSys(conv, joystick.joy2_y1 * (100.0/128.0), joystick.joy2_y2 * (100.0/128.0));
	}
}
