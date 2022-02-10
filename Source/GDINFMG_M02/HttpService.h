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
struct FArtifactData
{
		GENERATED_BODY()
		UPROPERTY() FString artif_description;
		UPROPERTY() FString artifactName;
		UPROPERTY() int artifactRarity;

		FArtifactData() {}
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

USTRUCT()
struct FRequest_CharacterAttributes
{
		GENERATED_BODY()
		UPROPERTY() int userMainID;
		UPROPERTY() int ownedCharacterID;

		FRequest_CharacterAttributes() {}
};

USTRUCT()
struct FResponse_CharacterAttributes
{
		GENERATED_BODY()
		UPROPERTY() FString character_name;
		UPROPERTY() int friendshipLevel;
		UPROPERTY() int refineRank;
		UPROPERTY() FString weap_description;
		UPROPERTY() int weaponLevel;
		UPROPERTY() FString weaponName;
		UPROPERTY() int weaponRarity;
		UPROPERTY() FArtifactData artifact1Data;
		UPROPERTY() FArtifactData artifact2Data;
		UPROPERTY() FArtifactData artifact3Data;
		UPROPERTY() FArtifactData artifact4Data;
		UPROPERTY() FArtifactData artifact5Data;

	FResponse_CharacterAttributes() {}
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

USTRUCT()
struct FResponse_CharacterAttributesHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_CharacterAttributes Response_CharacterAttributes;

	FResponse_CharacterAttributesHolder() {}
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

	//CHARACTER ATTRIBUTES REQUEST RESPONSE
	void getCharacterAttributes(FRequest_CharacterAttributes characterAttributesCredentials);
	void characterAttributesResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

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

	//FOR DISPLAY - CHARACTER ATTRIBUTES
	FString character_name;
	FString friendshipLevel;
	FString refineRank;
	FString weap_description;
	FString weaponLevel;
	FString weaponName;
	FString weaponRarity;
	FString artif_description1;
	FString artifactName1;
	FString artifactRarity1;
	FString artif_description2;
	FString artifactName2;
	FString artifactRarity2;
	FString artif_description3;
	FString artifactName3;
	FString artifactRarity3;
	FString artif_description4;
	FString artifactName4;
	FString artifactRarity4;
	FString artif_description5;
	FString artifactName5;
	FString artifactRarity5;
};
