// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/TankDriveCommand.h"
#include "Commands/TeleopDriveStraight.h"
#include "frc/RobotController.h"
#include <iostream>

double left;
double right; //create the variables here so they can be used in all methods of this class. 

double leftMove;
double leftRotate;
bool logData = false;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
        // Use requires() here to declare subsystem dependencies
TankDriveCommand::TankDriveCommand(): 
frc::Command(), driveMode((DriveMode) frc::Preferences::GetInstance()->GetInt("Drive Mode", arcadeDriveVelocity))
{
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void TankDriveCommand::Initialize() {
    //left = Robot::oi->getJoystickLeft()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
    //right = Robot::oi->getJoystickRight()->GetY(frc::GenericHID::JoystickHand::kRightHand);

    leftMove =  Robot::oi->getJoystickLeft()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
    leftRotate =  Robot::oi->getJoystickLeft()->GetX(frc::GenericHID::JoystickHand::kLeftHand);

    if(arrRow != 0){
        arrRow = 0;
    } //zero it to start with. 

    //Robot::driveTrain->TankDriveVelocity(left, right, false);
    //Robot::driveTrain->ArcadeDrive(leftMove, leftRotate);
    //Robot::driveTrain->ClosedLoopVelocityControl(leftMove);
    //Robot::driveTrain->ArcadeDriveVelocity(leftMove, leftRotate, true);
    Robot::driveTrain->MotionProfilePosition(dT, arrRow);

    if (logData) {
        std::cout << "Timestamp [ms]" << "\t\t" << "Motor RPM" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
    }
}

// Called repeatedly when this Command is scheduled to run
void TankDriveCommand::Execute() {
    double left;
    double right;
    double leftMove;
    double leftRotate;
    double sparkSpeed;

    switch(driveMode) {
        case tankDriveVelocity:
            left = Robot::oi->getJoystickLeft()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
            right = Robot::oi->getJoystickRight()->GetY(frc::GenericHID::JoystickHand::kRightHand);
            Robot::driveTrain->TankDriveVelocity(left, right, false);
            break;
        case arcadeDriveVelocity:
            leftMove = Robot::oi->getJoystickLeft()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
            leftRotate = Robot::oi->getJoystickLeft()->GetX(frc::GenericHID::JoystickHand::kLeftHand);
            leftMove *= (-1);
            Robot::driveTrain->ArcadeDriveVelocity(leftRotate, leftMove, false);
            break;
        case testCANSparkMax:
                sparkSpeed = Robot::oi->getJoystickLeft()->GetY(frc::GenericHID::JoystickHand::kLeftHand);
                Robot::driveTrain->getCANSparkMax(1)->Set(sparkSpeed);
            break;
        case motionProfileDrive:
            Robot::driveTrain->MotionProfilePosition(dT, arrRow);
            arrRow++;
            break;
    }

    if (logData) {
        // Datalogger
        long time = frc::RobotController::GetFPGATime() / 1e3;      // / 1e6 bc unit is microsecond
        std::cout << (double)time << "\t\t" << Robot::driveTrain->getMotorRPM(1) << std::endl;
    }
}

// Make this return true when this Command no longer needs to run execute()
bool TankDriveCommand::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void TankDriveCommand::End() {}   

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDriveCommand::Interrupted() {}
