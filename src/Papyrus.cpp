#include "PCH.h"
#include "Papyrus.h"
#include "PapyrusMapMarkers.h"


namespace MapMarkersEx
{
	auto Papyrus::Register() -> bool
	{
		logger::info("registering papyrus funcs");
		auto papyrus = SKSE::GetPapyrusInterface();
		if (!papyrus->Register(PapyrusMapMarkers::RegisterFunctions)) {
			logger::error("could not register papyrus funcs");
			return false;
		} else {
			logger::info("registered papyrus funcs");
		}

		return true;
	}
}
