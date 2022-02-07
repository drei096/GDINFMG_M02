// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpService.h"
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

	FRequest_Login LoginCredentials;
	LoginCredentials.email = TEXT("asdf@asdf.com");
	LoginCredentials.password = TEXT("asdfasdf");
	TestGet(LoginCredentials);
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



void AHttpService::Login(FRequest_Login LoginCredentials) {
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Login>(LoginCredentials, ContentJsonString);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = PostRequest("User/login", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
}

void AHttpService::TestGet(FRequest_Login LoginCredentials)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest("User/login");
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
}


void AHttpService::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!ResponseIsValid(Response, bWasSuccessful)) return;

	FResponse_Login LoginResponse;
	GetStructFromJsonString<FResponse_Login>(Response, LoginResponse);

	SetAuthorizationHash(LoginResponse.hash);

	UE_LOG(LogTemp, Warning, TEXT("Id is: %d"), LoginResponse.id);
	UE_LOG(LogTemp, Warning, TEXT("Name is: %s"), *LoginResponse.name);
}

