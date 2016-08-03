#pragma once

#include <ctime>
#include <string>

class Instant {
	public:

	enum WEEKDAY {
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};

	enum MONTH {
		JANUARY,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	Instant();
	Instant(time_t time);

	Instant& operator=(Instant& otherTime);
	Instant& operator=(time_t& otherTime);
	Instant& operator+=(Instant& otherTime);
	Instant& operator+=(time_t& otherTime);
	Instant operator+(Instant& otherTime);
	Instant operator+(time_t& otherTime);

	std::string Display();
	std::string Display(std::string format);

	time_t Time();
	Instant& now();
	int Year();
	int Month();
	int DayOfMonth();
	int DayOfYear();
	int DayOfWeek();
	int Hour();
	int Minute();
	int Second();

	bool IsAM();
	bool IsPM();

	void Year(int year);
	void Month(int month);
	void Month(MONTH month);
	void DayOfMonth(int day);
	void DayOfYear(int day);
	void DayOfWeek(int day);
	void Hour(int hour);
	void Minute(int minute);
	void Second(int second);

	private:
	time_t timeData;

	static const int YEAR_DIFFERENCE_TO_MK = 1900;

	std::string leadZeroes(std::string str, int desiredLength);
};