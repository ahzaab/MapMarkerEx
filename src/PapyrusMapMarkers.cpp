#include "PCH.h"
#include "PapyrusMapMarkers.h"
#include <vector>

RE::BSFixedString PapyrusMapMarkers::GetLocationName(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
	}

	auto extraMapMarker = GetMapMarkerInternal(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return RE::BSFixedString();
	}

	if (!extraMapMarker->mapData) {
		vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
		return RE::BSFixedString();
	}

	return extraMapMarker->mapData->locationName.fullName;
}

RE::BSTArray<RE::TESObjectREFR*> PapyrusMapMarkers::GetCurrentWorldSpaceMapMarkers([[maybe_unused]] VM* vm, [[maybe_unused]] StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, bool abcanTravelToOnly)
{
	auto pPC = RE::PlayerCharacter::GetSingleton();
	RE::BSTArray<RE::TESObjectREFR*> mapMarkers;

	for (auto& handle : pPC->currentMapMarkers) {
		RE::NiPointer<RE::TESObjectREFR> ref;
		if (RE::LookupReferenceByHandle(handle.native_handle(), ref)) {
			if (abcanTravelToOnly) {
				if (CanTravelToInternal(ref.get())) {
					mapMarkers.emplace_back(ref.get());
				}
			}
			else
			{
				mapMarkers.emplace_back(ref.get());
			}
		}
	}

	return mapMarkers;
}


uint32_t PapyrusMapMarkers::GetMarkerType(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
	}

	auto extraMapMarker = GetMapMarkerInternal(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return 0;
	}

	if (!extraMapMarker->mapData) {
		vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
		return 0;
	}

	// Opps, the common library is missed alligned here
	//return static_cast<uint32_t>(extraMapMarker->mapData->type.underlying());
	return static_cast<uint32_t>(extraMapMarker->mapData->pad02);
}

bool PapyrusMapMarkers::IsVisible(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
	}

	auto extraMapMarker = GetMapMarkerInternal(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return false;
	}

	if (!extraMapMarker->mapData) {
		vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
		return false;
	}

	// If the reference is disabled, it cannot be seen on the map regardless of the visible flag
	return extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !ref->IsDisabled();
}

bool PapyrusMapMarkers::CanTravelTo(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
	}

	auto extraMapMarker = GetMapMarkerInternal(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return false;
	}

	if (!extraMapMarker->mapData) {
		vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
		return false;
	}

	return CanTravelToInternal(ref);
}

//Helper function

RE::ExtraMapMarker* PapyrusMapMarkers::GetMapMarkerInternal(RE::TESObjectREFR* ref)
{
	if (!ref) {
		return nullptr;
	}

	if (!ref->extraList.HasType<RE::ExtraMapMarker>()) {
		return nullptr;
	}

	return ref->extraList.GetByType<RE::ExtraMapMarker>();
}

bool PapyrusMapMarkers::CanTravelToInternal(RE::TESObjectREFR* ref)
{
	if (!ref) {
		return false;
	}

	auto mm = GetMapMarkerInternal(ref);

	if (!mm) {
		return false;
	}

	// Also have to check if the object reference is enabled.  Certain civil war camp markers, for example, have the "Can Travel To" flag on but they are
	// disabled so they cannot be selected on the map
	return (mm->mapData->flags.all(RE::MapMarkerData::Flag::kCanTravelTo, RE::MapMarkerData::Flag::kVisible) && !ref->IsDisabled());
}

auto PapyrusMapMarkers::RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm) -> bool
{
	a_vm->RegisterFunction("GetLocationName", Plugin::NAME, GetLocationName);
	a_vm->RegisterFunction("GetCurrentWorldSpaceMapMarkers", Plugin::NAME, GetCurrentWorldSpaceMapMarkers);
	a_vm->RegisterFunction("CanTravelTo", Plugin::NAME, CanTravelTo);
	a_vm->RegisterFunction("GetMarkerType", Plugin::NAME, GetMarkerType);
	a_vm->RegisterFunction("IsVisible", Plugin::NAME, IsVisible);
    return true;
}
