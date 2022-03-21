#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
int Element_FLSH_update(UPDATE_FUNC_ARGS);


void Element::Element_BLOD() {
	Identifier = "DEFAULT_PT_BLOD";
	Name = "BLOD";
	Colour = PIXPACK(0xEB1515);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 65;

	DefaultProperties.tmp2 = 2;
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

	HeatConduct = 69;
	Description = "Blood. Stains particles, clots when exposed to air or when it's dry.";

	Properties = TYPE_LIQUID | PROP_NEUTPENETRATE | PROP_EDIBLE | PROP_ORGANISM | PROP_ANIMAL;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 273.15f;
	LowTemperatureTransition = NT;
	HighTemperature = 373.15f;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS) {


	/**
	 * Properties:
	 * carbons - nutrients
	 * oxygens - How much oxygen stored
	 * tmp - How many particles it can still stain
	 * tmp2 - Visocity, slowly increases randomly with contact to air
	 * tmp3 - How alive the blood is?
	 * tmp4: how much bloodish? to dissolve?
	 * hydrogens: carbon dioxide & waste
	 * nitrogen some stuff in blood
	 */

	// Boundng
	/*if (parts[i].oxygens < 0)
		parts[i].oxygens = 0;
	if (parts[i].oxygens > 100)
		parts[i].oxygens = 100;*/



if (parts[i].tmpcity[7] == 0)
	{
	parts[i].tmp2 = 2;
	parts[i].oxygens = 100;
	parts[i].carbons = 100;
	parts[i].hydrogens = 20;
	parts[i].water = 50;
	parts[i].tmp3 = 100;
	parts[i].tmp4 = 100;
	parts[i].tmpcity[7] = 1000;
	parts[i].tmpcity[3] = 100;
	parts[i].tmpcity[9] = 0;
	parts[i].metabolism = 50; 
	}
	




	// Freezing
	if (parts[i].temp - sim->pv[y / CELL][x / CELL] < 273.15f  && RNG::Ref().chance(1, restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, 100 + 273.15f))) {
		sim->part_change_type(i, x, y, PT_ICEI);
		parts[i].ctype = PT_BLOD;
		parts[i].dcolour = sim->elements[PT_BLOD].Colour + 0x77000000;
		return 0;
	}

	// Boiling
	if (parts[i].temp - sim->pv[y / CELL][x / CELL] > 273.15f + 100.0f && RNG::Ref().chance(restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, 200 + 273.15f), 200 + 273.15f)) {
		if (RNG::Ref().chance(1, 500))
			sim->part_change_type(i, x, y, PT_BRMT);
		else {
			sim->part_change_type(i, x, y, PT_WTRV);
			parts[i].dcolour = sim->elements[PT_BLOD].Colour + 0x44000000;
			parts[i].ctype = PT_BLOD;
		}
		return 0;
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

	}
	

	// Clotted blood is inert
	if (parts[i].tmp2 >= 150 + parts[i].water) {
		if (parts[i].pavg[0] != 2)
			parts[i].pavg[0];
		parts[i].vx = parts[i].vy = 0;
	}


	if (parts[i].tmp3 <= 0 && parts[i].pavg[0] != 2)
	{
		parts[i].pavg[0] = 2;
		parts[i].tmp3 = 0;
	}


	if (parts[i].pavg[0] != 2 && sim->timer % parts[i].metabolism == 0)
	{

		if (parts[i].oxygens > 0 && parts[i].carbons > 0 && parts[i].tmpcity[3] < 100 - 1)
		{
			parts[i].oxygens--;

			parts[i].carbons--;


			parts[i].hydrogens++;
			parts[i].tmpcity[3] += 2;

			if (RNG::Ref().chance(1, 10))

				parts[i].temp++;



			//temporary healing
			if (RNG::Ref().chance(1, 1000) && parts[i].tmp3 < 100)

				parts[i].tmp3++;


		}
		else if (parts[i].tmpcity[3] > 0 && parts[i].water > 0)
		{
			parts[i].tmpcity[3]--;

			if (RNG::Ref().chance(1, 10))
				parts[i].temp++;
			if (RNG::Ref().chance(1, 20))
			{

				parts[i].water--;
				parts[i].nitrogens++;
			}
		}
		else
		{
			parts[i].tmp3--;
		}


	}
	// Rot if dead and not frozem - gotta love the typo
	if (parts[i].temp > 3.0f + 273.15f && parts[i].pavg[0] == 2
		&& RNG::Ref().chance(1, 10000 / (surround_space + 1))) {
		if (RNG::Ref().chance(1, 20))
		{
			//parts[i].life = 110;
			int bctr = sim->create_part(-3, x, y, PT_BCTR);
			parts[bctr].ctype = RNG::Ref().chance(1, 8) ? (parts[i].ctype ^ (1 << RNG::Ref().between(0, 32))) : (512 ^ (1 << RNG::Ref().between(0, 32))); // 512 Meat eating gene
			parts[bctr].tmp = 0;
			parts[bctr].tmp2 = 0;
			parts[bctr].tmp3 = 420;
			parts[bctr].carbons += std::min(5, parts[i].carbons);
			parts[bctr].oxygens += std::min(5, parts[i].oxygens);
			parts[bctr].water += std::min(5, parts[i].water);
			parts[i].carbons -= std::min(5, parts[i].carbons);
			parts[i].oxygens -= std::min(5, parts[i].oxygens);
			parts[i].water -= std::min(5, parts[i].water);
			parts[i].tmp4 -= 20;
			//parts[i].life = 110;
			return 1;
		}

	}


	if (parts[i].pavg[0] != 2)
	{


		// Death
	// Radiation burns
		int r = sim->photons[y][x];
		if (r) {

			if (parts[ID(r)].temp > 273.15f + 110.0f)
			{
				parts[i].tmp2 += 10;
				parts[i].tmp3--;

			}
		}

		// Pressure
		if (fabs(sim->pv[y / CELL][x / CELL]) > 10.0f)
		{
			parts[i].tmp3--;

		}
		// Temperature
		if ((parts[i].temp < 273.15f - 5.0f || parts[i].temp > 50.0f + 273.15f) && RNG::Ref().chance(1, 10))
			parts[i].tmp3--;
	
	}
	int rx, ry, r, rt;
	unsigned int newcolor;
	for (rx = -1; rx <= 1; ++rx)
		for (ry = -1; ry <= 1; ++ry)
			if (BOUNDS_CHECK && (rx || ry)) {
				r = pmap[y + ry][x + rx];
				rt = TYP(r);
				int capacity, partnum = 0;
			//	if (rt == PT_SOAP && RNG::Ref().chance(1, 100)) {
					//sim->kill_part(i);
				//	continue;
				//}

				// Clotted blood has none of these updates
			/*	if (parts[i].tmp2 >= CLOT)
					continue;*/

				if (!r && parts[i].tmp2 < 150 + parts[i].water) {
					// Random visocity increase if not moving fast and minimal pressure
					if (fabs(parts[i].vx) < 0.1f && fabs(parts[i].vy) < 0.1f &&
							fabs(sim->pv[y / CELL][x / CELL]) < 1.0f)
						parts[i].tmp2 += RNG::Ref().between(1, 7 *restrict_flt(parts[i].pavg[0], 1, MAX_TEMP));
					continue;
				}
				//else if(!r && )
				else if (!r)
					continue;
				
				if (parts[i].pavg[0] != 2)
				{
					// Oxygenate
					//if (rt == PT_O2 && parts[i].oxygens < 100) {
					//	parts[i].oxygens += 10;
					//	parts[ID(r)].oxygens -= 10;
						//sim->kill_part(ID(r));
				//	}
					if (sqrtf(parts[ID(r)].vx * parts[ID(r)].vx + parts[ID(r)].vy * parts[ID(r)].vy) > 8.0f)
					{
					//	if (sqrtf(parts[ID(r)].vx * parts[ID(r)].vx + parts[ID(r)].vy * parts[ID(r)].vy) > parts[i].tmp3)
					//		parts[i].tmpcity[8] = 1;
						parts[i].tmp3 -= sqrtf(parts[ID(r)].vx * parts[ID(r)].vx + parts[ID(r)].vy * parts[ID(r)].vy);

					}
						// Distribute nutrients
						if (sim->elements[rt].Properties & PROP_ANIMAL && parts[ID(r)].pavg[0] != 2)
						{
							if (rt == PT_BVSL || rt == PT_BLOD)
								partnum += 60;
							else
								partnum += 30;

							
							//take
							capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
							if (RNG::Ref().chance(1, 8) && capacity + 10 < parts[i].tmpcity[7])
							{


								if (parts[i].oxygens < parts[i].tmpcity[7] / 3 && parts[ID(r)].oxygens >= 10 + 10 && parts[i].oxygens < parts[ID(r)].oxygens)
								{
									parts[i].oxygens += std::min(partnum, parts[ID(r)].oxygens - 10);
									parts[ID(r)].oxygens -= std::min(partnum, parts[ID(r)].oxygens - 10);
								}
								if (parts[i].carbons < parts[i].tmpcity[7] / 3 && parts[ID(r)].carbons >= 10 + 10 && parts[i].carbons < parts[ID(r)].carbons)
								{
									parts[i].carbons += std::min(partnum, parts[ID(r)].carbons - 10);
									parts[ID(r)].carbons -= std::min(partnum, parts[ID(r)].carbons - 10);
								}
								if (parts[i].hydrogens < parts[i].tmpcity[7] / 3 && parts[ID(r)].hydrogens >= 10 + 10 && parts[i].hydrogens < parts[ID(r)].hydrogens)
								{
									parts[i].hydrogens += std::min(partnum, parts[ID(r)].hydrogens - 10);
									parts[ID(r)].hydrogens -= std::min(partnum, parts[ID(r)].hydrogens - 10);
								}
								if (parts[i].nitrogens < parts[i].tmpcity[7] / 3 && parts[ID(r)].nitrogens >= 10 + 10 && parts[i].nitrogens < parts[ID(r)].nitrogens)
								{
									parts[i].nitrogens += std::min(partnum, parts[ID(r)].nitrogens - 10);
									parts[ID(r)].nitrogens -= std::min(partnum, parts[ID(r)].nitrogens - 10);

								}
								if (parts[i].water < parts[i].tmpcity[7] / 3 && parts[ID(r)].water >= 10 + 10 && parts[i].water < parts[ID(r)].water)
								{
									parts[i].water += std::min(partnum, parts[ID(r)].water - 10);
									parts[ID(r)].water -= std::min(partnum, parts[ID(r)].water - 10);

								}

							}
							//give
							capacity = parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
							if (RNG::Ref().chance(1, 8) && capacity + 10 < parts[ID(r)].tmpcity[7])
							{

								if (parts[ID(r)].oxygens < parts[ID(r)].tmpcity[7] / 3 && parts[i].oxygens >= 10 + 10 && parts[ID(r)].oxygens < parts[i].oxygens)
								{
									parts[ID(r)].oxygens += std::min(partnum, parts[i].oxygens - 10);
									parts[i].oxygens -= std::min(partnum, parts[i].oxygens - 10);
								}
								if (parts[ID(r)].carbons < parts[ID(r)].tmpcity[7] / 3 && parts[i].carbons >= 10 + 10 && parts[ID(r)].carbons < parts[i].carbons)
								{
									parts[ID(r)].carbons += std::min(partnum, parts[i].carbons - 10);
									parts[i].carbons -= std::min(partnum, parts[i].carbons - 10);
								}
								if (parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 3 && parts[i].hydrogens >= 10 + 10 && parts[ID(r)].hydrogens < parts[i].hydrogens)
								{
									parts[ID(r)].hydrogens += std::min(partnum, parts[i].hydrogens - 10);
									parts[i].hydrogens -= std::min(partnum, parts[i].hydrogens - 10);
								}
								if (parts[ID(r)].nitrogens < parts[ID(r)].tmpcity[7] / 3 && parts[i].nitrogens >= 10 + 10 && parts[ID(r)].nitrogens < parts[i].nitrogens)
								{
									parts[ID(r)].nitrogens += std::min(partnum, parts[i].nitrogens - 10);
									parts[i].nitrogens -= std::min(partnum, parts[i].nitrogens - 10);

								}
								if (parts[ID(r)].water < parts[ID(r)].tmpcity[7] / 3 && parts[i].water >= 10 + 10 && parts[ID(r)].water < parts[i].water)
								{
									parts[ID(r)].water += std::min(partnum, parts[i].water - 10);
									parts[i].water -= std::min(partnum, parts[i].water - 10);

								}
							}
						}



				//	if (rt == PT_FLSH || rt == PT_STMH || rt == PT_UDDR || rt == PT_LUNG || rt == PT_POPS)
				//	{
				//		capacity = parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
				//		if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[ID(r)].tmpcity[7])
				//		{

				//			//give stuff
				//			if (parts[ID(r)].oxygens + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens >= partnum + 10 && parts[i].oxygens > parts[ID(r)].oxygens)
				//			{
				//				parts[ID(r)].oxygens += partnum;
				//				parts[i].oxygens -= partnum;

				//			}
				//			if (parts[ID(r)].carbons < parts[ID(r)].tmpcity[7] / 2 && parts[i].carbons >= partnum + 10 && parts[i].carbons > parts[ID(r)].carbons)
				//			{
				//				parts[ID(r)].carbons += partnum;
				//				parts[i].carbons -= partnum;

				//			}

				//			if (((parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 5 && rt != PT_LUNG) || (parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 2 && rt == PT_LUNG)) && parts[i].hydrogens >= partnum + 10 && parts[i].hydrogens > parts[ID(r)].hydrogens)
				//			{
				//				parts[ID(r)].hydrogens += partnum;
				//				parts[i].hydrogens -= partnum;
				//			}
				//			if (parts[ID(r)].water < parts[ID(r)].tmpcity[7] / 3 && parts[i].water >= partnum + 10 && parts[i].water > parts[ID(r)].water)
				//			{
				//				parts[ID(r)].water += partnum;
				//				parts[i].water -= partnum;

				//			}
				//			////give carbon waste to lungs
				//			//else if (parts[ID(r)].hydrogens < parts[ID(r)].tmpcity[7] / 2 && parts[i].hydrogens >= partnum && parts[i].hydrogens > parts[ID(r)].hydrogens && rt == PT_LUNG)
				//			//{
				//			//	parts[ID(r)].hydrogens += partnum;
				//			//	parts[i].hydrogens -= partnum;

				//			//}



				//		}


				//		capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
				//		if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
				//		{

				//			//take stuff
				//			if (parts[i].carbons + partnum < parts[i].tmpcity[7] / 2 && parts[ID(r)].oxygens >= partnum + 10 && parts[ID(r)].oxygens > parts[i].oxygens)
				//			{
				//				parts[i].oxygens += partnum;
				//				parts[ID(r)].oxygens -= partnum;

				//			}
				//			if (parts[i].carbons + partnum < parts[i].tmpcity[7] / 2 && parts[ID(r)].carbons >= partnum + 10 && parts[ID(r)].carbons > parts[i].carbons)
				//			{
				//				parts[i].carbons += partnum;
				//				parts[ID(r)].carbons -= partnum;

				//			}
				//			if (((rt == PT_LUNG && parts[ID(r)].hydrogens > parts[i].tmpcity[7] / 2 && parts[i].hydrogens + partnum < parts[i].tmpcity[7] / 3) || (rt != PT_LUNG && parts[i].hydrogens + partnum < parts[i].tmpcity[7] / 3)) && parts[ID(r)].hydrogens >= partnum + 10 && parts[ID(r)].hydrogens > parts[i].hydrogens)
				//			{
				//				parts[i].hydrogens += partnum;
				//				parts[ID(r)].hydrogens -= partnum;

				//			}
				//			if (parts[i].water + partnum < parts[i].tmpcity[7] / 3 && parts[ID(r)].water >= partnum + 10 && parts[ID(r)].water > parts[i].water)
				//			{
				//				parts[i].water += partnum;
				//				parts[ID(r)].water -= partnum;

				//			}
				//		}

				//	}


				//	else if (rt == PT_BLOD || rt == PT_BVSL)
				//	{

				//		partnum += 10;
				//		capacity = parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
				//		if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
				//		{


				//			//give stuff to blood
				//			if (parts[ID(r)].oxygens + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[i].oxygens >= partnum + 10 && parts[i].oxygens > parts[ID(r)].oxygens)
				//			{
				//				parts[ID(r)].oxygens += partnum;
				//				parts[i].oxygens -= partnum;

				//			}
				//			if (parts[ID(r)].carbons + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[i].carbons >= partnum + 10 && parts[i].carbons > parts[ID(r)].carbons)
				//			{
				//				parts[ID(r)].carbons += partnum;
				//				parts[i].carbons -= partnum;

				//			}

				//			if (parts[ID(r)].hydrogens + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[i].hydrogens >= partnum + 10 && parts[i].hydrogens > parts[ID(r)].hydrogens)
				//			{
				//				parts[ID(r)].hydrogens += partnum;
				//				parts[i].hydrogens -= partnum;

				//			}
				//			if (parts[ID(r)].water + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[i].water >= partnum + 10 && parts[i].water > parts[ID(r)].water)
				//			{
				//				parts[ID(r)].water += partnum;
				//				parts[i].water -= partnum;

				//			}
				//		}
				//		capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
				//		if (RNG::Ref().chance(1, 8) && capacity + partnum < parts[i].tmpcity[7])
				//		{


				//			//take stuff from blood
				//			if (parts[i].oxygens + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[ID(r)].oxygens >= partnum + 10 && parts[ID(r)].oxygens > parts[i].oxygens)
				//			{
				//				parts[i].oxygens += partnum;
				//				parts[ID(r)].oxygens -= partnum;

				//			}
				//			if (parts[i].carbons + partnum < parts[ID(r)].tmpcity[7] / 2 && parts[ID(r)].carbons >= partnum + 10 && parts[ID(r)].carbons > parts[i].carbons)
				//			{
				//				parts[i].carbons += partnum;
				//				parts[ID(r)].carbons -= partnum;

				//			}
				//			if (parts[i].hydrogens + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[ID(r)].hydrogens >= partnum && parts[ID(r)].hydrogens > parts[i].hydrogens)
				//			{
				//				parts[i].hydrogens += partnum;
				//				parts[ID(r)].hydrogens -= partnum;

				//			}
				//			if (parts[i].water + partnum < parts[ID(r)].tmpcity[7] / 3 && parts[ID(r)].water >= partnum && parts[ID(r)].water > parts[i].water)
				//			{
				//				parts[i].water += partnum;



				//				parts[ID(r)].water -= partnum;

				//			}
				//		}

					
				}











				//	parts[i].oxygens = (parts[ID(r)].oxygens + parts[i].oxygens + 1) / 2;
					//parts[ID(r)].oxygens = parts[i].oxygens;
				
				// Stain powders and solids
				 if (rt != PT_ICEI && rt != PT_SNOW && rt != PT_BIZRS && RNG::Ref().chance(1, 8) &&
						(sim->elements[rt].Properties & TYPE_PART || sim->elements[rt].Properties & TYPE_SOLID)) {
					newcolor = 0xFF000000 + sim->elements[PT_BLOD].Colour;
					if (parts[ID(r)].dcolour != newcolor && parts[i].tmp > 0) {
						--parts[i].tmp;
						parts[ID(r)].dcolour = newcolor;
					}
				}
				// Stain liquids
				// Liquids get stained more, but in a diluted color
				 if (rt != PT_BLOD && rt != PT_SOAP && rt != PT_MILK && rt != PT_BIZR && !(sim->elements[rt].Properties & PROP_WATER) && sim->elements[rt].Properties & TYPE_LIQUID && RNG::Ref().chance(1, 8)) {
					if (parts[i].tmp > 0) {
						newcolor = 0xAA000000 + sim->elements[PT_BLOD].Colour;
						if (parts[ID(r)].dcolour != newcolor && RNG::Ref().chance(1, 8)) {
							--parts[i].tmp;
							parts[ID(r)].dcolour = newcolor;
						}
					}
				}
				 if ((sim->elements[rt].Properties & PROP_WATER || rt == PT_MILK) && RNG::Ref().chance(1, 40))
				 {
					 if (parts[ID(r)].tmpville[5] < 60 && RNG::Ref().chance(1, 8))
						 //&& parts[ID(r)].tmpville[5] < 60
						 parts[ID(r)].tmpville[5] += RNG::Ref().between(10, 40);

					 if(parts[ID(r)].tmpville[7] > -60 && RNG::Ref().chance(1, 8))
						 parts[ID(r)].tmpville[7] -= RNG::Ref().between(10, 40);

				 }

				 if ((rt == PT_H2O2 || rt == PT_ACID || rt == PT_CAUS || rt == PT_PLUT || rt == PT_URAN ||
					 rt == PT_ISOZ || rt == PT_ISZS || rt == PT_POLO || rt == PT_MERC  || sim->elements[rt].Properties & PROP_DEADLY  ||  (rt == PT_HCL && parts[i].type != PT_STMH)) && parts[i].pavg[0] != 2 && RNG::Ref().chance(1, 20)) 
					 parts[i].tmp3--;
				// Chance to kill VIRS
			//	else if (RNG::Ref().chance(1, 10) && (rt == PT_VIRS || rt == PT_VRSG || rt == PT_VRSS))
				//	sim->kill_part(ID(r));
				// Chance to kill BCTR
			//	else if (RNG::Ref().chance(1, 10) && rt == PT_BCTR)
			//		sim->kill_part(ID(r));
				 if ((sim->elements[TYP(r)].Properties & TYPE_PART ||
					 sim->elements[TYP(r)].Properties & TYPE_SOLID) && RNG::Ref().chance(parts[i].tmp2, 5 + parts[i].water / 10))
					 parts[i].vx = parts[i].vy = 0;
						 if (sim->NoWeightSwitching && sim->pmap_count[y][x]<2 && TYP(r) != parts[i].type && RNG::Ref().chance(1, 8) && (y > parts[ID(r)].y && RNG::Ref().chance(1, restrict_flt(sim->elements[i].Weight - pow(sim->elements[TYP(r)].Weight, 2) / 10.0f, 1, MAX_TEMP)) || y < parts[ID(r)].y && RNG::Ref().chance(1, 100)) && (sim->elements[TYP(r)].Properties & TYPE_PART || sim->elements[TYP(r)].Properties & TYPE_LIQUID) && !(sim->elements[TYP(r)].Properties & PROP_WATER|| TYP(r) == PT_HCL))
					 	sim->better_do_swap(i, x, y, ID(r), parts[ID(r)].x, parts[ID(r)].y);
			//if (rt == PT_BLOD && parts[i].tmpville[3] > 2 && parts[ID(r)].tmpville[3] > 2 && parts[i].tmpville[3] > parts[ID(r)].tmpville[3] && RNG::Ref().chance(1, 80))
			//{
			//	sim->better_do_swap(i, x, y, ID(r), parts[ID(r)].x, parts[ID(r)].y);
			//	return 1;
			//}
			}
			parts[i].tmpcity[9]++;
	return 0;

}

static int graphics(GRAPHICS_FUNC_ARGS) {
	if (cpart->tmp2 < 150 + cpart->water)
		*pixel_mode |= PMODE_BLUR;
	/**colr *= 0.2f + 0.8f * cpart->oxygens / 100.0f;
	*colg *= 0.2f + 0.8f * cpart->oxygens / 100.0f;
	*colb *= 0.2f + 0.8f * cpart->oxygens / 100.0f;*/
	*colr *= 0.2f + 0.4f * cpart->oxygens / 100.0f;
	*colg *= 0.2f + 0.4f * cpart->hydrogens / 100.0f;
	*colb *= 0.2f + 0.4f * cpart->carbons / 100.0f;


	return 0;
}
