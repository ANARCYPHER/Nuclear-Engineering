#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Config.h"

#include <vector>
#include "StructProperty.h"

struct Particle
{
	int type;
	int life, ctype;
	float x, y, vx, vy;
	float temp;
	float pavg[2];
	int flags;
	int tmp;
	int tmp2;
	int tmp3;
	int tmp4;
	int freespace;
	int surround[8];
	float tmpcity[10];
	float tmpville[20];
	int metabolism;
	int oxygens;
	int nitrogens;
	int carbons;
	int hydrogens;
	int water;
	int sugar;
	int salt;
	unsigned int dcolour;
//	String fullname;
	/** Returns a list of properties, their type and offset within the structure that can be changed
	 by higher-level processes referring to them by name such as Lua or the property tool **/
	static std::vector<StructProperty> const &GetProperties();
};

#endif
