#include "oprogress_console.h"
#include "oanimate.h"
#include <stdio.h>
#include <string>
namespace olib {
	/*
	PRIVATE
	*/
	void oprogress_console::helper(std::string overwrite) {
		static float last = oanimate::map(val, _from, _to, 0, 50);
		int current = oanimate::map(val, _from, _to, 1, 50);
		if (last != current) {
			_visual.replace((_visual.begin()) + current, (_visual.begin()) + current + 1, "#");
			_visual.erase(_visual.find("]") + 1, _visual.length());
			if (overwrite == "")
				_visual += " " + std::to_string(val) + "/" + std::to_string((int)_to);
			else
				_visual += overwrite;
			printf("\r%s", _visual.c_str());
			last = current;
		}
	}
	/*//*/
}