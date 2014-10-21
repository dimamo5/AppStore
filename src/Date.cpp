/*
 * Date.cpp
 *
 *  Created on: 18/10/2014
 *      Author: Casa
 */

#include "Date.h"

Date::Date(){}

Date::Date(struct tm* time_struct){
	this->year = time_struct->tm_year + 1900;
	this->month = time_struct->tm_mon +1;
	this->day = time_struct->tm_mday;
	this->hour = time_struct->tm_hour;
	this->minute = time_struct->tm_min;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day,
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
			} else {						// if the year, month and day are equal

				if (hour < dat.getHour()) {
					return true;
				} else if (hour > dat.getHour()) {
					return false;
				} else {					// if the year, month, day and hour were equal

					if (minute < dat.getMinute()) {
						return true;
					} else if (minute > dat.getMinute()) {
						return false;
					}
					else{
						return false; // everything was equal
					}
				}
			}
		}

	}

}

