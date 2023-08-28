#ifndef LIBKIFANCYASCII_HPP
#define LIBKIFANCYASCII_HPP

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace libkifancyascii{
	string get_string_n_times(const string str, const long long n=1){
		if (n <= 0)
			return "";

		string out = "";
		for (unsigned long long i=0; i<n; i++)
			out += str;

		return out;
	}

	string cutoff(const string str, const unsigned long long maxSize){
		if (str.size() <= maxSize)
			return str;

		return str.substr(0, maxSize);
	}

	string fill_space(const string str, const unsigned long long spaceLength, const string spaceSymbol, const unsigned long long maxDotDotDotLength = 0, const string dotDotDotSymbol="."){
		const bool useDotDotDot = str.size() > spaceLength;
		const unsigned long long dotDotDotLength = useDotDotDot * maxDotDotDotLength;
		return cutoff(str, spaceLength - dotDotDotLength) + get_string_n_times(spaceSymbol, spaceLength - str.size() - dotDotDotLength) + get_string_n_times(dotDotDotSymbol, dotDotDotLength);
	}

	vector <unsigned long long> get_column_widths(const vector <vector <string>> table){
		vector <unsigned long long> out(table[0].size(), 0);
		for (vector <string> row : table){
			for (unsigned long long i=0; i<row.size(); i++)
				out[i] = (row[i].size() > out[i]) ? (row[i].size()) : out[i];
		}

		return out;
	}

	struct Table{
//		string topLeftCorner="/", topRightCorner="\\", bottomLeftCorner="\\", bottomRightCorner="/";
		string topLeftCorner="+", topRightCorner="+", bottomLeftCorner="+", bottomRightCorner="+";
		string delimiterSymbol   = "+";
		string lengthSymbol      = "-";
		string heightSymbol      = "|";
		string spaceSymbol       = " ";
		string dotDotDotSymbol   = ".";

		vector <vector <string>> contents;

		void print(const unsigned long long paddingLeft=1, const unsigned long long paddingRight=1, const unsigned long long maxDotDotDotLength=0, vector <unsigned long long> columnMinWidths={}, const string optionalTitle=""){
			if (contents.empty())
				return;

			if (contents[0].empty())
				return;

			vector <unsigned long long> columnWidths = get_column_widths(contents);
			if (columnMinWidths.size() != columnWidths.size())
				columnMinWidths = columnWidths;

			// Make sure all the columnWidths are atleast the minimum width
			for (unsigned long long i=0; i<columnWidths.size(); i++)
				columnWidths[i] = (columnWidths[i] < columnMinWidths[i]) ? (columnMinWidths[i]) : (columnWidths[i]);

			// Print first line
			std::cout << topLeftCorner << get_string_n_times(lengthSymbol, paddingLeft) << fill_space(optionalTitle, columnWidths[0], lengthSymbol, maxDotDotDotLength, dotDotDotSymbol) << get_string_n_times(lengthSymbol, paddingRight);

			if (columnWidths.size() == 1)
				std::cout << topRightCorner;
			else
				std::cout << delimiterSymbol;

			for (unsigned long long i=1; i<columnWidths.size(); i++){
				std::cout << get_string_n_times(lengthSymbol, paddingLeft) << get_string_n_times(lengthSymbol, columnWidths[i]) << get_string_n_times(lengthSymbol, paddingRight);

				if (i == columnWidths.size() - 1)
					std::cout << topRightCorner;
				else
					std::cout << delimiterSymbol;
			}

			// Now, the contents
			for (vector <string> row : contents){
				std::cout << '\n' << heightSymbol;

				for (unsigned long long i=0; i<row.size(); i++)
					std::cout << get_string_n_times(spaceSymbol, paddingLeft) << fill_space(row[i], columnWidths[i], spaceSymbol, maxDotDotDotLength, dotDotDotSymbol) << get_string_n_times(spaceSymbol, paddingRight) << heightSymbol;
			}

			std::cout << '\n';

			// Last line
			std::cout << bottomLeftCorner << get_string_n_times(lengthSymbol, paddingLeft) << get_string_n_times(lengthSymbol, columnWidths[0]) << get_string_n_times(lengthSymbol, paddingRight);
			if (columnWidths.size() == 1)
				std::cout << bottomRightCorner;
			else
				std::cout << delimiterSymbol;

			for (unsigned long long i=1; i<columnWidths.size(); i++){
				std::cout << get_string_n_times(lengthSymbol, paddingLeft) << get_string_n_times(lengthSymbol, columnWidths[i]) << get_string_n_times(lengthSymbol, paddingRight);

				if (i == columnWidths.size() - 1)
					std::cout << bottomRightCorner;
				else
					std::cout << delimiterSymbol;
			}

			std::cout << '\n';
		}
	};
}

#endif // LIBKIFANCYASCII_HPP
