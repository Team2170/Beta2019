// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Subsystems/DriveTrain.h"
#include "Commands/TankDriveCommand.h"
#include <iostream>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
int count = 0;
DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
    sparkMax1.reset(new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless));
    sparkMax2.reset(new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless));
    sparkMax3.reset(new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless));
    sparkMax4.reset(new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless));
    differentialDrive.reset(new frc::DifferentialDrive(*sparkMax1, *sparkMax3));
    differentialDrive->SetSafetyEnabled(false);

    // Set follower modes for sparkMax2 and sparkMax4
    sparkMax2->Follow(*sparkMax1);
    sparkMax4->Follow(*sparkMax3);

    // Initialize PID controllers
    pidControllerL.reset(new rev::CANPIDController(sparkMax1->GetPIDController()));
    pidControllerR.reset(new rev::CANPIDController(sparkMax3->GetPIDController()));

    // Set min/max powers
    pidControllerL->SetOutputRange(kMinOutput, kMaxOutput);
    pidControllerR->SetOutputRange(kMinOutput, kMaxOutput);
}
void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    SetDefaultCommand(new TankDriveCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveTrain::Periodic() {
    // Put code here to be run every loop

}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::TankDrive(double left, double right) {
    //std::cout << left << "\t\t" << right << std::endl;
    differentialDrive->TankDrive(left, right);
}

void DriveTrain::ArcadeDrive(double leftMove, double leftRotate) {
    // Get joystick(s)
    double y = leftMove;
    double x = leftRotate;

    // if(x>0.5){
    //     x-=0.5;
    // } else if(x<-0.5){
    //     x+=0.5;
    // }

    // if(y>0.5){
    //     y-=0.5;
    // } else if(y<-0.5){
    //     y+=0.5;
    // } //set the max speeds of the x and y axes to 0.5. 

    std::cout << "Move: " << y << "\t\t" << "Rotate: " << x << std::endl;

    differentialDrive->ArcadeDrive(y, x);
}

void DriveTrain::VisionTargetDrive(){
    
}

void DriveTrain::ClosedLoopVelocityControl(double speed) {
    // read PID coefficients from SmartDashboard
    double p = frc::SmartDashboard::GetNumber("P Gain", 0);
    double i = frc::SmartDashboard::GetNumber("I Gain", 0);
    double d = frc::SmartDashboard::GetNumber("D Gain", 0);
    double iz = frc::SmartDashboard::GetNumber("I Zone", 0);
    double ff = frc::SmartDashboard::GetNumber("Feed Forward", 0);
    double commandedSpeed = frc::SmartDashboard::GetNumber("Commanded Speed: ", 0);

    // if PID coefficients on SmartDashboard have changed, write new values to controller
    if(p != kP) {
        pidControllerL->SetP(p); kP = p;
        pidControllerR->SetP(p); kP = p;  
    }
    if(i != kI) {
        pidControllerL->SetI(i); kI = i;
        pidControllerR->SetI(i); kI = i;  
    }
    if(d != kD) {
        pidControllerL->SetD(d); kD = d;
        pidControllerR->SetD(d); kD = d;  
    }
    if(iz != kIz) {
        pidControllerL->SetIZone(iz); kIz = iz;
        pidControllerR->SetIZone(iz); kIz = iz;  
    }
    if(ff != kFF) {
        pidControllerL->SetFF(ff); kFF = ff;
        pidControllerR->SetFF(ff); kFF = ff;  
    }

    // read setpoint from joystick and scale by max rpm
    double setPointL = maxRPM * commandedSpeed;
    double setPointR = maxRPM * -commandedSpeed;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(setPointL, rev::ControlType::kVelocity);
    pidControllerR->SetReference(setPointR, rev::ControlType::kVelocity);

	// Put editable PID values on Dashboard
	frc::SmartDashboard::PutNumber("P Gain", kP);
    frc::SmartDashboard::PutNumber("I Gain", kI);
    frc::SmartDashboard::PutNumber("D Gain", kD);
    frc::SmartDashboard::PutNumber("I Zone", kIz);
    frc::SmartDashboard::PutNumber("Feed Forward", kFF);
	frc::SmartDashboard::PutNumber("Commanded Speed: ", commandedSpeed);

    
    //std::cout << kFF << std::endl;
}

double DriveTrain::getMotorRPM(int id) {
    double rpm;

    switch (id) {
        case 1:
            rpm = sparkMax1->GetEncoder().GetVelocity();
            break;
        case 2:
            rpm = sparkMax2->GetEncoder().GetVelocity();
            break;
        case 3:
            rpm = sparkMax3->GetEncoder().GetVelocity();
            break;
        case 4:
            rpm = sparkMax4->GetEncoder().GetVelocity();    
            break;     
     }

    return rpm;
}

double DriveTrain::getRobotSpeed() {
    double rpm = getMotorRPM(1);
    double rpm_axle = rpm / GEARING_RATIO;

    double circumference = PI*WHEEL_SIZE;

    double speed = (rpm_axle * circumference) / 12.0 / 60.0;  // [ft/s]

    return speed;
}

double DriveTrain::getCommandedSpeed() {
    return commandedSpeed;
}