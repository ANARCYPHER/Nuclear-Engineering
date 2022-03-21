#include "simulation/ElementCommon.h"

int Element_WATR_update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_WATR()
{
	Identifier = "DEFAULT_PT_WATR";
	Name = "WATR";
	Colour = PIXPACK(0x2030D0);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.1f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Water. Conducts electricity, freezes, essencial for life.";

	Properties = TYPE_LIQUID|PROP_CONDUCTS| PROP_WATER;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 273.15f;
	LowTemperatureTransition = PT_ICEI;
	HighTemperature = 373.15f;
	HighTemperatureTransition = PT_WTRV;

	Update = &Element_WATR_update;
	Graphics = &graphics;
}

int Element_WATR_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].tmpcity[7] == 0 && parts[i].water == 0 && sim->elements[parts[i].type].Properties & PROP_WATER)
	{
		if(parts[i].water > 0)
			parts[i].tmpcity[7] = 400;
		else
		{
			switch (parts[i].type)
			{
			case PT_DSTW:
			case PT_WTRV:
			case PT_WATR:
				parts[i].water = 75;
				parts[i].tmpcity[7] = 400;
				break;

			case PT_CBNW:
				parts[i].water = 10;
				parts[i].tmp4 = 100;
				parts[i].ctype = PT_CO2;
				parts[i].tmpcity[7] = 400;

			break;
			case PT_SLTW:
				parts[i].water = 75;
				parts[i].tmp4 = 50;
				parts[i].ctype = PT_SALT;
				parts[i].tmpcity[7] = 400;
				break;

			case PT_SWTR:
				parts[i].water = 75;
				parts[i].tmp4 = 50;
				parts[i].carbons = 100;
				parts[i].hydrogens = 15;
				parts[i].nitrogens = 5;
				parts[i].ctype = PT_SUGR;
				parts[i].tmpcity[7] = 400;
				
				break;
			case PT_H2O2:
					parts[i].water = 75;
					parts[i].oxygens = 100;
					parts[i].tmpcity[7] = 400;

					break;


			default:
				parts[i].water = 75;
				parts[i].tmpcity[7] = 400;
				break;

			}
		}
	}



	if (parts[i].ctype == parts[i].type)
		parts[i].ctype = 0;
	//if(parts[i].water <= 0 && parts[i].ctype != 0)
	//	sim->part_change_type(i, x, y, parts[i].ctype);
//	if(parts[i].hydrogens <= 0 && parts[i].oxygens <= 0 && parts[i].carbons <= 0 && parts[i].tmp4 <= 0 && parts[i].nitrogens <= 0 && parts[i].water <= 0 && parts[i].ctype == 0)
	//	sim->kill_part(i);
	if (parts[i].ctype != 0 && parts[i].tmp4 <= 0)
		parts[i].ctype = 0;
	if (parts[i].ctype == 0 && parts[i].tmp4 > 0 && parts[i].type == PT_WATR)
		parts[i].tmp4 = 0;

	if (parts[i].tmp4 <= 0 && parts[i].water > 0 && parts[i].type != PT_WATR && parts[i].type != PT_H2O2)
		sim->part_change_type(i, x, y, PT_WATR);
	else if (parts[i].water <= 0 && parts[i].type != PT_H2O2)
		{
		if(parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].nitrogens + parts[i].tmp4 != 0)
		sim->part_change_type(i, x, y, PT_DUST);
		else if(parts[i].tmp4 > 0 && parts[i].ctype != 0)
		sim->part_change_type(i, x, y, parts[i].ctype);
		else
		 sim->kill_part(i);
		}

	// Freezing

	
	if ((sim->elements[parts[i].type].LowTemperature > 0 && parts[i].temp - (sim->pv[y / CELL][x / CELL] / 2) < sim->elements[parts[i].type].LowTemperature  && RNG::Ref().chance(1, restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, sim->elements[parts[i].type].LowTemperature))) ||
	 (sim->elements[parts[i].type].LowTemperature <= 0 && parts[i].temp - (sim->pv[y / CELL][x / CELL] / 2) < 273.15f  && RNG::Ref().chance(1, restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, 273.15f)))) 
	 {
	if(sim->elements[parts[i].type].LowTemperatureTransition > 0)
		sim->part_change_type(i, x, y, sim->elements[parts[i].type].LowTemperatureTransition);
	else
		sim->part_change_type(i, x, y, PT_ICEI);
	return 0;
	}


	// Boiling
	if ((sim->elements[parts[i].type].HighTemperature > 0 && parts[i].temp - (sim->pv[y / CELL][x / CELL] / 2) > sim->elements[parts[i].type].HighTemperature && RNG::Ref().chance(restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, sim->elements[parts[i].type].HighTemperature), sim->elements[parts[i].type].HighTemperature)) ||
	(sim->elements[parts[i].type].HighTemperature <= 0 && parts[i].temp - (sim->pv[y / CELL][x / CELL] / 2) > 373.15f && RNG::Ref().chance(restrict_flt(parts[i].temp - sim->pv[y / CELL][x / CELL], 1, 373.15f), 373.15f)))
	{
		switch(parts[i].type)

	if(sim->elements[parts[i].type].HighTemperatureTransition > 0)
			sim->part_change_type(i, x, y, sim->elements[parts[i].type].HighTemperatureTransition);
	else

		sim->part_change_type(i, x, y, PT_WTRV);
	
	return 0;
	}



	//water: amount of water
	//tmpcity[7]: capacity for stuff
	//ctype: thing dissolved
	//tmp4: amount of thing dissolved
	//tmpville[5]:r  for color
	//tmpville[6]:g  for color
	//tmpville[7]:b  for color
	int capacity = 0;
	int r, rx, ry;
	//int freeabove;
	for (ry=-1; ry<2; ry++)
	for (rx=-1; rx<2; rx++)
		
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				int partnum = 0;



				if (!r)
				{
					if (parts[i].water > 100)
					{
						parts[sim->create_part(-1, x + rx, y + ry, PT_WATR)].water = parts[i].water - 100;
						parts[i].water = 75;
					}
				//	if(ry == -1)
				//	{
						//if (RNG::Ref().chance(1, 3))
					//	freeabove = 1;

				//	}
					continue;
				}






				int rt = TYP(r);
				// water diffusion
				if (rt == PT_BRKN && parts[ID(r)].ctype != 0)
					rt = parts[ID(r)].ctype;

				// if(sim->elements[TYP(r)].Properties & PROP_WATER)
				// {	
				 
				//  diffuse()


				// }



					
			//	else
				//	parts[i].ctype = rt;


				
				if(TYP(r) == PT_WTRV && parts[i].water + parts[ID(r)].water < 100 && parts[i].ctype + parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].nitrogens == 0)
				{
					parts[i].water += parts[ID(r)].water;
					sim->kill_part(ID(r));
				
				}




				 if (sim->elements[rt].Properties & PROP_WATER || rt == PT_BLOD || rt == PT_HCL || rt == PT_MILK) {



					if (rt == parts[i].type)
						partnum += 10;
					else
						partnum += 5;

					capacity = parts[i].tmp4 + parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
					if (RNG::Ref().chance(1, 8) && capacity + 2 < parts[i].tmpcity[7])
					{

						// take
						if (parts[i].tmp4 < parts[i].tmpcity[7] / 2 && parts[ID(r)].tmp4 > 0 && parts[i].tmp4 < parts[ID(r)].tmp4 && (parts[i].tmp4 <= 0 || parts[ID(r)].ctype == parts[i].ctype || parts[i].ctype == 0) && RNG::Ref().chance(1, 6))
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
						if ((parts[i].water < 100 && parts[ID(r)].water > 0 && (parts[i].water < parts[ID(r)].water || parts[i].water > parts[ID(r)].water * 2) && RNG::Ref().chance(1, 6)))
						{
							parts[i].water += std::min(partnum, parts[ID(r)].water);
							parts[ID(r)].water -= std::min(partnum, parts[ID(r)].water);
						}
					}
					//give
					capacity = parts[ID(r)].tmp4 + parts[ID(r)].oxygens + parts[ID(r)].carbons + parts[ID(r)].hydrogens + parts[ID(r)].water + parts[ID(r)].nitrogens;
					if (RNG::Ref().chance(1, 8) && capacity + 2 < parts[ID(r)].tmpcity[7])
					{

							{
							if (parts[ID(r)].tmp4 < parts[ID(r)].tmpcity[7] / 2 && parts[i].tmp4 > parts[ID(r)].tmp4 && (parts[ID(r)].tmp4 == 0 || parts[i].ctype == parts[ID(r)].ctype || parts[ID(r)].ctype == 0) && RNG::Ref().chance(1, 6))
							{
								parts[ID(r)].tmp4 += std::min(20, parts[i].tmp4);
								parts[i].tmp4 -= std::min(20, parts[i].tmp4);
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
								if (parts[ID(r)].water < 100 && parts[i].water > 0 && (parts[ID(r)].water < parts[i].water && parts[i].water < parts[ID(r)].water * 2) && RNG::Ref().chance(1, 6))
								{
									parts[ID(r)].water += std::min(partnum, parts[i].water);
									parts[i].water -= std::min(partnum, parts[i].water);

								}
							}
						

					}
				 }
				//color diffusion
				if ((sim->elements[rt].Properties & PROP_WATER || rt == PT_MILK) && RNG::Ref().chance(1, 80) && (parts[i].tmpville[5] != 0 || parts[i].tmpville[6] != 0 || parts[i].tmpville[7] != 0))
				{
					if (parts[i].tmpville[5] != 0)
					{
						parts[ID(r)].tmpville[5] += restrict_flt(parts[i].tmpville[5], -5, 5);
						parts[i].tmpville[5] -= restrict_flt(parts[i].tmpville[5], -5, 5);
					}
					if (parts[i].tmpville[6] != 0)
					{
						parts[ID(r)].tmpville[6] += restrict_flt(parts[i].tmpville[6], -5, 5);
						parts[i].tmpville[6] -= restrict_flt(parts[i].tmpville[6], -5, 5);
					}

					if (parts[i].tmpville[7] != 0)
					{
						parts[ID(r)].tmpville[7] += restrict_flt(parts[i].tmpville[7], -5, 5);
						parts[i].tmpville[7] -= restrict_flt(parts[i].tmpville[7], -5, 5);

					}

				}





 

				 if (parts[i].ctype == PT_SALT && parts[i].tmp4 > 30 && RNG::Ref().chance(1, 50))
					sim->part_change_type(i,x,y,PT_SLTW);
				if(parts[i].ctype == PT_SUGR && parts[i].tmp4 > 30 && RNG::Ref().chance(1, 50))
					sim->part_change_type(i,x,y,PT_SWTR);
				
				 if ((rt==PT_RBDM||TYP(r)==PT_LRBD) && (sim->legacy_enable||parts[i].temp>(273.15f+12.0f)) && RNG::Ref().chance(1, 100))
				{
					sim->part_change_type(i,x,y,PT_FIRE);
					parts[i].life = 4;
					parts[i].ctype = PT_WATR;
				}
			//	else if (TYP(r)==PT_SLTW && RNG::Ref().chance(1, 2000))
				//{
			//		sim->part_change_type(i,x,y,PT_SLTW);
			//	}
				 if (TYP(r)==PT_ROCK && fabs(parts[i].vx)+fabs(parts[i].vy) >= 0.5 && RNG::Ref().chance(1, 1000)) // ROCK erosion
				{
					if (RNG::Ref().chance(1,3))
						sim->part_change_type(ID(r),x+rx,y+ry,PT_SAND);
					else
						sim->part_change_type(ID(r),x+rx,y+ry,PT_STNE);
				}
				if ((sim->elements[TYP(r)].Properties & TYPE_PART || sim->elements[TYP(r)].Properties & TYPE_SOLID) && abs(parts[i].vy + parts[i].vx) < 2 && RNG::Ref().chance(1, 2))
					parts[i].vx = parts[i].vy = 0;
			



				int capacity = parts[i].oxygens + parts[i].carbons + parts[i].hydrogens + parts[i].water + parts[i].nitrogens;
				if ((sim->elements[rt].Properties & PROP_EDIBLE && !(sim->elements[rt].Properties & PROP_ANIMAL || sim->elements[rt].Properties & PROP_ORGANISM  || sim->elements[rt].Properties & PROP_WATER)) && capacity < parts[i].tmpcity[7] && RNG::Ref().chance(1, restrict_flt(800 - parts[i].temp, 1, MAX_TEMP)))
				{
					
					if (parts[ID(r)].hydrogens > 0 || parts[ID(r)].oxygens > 0 || parts[ID(r)].carbons > 0 || parts[ID(r)].nitrogens > 0 || parts[ID(r)].water > 0)// (rt == PT_FLSH || (rt == PT_BRKN && parts[ID(r)].ctype == PT_FLSH) )
					{
						parts[i].carbons += std::min(10, parts[ID(r)].carbons);
						parts[i].oxygens += std::min(10, parts[ID(r)].oxygens);
						parts[i].hydrogens += std::min(10, parts[ID(r)].hydrogens);
						parts[i].nitrogens += std::min(10, parts[ID(r)].nitrogens);
						parts[i].water += std::min(10, parts[ID(r)].water);
					//	parts[i].tmp4 += std::min(10, parts[ID(r)].tmp4);
						parts[ID(r)].carbons -= std::min(10, parts[ID(r)].carbons);
						parts[ID(r)].oxygens -= std::min(10, parts[ID(r)].oxygens);
						parts[ID(r)].hydrogens -= std::min(10, parts[ID(r)].hydrogens);
						parts[ID(r)].nitrogens -= std::min(10, parts[ID(r)].nitrogens);
						parts[ID(r)].water -= std::min(10, parts[ID(r)].water);
					//	parts[ID(r)].tmp4 -= std::min(10, parts[ID(r)].tmp4);


						if (parts[ID(r)].hydrogens <= 0 && parts[ID(r)].oxygens <= 0 && parts[ID(r)].carbons <= 0 && parts[ID(r)].tmp4 <= 0 && parts[ID(r)].nitrogens <= 0 && parts[ID(r)].water <= 0)
						{

							sim->kill_part(ID(r));
						}
					}
					if (parts[ID(r)].tmp4 > 0 && RNG::Ref().chance(1, 8))
					{
						
							parts[i].tmp4 += std::min(10, parts[ID(r)].tmp4);
							parts[ID(r)].tmp4 -= std::min(10, parts[ID(r)].tmp4);
							parts[i].ctype = rt;
						
				//		else
					//	{
						//	sim->kill_part(ID(r));

					//	}

					}
					
					}

					 if (sim->NoWeightSwitching && sim->pmap_count[y][x]<2 && TYP(r) != parts[i].type && RNG::Ref().chance(1, 8) && (y > parts[ID(r)].y && RNG::Ref().chance(1, restrict_flt(sim->elements[i].Weight - pow(sim->elements[TYP(r)].Weight, 2) / 10.0f, 1, MAX_TEMP)) || y < parts[ID(r)].y && RNG::Ref().chance(1, 100)) && (sim->elements[TYP(r)].Properties & TYPE_PART || sim->elements[TYP(r)].Properties & TYPE_LIQUID) && !(sim->elements[TYP(r)].Properties & PROP_WATER || TYP(r) == PT_HCL))
					 	sim->better_do_swap(i, x, y, ID(r), parts[ID(r)].x, parts[ID(r)].y);
					//	  if(freeabove != 0 && parts[ID(r)].y > y)
					//	 {
						// parts[i].vx += freeabove;
					//	if(parts[ID(r)].vy > 0)
					//	 parts[i].vy += -2 - parts[ID(r)].vy;
					//	 else
						// parts[i].vy += -1;
						
						 
					    
					//	 }
						 
						

						 
						 
				 
				
			
				
			}
		//	parts[i].physstuff[1] = parts[i].water; ??
			parts[i].tmpcity[2]++;
	return 0;
}
static int graphics(GRAPHICS_FUNC_ARGS) {
	*pixel_mode |= PMODE_BLUR;
	//if (cpart->tmp2 >= COLOR_FRAMES)
	//	return 0;
	// Ease colors from water (2030D0) to F05000 (red)
//	float ease = 1;//cpart->tmp2 * 1.0f / COLOR_FRAMES;
	int dim = cpart->water - 100;
	*colr += cpart->tmpville[5];
	*colg += cpart->tmpville[6];
	*colb += cpart->tmpville[7]+ dim;

		return 0;
}























