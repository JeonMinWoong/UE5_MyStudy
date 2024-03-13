// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Student.h"
#include "StudentManager.h"

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	if(InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);	
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if(nullptr == InObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 언리얼 오브젝트"), *InTag);	
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"), *InTag);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();
	
	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));

	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
}
