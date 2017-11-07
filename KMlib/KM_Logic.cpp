#include "KM_Logic.h"
namespace Kuma {
	int RollRadio1toMax(int & l_radio, const int & l_max) {
		if (l_radio + 1 > l_max - 1)
		{
			l_radio = 0;
		}
		else {
			l_radio++;
		}
		return l_radio + 1;
	}
}