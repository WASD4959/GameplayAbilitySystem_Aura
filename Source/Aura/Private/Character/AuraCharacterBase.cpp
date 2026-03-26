// Copyright putuitou


#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("weapon");
	weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}