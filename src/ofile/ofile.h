#pragma once
#include <string>
namespace olib {
	class ofile {
	private:
		long long _size = 0;
		long kilo = 0;
		long mega = 0;
		long giga = 0;
		long tera = 0;
		long peta = 0;
	public:
		enum class metric {
			BYTE,
			KILO,
			MEGA,
			GIGA,
			TERA,
			PETA
		};

	public:
		void set_size(long long file_size);
		long long size_by_metric(metric _m);
		std::string size_format();
		std::string size_format_by_metric(metric _m);
	public:
		ofile() {}
		ofile(long long file_size) { set_size(file_size); }
	};
}