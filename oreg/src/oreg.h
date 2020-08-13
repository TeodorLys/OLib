#pragma once
#include <windows.h>
#include <string>
namespace olib {

	class key_base;
	class oreg {
	private:
	public:
		enum keys {
			CURRENT_USER,
			CLASSES_ROOT,
			CURRENT_CONFIG,
			LOCAL_MACHINE,
			USERS
		};
		/*
		* checks if a regkey exists
		*/
		static bool exists(key_base *_k);
		/*
		* reads the value buffer from oreg_key and sets the key
		*/
		static bool write(key_base *_k);
		/*
		* read key value and sets the value buffer in oreg_key object
		*/
		static bool read(key_base *_k);
	private:
		static std::string read_int(std::string sub, HKEY _key);
		static std::string read_string(std::string sub, HKEY _key);
		static bool write_int(std::string sub, HKEY _key, std::string data);
		static bool write_string(std::string sub, HKEY _key, std::string data);
		static void _print_if_error(long result) {
			if (result == ERROR_ACCESS_DENIED)
				printf("ACCESS DENIED, Probably needs to be elevated!\n");
		}
	};
}
