// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSL_Window.h"
#include "CableComponent.h"
#include "GameFramework/Character.h"
#include "BaseChr.generated.h"

UCLASS()
class ALEPH_API ABaseChr : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseChr();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Movement")
		FName MoveForwardBindName = "move_forward";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Movement")
		FName MoveSideBindName = "move_side";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Camera")
		FName VerticalLookBindName = "look_vertical";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Camera")
		FName VerticalLookOnControllerBindName = "LookRate";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Camera")
		FName HorizontalLookBindName = "look_horizontal";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Camera")
		FName HorizontalLookOnControllerBindName = "TurnRate";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Movement")
		FName JumpBindName = "Jump";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Movement")
		FName CrouchBindName = "Crouch";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bindings|Abilities")
		FName GrappleBindName = "Grapple";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Sensitivity")
		float MouseSensitivity = 0.25f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Sensitivity")
		float SensitivityZ = 25.0f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Sensitivity")
		float SensitivityY = 45.0f;

	UFUNCTION(BlueprintPure, Category = "Sensitivity")
		float GetMouseSens() const
		{
			UCSL_Window::PrintToConsole("Character", "Warning", FString::Printf(TEXT("Sensitivity: %f"), MouseSensitivity));
			return MouseSensitivity;	
		}
	UFUNCTION(BlueprintPure, Category = "Sensitivity")
		float GetSensZ() const
		{
			UCSL_Window::PrintToConsole("Character", "Warning", FString::Printf(TEXT("Z Sensitivity: %f"), SensitivityZ));
			return SensitivityZ;
		}
	UFUNCTION(BlueprintPure, Category = "Sensitivity")
		float GetSensY() const
		{
			UCSL_Window::PrintToConsole("Character", "Warning", FString::Printf(TEXT("X Sensitivity: %f"), SensitivityY));
			return SensitivityY;
		}

public:
	bool IsMoving();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Speed")
		float BaseWalkSpeed = 250.0f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Speed")
		float BaseWalkSpeedMultiplier = 2.2f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Speed")
		float BaseCrouchSpeed = 75.0f;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveSide(float Value);
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void VerticalLook(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void VerticalLookOnController(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void HorizontalLook(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void HorizontalLookOnController(float Axis);
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character Movement|Dash")
		int DashMode; // 0 = walking, 1 = sprinting, 2 = dashing
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Movement|Dash")
		float DashAxis = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Movement|Dash")
		bool IsWalkingV = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Movement|Dash")
		bool IsWalkingH = false;
	
	bool bDevWalk = false;
	UFUNCTION(BlueprintCallable, Exec, Category = "Cheats")
		void DevCam(int Mode); // 0 = disable, 1 = enable
	UFUNCTION(BlueprintCallable, Exec, Category = "Cheats")
		void AllowCheats(int Mode); // 0 = disable, 1 = enable

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Abilities")
		bool bCanUseHook = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Abilities")
		bool bCanWallrun = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Abilities")
		bool bCanPull = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Abilities")
		bool bCanDash = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Actions")
		bool bCanGrab = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Actions")
		bool bCanUseFlash = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences")
		bool bCanUseCheats = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences")
		bool bUseSmoothCrouch = true;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status|Suppressions")
		bool bIsHookSuppressed;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsCrouching = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsGrabbing = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsPulling = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsGrappling = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsOnWall = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsFlashOn = false;


protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character: Movement - Grapple")
		FVector GrappleLocation;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character: Movement - Grapple")
		float GrappleDistance = 3072.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Trace")
		bool Trace(float Distance);
	UFUNCTION(BlueprintCallable, Category = "Abilities|GrapplingHook")
		void Grapple();
	UFUNCTION(BlueprintCallable, Category = "Abilities|GrapplingHook")
		void GrappleTick();
	UFUNCTION(BlueprintCallable, Category = "Abilities|GrapplingHook")
		void GrappleStop();
	UFUNCTION(BlueprintCallable, Category = "Abilities|GrapplingHook")
		void SetGrappleVisibility(bool Visibility);

	UFUNCTION(BlueprintCallable, Category = "Abilities|Sprint/Dash")
		void BeginSprint();
	UFUNCTION(BlueprintCallable, Category = "Abilities|Sprint/Dash")
		void StopSprint();
	UFUNCTION(BlueprintCallable, Category = "Abilities|Sprint/Dash")
		void BeginDash(float AxisV, float AxisH, int Cost);
	UFUNCTION(BlueprintCallable, Category = "Abilities|Sprint/Dash")
		void DashVertically(float AxisV, int Value);
	UFUNCTION(BlueprintCallable, Category = "Abilities|Sprint/Dash")
		void DashHorizontally(float AxisH, int Value);
};
