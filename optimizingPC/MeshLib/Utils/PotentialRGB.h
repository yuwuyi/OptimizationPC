#ifndef PotentialRGB_h__
#define PotentialRGB_h__

#include <map>
#include <list>
#include <algorithm>
#include <iostream>
//#include "Helper.h"
#include "Common.h"
#include "RGB.h"

typedef std::set<double> POTENTIALSET;
typedef std::map<double, RGBColor> XRMAP;

//TODO:
// filter out range of %5 and %95

class PotentialRGB;

struct Rule {
	Rule(PotentialRGB& prgb_) : prgb(prgb_) {}
	virtual ~Rule() {}
	virtual bool apply(double newvalue) = 0;
	PotentialRGB& prgb;
	RGBColor rgb;
};

typedef std::list<Rule*> RULELST;

class PotentialRGB {
public:
	PotentialRGB() {}

	double norm(double value) {
		if (value <= minvalue) return 0;
		if (value >= maxvalue) return 1;
		return (value - minvalue) / (maxvalue - minvalue);
	}

	void init() {
		for (int i = 0; i < MAXCOLOR; ++i) {
			ptset.insert( minvalue + (maxvalue - minvalue) * i / (double)(MAXCOLOR - 1));
			xrmap[minvalue + (maxvalue - minvalue) * i / (double)(MAXCOLOR - 1)] =  DEFAULTRGBS[i];	
		}
	}

	void init(std::vector<RGBColor>& initRGBs) {

		for (size_t i = 0; i < initRGBs.size(); ++i) {
			ptset.insert( minvalue + (maxvalue - minvalue) * i / (double)(initRGBs.size() - 1));
			xrmap[minvalue + (maxvalue - minvalue) * i / (double)(initRGBs.size() - 1)] =  initRGBs[i];	
		}
	
	}

	void clear() {
		xrmap.clear();
		ptset.clear();
	}

	~PotentialRGB() {
		for (RULELST::iterator b = rlst.begin(), e = rlst.end(); b != e; ++b) {
			delete *b;		
		}
	}
	
	RGBColor getRGB(double newvalue) {
		
		if (newvalue <= minvalue) {
			return xrmap[minvalue];
		}
		if (newvalue >= maxvalue) {
			return xrmap[maxvalue];
		}

		std::pair<POTENTIALSET::iterator, bool> ret = ptset.insert(newvalue);
		if (!ret.second) {
			if (xrmap.find(newvalue) == xrmap.end()) {
				std::cout << "the rgb not found in xrmap!\n";
				exit(-1);
			}
			return xrmap[newvalue];
		}
		
		double prevp = *(--(ret.first));
		double nextp = *(++(++(ret.first)));
		double alpha = (newvalue - prevp) / (nextp - prevp);

		if (xrmap.find(prevp) == xrmap.end() || xrmap.find(nextp) == xrmap.end()) {
			std::cout << "the rgb not found in xrmap!\n";
			exit(-1);
		}

		RGBColor prevrgb = xrmap[prevp];
		RGBColor nextrgb = xrmap[nextp];

		RGBColor newrgb;
	
		newrgb = nextrgb * alpha + prevrgb * (1 - alpha);

		xrmap[newvalue] = newrgb;

		return newrgb;
	}

	double minvalue, maxvalue;
private:
	POTENTIALSET ptset;
	XRMAP xrmap;
	RULELST rlst;		
};

struct OutRangeRule : public Rule {
	using Rule::prgb;
	using Rule::rgb;

	virtual ~OutRangeRule() {}
	virtual bool apply(double newvalue) {
		if (newvalue < prgb.minvalue || newvalue > prgb.maxvalue) {
			rgb = RGBNULL;
			return true;
		}
	}

};

#endif // PotentialRGB_h__