/*
 * Date.cpp
 *
 *  Created on: 18/10/2014
 *      Author: Casa
 */

#include "Date.h"

Date::Date() {   // default constructor
}

Date::Date(struct tm* time_struct) { // constructor initizalized with a time_struct
	this->year = time_struct->tm_year + 1900;
	this->month = time_struct->tm_mon + 1;
	this->day = time_struct->tm_mday;
	this->hour = time_struct->tm_hour;
	this->minute = time_struct->tm_min;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day, //constructor initialized with a whole date
		unsigned int hour, unsigned int minute) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
}

unsigned int Date::getMinute() const {
	return minute;
}
unsigned int Date::getHour() const {
	return hour;
}
unsigned int Date::getDay() const {
	return day;
}
unsigned int Date::getMonth() const {
	return month;
}
unsigned int Date::getYear() const {
	return year;
}

bool Date::setMinute(unsigned int minute) {
	if (minute > 59 || minute < 0) {
		this->minute = minute;
		return true;
	}
	return false;
}

bool Date::setHour(unsigned int hour) {
	if (hour > 23 || hour < 0) {
		this->hour = hour;
		return true;
	}
	return false;
}

bool Date::setDay(unsigned int day) {
	if (day > 23 || day < 0) {
		this->day = day;
		return true;
	}
	return false;
}

bool Date::setMonth(unsigned int month) {
	if (month > 23 || month < 0) {
		this->month = month;
		return true;
	}
	return false;
}

bool Date::setYear(unsigned int year) {
	if (year > 23 || year < 0) {
		this->year = year;
		return true;
	}
	return false;
}

bool Date::operator<(const Date& dat) const {

	if (year < dat.getYear()) {
		return true;
	} else if (year > dat.getYear()) {
		return false;
	} else {    // if the years are equal

		if (month < dat.getMonth()) {
			return true;
		} else if (month > dat.getMonth()) {
			return false;
		} else {  // if both the year and month are equal

			if (day < dat.getDay()) {
				return true;
			} else if (day > dat.getDay()) {
				return false;
			} else {					// if the year, month and day are equal

				if (hour < dat.getHour()) {
					return true;
				} else if (hour > dat.getHour()) {
					return false;
				} else {		// if the year, month, day and hour were equal

					if (minute < dat.getMinute()) {
						return true;
					} else if (minute > dat.getMinute()) {
						return false;
					} else {
						return false; // everything was equal
					}
				}
			}
		}

	}

}

bool Date::operator>(const Date& dat) const {
	if (year > dat.getYear()) {
		return true;
	} else if (year < dat.getYear()) {
		return false;
	} else {    // if the years are equal

		if (month > dat.getMonth()) {
			return true;
		} else if (month < dat.getMonth()) {
			return false;
		} else {  // if both the year and month are equal

			if (day > dat.getDay()) {
				return true;
			} else if (day < dat.getDay()) {
				return false;
			} else {					// if the year, month and day are equal

				if (hour > dat.getHour()) {
					return true;
				} else if (hour < dat.getHour()) {
					return false;
				} else {		// if the year, month, day and hour were equal

					if (minute > dat.getMinute()) {
						return true;
					} else if (minute < dat.getMinute()) {
						return false;
					} else {
						return false; // everything was equal
					}
				}
			}
		}

	}

}

bool Date::operator==(const Date& dat) const {
	if (year == dat.getYear() && month == dat.getMonth() && day == dat.getDay()
			&& hour == dat.getHour() && minute == dat.getMinute()) {
		return true;
	} else {
		return false;
	}
}

bool Date::operator<=(const Date& dat) const {

	if ((*this) < dat || (*this) == dat) { // if the date is less or equal to the one it is being compared to
		return true;
	} else {
		return false;
	}
}

string Date::imprimeData() const {
	stringstream data;
	data<<year<<"-"<<month<<"-"<<day<<"  "<<hour<<":"<<minute;
	return data.str();
}

bool Date::operator>=(const Date& dat) const {

	if ((*this) > dat || (*this) == dat) { // if the date is less or equal to the one it is being compared to
		return true;
	} else {
		return false;
	}
}

tm make_tm(int year, int month, int day) {
	std::tm tm = { 0 };
	tm.tm_year = year - 1900; // years count from 1900
	tm.tm_mon = month - 1;    // months count from January=0
	tm.tm_mday = day;         // days count from 1
	return tm;
}

double daysBetweenDates(int year1, int month1, int day1, int year2, int month2,
		int day2) {

	// Assume-se que Data1 é mais recente que a Data2. Data1 será a data atual, que é sempre mais recente que a Data2, que é a da venda
	tm tm1 = make_tm(year1, month1, day1);    // Data atual
	tm tm2 = make_tm(year2, month2, day2);   // Data da venda

	std::time_t time1 = std::mktime(&tm1);
	std::time_t time2 = std::mktime(&tm2);

	const int seconds_per_day = 60 * 60 * 24;

	// To be fully portable, we shouldn't assume that these are Unix time;
	// instead, we should use "difftime" to give the difference in seconds:
	double portable_difference = std::difftime(time1, time2) / seconds_per_day;

	return abs(portable_difference);
}

