#include "simulation/ElementCommon.h"
#include "simulation/Air.h"

//#TPT-Directive ElementClass Element_STEL PT_STEL 187
Element_STEL::Element_STEL()
{
	Identifier = "DEFAULT_PT_STEL";
	Name = "STEL";
	Colour = PIXPACK(0x80808F);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	// element properties here

	Update = &Element_STEL::update;
	Graphics = &Element_STEL::graphics;

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
	Description = "Steel. Stronger than IRON, like a rustable TTAN.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_HOT_GLOW|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1800.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_STEL::update;
}

//#TPT-Directive ElementHeader Element_STEL static int update(UPDATE_FUNC_ARGS)
int Element_STEL::update(UPDATE_FUNC_ARGS)
{
	//Rust check
	int r, rx, ry;
	if (parts[i].life)
		return 0;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				switch TYP(r)
				{
				case PT_SALT:
					if (RNG::Ref().chance(1, 100))
						goto succ;
					break;
				case PT_SLTW:
					if (RNG::Ref().chance(1, 120))
						goto succ;
					break;
				case PT_WATR:
					if (RNG::Ref().chance(1, 2400))
						goto succ;
					break;
				case PT_O2:
					if (RNG::Ref().chance(1, 500))
						goto succ;
					break;
				case PT_LO2:
					goto succ;
				default:
					break;
				}
			}

	//Blockair check
	int stel = 0;
	if (nt <= 2)
		stel = 2;
	else if (parts[i].tmp)
		stel = 2;
	else if (nt <= 6)
	{
		for (int rx = -1; rx <= 1; rx++)
			for (int ry = -1; ry <= 1; ry++)
				if ((!rx != !ry) && BOUNDS_CHECK)
				{
					if (TYP(pmap[y + ry][x + rx]) == PT_SSTL
						|| TYP(pmap[y + ry][x + rx]) == PT_TTAN
						|| TYP(pmap[y + ry][x + rx]) == PT_STEL)
						stel++;
				}
	}

	if (stel >= 2)
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

//#TPT-Directive ElementHeader Element_STEL static int graphics(GRAPHICS_FUNC_ARGS)
int Element_STEL::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_STEL::~Element_STEL() {}
