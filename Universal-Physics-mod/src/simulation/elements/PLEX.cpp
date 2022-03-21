#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_PLEX()
{
	Identifier = "DEFAULT_PT_PLEX";
	Name = "C-4";
	Colour = PIXPACK(0xb58b1d);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;
	PhotonReflectWavelengths = 0x1F00003E;

	Weight = 100;

	HeatConduct = 88;
	Description = "Primary plastic explosive, works best with another explosive.";

	Properties = TYPE_SOLID | PROP_NEUTPENETRATE;

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
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)


{

	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				// Spark detection
				if (TYP(r) == PT_SPRK) {


				
					sim->vx[(y) / CELL][(x) / CELL] *= 1.3;
					sim->vy[(y) / CELL][(x) / CELL] *= 1.3;
					sim->pv[y / CELL][x / CELL] += 2 * (sim->vx[(y) / CELL][(x) / CELL] + sim->vy[(y) / CELL][(x) / CELL]);

					parts[i].life += 500;
					parts[i].temp += 500;
					sim->part_change_type(i, x, y, PT_EMBR);
					return 1;

				}
				else if (TYP(r) == PT_EMBR || TYP(r) == PT_FIRE && parts[i].temp > 800 - sim->pv[y / CELL][x / CELL] && RNG::Ref().chance(1, 20)) {


					sim->vx[(y) / CELL][(x) / CELL] *= 1.3;
					sim->vy[(y) / CELL][(x) / CELL] *= 1.3;
					sim->pv[y / CELL][x / CELL] += 1 * (sim->vx[(y) / CELL][(x) / CELL] + sim->vy[(y) / CELL][(x) / CELL]);
					parts[i].temp += 500; 
					parts[i].life += 100;
					sim->part_change_type(i, x, y, RNG::Ref().chance(1, 5) ? PT_EMBR : PT_FIRE);
					//	sim->part_change_type(i, x, y, PT_EMBR);
					return 1;
				}
			}
	if (parts[i].temp > 2000.0f - sim->pv[y / CELL][x / CELL]) {

	
		sim->vx[(y) / CELL][(x) / CELL] *= 1.3;
		sim->vy[(y) / CELL][(x) / CELL] *= 1.3;
		sim->pv[y / CELL][x / CELL] += 2 * (sim->vx[(y) / CELL][(x) / CELL] + sim->vy[(y) / CELL][(x) / CELL]);
		parts[i].temp += 400;
		parts[i].life += 100;

		sim->part_change_type(i, x, y, RNG::Ref().chance(1, 3) ? PT_EMBR : PT_FIRE);
		return 1;
	}
	if (parts[i].temp + sim->pv[y / CELL][x / CELL] > 320)
	{
 		parts[i].vx += restrict_flt(parts[i].temp / 1000, -0.9f, 0.9f) * sim->vx[y / CELL][x / CELL];
		parts[i].vy += restrict_flt(parts[i].temp / 1000, -0.9f, 0.9f) * sim->vy[y / CELL][x / CELL];
	}
	if (sim->pv[y / CELL][x / CELL] - parts[i].temp / 10 > 150)
	{
	
			sim->vx[(y) / CELL][(x) / CELL] *= 1.3;
			sim->vy[(y) / CELL][(x) / CELL] *= 1.3;
			sim->pv[y / CELL][x / CELL] += 1 * (sim->vx[(y) / CELL][(x) / CELL] + sim->vy[(y) / CELL][(x) / CELL]);
		parts[i].temp += 500;
		parts[i].life += 100;
		sim->part_change_type(i, x, y, RNG::Ref().chance(1, 3) ? PT_EMBR : PT_FIRE);
	
		//	sim->part_change_type(i, x, y, PT_EMBR);
		return 1;
	}
	return 0;
}


static void create(ELEMENT_CREATE_FUNC_ARGS) {

	sim->parts[i].tmpville[6] = RNG::Ref().between(0, 6);
}





static int graphics(GRAPHICS_FUNC_ARGS) {
	int z = (cpart->tmpville[6] - 5) * 10; // Speckles!
	*colr += z;
	*colg += z;
	*colb += z;

	return 0;
}
