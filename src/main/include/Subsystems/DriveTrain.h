// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<rev::CANSparkMax> sparkMax1;
	std::shared_ptr<rev::CANSparkMax> sparkMax2;
	std::shared_ptr<frc::SpeedControllerGroup> speedControllerGroupLeft;
	std::shared_ptr<rev::CANSparkMax> sparkMax3;
	std::shared_ptr<rev::CANSparkMax> sparkMax4;
	std::shared_ptr<frc::SpeedControllerGroup> speedControllerGroupRight;
	std::shared_ptr<frc::DifferentialDrive> differentialDrive;
	nt::NetworkTableEntry xEntry;
	nt::NetworkTableEntry yEntry;

	double GEARING_RATIO = 5.95;
	int WHEEL_SIZE = 4; 			// [in]
	double PI = 3.14159265358;

	// Members for closed-loop velocity control
	std::shared_ptr<rev::CANPIDController> pidControllerL;
	std::shared_ptr<rev::CANPIDController> pidControllerR;

	// PID Gains
	double kP = 0, kI = 0, kD = 0, kIz = 0, kFF = 1.75e-4, kMaxOutput = 1, kMinOutput = -1;
	// EDIT THESE VALUES LATER

	// Max RPM for motors
	const double maxRPM = 5600;

	double commandedSpeed;
public:
	DriveTrain();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void TankDrive(double left, double right);
	void ArcadeDrive(double leftMove, double leftRotate);
	void VisionTargetDrive();
	void ClosedLoopVelocityControl(double speed);

	// Functions for the closed-loop velocity
	double getMotorRPM(int id);
	double getRobotSpeed();
	double getCommandedSpeed();

	nt::NetworkTableEntry getXEntry();
	nt::NetworkTableEntry getYEntry();
};

#endif
