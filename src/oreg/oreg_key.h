#pragma once
#include "key_base.h"
#include <string>
#include <Windows.h>
#include <typeinfo>
namespace olib {

	template<class T>
	class oreg_key : public key_base {
	public:
		typedef std::string OREG_STRING;
		typedef int OREG_INT;
		typedef bool OREG_BOOL;

		/*
		These are the type checking for the supported types.
		The most common ones to use. i.e. the ones I will use...
		*/

		template<typename T>
		struct type_name {
			static constexpr bool is() { return false; }
			static constexpr const char* get() { return "NULL"; }
			static T conv(std::string _v) { return T; }
		};

		template<>
		struct type_name<OREG_STRING> {
			static constexpr bool is() { return true; }
			static constexpr const char* get() { return "string"; }
			static std::string conv(std::string _v) { return _v; }
		};

		template<>
		struct type_name<OREG_INT> {
			static constexpr bool is() { return true; }
			static constexpr const char* get() { return "int"; }
			static int conv(std::string _v) { return std::stoi(_v); }
		};

		template<>
		struct type_name<OREG_BOOL> {
			static constexpr bool is() { return true; }
			static constexpr const char* get() { return "bool"; }
			static bool conv(std::string _v) { return std::stoi(_v) > 0 ? true : false; }
		};

	private:
		std::string path = ""; // The full path to the key(excluding the name)
		std::string subkey = ""; // Just the keyname
		std::string _v = "";
		std::string type = "";
		HKEY _def_key = { 0 };
		enum keys {
			CURRENT_USER,
			CLASSES_ROOT,
			CURRENT_CONFIG,
			LOCAL_MACHINE,
			USERS
		};
	public:
		/*
		Saves all data about the regkey and checks so the type is valid(AT COMPILE TIME!)
		TODO: Maybe split up the subkey and the path into two different parameters, or maybe have a overload?
		*/
		oreg_key(int _k, std::string full_path){
			static_assert(type_name<T>::is());
			_def_key = keys_to_predef(_k);
			std::string _subkey = full_path.substr(full_path.rfind("\\") + 1, full_path.length());
			std::string _keypath = full_path.substr(0, full_path.rfind("\\"));
			path = _keypath;
			subkey = _subkey;
			type = type_name<T>::get();
		}

		/*
		For getting the internal value by the reg type.
		The value are always a string, internally, but this function converts it.
		*/
		T value() {
			return type_name<T>::conv(_v);
		}
		/*
		All of the "__" functions are for the polymorphic parent class, which the oreg class use.
		i.e. not really for the the "user"
		*/
		std::string __get_key_path() const {
			return path;
		}

		std::string __get_sub_key() const {
			return subkey;
		}

		HKEY __get_def_key() const {
			return _def_key;
		}

		std::string __get_type() const {
			return type;
		}

		std::string __get_value() const {
			return _v;
		}
		/*//*/
		/*
		Except for these! this is where the "user" sets the value if you want to write the regkey
		*/
		void set_value(std::string v) {
			_v = v;
		}

		void set_value(int v) {
			_v = std::to_string(v);
		}
		/*//*/

		oreg_key operator=(OREG_STRING s) {
			static_assert(type_name<T>::get() == "string", "[OREG] Was declared as a int");
			_v = s;
		}

		oreg_key operator=(OREG_INT i) {
			static_assert(type_name<T>::get() == "int", "[OREG] Was declared as a string");
			_v = std::to_string(i);
		}

		operator int() const {
			static_assert(type_name<T>::get() == "int", "[OREG] Was declared as a string");
			return std::stoi(_v);
		}

	  operator std::string() const {
			static_assert(type_name<T>::get() == "string", "[OREG] Was declared as a int");
			return _v;
		}

	private:

		HKEY keys_to_predef(int _k) {
			switch (_k)
			{
			case oreg_key::keys::CURRENT_USER:
				return HKEY_CURRENT_USER;
				break;
			case oreg_key::keys::CLASSES_ROOT:
				return HKEY_CLASSES_ROOT;
				break;
			case oreg_key::keys::CURRENT_CONFIG:
				return HKEY_CURRENT_CONFIG;
				break;
			case oreg_key::keys::LOCAL_MACHINE:
				return HKEY_LOCAL_MACHINE;
				break;
			case oreg_key::keys::USERS:
				return HKEY_USERS;
				break;
			default:
				return 0;
				break;
			}
		}
	};
}