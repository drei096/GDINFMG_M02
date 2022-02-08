// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HttpService.generated.h"


USTRUCT()
struct FQueryData
{
		GENERATED_BODY()
		UPROPERTY() int id;
		UPROPERTY() FString name;
		UPROPERTY() int score;
		FQueryData() {}
};

USTRUCT()
struct FRequest_Login {
		GENERATED_BODY()
        UPROPERTY() FString email;
		UPROPERTY() FString password;

		FRequest_Login() {}
};

USTRUCT()
struct FResponse_Login {
		GENERATED_BODY()
        UPROPERTY() int id;
		UPROPERTY() FString name;
		UPROPERTY() FString hash;
		UPROPERTY() FQueryData data;

		FResponse_Login() {}
};



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

	void Login(FRequest_Login LoginCredentials);
	void TestGet(FRequest_Login LoginCredentials);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
