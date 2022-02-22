// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include <vector>
#include "HttpService.generated.h"



USTRUCT(BlueprintType , meta = (BlueprintSpawnableComponent))
struct FOwnedCharacterData
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FOwnedCharacterData") FString constellationLevel;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FOwnedCharacterData") FString level;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FOwnedCharacterData") FString name;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FOwnedCharacterData") FString rarity;

		FOwnedCharacterData() {}
};

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FArtifactData
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArtifactData") FString artif_description;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArtifactData") FString artifactName;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArtifactData") FString artifactRarity;

		FArtifactData() {}
};

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FChallengeData
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString floor;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString chamber;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString stars;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name1H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level1H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name2H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level2H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name3H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level3H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name4H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level4H1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name1H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level1H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name2H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level2H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name3H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level3H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString character_name4H2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FChallengeData") FString level4H2;

		FChallengeData() {}
};

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_Login
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Login") FString username; //username or email
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Login") FString password;

		FRequest_Login() {}
};

USTRUCT()
struct FResponse_Login
{
		GENERATED_BODY()
		UPROPERTY() int userMainID;
		UPROPERTY() int nickname;

		FResponse_Login() {}
};

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_Server // SWITCH ACCOUNTS
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Server") int serverID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Server") int accountID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_Summary
{
		GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Summary") int userMainID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_WorldExplo
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_WorldExplo") int userMainID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_WorldExplo") FString region;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_SereniteaPot
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_Teapot") int userMainID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_CharacterCollection
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_CharacterCollection") int userMainID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_CharacterAttributes
{
		GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_CharAttribs") int userMainID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_CharAttribs") int ownedCharacterID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_SpiralAbyssSummary
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_SpiralSummary") int userMainID;

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

USTRUCT(BlueprintType, meta = (BlueprintSpawnableComponent))
struct FRequest_SpiralAbyssChallenge
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_SpiralChallenge") int abyssID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_SpiralChallenge") int floor;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FRequest_SpiralChallenge") int chamber;

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
struct FResponse_LoginHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_Login Response_Login;

	FResponse_LoginHolder() {}
};

USTRUCT()
struct FResponse_ServerHolder
{
	GENERATED_BODY()
		UPROPERTY() FResponse_Server Response_Server;

	FResponse_ServerHolder() {}
};

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


UCLASS(Blueprintable, hideCategories = (Rendering, Replication, Input, Actor, "Actor Tick"), meta = (BlueprintSpawnableComponent))
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
	UFUNCTION(BlueprintCallable) void Login(FRequest_Login LoginCredentials);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SERVER REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getServer(FRequest_Server serverCredentials);
	void ServerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SUMMARY REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getSummary(FRequest_Summary summaryCredentials);
	void SummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//WORLD EXPLO REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getWorldExploration(FRequest_WorldExplo worldExploCredentials);
	void worldExplorationResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SERENITEA POT REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getSereniteaPot(FRequest_SereniteaPot sereniteaPotCredentials);
	void sereniteaPotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//CHARACTER COLLECTION REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getCharacterCollection(FRequest_CharacterCollection characterCollectionCredentials);
	void characterCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//CHARACTER ATTRIBUTES REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getCharacterAttributes(FRequest_CharacterAttributes characterAttributesCredentials);
	void characterAttributesResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SPIRAL ABYSS SUMMARY REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getSpiralAbyssSummary(FRequest_SpiralAbyssSummary spiralAbyssSummaryCredentials);
	void spiralAbyssSummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//SPIRAL ABYSS CHALLENGE REQUEST RESPONSE
	UFUNCTION(BlueprintCallable) void getSpiralAbyssChallenge(FRequest_SpiralAbyssChallenge spiralAbyssChallengeCredentials);
	void spiralAbyssChallengeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	// FOR DISPLAY - LOGIN
	UPROPERTY(BlueprintReadWrite) FString userMainLoginID;
	UPROPERTY(BlueprintReadWrite) FString nicknameLogin;

	//FOR CHECKING - LOGIN
	UPROPERTY(BlueprintReadWrite) bool canLogin = false;

	// FOR DISPLAY - SERVER
	UPROPERTY(BlueprintReadWrite) FString userMainServerID;
	UPROPERTY(BlueprintReadWrite) FString nicknameSwitchServer;
	UPROPERTY(BlueprintReadWrite) FString userMainAccountID;

	// FOR DISPLAY - SUMMARY
	UPROPERTY(BlueprintReadWrite) FString ACuli;
	UPROPERTY(BlueprintReadWrite) FString CChestOpen;
	UPROPERTY(BlueprintReadWrite) FString DomUnlock;
	UPROPERTY(BlueprintReadWrite) FString EChestOpen;
	UPROPERTY(BlueprintReadWrite) FString ECuli;
	UPROPERTY(BlueprintReadWrite) FString GCuli;
	UPROPERTY(BlueprintReadWrite) FString LChestOpen;
	UPROPERTY(BlueprintReadWrite) FString PChestOpen;
	UPROPERTY(BlueprintReadWrite) FString SAbyss;
	UPROPERTY(BlueprintReadWrite) FString achievements;
	UPROPERTY(BlueprintReadWrite) FString characters;
	UPROPERTY(BlueprintReadWrite) FString daysActive;
	UPROPERTY(BlueprintReadWrite) FString noRemarkable;
	UPROPERTY(BlueprintReadWrite) FString wayPUnlock;

	// FOR DISPLAY - WORLD EXPLORATION
	UPROPERTY(BlueprintReadWrite) FString explorationProgress;
	UPROPERTY(BlueprintReadWrite) FString frostTreeLevel;
	UPROPERTY(BlueprintReadWrite) FString reputationLevel;
	UPROPERTY(BlueprintReadWrite) FString sakuraFavorLevel;

	//FOR DISPLAY - SERENITEA POT
	UPROPERTY(BlueprintReadWrite) FString FurnishingsObtained;
	UPROPERTY(BlueprintReadWrite) FString highestAdeptalEnergy;
	UPROPERTY(BlueprintReadWrite) FString trustRank;
	UPROPERTY(BlueprintReadWrite) FString visitorCount;

	//FOR DISPLAY - CHARACTER COLLECTION
	UPROPERTY(BlueprintReadWrite) TArray<FOwnedCharacterData> ownedCharacterList;

	//FOR DISPLAY - CHARACTER ATTRIBUTES
	UPROPERTY(BlueprintReadWrite) FString character_name;
	UPROPERTY(BlueprintReadWrite) FString friendshipLevel;
	UPROPERTY(BlueprintReadWrite) FString refineRank;
	UPROPERTY(BlueprintReadWrite) FString weap_description;
	UPROPERTY(BlueprintReadWrite) FString weaponLevel;
	UPROPERTY(BlueprintReadWrite) FString weaponName;
	UPROPERTY(BlueprintReadWrite) FString weaponRarity;
	UPROPERTY(BlueprintReadWrite) TArray<FArtifactData> ownedArtifactList;

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
	UPROPERTY(BlueprintReadWrite) FString abyss_ID;
	UPROPERTY(BlueprintReadWrite) FString battlesFought;
	UPROPERTY(BlueprintReadWrite) FString deepestDesc;
	UPROPERTY(BlueprintReadWrite) FString elemBurstUsed;
	UPROPERTY(BlueprintReadWrite) FString elemSkillsUsed;
	UPROPERTY(BlueprintReadWrite) FString mostDefeats;
	UPROPERTY(BlueprintReadWrite) FString mostDMGTaken;
	UPROPERTY(BlueprintReadWrite) FString sAbyssStars;
	UPROPERTY(BlueprintReadWrite) FString strongSingleStrike;

	//FOR DISPLAY - SPIRAL ABYSS CHALLENGE
	UPROPERTY(BlueprintReadWrite) TArray<FChallengeData> spiralAbyssChallengeData;
};


