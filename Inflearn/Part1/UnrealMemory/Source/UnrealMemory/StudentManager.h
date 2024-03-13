// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALMEMORY_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {};

	// 허상을 해결 하기 위해 추가 해야한다.
	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

	// 허상을 해결 하기 위해 추가 해야한다.
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

	const class UStudent* GetStudent() const { return SafeStudent; }
	
private:
	class UStudent* SafeStudent = nullptr;
};
