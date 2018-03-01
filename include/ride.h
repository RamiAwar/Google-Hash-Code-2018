#include <stdlib.h>

class Ride {
public:
	int a, b, x, y, s, f;
	int length;
	Ride(int _a, int _b, int _x,
			int _y, int _s, int _f) {
		a = _a; b = _b; x = _x;
		y = _y; s = _s; f = _f;
		
		length = abs(a - x) + abs(b - y);
	}

};
