#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static const int COLOR_FRAMES = 300;

void Element::Element_HCL() {
	Identifier = "DEFAULT_PT_HCL";
	Name = "HCL";
	Colour = PIXPACK(0xF05000);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 31;
	HeatConduct = 74;
	Description = "Hydrochloric acid. Acid used by the stomach.";

	Properties = TYPE_LIQUID ;

	DefaultProperties.water = 40;
	DefaultProperties.tmpcity[7] = 500;


	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 255.15f;//273.15f - 42.0f;
	LowTemperatureTransition = NT;
	HighTemperature = 376.15f;//273.15f + 108.0f;
	HighTemperatureTransition = NT;

	


	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS) {
	/**
	 * Properties:
	 * life:  Dissolving power left?
	 * ctype: part dissolved
	 * tmp2:  Color timer ? 
	 * oxygens: oxygensdissolved
	 * carbons: nutrients dissolved
	 * hydrogens: waste dissolved
	 * water: dissolved
	 * tmp4: amount dissolved of ctype? probably
	 * tmpcity[6]: part dissolved when boiling or freezing
	 * tmpcity[7]: capacity for dissolving stuff
	 */
	int randtemp;
	int capacity = 0;
	if (parts[i].temp + sim->pv[y / CELL][x / CELL] < sim->elements[parts[i].type].LowTemperature) 
	{
		parts[i].tmpcity[6] = parts[i].ctype;
		parts[i].ctype = parts[i].type;
		sim->part_change_type(i, x, y, PT_ICEI);
		return 1;

	}
	if (parts[i].temp - sim->pv[y / CELL][x / CELL] > sim->elements[parts[i].type].HighTemperature)
	{
		parts[i].tmpcity[6] = parts[i].ctype;
		sim->part_change_type(i, x, y, parts[i].ctype);
		parts[sim->create_part(-3, x, y, parts[i].ctype)].tmp4 = parts[i].tmp4;
		parts[i].tmp4 = 0;
		parts[i].ctype = parts[i].type;
	//	sim->part_change_type(i, x, y, PT_WTRV);
		return 1;
	}
	//	if (parts[i].type == PT_ICEI)
	//		parts[i].ctype = PT_HCL;
	//	return 1;
	//}
	//else if (parts[i].temp > sim->elements[PT_HCL].HighTemperature) {
	//	parts[i].tmp2 = 0;
	//	parts[i].tmp = 1;
	//	sim->part_change_type(i, x, y, parts[i].ctype ? PT_BRKN : PT_WTRV);
	//	return 1;
	//}
	if (parts[i].tmp4 <= 0 && parts[i].ctype != 0)
		parts[i].ctype = 0;
	//if(parts[i].tmpcity[6] != 0)


	for (int ry = -1; ry <= 1; ry++)
		for (int rx = -1; rx <= 1; rx++)
		if (BOUNDS_CHECK && (rx || ry)) {
			int r = pmap[y + ry][x + rx];
			int partnum = 0;
			if (!r) continue;
			int rt = TYP(r);
			//int cap = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
			int rt2 = rt; 
			if (rt2 == PT_BRKN)
				rt2 = parts[ID(r)].ctype;
			if (rt2 == PT_ROCK)
				rt2 = parts[ID(r)].ctype;
			if (rt2 < 0 || rt2 > PT_NUM)
				rt2 = 0;
			bool rt_is_noble_metl = rt2 == PT_BRAS || rt2 == PT_PTNM || rt2 == PT_GOLD; //rt2 == PT_TIN || rt2 == PT_COPR || rt2 == PT_BRNZ ||
								 	

			// Base / acid neutralizes
			/*if ( rt == PT_SOAP || rt == PT_WATR || rt == PT_DSTW) {
				parts[i].life--;
				parts[i].temp += 0.5f;
				if (RNG::Ref().chance(1, 75))
					sim->kill_part(ID(r));
			}*/

			// stuff diffusion
			if (sim->elements[rt].Properties & PROP_WATER || rt == PT_BLOD || rt == PT_HCL || rt == PT_MILK) {

				

				if (rt == parts[i].type)
					partnum += 10;
				else
					partnum += 5;

				capacity = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
				if (RNG::Ref().chance(1, 8) && capacity + 2 < parts[i].tmpcity[7])
				{

					// take
					if (parts[i].tmp4 < parts[i].tmpcity[7] / 2 && parts[ID(r)].tmp4 > 0 && parts[i].tmp4 < parts[ID(r)].tmp4 && (parts[i].tmp4 == 0 || parts[ID(r)].ctype == parts[i].ctype) && RNG::Ref().chance(1, 60))
					{
						parts[i].tmp4 += std::min(20, parts[ID(r)].tmp4);
						parts[ID(r)].tmp4 -= std::min(20, parts[ID(r)].tmp4);
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
					if (parts[i].nitrogens < parts[i].tmpcity[7] / 2 && parts[ID(r)].nitrogens > 0  && parts[i].nitrogens < parts[ID(r)].nitrogens && RNG::Ref().chance(1, 6))
					{
						parts[i].nitrogens += std::min(partnum, parts[ID(r)].nitrogens);
						parts[ID(r)].nitrogens -= std::min(partnum, parts[ID(r)].nitrogens);

					}
					if (parts[i].water < parts[i].tmpcity[7] / 2 && parts[ID(r)].water > 0 && parts[i].water < parts[ID(r)].water && RNG::Ref().chance(1, 6))
					{
						parts[i].water += std::min(partnum, parts[ID(r)].water);
						parts[ID(r)].water -= std::min(partnum, parts[ID(r)].water);

					}

				}
				//give
				capacity = parts[ID(r)].tmp4 + parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
				if (RNG::Ref().chance(1, 8) && capacity + 2 < parts[ID(r)].tmpcity[7])
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
						if (parts[ID(r)].water < parts[ID(r)].tmpcity[7] / 2 && parts[i].water > 0 && parts[ID(r)].water < parts[i].water && RNG::Ref().chance(1, 6))
						{
							parts[ID(r)].water += std::min(partnum, parts[i].water);
							parts[i].water -= std::min(partnum, parts[i].water);

						}
					}
				
			
				}
				
			//	else if (parts[i].ctype && !parts[ID(r)].ctype)
				//	std::swap(parts[i].ctype, parts[ID(r)].ctype);
			//}
			// Dissolve








			if (!(sim->elements[rt].Properties & PROP_WATER) && rt != PT_CLNE && rt != PT_PCLN && rt != PT_ACID && rt != PT_HCL && rt != PT_CAUS && RNG::Ref().chance(1, 8))
			{
				capacity = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
				if (RNG::Ref().chance(1, restrict_flt(sim->elements[rt2].Hardness + parts[i].water - parts[i].temp, 1, MAX_TEMP)) && (parts[i].ctype == rt || parts[i].ctype == 0) && capacity < parts[i].tmpcity[7]) {
					if (sim->parts_avg(i, ID(r), PT_GLAS) != PT_GLAS) { // GLAS protects stuff from acid 
						if (rt_is_noble_metl)
							parts[i].ctype = rt2;
						if ((rt == PT_BRKN || rt == PT_LQUD) && parts[ID(r)].ctype != 0)
							rt = parts[ID(r)].ctype;


						if (((sim->elements[rt].Properties & PROP_EDIBLE || sim->elements[rt].Properties & PROP_ORGANISM || sim->elements[rt].Properties & PROP_ANIMAL || sim->elements[rt].Properties & TYPE_LIQUID || sim->elements[rt].Properties & TYPE_PART || (parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens != 0)) && rt != PT_STMH) && RNG::Ref().chance(1, 8))
						{
							if ((parts[ID(r)].hydrogens > 0 || parts[ID(r)].oxygens > 0 || parts[ID(r)].carbons > 0 || parts[ID(r)].nitrogens > 0 || parts[ID(r)].water > 0))// (rt == PT_FLSH || (rt == PT_BRKN && parts[ID(r)].ctype == PT_FLSH) )
							{
								parts[i].carbons += std::min(20, parts[ID(r)].carbons);
								parts[i].oxygens += std::min(20, parts[ID(r)].oxygens);
								parts[i].hydrogens += std::min(20, parts[ID(r)].hydrogens);
								parts[i].nitrogens += std::min(20, parts[ID(r)].nitrogens);
								parts[i].water += std::min(20, parts[ID(r)].water);
								parts[i].tmp4 += std::min(20, parts[ID(r)].tmp4);
								parts[ID(r)].carbons -= std::min(20, parts[ID(r)].carbons);
								parts[ID(r)].oxygens -= std::min(20, parts[ID(r)].oxygens);
								parts[ID(r)].hydrogens -= std::min(20, parts[ID(r)].hydrogens);
								parts[ID(r)].nitrogens -= std::min(20, parts[ID(r)].nitrogens);
								parts[ID(r)].water -= std::min(20, parts[ID(r)].water);
								parts[ID(r)].tmp4 -= std::min(20, parts[ID(r)].tmp4);
								parts[i].temp++;

								parts[i].ctype = rt;

								if (parts[ID(r)].hydrogens <= 0 && parts[ID(r)].oxygens <= 0 && parts[ID(r)].carbons <= 0 && parts[ID(r)].tmp4 <= 0 && parts[ID(r)].nitrogens <= 0 && parts[ID(r)].water <= 0)
								{
									parts[i].temp += parts[ID(r)].temp - 273.15;
									sim->kill_part(ID(r));

								}
							}
							if (parts[ID(r)].tmp4 > 0 && RNG::Ref().chance(1, 8))
							{
								parts[i].tmp4 += std::min(20, parts[ID(r)].tmp4);
								parts[ID(r)].tmp4 -= std::min(20, parts[ID(r)].tmp4);
								parts[i].ctype = rt;

							}



							//sim->better_do_move(i, x, y, parts[ID(r)].x, parts[ID(r)].y);
						//	sim->better_do_move(ID(r), parts[ID(r)].x, parts[ID(r)].y, x, y);
						//	std::swap(pmap[y][x], r);


						}

						//else
						//{

						//	parts[i].life--;
							//sim->kill_part(ID(r));


					}
				}
				}
					if (sim->NoWeightSwitching && sim->pmap_count[y][x]<2 && TYP(r) != parts[i].type && RNG::Ref().chance(1, 8) && (y > parts[ID(r)].y && RNG::Ref().chance(1, restrict_flt(sim->elements[i].Weight - pow(sim->elements[TYP(r)].Weight, 2) / 10.0f, 1, MAX_TEMP)) || y < parts[ID(r)].y && RNG::Ref().chance(1, 100)) && (sim->elements[TYP(r)].Properties & TYPE_PART || sim->elements[TYP(r)].Properties & TYPE_LIQUID) )
				 	sim->better_do_swap(i, x, y, ID(r), parts[ID(r)].x, parts[ID(r)].y);
			}

	//if (RNG::Ref().chance(1, 30))
		//parts[i].life--;

	//if (parts[i].life < 0)
	//	parts[i].life = 0;
	//if (parts[i].life == 0 && RNG::Ref().chance(1, 150)) {
	//	parts[i].tmp2 = 0;
	//	parts[i].tmp = 1;
	//	sim->part_change_type(i, x, y, parts[i].ctype ?  PT_BRKN : PT_CAUS);
	//	if (parts[i].type == PT_CAUS) {
	//		if (RNG::Ref().chance(1, 50))
	//			parts[i].life = 75; // keep CAUS alive
	//		else
	//			sim->part_change_type(i, x, y, parts[i].ctype ? PT_BRKN : PT_WATR);
	//	}
	//	return 1;
	//}
	//if (parts[i].tmp2 < COLOR_FRAMES)
		parts[i].tmpcity[2]++;

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS) {
	*pixel_mode |= PMODE_BLUR;
	//if (cpart->tmp2 >= COLOR_FRAMES)
	//	return 0;
	// Ease colors from water (2030D0) to F05000 (red)
	float ease = 1;//cpart->tmp2 * 1.0f / COLOR_FRAMES;
	*colr = 0x20 + (0xF0 - 0x20) * ease;
	*colg = 0x30 + (0x50 - 0x30) * ease;
	*colb = 0xD0 + (0x00 - 0xD0) * ease;

	return 0;
}
