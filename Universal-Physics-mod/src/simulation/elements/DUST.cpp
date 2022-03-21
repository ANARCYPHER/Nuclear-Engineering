#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_DUST()
{
	Identifier = "DEFAULT_PT_DUST";
	Name = "DUST";
	Colour = PIXPACK(0xFFE0A0);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 3;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;
	PhotonReflectWavelengths = 0x3FFFFFC0;

	Weight = 85;

	HeatConduct = 20;
	Description = "Very light dust. Flammable, edible for some reason.";

	Properties = TYPE_PART | PROP_EDIBLE;
	

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;

	Graphics = NULL; // it this needed?
}

static int update(UPDATE_FUNC_ARGS) 
{

	if(parts[i].tmpcity[7] == 0 && parts[i].tmp4 == 0)
	{
	parts[i].tmpcity[7] = 400;
	parts[i].tmp4 = 1;
	}
	if(parts[i].ctype + parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].nitrogens + parts[i].water == 0)
		sim->kill_part(i);
	if(parts[i].water > 5)
	sim->part_change_type(i, x, y, PT_WATR);

	if(parts[i].ctype == parts[i].type)
	parts[i].ctype = 0;
	if(parts[i].ctype > 0 && parts[i].tmp4 > 0)
	sim->part_change_type(i, x, y, parts[i].ctype);
	// switch(parts[i].ctype)
	// {
	// 	case PT_SALT:
	// 	sim->part_change_type(i, x, y, PT_SALT);
	// 	break;
	// 	case PT_SUGR:
	// 	sim->part_change_type(i, x, y, PT_SUGR);
	// 	break;
	// }

	int r, rx, ry;
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
			}

	return 0;
}
