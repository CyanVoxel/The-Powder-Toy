#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_GPHT PT_GPHT 179
Element_GPHT::Element_GPHT()
{
	Identifier = "DEFAULT_PT_GPHT";
	Name = "GPHT";
	Colour = PIXPACK(0x333333);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.00f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 5;

	Weight = 100;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 251;
	Description = "Graphite. Acts as a degradable Ceramic.";

	Properties = TYPE_SOLID | PROP_NEUTPASS | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 4273.15f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_GPHT::update;
	Graphics = &Element_GPHT::graphics;
}

//#TPT-Directive ElementHeader Element_GPHT static int update(UPDATE_FUNC_ARGS)
int Element_GPHT::update(UPDATE_FUNC_ARGS)
{

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
				case PT_O2:
					if (RNG::Ref().chance(1, 250))
						goto succ;
					break;
				case PT_LO2:
					goto succ;
				default:
					break;
				}
			}
	if (sim->pv[y / CELL][x / CELL] < -30.0f)
		sim->create_part(i, x, y, PT_CLST);
	return 0;
succ:
	sim->part_change_type(i, x, y, PT_STNE);
	parts[i].tmp = RNG::Ref().between(20, 29);
	return 0;
}

//#TPT-Directive ElementHeader Element_GPHT static int graphics(GRAPHICS_FUNC_ARGS)
int Element_GPHT::graphics(GRAPHICS_FUNC_ARGS)
{
	int z = (cpart->tmp2 - 2) * 8;
	*colr += z;
	*colg += z;
	*colb += z;
	return 0;
}

Element_GPHT::~Element_GPHT() {}

