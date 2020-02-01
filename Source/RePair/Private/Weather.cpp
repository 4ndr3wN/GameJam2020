// Fill out your copyright notice in the Description page of Project Settings.


#include "Weather.h"
#include "Engine/Engine.h"
#include <algorithm>

// Sets default values
AWeather::AWeather(const class FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;
    Http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AWeather::BeginPlay()
{
    Super::BeginPlay();
}


void AWeather::HttpCall(FString a_Path, FString& a_CityName, FString& a_CityWeather )
{
    TSharedRef<IHttpRequest> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AWeather::OnResponseReceived);
    //This is the url on which to process the request
    Request->SetURL(a_Path);
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    if (!Request->ProcessRequest())
    {
        GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Yellow, "Http not processed");
    }
    else 
    {
        a_CityName = m_CityName;
        a_CityWeather = m_CityWeather;
    }
}

void AWeather::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    //Create a pointer to hold the json serialized data
    TSharedPtr<FJsonObject> JsonObject;

    //Create a reader pointer to read the json data
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    //Deserialize the json data given Reader and the actual object to deserialize
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        //Get the value of the json object by field name
        TArray<TSharedPtr<FJsonValue>> recievedArray = JsonObject->GetArrayField("weather");
        for (int i_Value = 0; i_Value < recievedArray.Num(); i_Value++)
        {
            TSharedPtr<FJsonObject> obj = recievedArray[i_Value]->AsObject();
            FString str = ""; obj->GetStringField(TEXT("main"));
            str = obj->GetStringField(TEXT("main"));
            if (str != "") 
            {
                m_CityWeather = str;
                break;
            }
        }

        FString recievedName = "";
        recievedName = JsonObject->GetStringField("name");
        if (recievedName != "")
        {
            m_CityName = recievedName;
        }
        //Output it to the engine
        GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, m_CityName);
        GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, m_CityWeather);
    }

}
// Called every frame
void AWeather::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

