// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "Weather.generated.h"

UCLASS()
class REPAIR_API AWeather : public AActor
{
	GENERATED_BODY()
	
public:	
    FHttpModule* Http;
    UPROPERTY()
    FString m_CityWeather;
    UPROPERTY()
    FString m_CityName;
    //
    //
    //

    UFUNCTION(BlueprintCallable)
    void HttpCall(const FString a_Path, FString& a_CityName, FString& a_CityWeather);

    // Sets default values for this actor's properties
    AWeather(const class FObjectInitializer& ObjectInitializer);

	// Sets default values for this actor's properties
	AWeather();

protected:

    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};