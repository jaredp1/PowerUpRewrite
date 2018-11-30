/******************************************************************************
	Description:	2018 PowerUp Robot Arm Subsystem.

	Subsystem:		ArmPosition

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "../IOMap.h"
#include "CANPosition.h"
#include "Subsystems/ArmPosition.h"
#include "Commands/ArmPosition/HomeArm.h"
///////////////////////////////////////////////////////////////////////////////


ArmPosition::ArmPosition() : Subsystem("ArmPosition")
{
	m_pBrakeSolenoid = new Solenoid(kBrakeSolenoidChannel);
	m_pArmMotor   	 = new CCANPosition(kArmPositionMotor);
	// Set the initial setpoint. Typically the arm starts at about 90 degrees. This makes
	// it where the arm is at least functional without homing.
	m_dArmSetpoint = 90.0;

	// Set the pulses per rev.
	m_pArmMotor->SetPulsesPerRev(1024);
	// Set the Revs/Unit.
	m_pArmMotor->SetRevsPerUnit(dArmPositionEncoderRevsPerDegree);
	// Invert the motor output.
	m_pArmMotor->SetMotorInverted(true);
	// Set the encoder's sensor phase.
	m_pArmMotor->SetSensorInverted(true);
	// Set the PID Terms.
	m_pArmMotor->SetPIDValues(dArmPositionProportional, dArmPositionIntegral, dArmPositionDerivative);
	// Set the I Zone.
	m_pArmMotor->SetAccumIZone(dArmPositionAccumIZone);
	// Set the soft limits.
	m_pArmMotor->SetSoftLimits(dArmPositionMinDistance, dArmPositionMaxDistance);
	// Set the position tolerance.
	m_pArmMotor->SetTolerance(dArmPositionTolerance);
	// Set the maximum forward and reverse percent output.
	m_pArmMotor->SetPeakOutputPercent(dArmPositionMaxSpeed, dArmPositionMinSpeed);
	// Set the nominal forward and reverse percent output.
	m_pArmMotor->SetNominalOutputVoltage(0.000, 0.000);
	// Set the open loop ramp rate.
	m_pArmMotor->SetOpenLoopRampRate(dArmPositionOpenLoopRampRate);
	// Set the closed loop ramp rate.
	m_pArmMotor->SetClosedLoopRampRate(dArmPositionClosedLoopRampRate);
	// Set motor neutral mode to brake.
	m_pArmMotor->SetMotorNeutralMode(NeutralMode::Brake);
	// Set limit switches to Normally Closed
	m_pArmMotor->ConfigLimitSwitches(false, false);
	// Set the homing speeds in Percent Output.
	m_pArmMotor->SetHomeSpeeds(dArmPositionHomingSpeedForward, dArmPositionHomingSpeedReverse);
	// Set the homing timeout.
	m_pArmMotor->SetMaxHomingTime(dArmPositionMaxHomingTimeout);
	// Set the finding timeout.
	m_pArmMotor->SetMaxFindingTime(dArmPositionMaxFindingTimeout);
	// Stop the motor.
	m_pArmMotor->Stop();
	// Reset encoder counts to zero.
	m_pArmMotor->ResetEncoderPosition();
	// Clear any sticky faults.
	m_pArmMotor->ClearStickyFaults();
}

ArmPosition::~ArmPosition()
{
	delete m_pArmMotor;
	delete m_pBrakeSolenoid;

	m_pArmMotor			= nullptr;
	m_pBrakeSolenoid	= nullptr;
}

void ArmPosition::Tick()
{
	// Call the CANPosition ticks.
	m_pArmMotor->Tick();

	// Get ArmPosition State.
	State nArmState = m_pArmMotor->GetState();

	// Engage/Disengage brake based on ArmPosition state.
	if ((nArmState == eHomingReverse) ||
		(nArmState == eHomingForward) ||
		(nArmState == eManualForward) ||
		(nArmState == eManualReverse) ||
		(nArmState == eFinding))
	{
		// Disengage brake.
		m_pBrakeSolenoid->Set(true);
	}
	else
	{
		// Engage brake.
		m_pBrakeSolenoid->Set(false);
	}

	// Check to see if the motor has reached setpoint.
	if ((nArmState == eFinding) && m_pArmMotor->IsReady())
	{
		// Stop the motor.
		m_pArmMotor->Stop();
	}

	// Put arm information on SmartDashboard for Auto/Teleop.
	SmartDashboard::PutNumber("Arm Actual", m_pArmMotor->GetActual());

}

/******************************************************************************
	InitDefaultCommand:	Starts the default command to Home the arm.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void ArmPosition::InitDefaultCommand()
{

}

/******************************************************************************
	SetSetpoint:	Moves to specified setpoint.

	Arguments:		dSetpoint

	Returns:		Nothing
******************************************************************************/
void ArmPosition::SetSetpoint(double dSetpoint)
{
	m_dArmSetpoint = dSetpoint;
	m_pArmMotor->SetSetpoint(m_dArmSetpoint);
	m_pArmMotor->SetState(eFinding);
}

/******************************************************************************
	GetSetpoint:	Returns the current setpoint.

	Arguments:		None

	Returns:		double Setpoint
******************************************************************************/
double ArmPosition::GetSetpoint()
{
	return m_dArmSetpoint;
}

/******************************************************************************
	GetActual:		Returns the current position.

	Arguments:		None

	Returns:		double Actual
******************************************************************************/
double ArmPosition::GetActual()
{
	return m_pArmMotor->GetActual();
}

/******************************************************************************
	IsReady:		Returns whether or not the Arm is ready.

	Arguments:		None

	Returns:		bool IsReady
******************************************************************************/
bool ArmPosition::IsReady()
{
	return m_pArmMotor->IsReady();
}

/******************************************************************************
	ArmHome:		Sets the state of the Arm to homing.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void ArmPosition::ArmHome()
{
	m_pArmMotor->SetState(eHomingReverse);
}

/******************************************************************************
	ArmJog:			Sets the state of the Arm to move in a direction.

	Arguments:		bool bUpDirection

	Returns:		Nothing
******************************************************************************/
void ArmPosition::ArmJog(bool bUpDirection)
{
	if (m_pArmMotor->GetState() == eIdle)
	{
		m_pArmMotor->SetState(bUpDirection ? eManualForward : eManualReverse);
	}
}
///////////////////////////////////////////////////////////////////////////////
