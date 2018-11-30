/******************************************************************************
	Description:	2018 PowerUp Robot Drivetrain Subsystem.

	Subsystem:		Drivetrain

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <Commands/Drivetrain/ArcadeDrive.h>
#include "../IOMap.h"
#include "CANPosition.h"
#include "Subsystems/Drivetrain.h"
///////////////////////////////////////////////////////////////////////////////


Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	m_pDriveSolenoid = new Solenoid(kDriveSolenoidChannel);

	m_pLeftDrive   	 = new CCANPosition(kLeftDriveMotor1);
	m_pLeftDrive2  	 = new WPI_TalonSRX(kLeftDriveMotor2);
	m_pLeftDrive3  	 = new WPI_TalonSRX(kLeftDriveMotor3);

	m_pRightDrive  	 = new CCANPosition(kRightDriveMotor1);
	m_pRightDrive2 	 = new WPI_TalonSRX(kRightDriveMotor2);
	m_pRightDrive3 	 = new WPI_TalonSRX(kRightDriveMotor3);

	m_pRobotDrive = new DifferentialDrive (*m_pLeftDrive->GetMotorPointer(), *m_pRightDrive->GetMotorPointer());

	m_pGyro = new AHRS(SPI::Port::kMXP);

	// Set the pulses per rev.
	m_pLeftDrive->SetPulsesPerRev(1024);
	m_pRightDrive->SetPulsesPerRev(1024);
	// Set the Revs/Unit for 6 inch drive wheels.
///	m_pLeftDrive->SetRevsPerUnit(dDriveEncoderRevsPerInch);
///	m_pRightDrive->SetRevsPerUnit(dDriveEncoderRevsPerInch);
	// Invert the motor outputs.
	m_pLeftDrive->SetMotorInverted(true);
	m_pLeftDrive2->SetInverted(false);
	m_pLeftDrive3->SetInverted(true);
	m_pRightDrive->SetMotorInverted(true);
	m_pRightDrive2->SetInverted(false);
	m_pRightDrive3->SetInverted(true);
	// Set the second and third motors on each drive to follow the first motor.
	m_pLeftDrive2->Follow(*m_pLeftDrive->GetMotorPointer());
	m_pLeftDrive3->Follow(*m_pLeftDrive->GetMotorPointer());
	m_pRightDrive2->Follow(*m_pRightDrive->GetMotorPointer());
	m_pRightDrive3->Follow(*m_pRightDrive->GetMotorPointer());
	// Set the encoder's sensor phase.
	m_pLeftDrive->SetSensorInverted(true);
	m_pRightDrive->SetSensorInverted(true);
	// Set the PID Terms.
///	m_pLeftDrive->SetPIDValues(dDriveProportional, dDriveIntegral, dDriveDerivative);
///	m_pRightDrive->SetPIDValues(dDriveProportional, dDriveIntegral, dDriveDerivative);
	// Set the I Zone.
///	m_pLeftDrive->SetAccumIZone(dDriveAccumIZone);
///	m_pRightDrive->SetAccumIZone(dDriveAccumIZone);
	// Set the soft limits.
///	m_pLeftDrive->SetSoftLimits(dDriveMinDistance, dDriveMaxDistance);
///	m_pRightDrive->SetSoftLimits(dDriveMinDistance, dDriveMaxDistance);
	// Set the position tolerance.
///	m_pLeftDrive->SetTolerance(dDriveTolerance);
///	m_pRightDrive->SetTolerance(dDriveTolerance);
	// Set the maximum forward and reverse percent output.
///	m_pLeftDrive->SetPeakOutputPercent(dDriveMaxSpeed, dDriveMinSpeed);
///	m_pRightDrive->SetPeakOutputPercent(dDriveMaxSpeed, dDriveMinSpeed);
	// Set the nominal forward and reverse percent output.
	m_pLeftDrive->SetNominalOutputVoltage(0.000, 0.000);
	m_pRightDrive->SetNominalOutputVoltage(0.000, 0.000);
	// Set the open loop ramp rate.
///	m_pLeftDrive->SetOpenLoopRampRate(dDriveOpenLoopRampRate);
///	m_pRightDrive->SetOpenLoopRampRate(dDriveOpenLoopRampRate);
	// Set the closed loop ramp rate.
///	m_pLeftDrive->SetClosedLoopRampRate(dDriveClosedLoopRampRate);
///	m_pRightDrive->SetClosedLoopRampRate(dDriveClosedLoopRampRate);
	// Set motor neutral mode to brake.
	m_pLeftDrive->GetMotorPointer()->SetNeutralMode(NeutralMode::Brake);
	m_pLeftDrive2->SetNeutralMode(NeutralMode::Brake);
	m_pLeftDrive3->SetNeutralMode(NeutralMode::Brake);
	m_pRightDrive->GetMotorPointer()->SetNeutralMode(NeutralMode::Brake);
	m_pRightDrive2->SetNeutralMode(NeutralMode::Brake);
	m_pRightDrive3->SetNeutralMode(NeutralMode::Brake);
	// Stop the motor.
	m_pLeftDrive->Stop();
	m_pRightDrive->Stop();
	// Reset encoder counts to zero.
	m_pLeftDrive->ResetEncoderPosition();
	m_pRightDrive->ResetEncoderPosition();
	// Clear any sticky faults.
	m_pLeftDrive->ClearStickyFaults();
	m_pRightDrive->ClearStickyFaults();

	// Shift to high gear.
	m_pDriveSolenoid->Set(false);
}

Drivetrain::~Drivetrain()
{
	delete m_pLeftDrive;
	delete m_pLeftDrive2;
	delete m_pLeftDrive3;
	delete m_pRightDrive;
	delete m_pRightDrive2;
	delete m_pRightDrive3;
	delete m_pDriveSolenoid;
	delete m_pRobotDrive;

	m_pLeftDrive      = nullptr;
	m_pLeftDrive2     = nullptr;
	m_pLeftDrive3     = nullptr;
	m_pRightDrive     = nullptr;
	m_pRightDrive2    = nullptr;
	m_pRightDrive3    = nullptr;
	m_pDriveSolenoid  = nullptr;
	m_pRobotDrive     = nullptr;
}

/******************************************************************************
	InitDefaultCommand:	Starts the default command ArcadeDrive.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Drivetrain::InitDefaultCommand()
{
	SetDefaultCommand(new ArcadeDrive());
}

/******************************************************************************
	Drive:			Begins TankDrive.

	Arguments:		Speeds dLeft, dRight

	Returns:		Nothing
******************************************************************************/
void Drivetrain::Drive(double dSpeed, double dRotation)
{
	m_pRobotDrive->CurvatureDrive(dSpeed, dRotation, m_pDriveSolenoid->Get());
}

void Drivetrain::ManualDrive(double dLeft, double dRight)
{
	m_pLeftDrive->GetMotorPointer()->Set(dLeft);
	m_pRightDrive->GetMotorPointer()->Set(dRight);
}
/******************************************************************************
	Shift:			Toggles the Drivetrain between Low and High gear.
					Used on controller during Teleop.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Drivetrain::Shift()
{
	m_pDriveSolenoid->Set(!m_pDriveSolenoid->Get());
}

/******************************************************************************
	Shift:			Sets the Drivetrain to Low or High gear.

	Arguments:		bHighGear

	Returns:		Nothing
******************************************************************************/
void Drivetrain::Shift(bool bHighGear)
{
	m_pDriveSolenoid->Set(bHighGear);
}

int Drivetrain::GetLeftEncoderCount()
{
	return m_pLeftDrive->GetRawEncoderCounts();
}

int Drivetrain::GetRightEncoderCount()
{
	return m_pLeftDrive->GetRawEncoderCounts();
}

double Drivetrain::GetAngle()
{
	return m_pGyro->GetAngle();
}
///////////////////////////////////////////////////////////////////////////////
