#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_RDFL PT_RDFL 188
Element_RDFL::Element_RDFL()
{
	Identifier = "DEFAULT_PT_RDFL";
	Name = "RDFL";
	Colour = PIXPACK(0x64DD17);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
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
	PhotonReflectWavelengths = 0x001FCE00;

	Weight = 80;

	Temperature = 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Radioactive Fuel, a liquid alternative to Plutonium";

	Properties = TYPE_LIQUID | PROP_NEUTPASS | PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_RDFL::update;
	Graphics = &Element_RDFL::graphics;
}

//#TPT-Directive ElementHeader Element_RDFL static int update(UPDATE_FUNC_ARGS)
int Element_RDFL::update(UPDATE_FUNC_ARGS)
{
	if (RNG::Ref().chance(1, 1000) && RNG::Ref().chance(5.0f * sim->pv[y / CELL][x / CELL], 1000))
	{
		sim->create_part(i, x, y, PT_NEUT);
	}
	return 0;
}

//#TPT-Directive ElementHeader Element_RDFL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_RDFL::graphics(GRAPHICS_FUNC_ARGS)

{
	*firea = 20;
	*firer = 118;
	*fireg = 255;
	*fireb = 3;

	*pixel_mode |= FIRE_ADD;
	return 1;
}


Element_RDFL::~Element_RDFL() {}
