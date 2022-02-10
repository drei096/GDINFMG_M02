// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include <vector>
#include "HttpService.generated.h"



USTRUCT()
struct FOwnedCharacterData
{
		GENERATED_BODY()
		UPROPERTY() FString constellationLevel;
		UPROPERTY() FString level;
		UPROPERTY() FString name;
		UPROPERTY() FString rarity;

		FOwnedCharacterData() {}
};

USTRUCT()
struct FRequest_Summary
{
		GENERATED_BODY()
        UPROPERTY() int userMainID;

		FRequest_Summary() {}
};

USTRUCT()
struct FResponse_Summary
{
		GENERATED_BODY()
		UPROPERTY() int ACuli;
		UPROPERTY() int CChestOpen;
		UPROPERTY() int DomUnlock;
		UPROPERTY() int EChestOpen;
		UPROPERTY() int ECuli;
		UPROPERTY() int GCuli;
		UPROPERTY() int LChestOpen;
		UPROPERTY() int PChestOpen;
		UPROPERTY() FString SAbyss;
		UPROPERTY() int achievements;
		UPROPERTY() int characters;
		UPROPERTY() int daysActive;
		UPROPERTY() int noRemarkable;
		UPROPERTY() int wayPUnlock;

		FResponse_Summary() {}
};

USTRUCT()
struct FRequest_WorldExplo
{
		GENERATED_BODY()
		UPROPERTY() int userMainID;
		UPROPERTY() FString region;

		FRequest_WorldExplo() {}
};

USTRUCT()
struct FResponse_WorldExplo
{
		GENERATED_BODY()
		UPROPERTY() int explorationProgress;
		UPROPERTY() int frostTreeLevel;
		UPROPERTY() int reputationLevel;
		UPROPERTY() int sakuraFavorLevel;


		FResponse_WorldExplo() {}
};

USTRUCT()
struct FRequest_SereniteaPot
{
	GENERATED_BODY()
		UPROPERTY() int userMainID;

	FRequest_SereniteaPot() {}
};

USTRUCT()
struct FResponse_SereniteaPot
{
		GENERATED_BODY()
		UPROPERTY() int FurnishingsObtained;
		UPROPERTY() int highestAdeptalEnergy;
		UPROPERTY() int trustRank;
		UPROPERTY() int visitorCount;


	FResponse_SereniteaPot() {}
};

USTRUCT()
struct FRequest_CharacterCollection
{
	GENERATED_BODY()
		UPROPERTY() int userMainID;

	FRequest_CharacterCollection() {}
};

USTRUCT()
struct FResponse_CharacterCollection
{
		GENERATED_BODY()
		UPROPERTY() int constellationLevel;
		UPROPERTY() int level;
		UPROPERTY() FString name;
		UPROPERTY() int rarity;

	FResponse_CharacterCollection() {}
};

/****************RESPONSE HOLDERS*********************/
USTRUCT()
struct FResponse_SummaryHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_Summary Response_Summary;

	FResponse_SummaryHolder() {}
};

USTRUCT()
struct FResponse_WorldExploHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_WorldExplo Response_WorldExploration;

	FResponse_WorldExploHolder() {}
};

USTRUCT()
struct FResponse_SereniteaPotHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_SereniteaPot Response_SereniteaPot;

	FResponse_SereniteaPotHolder() {}
};

USTRUCT()
struct FResponse_CharacterCollectionHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_CharacterCollection Response_CharacterCollection;

	FResponse_CharacterCollectionHolder() {}
};
/****************RESPONSE HOLDERS*********************/


UCLASS(Blueprintable, hideCategories = (Rendering, Replication, Input, Actor, "Actor Tick"))
class GDINFMG_M02_API AHttpService : public AActor
{
	GENERATED_BODY()

private:
	FHttpModule* Http;
	FString ApiBaseUrl = "http://localhost:8800/api/";

	FString AuthorizationHeader = TEXT("Authorization");
	FString AuthorizationHash = TEXT("asdfasdf");
	void SetAuthorizationHash(FString Hash);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PostRequest(FString Subroute, FString ContentJsonString);
	void Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);

public:
	AHttpService();
	virtual void BeginPlay() override;

	void Login(FRequest_Summary LoginCredentials);

	//SUMMARY REQUEST RESPONSE
	void getSummary(FRequest_Summary summaryCredentials);
	void SummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//WORLD EXPLO REQUEST RESPONSE
	void getWorldExploration(FRequest_WorldExplo worldExploCredentials);
	void worldExplorationResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SERENITEA POT REQUEST RESPONSE
	void getSereniteaPot(FRequest_SereniteaPot sereniteaPotCredentials);
	void sereniteaPotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//CHARACTER COLLECTION REQUEST RESPONSE
	void getCharacterCollection(FRequest_CharacterCollection characterCollectionCredentials);
	void characterCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


public:
	// FOR DISPLAY - SUMMARY
	FString ACuli;
	FString CChestOpen;
	FString DomUnlock;
	FString EChestOpen;
	FString ECuli;
	FString GCuli;
	FString LChestOpen;
	FString PChestOpen;
	FString SAbyss;
	FString achievements;
	FString characters;
	FString daysActive;
	FString noRemarkable;
	FString wayPUnlock;

	// FOR DISPLAY - WORLD EXPLORATION
	FString explorationProgress;
	FString frostTreeLevel;
	FString reputationLevel;
	FString sakuraFavorLevel;

	//FOR DISPLAY - SERENITEA POT
	FString FurnishingsObtained;
	FString highestAdeptalEnergy;
	FString trustRank;
	FString visitorCount;

	//FOR DISPLAY - CHARACTER COLLECTION
	std::vector<FOwnedCharacterData> ownedCharacterList;
};
