// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherActor.h"
#include "Engine/Engine.h"
#include <algorithm>

// Sets default values
AWeatherActor::AWeatherActor(const class FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	Http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AWeatherActor::BeginPlay()
{
	HttpCall("https://api.openweathermap.org/data/2.5/weather?q=Breda,nl&appid=2a6f32678e2ae10af489ffa238be4187");
	Super::BeginPlay();
	
}


void AWeatherActor::HttpCall(FString a_Path)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AWeatherActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL(a_Path);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	if (!Request->ProcessRequest())
	{
		GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Yellow, "Http not processed");
	}
}

void AWeatherActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		int32 recievedInt = JsonObject->GetIntegerField("customInt");
		TArray<TSharedPtr<FJsonValue>> recievedArray = JsonObject->GetArrayField("weather");
		for (int i_Value = 0; i_Value < recievedArray.Num(); i_Value++)
		{
			TSharedPtr<FJsonObject> obj = recievedArray[i_Value]->AsObject();
			FString str = ""; obj->GetStringField(TEXT("main"));
			str = obj->GetStringField(TEXT("main"));
			if()
		}

		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	}

}
// Called every frame
void AWeatherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

