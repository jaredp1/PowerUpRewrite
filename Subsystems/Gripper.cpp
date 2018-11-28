/******************************************************************************
	Description:	2018 PowerUp Robot Gripper Subsystem.

	Subsystem:		Gripper

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Subsystems/Gripper.h"
#include "../IOMap.h"
///////////////////////////////////////////////////////////////////////////////


Gripper::Gripper() : Subsystem("Gripper")
{
	m_pCubeSensor    = new DigitalInput(kCubeSensorPort);
	m_pLeftSolenoid  = new Solenoid(kLeftSolenoidChannel);
	m_pRightSolenoid = new Solenoid(kRightSolenoidChannel);
	m_pEjectSolenoid = new Solenoid(kPlungerSolenoidChannel);
	m_pPlungerVacuum = new Solenoid(kPlungerVacuumChannel);
	m_pTimer		 = new Timer();
	m_pIntakeMotors  = new WPI_TalonSRX(kLeftIntakeMotor);
	m_pRightIntake   = new WPI_TalonSRX(kRightIntakeMotor);
	m_pRightIntake->Follow(*m_pIntakeMotors);
}

Gripper::~Gripper()
{
	delete m_pCubeSensor;
	delete m_pLeftSolenoid;
	delete m_pRightSolenoid;
	delete m_pEjectSolenoid;
	delete m_pPlungerVacuum;
	delete m_pTimer;
	delete m_pIntakeMotors;
	delete m_pRightIntake;

	m_pCubeSensor     = nullptr;
	m_pLeftSolenoid   = nullptr;
	m_pRightSolenoid  = nullptr;
	m_pEjectSolenoid  = nullptr;
	m_pPlungerVacuum  = nullptr;
	m_pTimer		  = nullptr;
	m_pIntakeMotors   = nullptr;
	m_pRightIntake    = nullptr;
}
void Gripper::OpenIntake()
{
	m_pLeftSolenoid->Set(false);
	m_pRightSolenoid->Set(false);
}

/******************************************************************************
	StartIntake:	Opens the claw and starts intake motors.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Gripper::StartIntake()
{
	m_pLeftSolenoid->Set(true);
	m_pRightSolenoid->Set(true);
	m_pIntakeMotors->Set(-1.0);
}

/******************************************************************************
	Close:			Closes the claw using the Solenoids.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Gripper::Close()
{
	m_pLeftSolenoid->Set(false);
	m_pRightSolenoid->Set(false);
}

/******************************************************************************
	Stop:			Closes the claw and stops the intake motors.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Gripper::Stop()
{
	Close();
	m_pIntakeMotors->Set(0.0);
}

void Gripper::Eject(bool bActivate)
{
	m_pEjectSolenoid->Set(bActivate);
}

void Gripper::Vacuum(bool bActivate)
{
	m_pPlungerVacuum->Set(bActivate);
}

void Gripper::NormalEject()
{
	m_pIntakeMotors->Set(0.6);
}
///////////////////////////////////////////////////////////////////////////////
