// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "WeatherActor.generated.h"

UCLASS()
class REPAIR_API AWeatherActor : public AActor
{
	GENERATED_BODY()	
public:	

    FHttpModule* Http;
	//
	//
	//

	UFUNCTION()
	void HttpCall();
	
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	// Sets default values for this actor's properties
	AWeatherActor(const class FObjectInitializer& ObjectInitializer);
	AWeatherActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
