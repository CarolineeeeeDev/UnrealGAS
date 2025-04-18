// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

FGameplayAbilityInfo::FGameplayAbilityInfo():
	CD(0), CostType(ECostType::MP), CostValue(0), IconMaterial(nullptr), AbilityClass(nullptr)
{

}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility> AbilityClass):
	CD(CD), CostType(CostType), CostValue(CostValue), IconMaterial(IconMaterial), AbilityClass(AbilityClass)
{

}

FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo(int level)
{
	UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	ECostType CostType = ECostType::MP;
	float CD = 0;
	float CostValue = 0;
	if (CDEffect && CostEffect)
	{
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(level, CD);
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(level, CostValue);
			FString CostTypeName = CostEffectModifierInfo.Attribute.AttributeName;
			if (CostTypeName == "HP")
			{
				CostType = ECostType::HP;
			}
			if (CostTypeName == "MP")
			{
				CostType = ECostType::MP;
			}
			if (CostTypeName == "Strength")
			{
				CostType = ECostType::Strength;
			}
			return FGameplayAbilityInfo(CD, CostType, CostValue, IconMaterial, GetClass());
		}
	}
	return FGameplayAbilityInfo();
}
