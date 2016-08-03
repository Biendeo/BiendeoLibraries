#include "Time.h"
#include "Instant.h"


std::string Instant::leadZeroes(std::string str, int desiredLength) {
	for (int i = str.length(); i < desiredLength; i++) {
		str = "0" + str;
	}
	return str;
}

Instant::Instant() {
	timeData = static_cast<time_t>(0);
}

Instant::Instant(time_t time) {
	this->timeData = time;
}

std::string Instant::Display(std::string format) {
	size_t foundPos;

	while ((foundPos = format.find("a")) != std::string::npos) {
		format.replace(foundPos, 1, "\v");
	}

	while ((foundPos = format.find("YYYY")) != std::string::npos) {
		format.replace(foundPos, 4, std::to_string(Year()));
	}

	while ((foundPos = format.find("MMM")) != std::string::npos) {
		format.replace(foundPos, 3, "\t");
	}

	while ((foundPos = format.find("MM")) != std::string::npos) {
		format.replace(foundPos, 2, leadZeroes(std::to_string(Month()), 2));
	}

	while ((foundPos = format.find("M")) != std::string::npos) {
		format.replace(foundPos, 1, std::to_string(Month()));
	}

	while ((foundPos = format.find("dd")) != std::string::npos) {
		format.replace(foundPos, 2, leadZeroes(std::to_string(DayOfMonth()), 2));
	}

	while ((foundPos = format.find("d")) != std::string::npos) {
		format.replace(foundPos, 1, std::to_string(DayOfMonth()));
	}

	while ((foundPos = format.find("hh")) != std::string::npos) {
		format.replace(foundPos, 2, leadZeroes(std::to_string(Hour()), 2));
	}

	while ((foundPos = format.find("h")) != std::string::npos) {
		format.replace(foundPos, 1, std::to_string(Hour()));
	}

	while ((foundPos = format.find("mm")) != std::string::npos) {
		format.replace(foundPos, 2, leadZeroes(std::to_string(Minute()), 2));
	}

	while ((foundPos = format.find("ss")) != std::string::npos) {
		format.replace(foundPos, 2, leadZeroes(std::to_string(Second()), 2));
	}

	/*
	while ((foundPos = format.find("EEE")) != std::string::npos) {
		format.replace(foundPos, 3, weekdayToStrShort(intToWeekday(DayOfWeek())));
	}

	while ((foundPos = format.find("\t")) != std::string::npos) {
		format.replace(foundPos, 1, monthToStrShort(intToMonth(Month())));
	}*/

	while ((foundPos = format.find("\v")) != std::string::npos) {
		if (IsAM()) {
			format.replace(foundPos, 1, "AM");
		} else {
			format.replace(foundPos, 1, "PM");
		}
	}

	return format;
}

std::string Instant::Display() {
	return Display("EEE dd/MM/YYYY hh:mm:ss");
}

time_t Instant::Time() {
	return timeData;
}

Instant & Instant::now() {
	timeData = std::time(NULL);
	return *this;
}

int Instant::Year() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_year + YEAR_DIFFERENCE_TO_MK;
}

int Instant::Month() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_mon + 1;
}

int Instant::DayOfMonth() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_mday;
}

int Instant::DayOfYear() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_yday;
}

int Instant::DayOfWeek() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_wday;
}

int Instant::Hour() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_hour;
}

int Instant::Minute() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_min;
}

int Instant::Second() {
	// TODO: Create own localtime function to make it thread-safe.
	return localtime(&timeData)->tm_sec;
}

bool Instant::IsAM() {
	if (Hour() < 12) {
		return true;
	} else {
		return false;
	}
}

bool Instant::IsPM() {
	return !IsAM();
}

void Instant::Year(int year) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_year = year - YEAR_DIFFERENCE_TO_MK;
	timeData = mktime(timeStruct);
}

void Instant::Month(int month) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_mon = month - 1;
	timeData = mktime(timeStruct);
}

void Instant::Month(MONTH month) {
	// TODO
}

void Instant::DayOfMonth(int day) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_mday = day;
	timeData = mktime(timeStruct);
}

void Instant::DayOfYear(int day) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_yday = day;
	timeData = mktime(timeStruct);
}

void Instant::DayOfWeek(int day) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_yday = day;
	timeData = mktime(timeStruct);
}

void Instant::Hour(int hour) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_hour = hour;
	timeData = mktime(timeStruct);
}

void Instant::Minute(int minutes) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_min = minutes;
	timeData = mktime(timeStruct);
}

void Instant::Second(int seconds) {
	// TODO: Determine behaviour when time is out of range.
	tm *timeStruct = localtime(&timeData);
	timeStruct->tm_sec = seconds;
	timeData = mktime(timeStruct);
}

/*
MONTH Instant::intToMonth(int i) {
	switch (i) {
		case 1:
			return JANUARY;
		case 2:
			return FEBRUARY;
		case 3:
			return MARCH;
		case 4:
			return APRIL;
		case 5:
			return MAY;
		case 6:
			return JUNE;
		case 7:
			return JULY;
		case 8:
			return AUGUST;
		case 9:
			return SEPTEMBER;
		case 10:
			return OCTOBER;
		case 11:
			return NOVEMBER;
		case 12:
			return DECEMBER;
		default:
			// TODO: Decide what happens with invalid input.
			return JANUARY;
	}
}

std::string Instant::monthToStrShort(MONTH month) {
	switch (month) {
		case JANUARY:
			return "Jan";
		case FEBRUARY:
			return "Feb";
		case MARCH:
			return "Mar";
		case APRIL:
			return "Apr";
		case MAY:
			return "May";
		case JUNE:
			return "Jun";
		case JULY:
			return "Jul";
		case AUGUST:
			return "Aug";
		case SEPTEMBER:
			return "Sep";
		case OCTOBER:
			return "Oct";
		case NOVEMBER:
			return "Nov";
		case DECEMBER:
			return "Dec";
		default:
			// TODO: Decide what happens with invalid input.
			return "???";
	}
}

WEEKDAY Instant::intToWeekday(int i) {
	switch (i) {
		case 0:
			return MONDAY;
		case 1:
			return TUESDAY;
		case 2:
			return WEDNESDAY;
		case 3:
			return THURSDAY;
		case 4:
			return FRIDAY;
		case 5:
			return SATURDAY;
		case 6:
			return SUNDAY;
		default:
			// TODO: Decide what happens with invalid input.
			return MONDAY;
	}
}

std::string Instant::weekdayToStrShort(WEEKDAY weekday) {
	switch (weekday) {
		case MONDAY:
			return "Mon";
		case TUESDAY:
			return "Tue";
		case WEDNESDAY:
			return "Wed";
		case THURSDAY:
			return "Thu";
		case FRIDAY:
			return "Fri";
		case SATURDAY:
			return "Sat";
		case SUNDAY:
			return "Sun";
		default:
			// TODO: Decide what happens with invalid input.
			return "???";
	}
}

*/