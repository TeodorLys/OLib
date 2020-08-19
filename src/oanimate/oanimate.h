#pragma once
#include <assert.h>
namespace olib {
	class oanimate {
	private:
		bool __ease_in = false;
		bool __ease_out = false;
		bool __non_blocking = true;
		void(*__func)(float) = nullptr;
		void(*__full_func)(float, float) = nullptr;
		float __increment = 0.1;
	public:
		float linear_lerp(float from, float to, float time);
		float execute(float from, float to, float time);
	public:
		oanimate() {}
		oanimate ease_in() { __ease_in = true; return *this; }
		oanimate ease_out() { __ease_out = true; return *this; }
		/*
		Executes the function pointer by given parameters.
		And wont return until it is done!
		*/
		oanimate block(void(*func)(float), float increment = 0.1) { __increment = increment; __func = func; __non_blocking = false; return *this; }
		oanimate block(void(*func)(float, float), float increment = 0.1) { __increment = increment; __full_func = func; __non_blocking = false; return *this; }
		operator oanimate() {
			return *this;
		}

		static float get_position_on_line(float _to, float val) {return val / _to;}
		static float map(float val, float _from, float _to, float m_from, float m_to){
			assert(_from < _to);
			return (val - _from) * (m_to - m_from) / (_to - _from) + m_from;
		}

	private:
		float _ease_in(float t);
		float _ease_out(float t);
		float _bezier(float t);
		void call_func(float _f, float _t, float t) {
			if (__func == nullptr)
				__full_func(linear_lerp(_f, _t, t), t);
			else if(__full_func == nullptr)
				__func(linear_lerp(_f, _t, t));
		}
	};
}

