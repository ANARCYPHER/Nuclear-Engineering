#include <cmath>
#include "common/String.h"
#include <string>
#include <cstring>

//Kelvin to Joule Scale
static int KtoJS = 1000000;


//from nuclear-power.net
static float aV = 15.76f;
static float aS = 17.81f;
static float aC = 0.711f;
static float aA = 23.7f;
static float aP = 34.4f; //34.4 for (3 / 4), 11.18 for (1 / 2)
//in u units
static double mPu = 1.007276, mPkg = 1.672621 * pow(10, -27);
static double mNu = 1.008664, mNkg = 1.674927 * pow(10, -27);
static double meu = 5.485799 * pow(10, -4), mekg = 9.109383 * pow(10, -31);
static double utoMeV = 931.494;

static int c = 299792458; //speed of light, in m/s
static double e = 1.602176 * pow(10, -19); //elementary charge, in Coulombs
static double k = 8.9876 * pow(10, 9); //Coulomb constant

static double KtoJ = 1.38064852 * pow(10, -23) * KtoJS;
static double JtoeV = 1 / e;


static double BindingEnergy(int Z, int A)
//Z = proton number, A = nucleon number, A-Z = N = neutron number
{
	double volumeTerm, surfaceTerm, coulombTerm, assymetryTerm, BE;
	//pairing term
	double pairingTerm = 0;
	//proton-neutron numbers
	if(A % 2 == 1) //A odd, Z-N even-odd or odd-even
		pairingTerm = 0;
	if (A % 2 == 0)
	{
		if (Z % 2 == 0 && (A - Z) % 2 == 0)		//Z-N even-even
			pairingTerm = aP / pow(A, 3.0/4.0);
		if (Z % 2 == 1 && (A - Z) % 2 == 1)		//Z-N odd-odd
			pairingTerm = -aP / pow(A, 3.0/4.0);
	}

	
	volumeTerm = aV * A;
	surfaceTerm = -aS * pow(A, 2.0 / 3.0);
	coulombTerm = -aC * (pow(Z, 2) / pow(A, 1.0 / 3.0));
	assymetryTerm = -aA * (pow(A - 2 * Z, 2) / A);

	BE = volumeTerm + surfaceTerm + coulombTerm + assymetryTerm + pairingTerm;

	//The formula fails for light nuclei
	if (Z == 0 && A == 1) //neutron
		BE = 0;
	else if (Z == 1) //H
	{
		switch (A)
		{
		case 1:
			BE = 0;
			break;
		case 2:
			BE = 2.22452;
			break;
		case 3:
			BE = 8.481;
			break;
		case 4:
			BE = 5.6;
			break;
		case 5:
			BE = 6.68;
			break;
		case 6:
			BE = 5.78;
			break;
		case 7:
			BE = 6.58;
			break;
		}
	}


	else if (Z == 2) //He
	{
		switch (A)
		{
		case 3:
			BE = 7.71;
			break;
		case 4:
			BE = 28.2956;
			break;
		case 5:
			BE = 27.4055;
			break;
		}
	}


	else if (Z == 3) //Li
	{
		switch (A)
		{
		case 3:
			BE = 6.8028;
			break;
		case 4:
			BE = 4.6148;
			break;
		case 5:
			BE = 26.3305;
			break;
		case 6:
			BE = 31.9938;
			break;
		case 7:
			BE = 39.2434;
			break;
		case 8:
			BE = 41.276;
			break;
		}
	}

	else if (Z == 4 && A == 8) //Be-8
		BE = 56.4992;
	else if (Z == 4 && A == 9) //Be-9
		BE = 58.1625;
	else if (Z == 5 && A == 10) //B-10
		BE = 64.75;
	else if (Z == 5 && A == 11) //B-11
		BE = 76.2047;
	else if (Z == 6 && A == 12) //C-12
		BE = 92.1612;
	
	return BE;
}

static double CoulombBarrier(int Z, int A, int tZ, int tA)
{
	double ri = 1.2 * pow(10, -15) * pow(A, 1.0 / 3.0); //radius of particle i
	double rt = 1.2 * pow(10, -15) * pow(tA, 1.0 / 3.0); //radius of particle t

	double barrier = k * pow(e, 2) * Z * tZ / (ri + rt);
	return barrier;
}

static String PeriodicProperties(int Z)
//returns Elementname-Isotope
{
	StringBuilder formula, name;
	if (Z <= 118)
		switch (Z)
		{
		case 0 :
			formula << "n";
			name << "neutron";
			break;
		case 1:
			formula << "H";
			name << "Hydrogen";
			break;
		case 2:
			formula << "He";
			name << "Helium";
			break;
		case 3:
			formula << "Li";
			name << "Lithium";
			break;
		case 4:
			formula << "Be";
			name << "Beryllium";
			break;
		case 5:
			formula << "B";
			name << "Boron";
			break;
		case 6:
			formula << "C";
			name << "Carbon";
			break;
		case 7:
			formula << "N";
			name << "Nitrogen";
			break;
		case 8:
			formula << "O";
			name << "Oxygen";
			break;
		case 9:
			formula << "F";
			name << "Fluorine";
			break;
		case 10:
			formula << "Ne";
			name << "Neon";
			break;
		case 11:
			formula << "Na";
			name << "Sodium";
			break;
		case 12:
			formula << "Mg";
			name << "Magnesium";
			break;
		case 13:
			formula << "Al";
			name << "Aluminium";
			break;
		case 14:
			formula << "Si";
			name << "Silicon";
			break;
		case 15:
			formula << "P";
			name << "Phosphorus";
			break;
		case 16:
			formula << "S";
			name << "Sulfur";
			break;
		case 17:
			formula << "Cl";
			name << "Chlorine";
			break;
		case 18:
			formula << "Ar";
			name << "Argon";
			break;
		case 19:
			formula << "K";
			name << "Potassium";
			break;
		case 20:
			formula << "Ca";
			name << "Calcium";
			break;
		case 21:
			formula << "Sc";
			name << "Scandium";
			break;
		case 22:
			formula << "Ti";
			name << "Titanium";
			break;
		case 23:
			formula << "V";
			name << "Vanadium";
			break;
		case 24:
			formula << "Cr";
			name << "Chromium";
			break;
		case 25:
			formula << "Mn";
			name << "Manganese";
			break;
		case 26:
			formula << "Fe";
			name << "Iron";
			break;
		case 27:
			formula << "Co";
			name << "Cobalt";
			break;
		case 28:
			formula << "Ni";
			name << "Nickel";
			break;
		case 29:
			formula << "Cu";
			name << "Copper";
			break;
		case 30:
			formula << "Zn";
			name << "Zinc";
			break;
		case 31:
			formula << "Ga";
			name << "Gallium";
			break;
		case 32:
			formula << "Ge";
			name << "Germanium";
			break;
		case 33:
			formula << "As";
			name << "Arsenic";
			break;
		case 34:
			formula << "Se";
			name << "Selenium";
			break;
		case 35:
			formula << "Br";
			name << "Bromine";
			break;
		case 36:
			formula << "Kr";
			name << "Krypton";
			break;
		case 37:
			formula << "Rb";
			name << "Rubidium";
			break;
		case 38:
			formula << "Sr";
			name << "Strontium";
			break;
		case 39:
			formula << "Y";
			name << "Yttrium";
			break;
		case 40:
			formula << "Zr";
			name << "Zirconium";
			break;
		case 41:
			formula << "Nb";
			name << "Niobium";
			break;
		case 42:
			formula << "Mo";
			name << "Molybdenum";
			break;
		case 43:
			formula << "Tc";
			name << "Technetium";
			break;
		case 44:
			formula << "Ru";
			name << "Ruthenium";
			break;
		case 45:
			formula << "Rh";
			name << "Rhodium";
			break;
		case 46:
			formula << "Pd";
			name << "Palladium";
			break;
		case 47:
			formula << "Ag";
			name << "Silver";
			break;
		case 48:
			formula << "Cd";
			name << "Cadmium";
			break;
		case 49:
			formula << "In";
			name << "Indium";
			break;
		case 50:
			formula << "Sn";
			name << "Tin";
			break;
		case 51:
			formula << "Sb";
			name << "Antimony";
			break;
		case 52:
			formula << "Te";
			name << "Tellurium";
			break;
		case 53:
			formula << "I";
			name << "Iodine";
			break;
		case 54:
			formula << "Xe";
			name << "Xenon";
			break;
		case 55:
			formula << "Cs";
			name << "Caesium";
			break;
		case 56:
			formula << "Ba";
			name << "Barium";
			break;
		case 57:
			formula << "La";
			name << "Lanthanum";
			break;
		case 58:
			formula << "Ce";
			name << "Cerium";
			break;
		case 59:
			formula << "Pr";
			name << "Praseodymium";
			break;
		case 60:
			formula << "Nd";
			name << "Neodymium";
			break;
		case 61:
			formula << "Pm";
			name << "Promethium";
			break;
		case 62:
			formula << "Sm";
			name << "Samarium";
			break;
		case 63:
			formula << "Er";
			name << "Erbium";
			break;
		case 64:
			formula << "Gd";
			name << "Gadolinium";
			break;
		case 65:
			formula << "Tb";
			name << "Terbium";
			break;
		case 66:
			formula << "Dy";
			name << "Dysprosium";
			break;
		case 67:
			formula << "Ho";
			name << "Holmium";
			break;
		case 68:
			formula << "Er";
			name << "Erbium";
			break;
		case 69:
			formula << "Tm";
			name << "Thulium";
			break;
		case 70:
			formula << "Yb";
			name << "Ytterbium";
			break;
		case 71:
			formula << "Lu";
			name << "Lutetium";
			break;
		case 72:
			formula << "Hf";
			name << "Hafnium";
			break;
		case 73:
			formula << "Ta";
			name << "Tantalum";
			break;
		case 74:
			formula << "W";
			name << "Tungsten";
			break;
		case 75:
			formula << "Re";
			name << "Rhenium";
			break;
		case 76:
			formula << "Os";
			name << "Osmium";
			break;
		case 77:
			formula << "Ir";
			name << "Iridium";
			break;
		case 78:
			formula << "Pt";
			name << "Platinum";
			break;
		case 79:
			formula << "Au";
			name << "Gold";
			break;
		case 80:
			formula << "Hg";
			name << "Mercury";
			break;
		case 81:
			formula << "Tl";
			name << "Thallium";
			break;
		case 82:
			formula << "Pb";
			name << "Lead";
			break;
		case 83:
			formula << "Bi";
			name << "Bismuth";
			break;
		case 84:
			formula << "Po";
			name << "Polonium";
			break;
		case 85:
			formula << "At";
			name << "Astatine";
			break;
		case 86:
			formula << "Rn";
			name << "Radon";
			break;
		case 87:
			formula << "Fr";
			name << "Francium";
			break;
		case 88:
			formula << "Ra";
			name << "Radium";
			break;
		case 89:
			formula << "Ac";
			name << "Actinium";
			break;
		case 90:
			formula << "Th";
			name << "Thorium";
			break;
		case 91:
			formula << "Pa";
			name << "Protactinium";
			break;
		case 92:
			formula << "U";
			name << "Uranium";
			break;
		case 93:
			formula << "Np";
			name << "Neptunium";
			break;
		case 94:
			formula << "Pu";
			name << "Plutonium";
			break;
		case 95:
			formula << "Am";
			name << "Americium";
			break;
		case 96:
			formula << "Cm";
			name << "Curium";
			break;
		case 97:
			formula << "Bk";
			name << "Berkelium";
			break;
		case 98:
			formula << "Cd";
			name << "Californium";
			break;
		case 99:
			formula << "Es";
			name << "Einsteinium";
			break;
		case 100:
			formula << "Fm";
			name << "Fermium";
			break;
		case 101:
			formula << "Md";
			name << "Mendelevium";
			break;
		case 102:
			formula << "No";
			name << "Nobelium";
			break;
		case 103:
			formula << "Lr";
			name << "Lawrencium";
			break;
		case 104:
			formula << "Rf";
			name << "Rutherfordium";
			break;
		case 105:
			formula << "Db";
			name << "Dubnium";
			break;
		case 106:
			formula << "Sg";
			name << "Seaborgium";
			break;
		case 107:
			formula << "Bh";
			name << "Bohrium";
			break;
		case 108:
			formula << "Hs";
			name << "Hassium";
			break;
		case 109:
			formula << "Mt";
			name << "Meitnerium";
			break;
		case 110:
			formula << "Ds";
			name << "Darmstadtium";
			break;
		case 111:
			formula << "Rg";
			name << "Roentgenium";
			break;
		case 112:
			formula << "Cn";
			name << "Copernicium";
			break;
		case 113:
			formula << "Nh";
			name << "Nihonium";
			break;
		case 114:
			formula << "Fl";
			name << "Flerovium";
			break;
		case 115:
			formula << "Mc";
			name << "Moscovium";
			break;
		case 116:
			formula << "Lv";
			name << "Livermorium";
			break;
		case 117:
			formula << "Ts";
			name << "Tennessine";
			break;
		case 118:
			formula << "Og";
			name << "Oganesson";
			break;
		}
	else if (Z > 118)
	{
		for (int i = floor(log10(Z)); i >= 0; i--)
		{
			String tempformula, tempname;
			int d = floor(Z / pow(10, i));
			if (d%10 == 0)
			{
				tempformula = "n";
				tempname = "nil";
			}
			else if (d%10 == 1)
			{
				tempformula = "u";
				tempname = "un";
			}
			else if (d%10 == 2)
			{
				tempformula = "b";
				tempname = "bi";
			}
			else if (d%10 == 3)
			{
				tempformula = "t";
				tempname = "tri";
			}
			else if (d%10 == 4)
			{
				tempformula = "q";
				tempname = "quad";
			}
			else if (d%10 == 5)
			{
				tempformula = "p";
				tempname = "pent";
			}
			else if (d%10 == 6)
			{
				tempformula = "h";
				tempname = "hex";
			}
			else if (d%10 == 7)
			{
				tempformula = "s";
				tempname = "sept";
			}
			else if (d%10 == 8)
			{
				tempformula = "o";
				tempname = "oct";
			}
			else if (d%10 == 9)
			{
				tempformula = "n";
				tempname = "non";
			}
			if (i == floor(log10(Z)))
			{
				tempformula[0] = toupper(tempformula[0]);
				tempname[0] = toupper(tempname[0]);
			}
			formula << tempformula;
			name << tempname;
		}
		name << "ium";
	}
	return name.Build();
}