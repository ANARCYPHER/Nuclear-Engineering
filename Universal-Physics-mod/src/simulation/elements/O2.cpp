#include "simulation/ElementCommon.h"

int Element_O2_update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_O2()
{
	Identifier = "DEFAULT_PT_O2";
	Name = "OXYG";
	Colour = PIXPACK(0x80A0FF);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.1f;
	Diffusion = 10.0f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	HeatConduct = 70;
	Description = "Oxygen gas. Needed for most things to burn.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 90.0f;
	LowTemperatureTransition = PT_LO2;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_O2_update;
	Create = &create;
}

int Element_O2_update(UPDATE_FUNC_ARGS)
{


		if (parts[i].tmpcity[7] == 0)
		{
		

			if(parts[i].oxygens == 0)
				parts[i].oxygens = RNG::Ref().between(50, 100) * 2;
			parts[i].tmpcity[7] = 400;
		}


		if (parts[i].oxygens <= 0)
		{


			sim->kill_part(i);


		}

	if (!sim->betterburning_enable)
	{
		int r, rx, ry;
		for (rx = -2; rx < 3; rx++)
			for (ry = -2; ry < 3; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y + ry][x + rx];
					if (!r)
						continue;

				}
		if (parts[i].temp > 9973.15 && sim->pv[y / CELL][x / CELL] > 250.0f)
		{
			int gravPos = ((y / CELL) * (XRES / CELL)) + (x / CELL);
			float gravx = sim->gravx[gravPos];
			float gravy = sim->gravy[gravPos];
			if (gravx * gravx + gravy * gravy > 400)
			{
				if (RNG::Ref().chance(1, 5))
				{
					int j;
					sim->create_part(i, x, y, PT_BRMT);

					j = sim->create_part(-3, x, y, PT_NEUT);
					if (j != -1)
						parts[j].temp = NORMAL_MAX_TEMP;
					j = sim->create_part(-3, x, y, PT_PHOT);
					if (j != -1)
					{
						parts[j].temp = NORMAL_MAX_TEMP;
						parts[j].tmp = 0x1;
					}
					rx = x + RNG::Ref().between(-1, 1), ry = y + RNG::Ref().between(-1, 1), r = TYP(pmap[ry][rx]);
					if (sim->can_move[PT_PLSM][r] || r == PT_O2)
					{
						j = sim->create_part(-3, rx, ry, PT_PLSM);
						if (j > -1)
						{
							parts[j].temp = NORMAL_MAX_TEMP;
							parts[j].tmp |= 4;
						}
					}
					j = sim->create_part(-3, x, y, PT_GRVT);
					if (j != -1)
						parts[j].temp = NORMAL_MAX_TEMP;
					parts[i].temp = NORMAL_MAX_TEMP;
					sim->pv[y / CELL][x / CELL] = 256;
				}
			}
		}
	}

	return 0;
}
static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	sim->parts[i].oxygens = RNG::Ref().between(50, 100) * 2;
	sim->parts[i].tmpcity[7] = 400;
}
