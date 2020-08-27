// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/InteractiveProcess.h"
#include "WindowsCommander.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutHandle, FString, text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputHandle, FString, text);

UCLASS()
class SCREENCAPTURE_API AWindowsCommander : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindowsCommander();

	// launch cmd exe 
	UFUNCTION(BlueprintCallable, Category = "Screen Recorder")
		void Launch(FString ExePath, FString ExeParam, bool bShouldHidden);

	// close process
	UFUNCTION(BlueprintCallable, Category = "Screen Recorder")
		void CloseProcess();

	// get the addition asset path
	UFUNCTION(BlueprintPure)
		FString GetAddtionAssetPath();

	// get the video path
	UFUNCTION(BlueprintPure)
		FString GetVideoPath();

	// OutHandle Delegate
	UPROPERTY(BlueprintAssignable, Category = "Screen Recorder")
		FOutHandle OutEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void* ReadPipeParent = nullptr;
	void* WritePipeChild = nullptr;
	void* ReadPipeChild = nullptr;
	void* WritePipeParent = nullptr;
	FProcHandle handle;

	FInteractiveProcess* proc;

private:
	// comand input
	void InputCmd(FString text);
	bool bLaunchProcess = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
