#include "PCH.h"
#include "Papyrus.h"
#include "PapyrusMapMarkers.h"


namespace MapMarkersEx
{
	auto Papyrus::Register() -> bool
	{
		auto papyrus = SKSE::GetPapyrusInterface();
		if (!papyrus->Register(PapyrusMapMarkers::RegisterFunctions)) {
			return false;
		} else {
			logger::info("registered papyrus PapyrusMapMarkers funcs");
		}

		return true;
	}
}
