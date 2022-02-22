// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpService.h"

#include <string>

#include "GDINFMG_M02.h"

// Sets default values
AHttpService::AHttpService()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHttpService::BeginPlay()
{
	Super::BeginPlay();

	// We don't want clients to be able to run HTTP requests. Only servers.
	if (!HasAuthority())
	{
		return;
	}	
		
	Http = &FHttpModule::Get();

	//TESTER CODE FOR SUMMARY
	//FRequest_Summary summaryCredentials;
	//summaryCredentials.userMainID = 808123456;
	//getSummary(summaryCredentials);

	//TESTER CODE FOR WORLD EXPLO
	//FRequest_WorldExplo worldExploCredentials;
	//worldExploCredentials.userMainID = 808123456;
	//worldExploCredentials.region = "Liyue";
	//getWorldExploration(worldExploCredentials);

	//TESTER CODE FOR SERENITEA POT
	//FRequest_SereniteaPot sereniteaPotCredentials;
	//sereniteaPotCredentials.userMainID = 808123456;
	//getSereniteaPot(sereniteaPotCredentials);

	//TESTER CODE FOR CHARACTER COLLECTION
	//FRequest_CharacterCollection characterCollectionCredentials;
	//characterCollectionCredentials.userMainID = 808123456;
	//getCharacterCollection(characterCollectionCredentials);

	//TESTER CODE FOR CHARACTER ATTRIBUTES
	//FRequest_CharacterAttributes characterAttributesCredentials;
	//characterAttributesCredentials.ownedCharacterID = 1;
	//characterAttributesCredentials.userMainID = 808123456;
	//getCharacterAttributes(characterAttributesCredentials);

	//TESTER CODE FOR SPIRAL ABYSS SUMMARY
	//FRequest_SpiralAbyssSummary spiralAbyssSummaryCredentials;
	//spiralAbyssSummaryCredentials.userMainID = 808123456;
	//getSpiralAbyssSummary(spiralAbyssSummaryCredentials);

	//TESTER CODE FOR SPIRAL ABYSS CHALLENGE
	//FRequest_SpiralAbyssChallenge spiralAbyssChallengeCredentials;
	//spiralAbyssChallengeCredentials.abyssID = 1;
	//spiralAbyssChallengeCredentials.chamber = 1;
	//spiralAbyssChallengeCredentials.floor = 9;
	//getSpiralAbyssChallenge(spiralAbyssChallengeCredentials);

	//TESTER CODE FOR LOGIN
	//FRequest_Login loginCredentials;
	//loginCredentials.username = "derpyderp1";
	//loginCredentials.password = "derpderp1233";
	//Login(loginCredentials);
}

void AHttpService::SetAuthorizationHash(FString Hash)
{
	this->AuthorizationHash = Hash;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::RequestWithRoute(FString Subroute) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->SetURL(ApiBaseUrl + Subroute);
	SetRequestHeaders(Request);
	return Request;
}

void AHttpService::SetRequestHeaders(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request) {
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	Request->SetHeader(AuthorizationHeader, AuthorizationHash);
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::GetRequest(FString Subroute) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::PostRequest(FString Subroute, FString ContentJsonString) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void AHttpService::Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request) {
	Request->ProcessRequest();
}

bool AHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else {
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}





/**********************************************************************************************************************************************/



template <typename StructType>
void AHttpService::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
void AHttpService::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput) {
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}



/**********************************************************************************************************************************************/



void AHttpService::Login(FRequest_Login LoginCredentials)
{

	FString loginEndpoint = "UserD/";
	loginEndpoint.Append(LoginCredentials.username);
	loginEndpoint.Append("/").Append(LoginCredentials.password);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(loginEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
	UE_LOG(LogTemp, Warning, TEXT("AAAAA: %s, BBBBB:%s"), *LoginCredentials.username, *LoginCredentials.password);
}

void AHttpService::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_LoginHolder LoginResponse;
	GetStructFromJsonString<FResponse_LoginHolder>(Response, LoginResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());

		if(ArrayObj.Num() > 0)
		{
			canLogin = true;

			userMainLoginID = ArrayObj[0]->AsObject()->GetStringField("user_main_ID");
			nicknameLogin = ArrayObj[0]->AsObject()->GetStringField("characterNickname");
			abyss_ID = ArrayObj[0]->AsObject()->GetStringField("abyss_ID");
			userMainAccountID = ArrayObj.Last()->AsObject()->GetStringField("account_ID");

			//UE_LOG(LogTemp, Warning, TEXT("%s"), *userMainAccountID);
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAA"));
		}

	}
}

void AHttpService::getServer(FRequest_Server ServerCredentials)
{
	FString serverEndpoint = "UserE/";
	serverEndpoint.Append(FString::FromInt(ServerCredentials.accountID));
	serverEndpoint.Append("/").Append(FString::FromInt(ServerCredentials.serverID));

	UE_LOG(LogTemp, Warning, TEXT("%d"), ServerCredentials.serverID);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(serverEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::ServerResponse);
	Send(Request);

}

void AHttpService::ServerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_ServerHolder ServerResponse;
	GetStructFromJsonString<FResponse_ServerHolder>(Response, ServerResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		if(ArrayObj.Num() > 0)
		{
			userMainLoginID = ArrayObj.Last()->AsObject()->GetStringField("user_main_ID");
			nicknameLogin = ArrayObj.Last()->AsObject()->GetStringField("characterNickname");
			abyss_ID = ArrayObj.Last()->AsObject()->GetStringField("abyss_ID");
		}
		else
		{
			userMainLoginID = "";
			nicknameLogin = "";
		}

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *userMainLoginID);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
}

void AHttpService::getSummary(FRequest_Summary LoginCredentials)
{
	FString loginEndpoint = "User/";
	loginEndpoint.Append(FString::FromInt(LoginCredentials.userMainID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(loginEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::SummaryResponse);
	Send(Request);
}

void AHttpService::SummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful)) 
		return;

	FResponse_SummaryHolder SummaryResponse;
	GetStructFromJsonString<FResponse_SummaryHolder>(Response, SummaryResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		ACuli = ArrayObj.Last()->AsObject()->GetStringField("ACuli");
		CChestOpen = ArrayObj.Last()->AsObject()->GetStringField("CChestOpen");
		DomUnlock = ArrayObj.Last()->AsObject()->GetStringField("DomUnlock");
		EChestOpen = ArrayObj.Last()->AsObject()->GetStringField("EChestOpen");
		ECuli = ArrayObj.Last()->AsObject()->GetStringField("ECuli");
		GCuli = ArrayObj.Last()->AsObject()->GetStringField("GCuli");
		LChestOpen = ArrayObj.Last()->AsObject()->GetStringField("LChestOpen");
		PChestOpen = ArrayObj.Last()->AsObject()->GetStringField("PChestOpen");
		SAbyss = ArrayObj.Last()->AsObject()->GetStringField("SAbyss");
		achievements = ArrayObj.Last()->AsObject()->GetStringField("achievements");
		characters = ArrayObj.Last()->AsObject()->GetStringField("characters");
		daysActive = ArrayObj.Last()->AsObject()->GetStringField("daysActive");
		noRemarkable = ArrayObj.Last()->AsObject()->GetStringField("noRemarkable");
		wayPUnlock = ArrayObj.Last()->AsObject()->GetStringField("wayPUnlock");
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
}

void AHttpService::getWorldExploration(FRequest_WorldExplo worldExploCredentials)
{
	FString regionAppend = "User/";
	regionAppend.Append(FString::FromInt(worldExploCredentials.userMainID));
	regionAppend.Append("/").Append(worldExploCredentials.region);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(regionAppend);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::worldExplorationResponse);
	Send(Request);
}

void AHttpService::worldExplorationResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_WorldExploHolder worldExploResponse;
	GetStructFromJsonString<FResponse_WorldExploHolder>(Response, worldExploResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		explorationProgress = ArrayObj.Last()->AsObject()->GetStringField("explorationProgress");
		frostTreeLevel = ArrayObj.Last()->AsObject()->GetStringField("frostTreeLevel");
		reputationLevel = ArrayObj.Last()->AsObject()->GetStringField("reputationLevel");
		sakuraFavorLevel = ArrayObj.Last()->AsObject()->GetStringField("sakuraFavorLevel");
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
}

void AHttpService::getSereniteaPot(FRequest_SereniteaPot sereniteaPotCredentials)
{
	FString sereniteaEndpoint = "UserA/";
	sereniteaEndpoint.Append(FString::FromInt(sereniteaPotCredentials.userMainID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(sereniteaEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::sereniteaPotResponse);
	Send(Request);
}

void AHttpService::sereniteaPotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_SereniteaPotHolder sereniteaPotResponse;
	GetStructFromJsonString<FResponse_SereniteaPotHolder>(Response, sereniteaPotResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		FurnishingsObtained = ArrayObj.Last()->AsObject()->GetStringField("FurnishingsObtained");
		highestAdeptalEnergy = ArrayObj.Last()->AsObject()->GetStringField("highestAdeptalEnergy");
		trustRank = ArrayObj.Last()->AsObject()->GetStringField("trustRank");
		visitorCount = ArrayObj.Last()->AsObject()->GetStringField("visitorCount");
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FurnishingsObtained);
}

void AHttpService::getCharacterCollection(FRequest_CharacterCollection characterCollectionCredentials)
{
	FString characterCollectionEndpoint = "UserB/";
	characterCollectionEndpoint.Append(FString::FromInt(characterCollectionCredentials.userMainID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(characterCollectionEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::characterCollectionResponse);
	Send(Request);
}

void AHttpService::characterCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_CharacterCollectionHolder characterCollectionResponse;
	GetStructFromJsonString<FResponse_CharacterCollectionHolder>(Response, characterCollectionResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		for(int i = 0; i < ArrayObj.Num(); i++)
		{
			FOwnedCharacterData tempHolder;
			tempHolder.name = ArrayObj[i]->AsObject()->GetStringField("character_name");
			tempHolder.constellationLevel = ArrayObj[i]->AsObject()->GetStringField("constellationLevel");
			tempHolder.level = ArrayObj[i]->AsObject()->GetStringField("level");
			tempHolder.rarity = ArrayObj[i]->AsObject()->GetStringField("rarity");

			ownedCharacterList.Add(tempHolder);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *ownedCharacterList[0].name);
}

void AHttpService::getCharacterAttributes(FRequest_CharacterAttributes characterAttributesCredentials)
{
	FString characterAttributesEndpoint = "UserC/";
	characterAttributesEndpoint.Append(FString::FromInt(characterAttributesCredentials.ownedCharacterID));
	characterAttributesEndpoint.Append("/").Append(FString::FromInt(characterAttributesCredentials.userMainID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(characterAttributesEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::characterAttributesResponse);
	Send(Request);
}

void AHttpService::characterAttributesResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_CharacterAttributesHolder characterAtrributesResponse;
	GetStructFromJsonString<FResponse_CharacterAttributesHolder>(Response, characterAtrributesResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		character_name = ArrayObj[0]->AsObject()->GetStringField("character_name");
		friendshipLevel = ArrayObj[0]->AsObject()->GetStringField("friendshipLevel");
		refineRank = ArrayObj[0]->AsObject()->GetStringField("refineRank");
		weap_description = ArrayObj[0]->AsObject()->GetStringField("weap_description");
		weaponLevel = ArrayObj[0]->AsObject()->GetStringField("weaponLevel");
		weaponName = ArrayObj[0]->AsObject()->GetStringField("weaponName");
		weaponRarity = ArrayObj[0]->AsObject()->GetStringField("weaponRarity");

		for (int i = 1; i < ArrayObj.Num(); i++)
		{
			FArtifactData tempHolder;
			tempHolder.artif_description = ArrayObj[i]->AsObject()->GetStringField("artif_description");
			tempHolder.artifactName = ArrayObj[i]->AsObject()->GetStringField("artifactName");
			tempHolder.artifactRarity = ArrayObj[i]->AsObject()->GetStringField("artifactRarity");

			ownedArtifactList.Add(tempHolder);
		}

		//NOTE: OWNED ARTIFACT LIST INDEX REFERENCE: [0] = ARTIFACT 1
		//											 [1] = ARTIFACT 2
		//											 [2] = ARTIFACT 3
		//											 [3] = ARTIFACT 4
		//											 [4] = ARTIFACT 5
		
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *artifactName1);
}

void AHttpService::getSpiralAbyssSummary(FRequest_SpiralAbyssSummary spiralAbyssSummaryCredentials)
{
	FString spiralAbyssSummaryEndpoint = "UserF/";
	spiralAbyssSummaryEndpoint.Append(FString::FromInt(spiralAbyssSummaryCredentials.userMainID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(spiralAbyssSummaryEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::spiralAbyssSummaryResponse);
	Send(Request);
}

void AHttpService::spiralAbyssSummaryResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_SpiralAbyssSummaryHolder spiralAbyssSummaryResponse;
	GetStructFromJsonString<FResponse_SpiralAbyssSummaryHolder>(Response, spiralAbyssSummaryResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		abyss_ID = ArrayObj.Last()->AsObject()->GetStringField("abyss_ID");
		battlesFought = ArrayObj.Last()->AsObject()->GetStringField("battlesFought");
		deepestDesc = ArrayObj.Last()->AsObject()->GetStringField("deepestDesc");
		elemBurstUsed = ArrayObj.Last()->AsObject()->GetStringField("elemBurstUsed");
		elemSkillsUsed = ArrayObj.Last()->AsObject()->GetStringField("elemSkillsUsed");
		mostDefeats = ArrayObj.Last()->AsObject()->GetStringField("mostDefeats");
		mostDMGTaken = ArrayObj.Last()->AsObject()->GetStringField("mostDMGTaken");
		sAbyssStars = ArrayObj.Last()->AsObject()->GetStringField("sAbyssStars");
		strongSingleStrike = ArrayObj.Last()->AsObject()->GetStringField("strongSingleStrike");
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *strongSingleStrike);
}

void AHttpService::getSpiralAbyssChallenge(FRequest_SpiralAbyssChallenge spiralAbyssChallengeCredentials)
{
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAA: %s"), *abyss_ID);

	FString spiralAbyssChallengeEndpoint = "UserG/";
	spiralAbyssChallengeEndpoint.Append(FString::FromInt(spiralAbyssChallengeCredentials.abyssID));
	

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(spiralAbyssChallengeEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::spiralAbyssChallengeResponse);
	Send(Request);
}

void AHttpService::spiralAbyssChallengeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful))
		return;

	FResponse_SpiralAbyssChallengeHolder spiralAbyssChallengeResponse;
	GetStructFromJsonString<FResponse_SpiralAbyssChallengeHolder>(Response, spiralAbyssChallengeResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//store results to inClass variables
		
		for (int i = 0; i < ArrayObj.Num(); i++)
		{
			FChallengeData tempHolder;
			tempHolder.chamber = ArrayObj[i]->AsObject()->GetStringField("chamber");

			tempHolder.character_name1H1 = ArrayObj[i]->AsObject()->GetStringField("char1");
			tempHolder.level1H1 = ArrayObj[i]->AsObject()->GetStringField("char1Level");

			tempHolder.character_name2H1 = ArrayObj[i]->AsObject()->GetStringField("char2");
			tempHolder.level2H1 = ArrayObj[i]->AsObject()->GetStringField("char2Level");

			tempHolder.character_name3H1 = ArrayObj[i]->AsObject()->GetStringField("char3");
			tempHolder.level3H1 = ArrayObj[i]->AsObject()->GetStringField("char3Level");

			tempHolder.character_name4H1 = ArrayObj[i]->AsObject()->GetStringField("char4");
			tempHolder.level4H1 = ArrayObj[i]->AsObject()->GetStringField("char4Level");

			tempHolder.character_name1H2 = ArrayObj[i]->AsObject()->GetStringField("char5");
			tempHolder.level1H2 = ArrayObj[i]->AsObject()->GetStringField("char5Level");

			tempHolder.character_name2H2 = ArrayObj[i]->AsObject()->GetStringField("char6");
			tempHolder.level2H2 = ArrayObj[i]->AsObject()->GetStringField("char6Level");

			tempHolder.character_name3H2 = ArrayObj[i]->AsObject()->GetStringField("char7");
			tempHolder.level3H2 = ArrayObj[i]->AsObject()->GetStringField("char7Level");

			tempHolder.character_name4H2 = ArrayObj[i]->AsObject()->GetStringField("char8");
			tempHolder.level4H2 = ArrayObj[i]->AsObject()->GetStringField("char8Level");

			tempHolder.floor = ArrayObj[i]->AsObject()->GetStringField("floor");
			tempHolder.stars = ArrayObj[i]->AsObject()->GetStringField("stars");

			spiralAbyssChallengeData.Add(tempHolder);
		}
		
		//NOTE: CHALLENGE LIST INDEX REFERENCE:      [0] = CHALLENGE 9-1
		//											 [1] = CHALLENGE 9-2
		//											 [2] = CHALLENGE 9-3
		//											 [3] = CHALLENGE 10-1
		//											 and so on...
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *abyss_ID);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	//UE_LOG(LogTemp, Warning, TEXT("AAAAAA: %d"), ArrayObj.Num());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *spiralAbyssChallengeData[0].level2H1);
}

