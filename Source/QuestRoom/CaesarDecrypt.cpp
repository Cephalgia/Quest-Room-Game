// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestRoom.h"
#include "CaesarDecrypt.h"

FString UCaesarDecrypt::Decrypt(FString message, int shift)
{
	FString Result;
    const TCHAR* convert = *message;
    for (int i = 0; i < message.Len(); ++i) {
        if((convert[i] < 91) && ((convert[i] + shift) > 90))
        {
            Result.AppendChar(64 + shift - (90 - convert[i]));
        } else if((convert[i] > 97) && ((convert[i] + shift) > 122))
        {
            Result.AppendChar(96 + shift - (122 - convert[i]));
        } else
        {
            Result.AppendChar(convert[i] +shift);
        }
    }
    return Result;
}


