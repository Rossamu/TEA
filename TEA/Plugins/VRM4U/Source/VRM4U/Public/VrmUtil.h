// VRM4U Copyright (c) 2019 Haruyoshi Yamamoto. This software is released under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

//#include "VrmUtil.generated.h"


namespace {
	//bool operator<(const FBoneTransform &a, const FBoneTransform &b) {
	//	return a.BoneIndex < b.BoneIndex;
	//}
}

class VRM4U_API VRMUtil {
public:

	struct VRMBoneTable {
		FString BoneUE4;
		FString BoneVRM;
	};
	static const TArray<VRMBoneTable> table_ue4_vrm;
	static const TArray<VRMBoneTable> table_ue4_pmx;

	static const TArray<FString> vrm_humanoid_bone_list;
	static const TArray<FName> vrm_humanoid_bone_list_name;

	static const TArray<FString> vrm_humanoid_parent_list;

	static const TArray<FString> ue4_humanoid_bone_list;
};
