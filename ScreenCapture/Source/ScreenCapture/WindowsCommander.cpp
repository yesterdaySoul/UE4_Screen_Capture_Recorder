// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowsCommander.h"
#include "Misc/Paths.h"
#include "Misc/InteractiveProcess.h"

// Sets default values
AWindowsCommander::AWindowsCommander()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWindowsCommander::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWindowsCommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWindowsCommander::Launch(FString ExePath, FString ExeParam, bool bShouldHidden)
{
	proc = new FInteractiveProcess(ExePath, ExeParam, bShouldHidden, true);
	proc->OnOutput().BindLambda([=](FString tex) {
		if (OutEvent.IsBound())
		{
			OutEvent.Broadcast(tex);
		}
	});
	proc->Launch();
	bLaunchProcess = true;
}

void AWindowsCommander::CloseProcess()
{
	if (!bLaunchProcess) return;
	InputCmd("q");
	bLaunchProcess = false;
}

void AWindowsCommander::InputCmd(FString text)
{
	if (proc != nullptr)
	{
		proc->SendWhenReady(text);
	}
}

FString AWindowsCommander::GetAddtionAssetPath()
{
	return FPaths::ProjectDir() + FString("AdditionAsset");
}

FString AWindowsCommander::GetVideoPath()
{
	return FPaths::ProjectDir() + FString("Video");
}
