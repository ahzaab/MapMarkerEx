#include <string.h>
#include <map>

class PapyrusMapMarkers
{
	using VM = RE::BSScript::Internal::VirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

public:
    static bool   RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm);


private:
	static RE::BSFixedString GetLocationName(VM *vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref);
	static uint32_t GetMarkerType(VM *vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref);
	static bool IsVisible(VM *vm, StackID stackId, [[maybe_unused]] RE::StaticFunctionTag* base, RE::TESObjectREFR* ref);


	static RE::ExtraMapMarker* GetMapMarker(RE::TESObjectREFR* ref);
};
