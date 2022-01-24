#include "PCH.h"
#include "PapyrusMapMarkers.h"

RE::BSFixedString PapyrusMapMarkers::GetLocationName(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kWarning);
	}

	auto extraMapMarker = GetMapMarker(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return RE::BSFixedString();
	}

	if (!extraMapMarker->mapData) {
		return RE::BSFixedString();
	}

	return extraMapMarker->mapData->locationName.fullName;
}

uint32_t PapyrusMapMarkers::GetMarkerType(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kWarning);
	}

	auto extraMapMarker = GetMapMarker(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return 0;
	}

	if (!extraMapMarker->mapData) {
		return 0;
	}

	return static_cast<uint32_t>(extraMapMarker->mapData->type.underlying());
}

bool PapyrusMapMarkers::IsVisible(VM* vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
{
	if (!ref) {
		vm->TraceStack("ObjectReference is None", stackId, Severity::kWarning);
	}

	auto extraMapMarker = GetMapMarker(ref);

	if (!extraMapMarker) {
		vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
		return false;
	}

	if (!extraMapMarker->mapData) {
		return false;
	}

	return extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible);
}

//RE::BSFixedString PapyrusMapMarkers::GetLocationName([[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref)
//{
//	auto extraMapMarker = GetMapMarker(ref);
//
//	if (!extraMapMarker) {
//		return RE::BSFixedString();
//	}
//
//	return extraMapMarker->mapData->locationName.fullName;
//}

RE::ExtraMapMarker* PapyrusMapMarkers::GetMapMarker(RE::TESObjectREFR* ref)
{
	if (!ref) {
		return nullptr;
	}

	if (!ref->extraList.HasType<RE::ExtraMapMarker>()) {
		return nullptr;
	}

	return ref->extraList.GetByType<RE::ExtraMapMarker>();
}

auto PapyrusMapMarkers::RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm) -> bool
{
	a_vm->RegisterFunction("GetLocationName", Plugin::NAME, GetLocationName);
    return true;
}
