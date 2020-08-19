#pragma once
#include <string>
namespace olib {
	class oprogress_console {
	private:
		bool __block = true;
		float _from = 0.f;
		float _to = 0.f;
		int val = 0;
		std::string _visual = "[                                                  ]";
	public:
		oprogress_console range(float from, float to) { _from = from; _to = to; return *this; }
		void update(int _v, std::string overwrite = "") { val = _v; helper(overwrite); }
	private:
		void helper(std::string overwrite);
	};
}