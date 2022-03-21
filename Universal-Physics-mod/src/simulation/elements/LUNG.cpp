#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
int Element_FLSH_update(UPDATE_FUNC_ARGS);

void Element::Element_LUNG() {
	Identifier = "DEFAULT_PT_LUNG";
	Name = "LUNG";
	Colour = PIXPACK(0xd4aaab);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	HeatConduct = 104;
	Description = "Lungs. Absorbs O2 and releases CO2.";
	 
	Properties = TYPE_SOLID | PROP_NEUTPENETRATE | PROP_EDIBLE | PROP_ORGANISM | PROP_ANIMAL;

	DefaultProperties.carbons = 50;
	DefaultProperties.oxygens = 50;
	DefaultProperties.hydrogens = 10;
	DefaultProperties.water = 50;
	DefaultProperties.tmp3 = 100;
	DefaultProperties.tmp4 = 100;
	DefaultProperties.tmpcity[7] = 800;
	DefaultProperties.tmpcity[3] = 100;
	DefaultProperties.tmpcity[9] = 0;
	DefaultProperties.metabolism = 50;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS) {
	/**
	 * Properties
	 * oxygens:   Oxygen stored
	 * carbons:  Nutrients stored
	 * tmp2: Highest temperature
	 * hydrogens: waste
	 * pavg[0]: Type 0 = inside, 1 = skin, 2 = dead
	 * tmp3: health of part 0-100
	 * tmp4: energy stored for use
	 * tmpcity[8]:  != 0 breaks meat
	 * water: water needed for life
	 * tmpcity[7]: capacity for stuff
	 * 
                  	 */
	Element_FLSH_update(sim, i, x, y, surround_space, nt, parts, pmap);
	int capacity = 0;
	if (parts[i].pavg[0] != 2)
	{
	if (parts[i].oxygens > parts[i].tmpcity[7] / 2 && RNG::Ref().chance(1, 100))
		parts[i].tmpcity[5]++;
	if (parts[i].hydrogens > 50 && RNG::Ref().chance(1, 10))
		parts[i].tmpcity[6]++;


		int rx, ry, r, rt;
		for (ry = -1; ry < 2; ++ry)
		for (rx = -1; rx < 2; ++rx)
			
				if (BOUNDS_CHECK && (rx || ry)) {
					r = pmap[y + ry][x + rx];
					int partnum = 10;
					if (!r)
					{
						if(parts[i].tmpcity[6] > 0 && parts[i].hydrogens > 50 + 10 && RNG::Ref().chance(1, 8))
						{
							parts[sim->create_part(-1, x + rx, y + ry, PT_CO2)].tmp3 = std::min(100, parts[i].hydrogens - 10);
							parts[i].hydrogens -= std::min(100, parts[i].hydrogens - 10);
							parts[i].tmpcity[6]--;
						}
						if (parts[i].tmpcity[5] > 0 && parts[i].oxygens > 60 && RNG::Ref().chance(1, 8))
						{
							parts[sim->create_part(-1, x + rx, y + ry, PT_O2)].tmp3 = 50;
							parts[i].oxygens -= 50;
							parts[i].tmpcity[5]--;
						}

						continue;
					}
					rt = TYP(r);
					//	if (rt == PT_BRKN)
						//	rt = parts[ID(r)].ctype;

					if ((rt == PT_O2 || rt == PT_LO2 || rt == PT_WATR) && parts[i].oxygens < parts[i].tmpcity[7] / 2 && parts[ID(r)].oxygens > 0 && RNG::Ref().chance(1, 8)
						) {

						parts[i].oxygens += std::min(5, parts[ID(r)].oxygens);
						parts[ID(r)].oxygens -= std::min(5, parts[ID(r)].oxygens);
						//sim->kill_part(ID(r));
					}
					//int capacity = parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
					/*if ((rt == PT_BVSL || rt == PT_BLOD) && capacity < parts[ID(r)].tmpcity[7] && parts[ID(r)].oxygens < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens >= partnum + 10)
					{
						parts[ID(r)].oxygens += partnum;
						parts[i].oxygens -= partnum;
					}*/
				//	capacity = 0;

					//nerve signals
					if(rt == PT_LUNG && parts[i].tmpcity[5] > parts[ID(r)].tmpcity[5] && parts[i].tmpcity[5] > 0 && parts[ID(r)].tmpcity[5] < 2  && parts[ID(r)].pavg[0] != 2 && RNG::Ref().chance(1, 8))
					{
						parts[ID(r)].tmpcity[5]++;
						parts[i].tmpcity[5]--;
					}
					if (rt == PT_LUNG && parts[i].tmpcity[6] > parts[ID(r)].tmpcity[6] && parts[i].tmpcity[6] > 0 && parts[ID(r)].tmpcity[6] < 2 && parts[ID(r)].pavg[0] != 2 && RNG::Ref().chance(1, 8))
					{
						parts[ID(r)].tmpcity[6]++;
						parts[i].tmpcity[6]--;
					}
				/*	if (rt == PT_LUNG && parts[ID(r)].oxygens < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens >= partnum + 10 && parts[i].oxygens > parts[ID(r)].oxygens && RNG::Ref().chance(1, 8))
					{

						parts[ID(r)].oxygens += partnum;
						parts[i].oxygens -= partnum;

					}*/
					if (rt == PT_LUNG && parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 3 && parts[i].hydrogens >= 10 + 10 && parts[i].hydrogens > parts[ID(r)].hydrogens && RNG::Ref().chance(1, 8))
					{
						partnum += 10;

						parts[ID(r)].hydrogens += std::min(partnum, parts[i].hydrogens);
						parts[i].hydrogens -= std::min(partnum, parts[i].hydrogens);

					}




					// Consume food
				/*	if (rt == PT_PLNT || rt == PT_VINE || rt == PT_SEED || rt == PT_POTO ||
						rt == PT_SPDR || rt == PT_ANT || rt == PT_SUGR) {
						if (RNG::Ref().chance(1, 500)) {
							parts[i].tmp += 50;
							parts[i].tmp2 += 500;
							sim->kill_part(ID(r));
						}*/

				}

	}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS) {
	// Redden if oxygenated
	int red = std::min(20, cpart->oxygens / 10);
	*colr += red;
	*colg -= red;
	*colb -= red;

	// Cooking
	// Well done (Around 70 - 80 C)
	if (cpart->carbons > 273.15f + 40.0f) {
		float percent_fade = std::min(cpart->tmp2 - 273.15f, 80.0f) / 80.0f;
		percent_fade += ((abs(nx - ny) * (nx + ny) + nx) % 5) / 10.0f; // Noise

		*colr -= (*colr - 176) * percent_fade;
		*colg -= (*colg - 131) * percent_fade;
		*colb -= (*colb - 90) * percent_fade;

		// Grill lines
		if ((nx + ny) % 30 < 3) {
			*colr *= 0.9f, *colg *= 0.9f, *colb *= 0.9f;
		}
	}
	// Burnt (Above 110 C)
	if (cpart->tmp2 > 273.15f + 110.0f) {
		float m = 1.0f - std::min(cpart->tmp2 - 273.15f + 90.0f, 200.0f) / 200.0f;
		m = 0.2 + 0.8 * m; // Prevent 100% black
		*colr *= m, *colg *= m, *colb *= m;
	}
	// Blue when cold
	if (cpart->temp < 273 && cpart->tmp2 < 273.15f + 110.0f) {
		*colr -= (int)restrict_flt((273.15f-cpart->temp)/5,0,80);
		*colg += (int)restrict_flt((273.15f-cpart->temp)/4,0,40);
		*colb += (int)restrict_flt((273.15f-cpart->temp)/1.5,0,100);
	}

	return 0;
}
