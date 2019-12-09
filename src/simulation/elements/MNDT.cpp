#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_MNDT PT_MNDT 5
Element_MNDT::Element_MNDT()
{
	Identifier = "DEFAULT_PT_MNDT";
	Name = "MNDT";
	Colour = PIXPACK(0xCCCCCC);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.1f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 1;

	Weight = 40;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 150;
	Description = "Moondust.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1224.0;
	HighTemperatureTransition = PT_MNRK;

	Update = NULL;
}

Element_MNDT::~Element_MNDT() {}
