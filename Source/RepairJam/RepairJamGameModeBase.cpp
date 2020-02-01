// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairJamGameModeBase.h"

FRotator ARepairJamGameModeBase::SLerp(FRotator A, FRotator B, float alpha)
{
	return FQuat::Slerp(A.Quaternion(), B.Quaternion(), alpha).Rotator();
}
