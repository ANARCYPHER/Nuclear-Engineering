#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_SUGR() {
	Identifier = "DEFAULT_PT_SUGR";
	Name = "SUGR";
	Colour = PIXPACK(0xFFF9F2);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 20;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;
	Description = "Sugar. Great food for bacteria.";

	Properties = TYPE_PART | PROP_NEUTPASS | PROP_EDIBLE;

	DefaultProperties.tmpcity[7] = 400;
	DefaultProperties.tmp4 = 150;
	DefaultProperties.carbons = 100;
	DefaultProperties.oxygens = 10;
	DefaultProperties.hydrogens = 20;
	DefaultProperties.nitrogens = 20;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 273.15f + 186.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS) {

	/**
 * Properties
 * tmp4:  amount of matter
 */
	


if (parts[i].tmpcity[7] == 0)
	{
	parts[i].tmpcity[7] = 400;
	parts[i].tmp4 = 100;
	parts[i].carbons = 100;
	parts[i].oxygens = 10;
	parts[i].hydrogens = 20;
	parts[i].nitrogens = 20;
	}


	if (parts[i].tmp4 <= 0)
	{
		if (parts[i].oxygens > 0 || parts[i].carbons > 0 || parts[i].hydrogens > 0 || parts[i].water > 0 || parts[i].nitrogens > 0)
		{
			if (parts[i].water > 0)
				sim->part_change_type(i, x, y, PT_WATR);
			else
				sim->part_change_type(i, x, y, PT_DUST);
				
		}
		else
			sim->kill_part(i);
		return 0;

	}


	if(parts[i].water > 5)
	{
	parts[i].ctype = PT_SUGR;
	sim->part_change_type(i, x, y, PT_SWTR);
	}
	


	int r, rx, ry;

	r = sim->photons[y][x];
	
	// React with NEUT to make carbon, hydrogen, oxygen
	if (TYP(r) == PT_NEUT && RNG::Ref().chance(1, 20)) {
		sim->kill_part(ID(r));
		if (RNG::Ref().chance(1, 3))
			sim->part_change_type(i, x, y, PT_CRBN);
		else
			sim->part_change_type(i, x, y, RNG::Ref().chance(1, 2) ? PT_O2 : PT_H2);
		return 0;
	}



	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry)) {
				r = pmap[y+ry][x+rx];
				int capacity = 0;
				int partnum = 0;
				if (!r) 
				{
				if(parts[i].temp > 373.15f && parts[i].water > 0)
				{
				parts[sim->create_part(-1, x + rx, y + ry, PT_WTRV)].water = parts[i].water;
					parts[i].water = 0;
				}
				continue;
				}
				int rt = TYP(r);
				// Dissolve
				// if (sim->elements[rt].Properties & PROP_WATER) {
				// 	//sim->part_change_type(i, x, y, PT_SWTR);
				// 	//	sim->kill_part(ID(r));
				// 	return 0;
				// }

					if (sim->elements[rt].Properties & PROP_WATER || rt == parts[i].type) {



						if (rt == parts[i].type)
							partnum += 1;
						else
							partnum += 2;

						capacity = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
						if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
						{

							// take

							if (parts[i].water < parts[i].tmpcity[7] / 2 && parts[ID(r)].water > 0 && parts[i].water < parts[ID(r)].water && RNG::Ref().chance(1, 6))
							{
								parts[i].water += std::min(partnum, parts[ID(r)].water);
								parts[ID(r)].water -= std::min(partnum, parts[ID(r)].water);

							}
						}
						capacity = parts[ID(r)].tmp4 + parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
						if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[ID(r)].tmpcity[7] && rt == parts[i].type)
						{

							if (parts[ID(r)].water < parts[ID(r)].tmpcity[7] / 2 && parts[i].water > 0 && parts[ID(r)].water < parts[i].water && RNG::Ref().chance(1, 6))
							{
								parts[ID(r)].water += std::min(partnum, parts[i].water);
								parts[i].water -= std::min(partnum, parts[i].water);

							}

						}
						//give


						}

				// Grow YEST

				else if (TYP(r) == PT_YEST && RNG::Ref().chance(1, 300)) {
					sim->part_change_type(i, parts[i].x, parts[i].y, PT_YEST);
					return 0;
				}

				// React with acid to form carbon
				else if (TYP(r) == PT_ACID || TYP(r) == PT_CAUS) {
					parts[i].temp += 120.0f;
					sim->part_change_type(ID(r), parts[ID(r)].x, parts[ID(r)].y,
						RNG::Ref().chance(1, 2) ? PT_CRBN : PT_WTRV);
					if (RNG::Ref().chance(1, 2))
						sim->kill_part(i);
					return 0;
				}
			} 
	return 0;
}
