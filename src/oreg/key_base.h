#pragma once
#include <string>
#include <windows.h>
namespace olib {
	/*
	Just a helper class for oreg_key, because it is a template class
	it cannot be passed to a function... in the words of jeremy clarksson: Stupid
	*/
	class key_base {
	public:
		virtual std::string __get_key_path() const { return ""; }
		virtual std::string __get_sub_key() const { return ""; }
		virtual HKEY __get_def_key() const { return 0; }
		virtual void set_value(std::string _v) {}
		virtual void set_value(int _v) {}
		virtual std::string __get_value() const { return ""; }
		virtual std::string __get_type() const {return "";}

	};
}