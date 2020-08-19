#include "ofile.h"

namespace olib{

	void ofile::set_size(long long file_size) {
		_size = file_size;
		kilo = (long)(file_size / 1000);
		mega = (long)(file_size / 1000000);
		giga = (long)(file_size / 1000000000);
		//These two probably wont be used that much
		tera = (long)(file_size / 1000000000000);
		peta = (long)(file_size / 1000000000000000);
	}

	long long ofile::size_by_metric(metric _m) {
		switch (_m)
		{
		case metric::BYTE:
			return _size;
			break;
		case metric::KILO:
			return kilo;
			break;
		case metric::MEGA:
			return mega;
			break;
		case metric::GIGA:
			return giga;
			break;
		case metric::TERA:
			return tera;
			break;
		case metric::PETA:
			return peta;
			break;
		default:
			return 0;
			break;
		}
	}

	std::string ofile::size_format() {
		if (peta > 0)
			return std::string(std::to_string(peta) + "PB");
		else if (tera > 0)
			return std::string(std::to_string(tera) + "TB");
		else if (giga > 0)
			return std::string(std::to_string(giga) + "GB");
		else if (mega > 0)
			return std::string(std::to_string(mega) + "MB");
		else if (kilo > 0)
			return std::string(std::to_string(kilo) + "kB");
		else
			return std::string(std::to_string(_size) + "b");
	}

	std::string ofile::size_format_by_metric(metric _m) {
		switch (_m)
		{
		case metric::BYTE:
			return std::string(std::to_string(_size) + "b");
			break;
		case metric::KILO:
			return std::string(std::to_string(kilo) + "kB");
			break;
		case metric::MEGA:
			return std::string(std::to_string(mega) + "MB");
			break;
		case metric::GIGA:
			return std::string(std::to_string(giga) + "GB");
			break;
		case metric::TERA:
			return std::string(std::to_string(tera) + "TB");
			break;
		case metric::PETA:
			return std::string(std::to_string(peta) + "PB");
			break;
		default:
			return 0;
			break;
		}
	}

}