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
	FRequest_SereniteaPot sereniteaPotCredentials;
	sereniteaPotCredentials.userMainID = 808123456;
	getSereniteaPot(sereniteaPotCredentials);
	
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



void AHttpService::Login(FRequest_Summary LoginCredentials)
{
	/*
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Summary>(LoginCredentials, ContentJsonString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = PostRequest("User/login", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::SummaryResponse);
	Send(Request);
	*/
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

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
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

