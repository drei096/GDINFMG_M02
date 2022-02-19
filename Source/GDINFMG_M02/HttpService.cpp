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
	/*
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Summary>(LoginCredentials, ContentJsonString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = PostRequest("User/login", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::SummaryResponse);
	Send(Request);
	*/

	/*
	FString loginEndpoint = "UserD/";
	loginEndpoint.Append(LoginCredentials.username);
	loginEndpoint.Append("/").Append(LoginCredentials.password);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(loginEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
	*/
}

void AHttpService::getServer(FRequest_Server ServerCredentials)
{
	FString serverEndpoint = "UserE/";
	serverEndpoint.Append(FString::FromInt(ServerCredentials.serverID));
	serverEndpoint.Append("/").Append(FString::FromInt(ServerCredentials.accountID));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(serverEndpoint);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::ServerResponse);
	Send(Request);
}

void AHttpService::ServerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
		userMainID = ArrayObj.Last()->AsObject()->GetStringField("user_main_ID");
		nickname = ArrayObj.Last()->AsObject()->GetStringField("characterNickname");
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

			ownedCharacterList.push_back(tempHolder);
		}
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

			ownedArtifactList.push_back(tempHolder);
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

