#include "oreg.h"
#include "key_base.h"
#include <filesystem>
#include <Windows.h>

namespace olib {
	bool oreg::exists(key_base *_k) {
		HKEY hKey = 0;
		char lpbuffer[1024] = { 0 };
		DWORD buffersize = sizeof(lpbuffer);

		std::string path_tmp = _k->__get_key_path();
		std::string sub_tmp = _k->__get_sub_key();

		long result = RegOpenKeyExA(_k->__get_def_key(), path_tmp.c_str(), 0, KEY_QUERY_VALUE, &hKey);
		_print_if_error(result);

		if (result == ERROR_SUCCESS) {
			result = RegQueryValueExA(hKey, sub_tmp.c_str(), NULL, NULL, (LPBYTE)lpbuffer, &buffersize);
			_print_if_error(result);
			if (result == ERROR_SUCCESS) {
				RegCloseKey(hKey);
				return true;
			}
			else {
				RegCloseKey(hKey);
				return false;
			}
		}
		else {
			RegCloseKey(hKey);
			return false;
		}
	}

	bool oreg::write(key_base *_k) {
		HKEY hKey = 0;
		WCHAR szbuffer[512];
		DWORD dwBufferSize = sizeof(szbuffer);

		std::string path_tmp = _k->__get_key_path();
		std::string sub_tmp = _k->__get_sub_key();

		long result = RegCreateKeyExA(_k->__get_def_key(), path_tmp.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
		_print_if_error(result);

		if (result == ERROR_SUCCESS) {
			if (_k->__get_type() == "int" || _k->__get_type() == "bool") {
				if (write_int(sub_tmp, hKey, _k->__get_value())) {
					RegCloseKey(hKey);
					return true;
				}
				else {
					RegCloseKey(hKey);
					return false;
				}
			}
			else if (_k->__get_type() == "string") {
				if (write_string(sub_tmp, hKey, _k->__get_value())) {
					RegCloseKey(hKey);
					return true;
				}
				else {
					RegCloseKey(hKey);
					return false;
				}
			}
		}
		return false;
	}

	bool oreg::read(key_base *_k) {
		HKEY hKey = 0;

		std::string path_tmp = _k->__get_key_path();
		std::string sub_tmp = _k->__get_sub_key();

		long result = RegOpenKeyExA(_k->__get_def_key(), path_tmp.c_str(), 0, KEY_QUERY_VALUE, &hKey);

		_print_if_error(result);

		if (result == ERROR_SUCCESS) {
			if(_k->__get_type() == "int" || _k->__get_type() == "bool"){
				std::string read_buffer = read_int(sub_tmp, hKey);
				if (read_buffer != "NULL") {
					_k->set_value(read_buffer);
					RegCloseKey(hKey);
					return true;
				}
				else {
					RegCloseKey(hKey);
					return false;
				}
			}
			else if (_k->__get_type() == "string") {
				std::string read_buffer = read_string(sub_tmp, hKey);
				if (read_buffer != "NULL") {
					_k->set_value(read_buffer);
					RegCloseKey(hKey);
					return true;
				}
				else {
					RegCloseKey(hKey);
					return false;
				}
			}
		}
		else {
			RegCloseKey(hKey);
			return false;
		}
		return false;
	}

	/*
	PRIVATE
	*/
	std::string oreg::read_int(std::string sub, HKEY _key) {
		DWORD lpbuffer = 0;
		DWORD buffersize = sizeof(DWORD);
		long result = RegQueryValueExA(_key, sub.c_str(), NULL, NULL, (LPBYTE)&lpbuffer, &buffersize);
		_print_if_error(result);
		if (result == ERROR_SUCCESS) {
			return std::to_string(lpbuffer);
		}
		else {
			return "NULL";
		}
	}
	std::string oreg::read_string(std::string sub, HKEY _key) {
		char lpbuffer[1024] = { 0 };
		DWORD buffersize = sizeof(lpbuffer);
		long result = RegQueryValueExA(_key, sub.c_str(), NULL, NULL, (LPBYTE)&lpbuffer, &buffersize);
		_print_if_error(result);
		if (result == ERROR_SUCCESS) {
			return lpbuffer;
		}
		else {
			return "NULL";
		}
	}

	bool oreg::write_int(std::string sub, HKEY _key, std::string data) {
		DWORD lpbuffer = std::stoi(data);
		long result = RegSetValueExA(_key, sub.c_str(), 0, REG_DWORD, (BYTE*)&lpbuffer, sizeof(lpbuffer));
		_print_if_error(result);

		if (result == ERROR_SUCCESS) {
			return true;
		}
		return false;
	}

	bool oreg::write_string(std::string sub, HKEY _key, std::string data) {
		long result = RegSetValueExA(_key, sub.c_str(), 0, REG_SZ, (BYTE*)data.c_str(), data.size());
		_print_if_error(result);
		if (result == ERROR_SUCCESS) {
			return true;
		}
		return false;
	}

	/*//*/
}