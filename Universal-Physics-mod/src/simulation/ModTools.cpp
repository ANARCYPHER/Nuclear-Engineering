#include "ModTools.h"






//cyens god
//Generates a random hydrocarbon type (alkane/ene/yne) with given number of carbons, returns number of hydrogens
 int makeAlk(int c) {
	int alkType = RNG::Ref().between(1, 3);
	return alkType == 0 ? (2 * c + 2) : alkType == 1 ? (2 * c) : (2 * c - 2);
}
 //cyens god
//Gets the bond location randomly for alkenes and alkynes
 int getBondLoc(int c) {
	 return (RNG::Ref().between(c / 2, c / 2 + 1));
}
