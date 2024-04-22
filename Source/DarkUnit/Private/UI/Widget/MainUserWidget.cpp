// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MainUserWidget.h"

void UMainUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
