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
		UPROPERTY() FString artifactRarity;

		FArtifactData() {}
};

USTRUCT()
struct FChallengeData
{
		GENERATED_BODY()
		UPROPERTY() FString stars;
		UPROPERTY() FString char1H1;
		UPROPERTY() FString character_name1H1;
		UPROPERTY() FString level1H1;
		UPROPERTY() FString char2H1;
		UPROPERTY() FString character_name2H1;
		UPROPERTY() FString level2H1;
		UPROPERTY() FString char3H1;
		UPROPERTY() FString character_name3H1;
		UPROPERTY() FString level3H1;
		UPROPERTY() FString char4H1;
		UPROPERTY() FString character_name4H1;
		UPROPERTY() FString level4H1;
		UPROPERTY() FString char1H2;
		UPROPERTY() FString character_name1H2;
		UPROPERTY() FString level1H2;
		UPROPERTY() FString char2H2;
		UPROPERTY() FString character_name2H2;
		UPROPERTY() FString level2H2;
		UPROPERTY() FString char3H2;
		UPROPERTY() FString character_name3H2;
		UPROPERTY() FString level3H2;
		UPROPERTY() FString char4H2;
		UPROPERTY() FString character_name4H2;
		UPROPERTY() FString level4H2;

		FChallengeData() {}
};

USTRUCT()
struct FRequest_Login
{
		GENERATED_BODY()
		UPROPERTY() FString username; //username or email
		UPROPERTY() FString password;

		FRequest_Login() {}
};

/*
-----------------------Still not sure what login response should be
USTRUCT()
struct FResponse_Login
{
		GENERATED_BODY()
		UPROPERTY() int userMainID;

		FResponse_Login() {}
};
*/

USTRUCT()
struct FRequest_Server // SWITCH ACCOUNTS
{
		GENERATED_BODY()
		UPROPERTY() int serverID;
		UPROPERTY() int accountID;

		FRequest_Server() {}
};

USTRUCT()
struct FResponse_Server // SWITCH ACCOUNTS
{
		GENERATED_BODY()
		UPROPERTY() int userMainID;
		UPROPERTY() int nickname;

		FResponse_Server() {}
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

USTRUCT()
struct FRequest_SpiralAbyssSummary
{
	GENERATED_BODY()
		UPROPERTY() int userMainID;

	FRequest_SpiralAbyssSummary() {}
};

USTRUCT()
struct FResponse_SpiralAbyssSummary
{
		GENERATED_BODY()
		UPROPERTY() int abyss_ID;
		UPROPERTY() int battlesFought;
		UPROPERTY() int deepestDesc;
		UPROPERTY() int elemBurstUsed;
		UPROPERTY() int elemSkillsUsed;
		UPROPERTY() int mostDefeats;
		UPROPERTY() int mostDMGTaken;
		UPROPERTY() int sAbyssStars;
		UPROPERTY() int strongSingleStrike;


	FResponse_SpiralAbyssSummary() {}
};

USTRUCT()
struct FRequest_SpiralAbyssChallenge
{
	GENERATED_BODY()
		UPROPERTY() int abyssID;
		UPROPERTY() int floor;
		UPROPERTY() int chamber;

	FRequest_SpiralAbyssChallenge() {}
};

USTRUCT()
struct FResponse_SpiralAbyssChallenge
{
	GENERATED_BODY()
		UPROPERTY() int stars;
		UPROPERTY() int char1H1;
		UPROPERTY() FString character_name1H1;
		UPROPERTY() int level1H1;
		UPROPERTY() int char2H1;
		UPROPERTY() FString character_name2H1;
		UPROPERTY() int level2H1;
		UPROPERTY() int char3H1;
		UPROPERTY() FString character_name3H1;
		UPROPERTY() int level3H1;
		UPROPERTY() int char4H1;
		UPROPERTY() FString character_name4H1;
		UPROPERTY() int level4H1;
		UPROPERTY() int char1H2;
		UPROPERTY() FString character_name1H2;
		UPROPERTY() int level1H2;
		UPROPERTY() int char2H2;
		UPROPERTY() FString character_name2H2;
		UPROPERTY() int level2H2;
		UPROPERTY() int char3H2;
		UPROPERTY() FString character_name3H2;
		UPROPERTY() int level3H2;
		UPROPERTY() int char4H2;
		UPROPERTY() FString character_name4H2;
		UPROPERTY() int level4H2;


	FResponse_SpiralAbyssChallenge() {}
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

USTRUCT()
struct FResponse_SpiralAbyssSummaryHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_SpiralAbyssSummary Response_SpiralAbyssSummary;

	FResponse_SpiralAbyssSummaryHolder() {}
};

USTRUCT()
struct FResponse_SpiralAbyssChallengeHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_SpiralAbyssChallenge Response_SpiralAbyssChallenge;

	FResponse_SpiralAbyssChallengeHolder() {}
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

	//SERVER LOGIN
	void Login(FRequest_Login LoginCredentials);

	//SERVER REQUEST RESPONSE
	void getServer(FRequest_Server serverCredentials);
	void ServerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

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

	//SPIRAL ABYSS SUMMARY REQUEST RESPONSE
	void getSpiralAbyssSummary(FRequest_SpiralAbyssSummary spiralAbyssSummaryCredentials);
	void spiralAbyssSummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SPIRAL ABYSS CHALLENGE REQUEST RESPONSE
	void getSpiralAbyssChallenge(FRequest_SpiralAbyssChallenge spiralAbyssChallengeCredentials);
	void spiralAbyssChallengeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	// FOR DISPLAY - SERVER
	FString userMainID;
	FString nickname;

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
	std::vector<FArtifactData> ownedArtifactList;

	/*
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
	*/

	//FOR DISPLAY - SPIRAL ABYSS SUMMARY
	FString abyss_ID;
	FString battlesFought;
	FString deepestDesc;
	FString elemBurstUsed;
	FString elemSkillsUsed;
	FString mostDefeats;
	FString mostDMGTaken;
	FString sAbyssStars;
	FString strongSingleStrike;

	//FOR DISPLAY - SPIRAL ABYSS CHALLENGE
	std::vector<FChallengeData> spiralAbyssChallengeData;
};


