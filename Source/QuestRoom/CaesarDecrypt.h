// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CaesarDecrypt.generated.h"

/**
 * 
 */
UCLASS()
class QUESTROOM_API UCaesarDecrypt : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure, meta = (DisplayName = "Caesar decryption", CompactNodeTitle = "Caesar decryption", Keywords = "Caesar Decrypt"), Category = Game)
	static FString Decrypt(FString message, int shift);
	
};
