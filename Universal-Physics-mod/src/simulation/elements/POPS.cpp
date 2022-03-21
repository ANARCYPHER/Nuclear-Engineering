#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
int Element_FLSH_update(UPDATE_FUNC_ARGS);

void Element::Element_POPS() {
	Identifier = "DEFAULT_PT_POPS";
	Name = "POPS";
	Colour = PIXPACK(0xF4AE95);
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
HotAir = 0.000f * CFDS;
Falldown = 0;

Flammable = 10;
Explosive = 0;
Meltable = 0;
Hardness = 20;

Weight = 100;

HeatConduct = 104;
Description = "Poop shoot. Releases waste and exess stuff.";

Properties = TYPE_SOLID | PROP_NEUTPENETRATE | PROP_EDIBLE | PROP_ORGANISM | PROP_ANIMAL;

DefaultProperties.oxygens = 100;
DefaultProperties.carbons = 100;
DefaultProperties.hydrogens = 20;
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
	 * life:  Graphics
	 * oxygens:   Oxygen stored
	 * carbons:  Nutrients stored
	 * tmp2: Highest temperature
	 * tmp3: Type 0 = inside, 1 = skin, 2 = dead
	 * hydrogens: carbon dioxide & waste
	 * water: water for life
	 * tmpcity[7]: capacity for stuff
	 */
	Element_FLSH_update(sim, i, x, y, surround_space, nt, parts, pmap);
	//if (parts[i].pavg[0] == 1) // Override skin formation
	//	parts[i].pavg[0] = 0;
	if (parts[i].pavg[0] != 2) {




		int rx, ry, r, rt;
		//int capacity = 0;




		if (surround_space != 0 && parts[i].tmpcity[0] == 0)
			parts[i].tmpcity[0] = 1;
		if (surround_space == 0 && parts[i].tmpcity[0] == 1)
			parts[i].tmpcity[0] = 0;
		if (sim->timer % 500 == 0 && parts[i].tmpcity[5] > 0)
			parts[i].tmpcity[5]--;



		if (parts[i].tmpcity[5] < 3 && RNG::Ref().chance(1, 8) && (parts[i].hydrogens > parts[i].tmpcity[7] / 4 || parts[i].oxygens > parts[i].tmpcity[7] / 4 || parts[i].carbons > parts[i].tmpcity[7] / 4 || parts[i].water > parts[i].tmpcity[7] / 4 || parts[i].nitrogens > 30))
			parts[i].tmpcity[5]++;
			//	if (parts[i].hydrogens > parts[i].tmpcity[7] / 2)
				//{
		//}
				//if()

		


		for (ry = -1; ry < 2; ++ry)
			for (rx = -1; rx < 2; ++rx)
				if (BOUNDS_CHECK && (rx || ry)) {
					r = pmap[y + ry][x + rx];
					int partnum = 10;
					if (!r && parts[i].pavg[0] != 2 && parts[i].tmpcity[5] > 0 && RNG::Ref().chance(1, 8))
					{
						int wste = 0;
						int dawaste = 0;

						if (parts[i].hydrogens > 20 && parts[i].hydrogens > parts[i].tmpcity[7] / 6 && RNG::Ref().chance(1, 2))
						{
						/*	if (wste == 0 && )
							 wste = sim->create_part(-1, x + rx, y + ry, RNG::Ref().chance(1, 3) ? PT_WSTE : PT_WATR);*/
							dawaste++;
							


						}
						if (parts[i].carbons > 20 && parts[i].carbons > parts[i].tmpcity[7] / 4 && RNG::Ref().chance(1, 2))
						{
						/*	if (wste == 0)
								wste = sim->create_part(-1, x + rx, y + ry, RNG::Ref().chance(1, 3) ? PT_WSTE : PT_WATR);
							else if (parts[wste].hydrogens > 0)*/
							dawaste += 2;
							
						}

						 if (parts[i].oxygens > 20 && parts[i].oxygens > parts[i].tmpcity[7] / 4 && RNG::Ref().chance(1, 2))
						{
							// if (wste == 0)
							//	 wste = sim->create_part(-1, x + rx, y + ry, RNG::Ref().chance(1, 3) ? PT_WSTE : PT_WATR);
							 dawaste += 4;
						}
						 if (parts[i].nitrogens > 10 && RNG::Ref().chance(1, 5))
						{


							 dawaste += 8;

						/*	 if (wste == 0)
								 wste = sim->create_part(-1, x + rx, y + ry, RNG::Ref().chance(1, 3) ? PT_WSTE : PT_WATR);
							 parts[wste].nitrogens += 10;
							 parts[i].nitrogens -= 10;*/
						}
						if (parts[i].water > 20 && parts[i].water > parts[i].tmpcity[7] / 6 && RNG::Ref().chance(1, 2))
						{
							dawaste += 16;
						/*	if (wste == 0)
								wste = sim->create_part(-1, x + rx, y + ry, RNG::Ref().chance(1, 3) ? PT_WSTE : PT_WATR);
							parts[wste].water += 10;
							parts[i].water -= 10;*/
						}
						//if(wste != 0)
							



						switch(dawaste)
						{ 
						
						case 1:


					//	parts[wste].hydrogens += 10;
					//	parts[i].hydrogens -= 10;



					//	parts[i].tmpcity[5]--;
						break;
						case 2:
							wste = sim->create_part(-1, x + rx, y + ry, PT_CRBN);

							parts[wste].carbons += 10;
							parts[i].carbons -= 10;
							parts[i].tmpcity[5]--;
						break;
						case 3:
							wste = sim->create_part(-1, x + rx, y + ry, PT_WSTE);


							parts[wste].carbons += 10;
							parts[wste].hydrogens += 10;
							parts[i].carbons -= 10;
							parts[i].hydrogens -= 10;

							parts[i].tmpcity[5]--;
							break;
						case 4:


						//	parts[wste].oxygens += 10;
						//	parts[i].oxygens -= 10;
						//	parts[i].tmpcity[5]--;
						break;
						case 5:


						//	parts[i].tmpcity[5]--;
							break;
						case 6:

							wste = sim->create_part(-1, x + rx, y + ry, PT_GAS);
							parts[wste].carbons += 10;
							parts[wste].oxygens += 10;
							parts[i].carbons -= 10;
							parts[i].oxygens -= 10;
						



							parts[i].tmpcity[5]--;
							break;

						case 16:

							wste = sim->create_part(-1, x + rx, y + ry, PT_WATR);
							parts[wste].water += 10;
							parts[i].water -= 10;




							parts[i].tmpcity[5]--;
							break;

						case 18:

							wste = sim->create_part(-1, x + rx, y + ry, PT_OIL);
							parts[wste].carbons += 10;
							parts[wste].water += 10;
							parts[i].carbons -= 10;
							parts[i].water -= 10;




							parts[i].tmpcity[5]--;
							break;
						case 19:

							wste = sim->create_part(-1, x + rx, y + ry, PT_WSTE);
							parts[wste].carbons += 10;
							parts[wste].water += 10;
							parts[wste].hydrogens += 10;
							parts[i].carbons -= 10;
							parts[i].water -= 10;
							parts[i].hydrogens -= 10;




							parts[i].tmpcity[5]--;
							break;
						case 20:

							wste = sim->create_part(-1, x + rx, y + ry, PT_WATR);
							parts[wste].oxygens += 10;
							parts[wste].water += 10;
							parts[i].oxygens -= 10;
							parts[i].water -= 10;




							parts[i].tmpcity[5]--;
							break;

						case 22:

							wste = sim->create_part(-1, x + rx, y + ry, PT_DESL);
							parts[wste].carbons += 10;
							parts[wste].water += 10;
							parts[wste].oxygens += 10;
							parts[i].carbons -= 10;
							parts[i].water -= 10;
							parts[i].oxygens -= 10;




							parts[i].tmpcity[5]--;
							break;
						case 24:

							wste = sim->create_part(-1, x + rx, y + ry, PT_WSTE);
							parts[wste].nitrogens += 10;
							parts[wste].water += 10;
							parts[i].nitrogens -= 10;
							parts[i].water -= 10;




							parts[i].tmpcity[5]--;
							break;


						case 27:

							wste = sim->create_part(-1, x + rx, y + ry, PT_WSTE);
							parts[wste].nitrogens += 10;
							parts[wste].carbons += 10;
							parts[wste].hydrogens += 10;
							parts[wste].water += 10;
							parts[i].nitrogens -= 10;
							parts[i].carbons -= 10;
							parts[i].hydrogens -= 10;
							parts[i].water -= 10;




							parts[i].tmpcity[5]--;
							break;
						default:


							break;
						}




				//	parts[i].carbons > 20 && parts[i].hydrogens > 20 && parts[i].water > 20 &&
				//	sim->create_part(-1, x + rx, y + ry, PT_OIL);
				
					
					//parts[i].tmpcity[5\]--;
				}
				if (!r) continue;
				rt = TYP(r);
				if (rt == PT_BRKN)
					rt = parts[ID(r)].ctype;
				//if(sim->timer % 501 == 0 && sim->elements[rt].Properties & PROP_EDIBLE && parts[i].tmpcity[0] != 1)
				//	parts[i].tmpcity[0] = 1;

				if (rt == PT_POPS && parts[i].tmpcity[0] == 0 && parts[ID(r)].tmpcity[0] == 1)
					parts[i].tmpcity[0] = 2;
				//(sim->elements[rt].Properties & PROP_EDIBLE && parts[ID(r)].tmp4 > 0 && parts[i].tmpcity[0] == 1 && parts[i].tmpcity[1] == 0 && RNG::Ref().chance(1, 50))
				//if()
			//	{
			//		parts[i].tmpcity[1]++;
			//	}
			
				if (rt == PT_POPS && parts[i].tmpcity[5] > 0 && parts[i].tmpcity[5] > parts[ID(r)].tmpcity[5]  && parts[ID(r)].tmpcity[5] < 3 && ((parts[ID(r)].tmpcity[0] == 1 && RNG::Ref().chance(1, 2)) || (parts[ID(r)].tmpcity[0] == 2 && RNG::Ref().chance(1, 3)) || (parts[ID(r)].tmpcity[0] == 0 && RNG::Ref().chance(1, 10))))
				{
					parts[ID(r)].tmpcity[5]++;
					parts[i].tmpcity[5]--;
				}
			/*	if (rt == PT_POPS && parts[i].tmpcity[6] > 0 && parts[i].tmpcity[6] > parts[ID(r)].tmpcity[6] && ((parts[ID(r)].tmpcity[0] == 1 && RNG::Ref().chance(1, 2)) || (parts[ID(r)].tmpcity[0] == 2 && RNG::Ref().chance(1, 3)) || (parts[ID(r)].tmpcity[0] == 0 && RNG::Ref().chance(1, 10))))
				{
					parts[ID(r)].tmpcity[6]++;
					parts[i].tmpcity[6]--;
				}*/

				//if (rt == PT_BLOD || rt == PT_BVSL)
				//{
				//	partnum += 20;
				//	//int capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens;
				//	int capacity = parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
				//	if (parts[i].tmpcity[6] > 0 && RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
				//	{
				//		


				//		//give stuff blood
				//	if (parts[ID(r)].oxygens + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens >= partnum + 10 && parts[i].oxygens > parts[ID(r)].oxygens)
				//	{
				//		parts[ID(r)].oxygens += partnum;
				//		parts[i].oxygens -= partnum;

				//	}
				//	if (parts[ID(r)].carbons + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[i].carbons >= partnum + 10 && parts[i].carbons > parts[ID(r)].carbons)
				//	{
				//		parts[ID(r)].carbons += partnum;
				//		parts[i].carbons -= partnum;

				//	}

				//	if (parts[ID(r)].hydrogens + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[i].hydrogens >= partnum + 10 && parts[i].hydrogens > parts[ID(r)].hydrogens)
				//	{
				//		parts[ID(r)].hydrogens += partnum;
				//		parts[i].hydrogens -= partnum;

				//	}
				//	if (parts[ID(r)].water + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[i].water >= partnum + 10 && parts[i].water > parts[ID(r)].water)
				//	{
				//		parts[ID(r)].water += partnum;
				//		parts[i].water -= partnum;

				//	}
				//}
				//	capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;

				//	//take stuff blood
				//	if (parts[i].tmpcity[5] > 0 && RNG::Ref().chance(1, 8))
				//	{
				//		if (capacity + partnum < 300 && parts[i].oxygens + partnum < 300 && parts[ID(r)].oxygens >= partnum + 10 && parts[ID(r)].oxygens > parts[i].oxygens)
				//		{
				//			parts[i].oxygens += partnum;
				//			parts[ID(r)].oxygens -= partnum;

				//		}
				//		if (capacity + partnum < 300 && parts[i].carbons + partnum < 300 && parts[ID(r)].carbons >= partnum + 10 && parts[ID(r)].carbons > parts[i].carbons)
				//		{
				//			parts[i].carbons += partnum;
				//			parts[ID(r)].carbons -= partnum;

				//		}
				//		if (capacity + partnum < 300 && parts[i].hydrogens + partnum < 300 && parts[ID(r)].hydrogens >= partnum + 10 && parts[i].hydrogens < parts[ID(r)].hydrogens)
				//		{
				//			parts[i].hydrogens += partnum;
				//			parts[ID(r)].hydrogens -= partnum;

				//		}
				//	}
				//}
				/*if (rt == PT_HCL)
				{
					if (parts[ID(r)].tmp4 > 0 && parts[i].carbons < 290 && (sim->elements[parts[ID(r)].ctype].Properties & PROP_EDIBLE || sim->elements[parts[ID(r)].tmpcity[]].Properties))
					{

					
						if (parts[ID(r)].ctype == PT_SUGR || parts[ID(r)].ctype == PT_SWTR)
						{
							parts[i].carbons += std::min(15, parts[ID(r)].tmp4);
							parts[i].hydrogens += std::min(5, parts[ID(r)].tmp4);;
	
							parts[ID(r)].tmp4 -= std::min(20, parts[ID(r)].tmp4);;
						}
						else
						{
						parts[i].carbons += std::min(10, parts[ID(r)].tmp4);
						parts[ID(r)].tmp4 -= std::min(10, parts[ID(r)].tmp4);
						if (parts[ID(r)].carbons > 0)
						{
							parts[i].carbons += std::min(10, parts[ID(r)].carbons);
							parts[ID(r)].carbons -= std::min(10, parts[ID(r)].carbons);
							}
						if (parts[ID(r)].oxygens > 0)
						{
							parts[i].oxygens += std::min(10, parts[ID(r)].oxygens);
							parts[ID(r)].oxygens -= std::min(10, parts[ID(r)].oxygens);
						}
						if (parts[ID(r)].hydrogens > 0)
						{
							parts[i].hydrogens += std::min(10, parts[ID(r)].hydrogens);
							parts[ID(r)].hydrogens -= std::min(10, parts[ID(r)].hydrogens);
						}
						}
						if(parts[ID(r)].tmp4 <= 0 && parts[ID(r)].hydrogens <= 0 && parts[ID(r)].oxygens <= 0 && parts[ID(r)].carbons <= 0 && RNG::Ref().chance(1, 10))
							sim->kill_part(ID(r));
					
					}

				}*/
			}
	}

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS) {
	// Redden if oxygenated
	int red = std::min(20, cpart->oxygens / 10);
	*colr += cpart->tmpcity[5] * 50;
	*colg -= red;
	*colb -= cpart->tmpcity[0] * 255;

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
		*colr -= (int)restrict_flt((273-cpart->temp)/5,0,80);
		*colg += (int)restrict_flt((273-cpart->temp)/4,0,40);
		*colb += (int)restrict_flt((273-cpart->temp)/1.5,0,100);
	}

	return 0;
}
