#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_LNTG PT_LNTG 37
Element_CLNT::Element_CLNT()
{
	Identifier = "DEFAULT_PT_CLNT";
	Name = "CLNT";
	Colour = PIXPACK(0x03a9f4);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 30;

	Temperature = 0;
	HeatConduct = 251;
	Description = "Coolant. Used to rapidly cool other elements down.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 0;
	LowTemperatureTransition = NT;
	HighTemperature = 257.0f;
	HighTemperatureTransition = PT_NONE;

	Update = NULL;
}

Element_CLNT::~Element_CLNT() {}
