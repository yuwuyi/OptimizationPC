#ifndef RGB_h__
#define RGB_h__

#include <set>

enum RGBIndex {
	R, G, B
};

struct RGBColor {
public:
	RGBColor() {
		value[0] = value[1] = value[2] = 0;
	}
	
	RGBColor(double r, double g, double b)  {
		value[0] = r, value[1] = g, value[2] = b; 
	}

	double& operator[] (RGBIndex index) {
		return value[index];
	}

	double operator[] (RGBIndex index) const {
		return value[index];
	}

	double value[3];	

	bool operator== (RGBColor &rgb1) {
		return ( value[R] == rgb1[R] && value[G] == rgb1[G] && value[B] == rgb1[B] ); 
	}

	RGBColor operator*( const double s  ) const
	{
		RGBColor r( value[0] * s, value[1] * s, value[2] * s );
		return r;
	};

	RGBColor operator+( const RGBColor& p  ) 
	{
		RGBColor r( value[0] + p.value[0], value[1] + p.value[1], value[2] + p.value[2] );
		return r;
	};

}  ;
static RGBColor RGBNULL;



enum {
	//DARKBLUE,
	BLUE,
 	CYAN,
// 	GREEN,
// 	YELLOW,
 	ORANGE,
	RED,
// 	DARKRED,
	MAXCOLOR
};

const RGBColor DEFAULTRGBS[] = {
//	RGBColor(0, 0, 0.5),
	RGBColor(0, 0, 1),
 	RGBColor(0, 1, 1),
// 	RGBColor(0, 1, 0),
// 	RGBColor(1, 1, 0),
 	RGBColor(1, 0.5, 0),
	RGBColor(1, 0, 0),
//	RGBColor(0.5, 0, 0)
};

#endif // RGB_h__
