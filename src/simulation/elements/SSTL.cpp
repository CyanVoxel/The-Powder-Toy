#include "simulation/ElementCommon.h"
#include "simulation/Air.h"

//#TPT-Directive ElementClass Element_SSTL PT_SSTL 187
Element_SSTL::Element_SSTL()
{
	Identifier = "DEFAULT_PT_SSTL";
	Name = "SSTL";
	Colour = PIXPACK(0x90909F);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	// element properties here

	Update = &Element_SSTL::update;
	Graphics = &Element_SSTL::graphics;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 50;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Stainless Steel. Does not rust like normal STEL.";

	Properties = TYPE_SOLID | PROP_CONDUCTS | PROP_HOT_GLOW | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1800.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_SSTL::update;
}

//#TPT-Directive ElementHeader Element_SSTL static int update(UPDATE_FUNC_ARGS)
int Element_SSTL::update(UPDATE_FUNC_ARGS)
{
	//Blockair check
	int sstl = 0;
	if (nt <= 2)
		sstl = 2;
	else if (parts[i].tmp)
		sstl = 2;
	else if (nt <= 6)
	{
		for (int rx = -1; rx <= 1; rx++)
			for (int ry = -1; ry <= 1; ry++)
				if ((!rx != !ry) && BOUNDS_CHECK)
				{
					if (TYP(pmap[y + ry][x + rx]) == PT_SSTL 
						|| TYP(pmap[y + ry][x + rx]) == PT_TTAN
						|| TYP(pmap[y + ry][x + rx]) == PT_STEL)
						sstl++;
				}
	}

	if (sstl >= 2)
	{
		sim->air->bmap_blockair[y / CELL][x / CELL] = 1;
		sim->air->bmap_blockairh[y / CELL][x / CELL] = 0x8;
	}

	return 0;
succ:
	sim->part_change_type(i, x, y, PT_IRON);
	parts[i].tmp = RNG::Ref().between(20, 29);
	return 0;
}

//#TPT-Directive ElementHeader Element_SSTL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_SSTL::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_SSTL::~Element_SSTL() {}
