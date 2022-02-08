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

	FRequest_Summary summaryCredentials;
	summaryCredentials.userMainID = 808123456;
	TestGet(summaryCredentials);
	//Login(LoginCredentials);
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



void AHttpService::Login(FRequest_Summary LoginCredentials) {
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Summary>(LoginCredentials, ContentJsonString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = PostRequest("User/login", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
}

void AHttpService::TestGet(FRequest_Summary LoginCredentials)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest("User/808123456");
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
}


void AHttpService::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!ResponseIsValid(Response, bWasSuccessful)) return;

	FResponse_SummaryHolder LoginResponse;
	GetStructFromJsonString<FResponse_SummaryHolder>(Response, LoginResponse);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	FString dataString = Response->GetContentAsString();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*dataString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		TArray<TSharedPtr<FJsonValue>> ArrayObj = JsonObj->GetArrayField("data");

		//how to display number???
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("ACuli"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("CChestOpen"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("DomUnlock"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("EChestOpen"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("ECuli"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("GCuli"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("LChestOpen"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("PChestOpen"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("SAbyss"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("achievements"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("characters"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("daysActive"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("noRemarkable"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayObj.Last()->AsObject()->GetStringField("wayPUnlock"));
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
}

