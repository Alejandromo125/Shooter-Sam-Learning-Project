// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::setPercentage(float percentage)
{
	if (healthBar)
	{
		healthBar->SetPercent(percentage);
	}
}
