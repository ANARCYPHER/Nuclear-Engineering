#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_WSTE() {
	Identifier = "DEFAULT_PT_WSTE";
	Name = "WSTE";
	Colour = PIXPACK(0x222222);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.1f;
	AirDrag = 0.03f * CFDS;
	AirLoss = 0.92f;
	Loss = 0.96f;
	Collision = -0.1f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 3;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;

	Weight = 60;

	HeatConduct = 60;
	Description = "Waste from living things.";

	Properties = TYPE_PART;

	DefaultProperties.water = 3;
	DefaultProperties.tmpcity[7] = 100;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	//DefaultProperties.water = 50;

	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS) {

	if (parts[i].water > 10 && parts[i].tmpcity[8] == 0)
	{

		parts[i].tmpcity[8] = 2;
		sim->part_change_type(i, x, y, PT_LQUD);

	}
	else if (parts[i].water < 10 && parts[i].tmpcity[8] != 0)
	{

		parts[i].tmpcity[8] = 0;
	}


	if (parts[i].temp > 50.0f + 273.15f
		&& RNG::Ref().chance(1, restrict_flt(10000 - parts[i].temp, 1, MAX_TEMP)) && surround_space > 0) {
		int wtrv = sim->create_part(-3, x, y, PT_WTRV);
		parts[wtrv].water = std::min(20, parts[i].water);
		parts[i].water -= std::min(20, parts[i].water);
	}


	//bctr do goin nutz
	if (RNG::Ref().chance(1, 50000)) {
		//sim->kill_part(i);
		int bctr = sim->create_part(-3, x, y, PT_BCTR);
		parts[bctr].ctype = (parts[i].ctype ^ (1 << RNG::Ref().between(0, 32))) ^ (1 << RNG::Ref().between(0, 32) ^ (1 << RNG::Ref().between(0, 32)));
		
		parts[bctr].water += std::min(parts[i].water, 10);
		parts[i].water -= std::min(parts[i].water, 10);
		return 1;
	}


		for (int ry = -1; ry <= 1; ry++)
			for (int rx = -1; rx <= 1; rx++)
				if (BOUNDS_CHECK && (rx || ry)) {
					int r = pmap[y + ry][x + rx];
					int capacity = 0;
					int partnum = 0;
					if (!r) continue;
					int rt = TYP(r);




					if (sim->elements[rt].Properties & PROP_WATER || rt == PT_WSTE) {



						if (rt == parts[i].type)
							partnum += 2;
						else
							partnum += 1;

						capacity = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
						if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
						{

							// take
							if (parts[i].tmpcity[8] == 2)
							{
								if (parts[i].tmp4 < parts[i].tmpcity[7] / 2 && parts[ID(r)].tmp4 > 0 && parts[i].tmp4 < parts[ID(r)].tmp4 && (parts[i].tmp4 <= 0 || parts[ID(r)].ctype == parts[i].ctype) && RNG::Ref().chance(1, 6))
								{
									parts[i].tmp4 += std::min(10, parts[ID(r)].tmp4);
									parts[ID(r)].tmp4 -= std::min(10, parts[ID(r)].tmp4);
									parts[i].ctype = parts[ID(r)].ctype;
								}
								if (parts[i].oxygens < parts[i].tmpcity[7] / 2 && parts[ID(r)].oxygens > 0 && parts[i].oxygens < parts[ID(r)].oxygens && RNG::Ref().chance(1, 6))
								{
									parts[i].oxygens += std::min(partnum, parts[ID(r)].oxygens);
									parts[ID(r)].oxygens -= std::min(partnum, parts[ID(r)].oxygens);
								}
								if (parts[i].carbons < parts[i].tmpcity[7] / 2 && parts[ID(r)].carbons > 0 && parts[i].carbons < parts[ID(r)].carbons && RNG::Ref().chance(1, 6))
								{
									parts[i].carbons += std::min(partnum, parts[ID(r)].carbons);
									parts[ID(r)].carbons -= std::min(partnum, parts[ID(r)].carbons);
								}
								if (parts[i].hydrogens < parts[i].tmpcity[7] / 2 && parts[ID(r)].hydrogens > 0 && parts[i].hydrogens < parts[ID(r)].hydrogens && RNG::Ref().chance(1, 6))
								{
									parts[i].hydrogens += std::min(partnum, parts[ID(r)].hydrogens);
									parts[ID(r)].hydrogens -= std::min(partnum, parts[ID(r)].hydrogens);
								}
								if (parts[i].nitrogens < parts[i].tmpcity[7] / 2 && parts[ID(r)].nitrogens > 0 && parts[i].nitrogens < parts[ID(r)].nitrogens && RNG::Ref().chance(1, 6))
								{
									parts[i].nitrogens += std::min(partnum, parts[ID(r)].nitrogens);
									parts[ID(r)].nitrogens -= std::min(partnum, parts[ID(r)].nitrogens);

								}
							}
							if (parts[i].water < parts[i].tmpcity[7] / 2 && parts[ID(r)].water > 0 && parts[i].water < parts[ID(r)].water && RNG::Ref().chance(1, 6))
							{
								parts[i].water += std::min(partnum, parts[ID(r)].water);
								parts[ID(r)].water -= std::min(partnum, parts[ID(r)].water);

							}

						}
						//give
						capacity = parts[ID(r)].tmp4 + parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
						if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[ID(r)].tmpcity[7])
						{

							if (parts[i].tmpcity[8] == 2)
							{
								if (parts[ID(r)].tmp4 < parts[ID(r)].tmpcity[7] / 2 && parts[i].tmp4 > parts[ID(r)].tmp4 && (parts[ID(r)].tmp4 == 0 || parts[i].ctype == parts[ID(r)].ctype) && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].tmp4 += std::min(10, parts[i].tmp4);
									parts[i].tmp4 -= std::min(10, parts[i].tmp4);
									parts[ID(r)].ctype = parts[i].ctype;
								}
								//((parts[ID(r)].tmp4 == 0 && parts[ID(r)].ctype == 0) || parts[ID(r)].ctype == parts[i].ctype)
								if (parts[ID(r)].oxygens < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens > 0 && parts[ID(r)].oxygens < parts[i].oxygens && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].oxygens += std::min(partnum, parts[i].oxygens);
									parts[i].oxygens -= std::min(partnum, parts[i].oxygens);
								}
								if (parts[ID(r)].carbons < parts[ID(r)].tmpcity[7] / 2 && parts[i].carbons > 0 && parts[ID(r)].carbons < parts[i].carbons && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].carbons += std::min(partnum, parts[i].carbons);
									parts[i].carbons -= std::min(partnum, parts[i].carbons);
								}
								if (parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 2 && parts[i].hydrogens > 0 && parts[ID(r)].hydrogens < parts[i].hydrogens && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].hydrogens += std::min(partnum, parts[i].hydrogens);
									parts[i].hydrogens -= std::min(partnum, parts[i].hydrogens);
								}
								if (parts[ID(r)].nitrogens < parts[ID(r)].tmpcity[7] / 2 && parts[i].nitrogens > 0 && parts[ID(r)].nitrogens < parts[i].nitrogens && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].nitrogens += std::min(partnum, parts[i].nitrogens);
									parts[i].nitrogens -= std::min(partnum, parts[i].nitrogens);

								}
							}
							if (parts[ID(r)].water < parts[ID(r)].tmpcity[7] / 2 && parts[i].water > 0 && parts[ID(r)].water < parts[i].water && RNG::Ref().chance(1, 6))
							{
								parts[ID(r)].water += std::min(partnum, parts[i].water);
								parts[i].water -= std::min(partnum, parts[i].water);

							}

						}

					}


				}

				
	

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS) {
	if (cpart->temp < 273.15f) {
		*colr += 273.15f - cpart->temp;
		*colg += 273.15f - cpart->temp;
		*colb += 273.15f - cpart->temp;
	}
	*colr *= 0.2f + 0.4f * cpart->oxygens / 100.0f;
	*colg *= 0.2f + 0.4f * cpart->hydrogens / 100.0f;
	*colb *= 0.2f + 0.4f * cpart->carbons + cpart->water / 100.0f;
	return 0;
}
