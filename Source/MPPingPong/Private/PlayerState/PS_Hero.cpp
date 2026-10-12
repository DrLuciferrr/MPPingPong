// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PS_Hero.h"
#include <Net/UnrealNetwork.h>

void APS_Hero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APS_Hero, Team);
}