#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORIGIN_YEAR 1206
#define ORIGIN_MONTH 1
#define ORIGIN_DAY 1

void CalendarMenu();
void AgeMenu();
void ConversionMenu();

// تشخیص کبیسه بودن یک سال شمسی
bool IsShamsiKabise(int y)
{
    // لیست سال‌های کبیسه
    int kabiseYears[71] = {
        1210, 1214, 1218, 1222, 1226, 1230, 1234, 1238,
        1243, 1247, 1251, 1255, 1259, 1263, 1267, 1271,
        1276, 1280, 1284, 1288, 1292, 1296, 1300, 1304,
        1309, 1313, 1317, 1321, 1325, 1329, 1333, 1337,
        1342, 1346, 1350, 1354, 1358, 1362, 1366, 1370,
        1375, 1379, 1383, 1387, 1391, 1395, 1399, 1403,
        1408, 1412, 1416, 1420, 1424, 1428, 1432, 1436,
        1441, 1445, 1449, 1453, 1457, 1461, 1465, 1469,
        1474, 1478, 1482, 1486, 1490, 1494, 1498};

    for (int i = 0; i < 71; ++i)
    {
        if (kabiseYears[i] == y)
        {
            // اگر در لیست بود کبیسه است
            return true;
        }
        else if (y < kabiseYears[i])
        {
            // اگر سال موردنظر از سال کبیسه بزرگتر شد نیازی نیست باقی سال‌های را مقایسه کنیم
            break;
        }
    }
    return false;
}

// تعداد روزهای یک ماه در تقویم شمسی
int ShamsiMonthDays(int y, int m)
{
    if (m <= 6)
    {
        // شش ماه اول
        return 31;
    }
    else if (m == 12 && !IsShamsiKabise(y))
    {
        // بیست و نه روز اسفند غیر کبیسه
        return 29;
    }
    else
    {
        // سایر ماه‌ها + اسفند در کبیسه
        return 30;
    }
}

// محاسبه‌ی روزهای گذشته شده از مبدا زمان در تاریخ شمسی
int mohasebeShamsiDays(int y, int m, int d)
{
    int days = 0;

    // افزودن روزهای قبل از سال فعلی
    for (int i = ORIGIN_YEAR; i < y; i++)
    {
        days += 365;

        // افزودن روز اضافی اگه سال کبیسه بود
        if (IsShamsiKabise(i))
        {
            days++;
        }
    }

    // افزودن روزهای قبل از ماه فعلی
    for (int i = 1; i < m; i++)
    {
        days += ShamsiMonthDays(y, i);
    }

    // افزودن روزهای این ماه
    days += d - 1;

    return days;
}

// تشخیص کبیسه بودن یک سال شمسی
bool IsHijriKabise(int year)
{
    if ((((11 * year) + 14) % 30) < 11)
        return true;
    else
        return false;
}

// تعداد روزهای یک ماه در تقویم قمری
int HijriiMonthDays(int month, int year)
{
    if (((month % 2) == 1) || ((month == 12) && IsHijriKabise(year)))
        return 30;
    else
        return 29;
}

// محاسبه‌ی روزهای گذشته شده از مبدا زمان در تاریخ قمری
int mohasebeHijriDays(int year, int month, int day)
{
    return (day                                   // روز های گذشته زده از این ماه
            + 29 * (month - 1)                    // روز های گذشته شده...
            + month / 2                           //                  ...از این سال
            + 354 * ((year - 1242))               // سال‌های گذشته‌شده‌ی غیر کبیسه
            + (3 + (11 * (year - 1242 + 1))) / 30 // سال‌های گذشته  شده‌ی کبیسه
            - 229);                               // فاصله‌ی مبدا قمری با مبدا شمسی
}

// نام روز هفته
char *GetWeekDayName(int d)
{
    switch (d)
    {
    case 0:
        return "Shanbe";
    case 1:
        return "Yekshanbe";
    case 2:
        return "Doshanbe";
    case 3:
        return "Seshanbe";
    case 4:
        return "Chaharshanbe";
    case 5:
        return "Panjshanbe";
    case 6:
        return "Jome";
    }
    return "";
}

// نام ماه به شمسی
char *GetShamsiMonthName(int m)
{
    switch (m)
    {
    case 1:
        return "Farvardin";
    case 2:
        return "Ordibehesht";
    case 3:
        return "Khordad";
    case 4:
        return "Tir";
    case 5:
        return "Mordad";
    case 6:
        return "Sharivar";
    case 7:
        return "Mehr";
    case 8:
        return "Aban";
    case 9:
        return "Azar";
    case 10:
        return "Day";
    case 11:
        return "Bahman";
    case 12:
        return "Esfand";
    }
    return "";
}

// نام ماه به قمری
char *GetHijriMonthName(int m)
{
    switch (m)
    {
    case 1:
        return "Muharram";
    case 2:
        return "Safar";
    case 3:
        return "Rabi Al-Awwal";
    case 4:
        return "Rabi Al-Akhar";
    case 5:
        return "Jumada Al-Awwal";
    case 6:
        return "Jumada Al-Akhirah";
    case 7:
        return "Rajab";
    case 8:
        return "Shaban";
    case 9:
        return "Ramadan";
    case 10:
        return "Shawwal";
    case 11:
        return "Dhul-Qadah";
    case 12:
        return "Dhul-Hijjah";
    }
    return "";
}

// نام ماه به میلادی
char *GetMiladiMonthName(int m)
{
    switch (m)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    }
    return "";
}

// تبدیل شمسی به میلادی
void ShamsiToMiladi(int year, int month, int day)
{
    int sal, mah, rooz;

    // محاسبه‌ی سال
    if (month == 10 && day > 10)
    {
        sal = year + 622;
    }
    else
    {
        sal = year + 621;
    }

    // محاسبه‌ی روز و ماه
    if (month == 1)
    {
        if (day < 12)
        {
            mah = 3;
            rooz = day + 20;
        }
        else
        {
            mah = 4;
            rooz = day - 11;
        }
    }
    else if (month == 2)
    {

        if (day < 11)
        {
            mah = 4;
            rooz = day + 20;
        }
        else
        {
            mah = 5;
            rooz = day - 10;
        }
    }
    else if (month == 3)
    {
        if (day < 11)
        {
            mah = 5;
            rooz = day + 21;
        }
        else
        {
            mah = 6;
            rooz = day - 10;
        }
    }
    else if (month == 4)
    {
        if (day < 10)
        {
            mah = 6;
            rooz = day + 21;
        }
        else
        {
            mah = 7;
            rooz = day - 9;
        }
    }
    else if (month == 5)
    {
        if (day < 10)
        {
            mah = 7;
            rooz = day + 22;
        }
        else
        {
            mah = 8;
            rooz = day - 9;
        }
    }
    else if (month == 6)
    {
        if (day < 10)
        {
            mah = 8;
            rooz = day + 22;
        }
        else
        {
            mah = 9;
            rooz = day - 9;
        }
    }
    else if (month == 7)
    {
        if (day < 9)
        {
            mah = 9;
            rooz = day + 22;
        }
        else
        {
            mah = 10;
            rooz = day - 8;
        }
    }
    else if (month == 8)
    {
        if (day < 10)
        {
            mah = 10;
            rooz = day + 22;
        }
        else
        {
            mah = 11;
            rooz = day - 9;
        }
    }
    else if (month == 9)
    {
        if (day < 10)
        {
            mah = 11;
            rooz = day + 21;
        }
        else
        {
            mah = 12;
            rooz = day - 9;
        }
    }
    else if (month == 10)
    {
        if (day < 11)
        {
            mah = 12;
            rooz = day + 21;
        }
        else
        {
            mah = 1;
            rooz = day - 10;
        }
    }
    else if (month == 11)
    {
        if (day < 12)
        {
            mah = 1;
            rooz = day + 20;
        }
        else
        {
            mah = 2;
            rooz = day - 11;
        }
    }
    else
    {
        if (day < 11)
        {
            mah = 2;
            rooz = day + 19;
        }
        else
        {
            mah = 3;
            rooz = day - 10;
        }
    }

    // چاپ کردن
    printf("%d %s %d\n", sal, GetMiladiMonthName(mah), rooz);
}

// تبدیل شمسی به قمری
void ShamsiToHijri(int y, int m, int d)
{
    int days, sal, mah, rooz;
    days = mohasebeShamsiDays(y, m, d) + 1;

    // محاسبه‌ی سال قمری
    sal = 1242; // مبدا سال قمری
    while (days >= mohasebeHijriDays(sal, 1, 1))
    {
        sal++;
    }
    sal--; // کم کردن سال آخر

    // محاسبه‌ی ماه‌های قمری
    mah = 1;
    while (days > mohasebeHijriDays(sal, mah, HijriiMonthDays(mah, sal)))
    {
        mah++;
    }

    rooz = days - mohasebeHijriDays(sal, mah, 1) + 1;

    printf("%d %s %d\n", sal, GetHijriMonthName(mah), rooz);
}

// چاپ‌کردن نتیجه‌ی تقویم
void PrintCalendar(int y, int m)
{
    int startDay, i;

    startDay = (mohasebeShamsiDays(y, m, 1) // روزهای قبل از این تاریخ
                + 5                         // اولین روز مبدا زمان پنجشنبه است
                ) %
               7;

    // چاپ سال و ماه بالای تقویم
    printf("\x1b[38;5;231m");
    printf("\x1b[48;5;183m");
    if (m < 13 && m >= 1)
    {

        if (m == 1)
        {
            printf("%d   FARVARDIN    \n", y);
        }
        else if (m == 2)
        {
            printf("%d   ORDIBEHESHT   \n", y);
        }
        else if (m == 3)
        {
            printf("%d    KHORDAD     \n", y);
        }
        else if (m == 4)
        {
            printf("%d      TIR       \n", y);
        }
        else if (m == 5)
        {
            printf("%d     MORDAD     \n", y);
        }
        else if (m == 6)
        {
            printf("%d   SHAHRIVAR    \n", y);
        }
        else if (m == 7)
        {
            printf("%d      MEHR      \n", y);
        }
        else if (m == 8)
        {
            printf("%d      ABAN      \n", y);
        }
        else if (m == 9)
        {
            printf("%d      AZAR      \n", y);
        }
        else if (m == 10)
        {
            printf("%d      DEY       \n", y);
        }
        else if (m == 11)
        {
            printf("%d     BAHMAN     \n", y);
        }
        else if (m == 12)
        {
            printf("%d     ESFAND     \n", y);
        }
        printf("\x1b[0m");

        printf("SH Ye DO SE CH PN JO\n");
        for (i = 0; i < startDay; i++)
        {
            // چاپ فضای خالی
            printf("   ");
        }
        for (i = 1; i <= ShamsiMonthDays(y, m); i++)
        {
            // چاپ تاریخ روز
            printf("%2d ", i);

            // رفتن به خط بعدی
            if ((startDay + i) % 7 == 0)
            {
                printf("\n");
            }
        }
        printf("\n\n");
    }
    else
    {
        printf("You enterd invalid date\n");
        printf("\n\n");
    }
}

// چاپ‌کردن نتیجه‌ی سن
void PrintAgeDetails(int now_year, int now_month, int now_day, int birth_year, int birth_month, int birth_day)
{
    int sal, mah, rooz, roozhaye_zendegi;
    if (now_year >= 1206 && now_month >= 1 && now_month <= 12 && now_day >= 1 && now_day <= 31 && birth_year >= 1206 && birth_month >= 1 && birth_month <= 12 && birth_day >= 1 && birth_day <= 31)
    {

        // محاسبه‌ی تعداد سال
        sal = now_year - birth_year;

        // محاسبه‌ی تعداد ماه
        if (birth_month > now_month)
        {
            // اگر ماه تولد بزرگتر از ماه الان بود یک سال از تعداد سال‌ها کم می‌کنیم و به تعداد ماه‌ها اضافی می‌کنیم
            sal--;
            mah = now_month + (12 - birth_month);
        }
        else
        {
            mah = now_month - birth_month;
        }

        if (birth_day > now_day)
        {
            // اگر روز تولد بزرگتر از روز الان بود یک ماه از تعداد ماه‌ها کم می‌کنیم و به تعداد روزها اضافی می‌کنیم
            mah--;
            rooz = now_day + (ShamsiMonthDays(birth_year, birth_month) - birth_day);
        }
        else
        {
            rooz = now_day - birth_day;
        }
        // تعداد روز های گذشته شذه از عمر: (روزهای گذشته شده از امروز - روزهای گذشته شده از روز تولد)
        roozhaye_zendegi = mohasebeShamsiDays(now_year, now_month, now_day) - mohasebeShamsiDays(birth_year, birth_month, birth_day);

        // چاپ کردن
        printf("Your age is ");
        printf("%d Years, %d Months, %d Days\n", sal, mah, rooz);
        printf("Your life days: %d\n", roozhaye_zendegi);
        printf("You born on %s\n", GetWeekDayName((mohasebeShamsiDays(birth_year, birth_month, birth_day) + 5) % 7));
        printf("Shamsi %d %s %d\n", birth_year, GetShamsiMonthName(birth_month), birth_day);
        printf("Miladi ");
        ShamsiToMiladi(birth_year, birth_month, birth_day);
        printf("Hijri  ");
        ShamsiToHijri(birth_year, birth_month, birth_day);
        printf("\n");
    }
    else
    {
        printf("You enterd invalid date\n\n");
    }
}

void CalendarMenu()
{
    int selected_option, year, month;
    do
    {
        printf("\x1b[48;5;232m");
        printf("                       Calendar Menu                        \n");
        printf("\x1b[48;5;240m");
        printf("                       Select Option                        \n");
        printf("\x1b[38;5;232m");
        printf("\x1b[48;5;255m");
        printf("[0] Back To Main Menu                                       \n");
        printf("[1] Continue                                                \n");
        printf("\x1b[0m");
        printf("Enter Option: ");

        scanf("%d", &selected_option);

        system("clear");

        switch (selected_option)
        {
        case 0:
            break;
        case 1:
            printf("Enter Year: ");
            scanf("%d", &year);

            printf("Enter Month: ");
            scanf("%d", &month);
            system("clear");
            PrintCalendar(year, month);
            break;
        default:
            printf("\x1b[38;5;196m");
            printf("                       Invalid Option                       \n");
            printf("\x1b[0m");
        }
    } while (selected_option != 0);
}

void AgeMenu()
{
    int selected_option, now_year, now_month, now_day, birth_year, birth_month, birth_day;
    do
    {
        printf("\x1b[48;5;232m");
        printf("                    Age Calculation Menu                    \n");
        printf("\x1b[48;5;240m");
        printf("                       Select Option                        \n");
        printf("\x1b[38;5;232m");
        printf("\x1b[48;5;255m");
        printf("[0] Back To Main Menu                                       \n");
        printf("[1] Continue                                                \n");
        printf("\x1b[0m");
        printf("Enter Option: ");

        scanf("%d", &selected_option);

        system("clear");

        switch (selected_option)
        {
        case 0:
            break;
        case 1:
            printf("Enter Today    [Year Month Day]: ");
            scanf("%d %d %d", &now_year, &now_month, &now_day);
            printf("Enter Birthday [Year Month Day]: ");
            scanf("%d %d %d", &birth_year, &birth_month, &birth_day);
            system("clear");
            PrintAgeDetails(now_year, now_month, now_day, birth_year, birth_month, birth_day);
            break;
        default:
            printf("\x1b[38;5;196m");
            printf("                       Invalid Option                       \n");
            printf("\x1b[0m");
        }
    } while (selected_option != 0);
}

void ConversionMenu()
{
    int selected_option, year, month, day;

    do
    {
        printf("\x1b[48;5;232m");
        printf("                    Date Conversion Menu                    \n");
        printf("\x1b[48;5;240m");
        printf("                       Select Option                        \n");
        printf("\x1b[38;5;232m");
        printf("\x1b[48;5;255m");
        printf("[0] Back To Main Menu                                       \n");
        printf("[1] Continue                                                \n");
        printf("\x1b[0m");
        printf("Enter Option: ");

        scanf("%d", &selected_option);

        system("clear");
        switch (selected_option)
        {
        case 0:
            break;
        case 1:
            printf("Enter Date [Year Month Day]: ");
            scanf("%d %d %d", &year, &month, &day);
            if (year >= 1206 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                system("clear");
                printf("Shamsi %d %s %d\n", year, GetShamsiMonthName(month), day);
                printf("Miladi ");
                ShamsiToMiladi(year, month, day);
                printf("Hijri  ");
                ShamsiToHijri(year, month, day);
                printf("\n");
            }
            else
            {
                printf("\x1b[38;5;196m");
                printf("                       Invalid Input                        \n");
                printf("\x1b[0m");
            }
            break;
        default:
            printf("\x1b[38;5;196m");
            printf("                       Invalid Option                       \n");
            printf("\x1b[0m");
        }
    } while (selected_option != 0);
}

int main()
{
    system("clear");

    int selected_option;
    do
    {
        printf("\x1b[48;5;232m");
        printf("                         Main Menu                          \n");
        printf("\x1b[48;5;240m");
        printf("                       Select Option                        \n");
        printf("\x1b[38;5;232m");
        printf("\x1b[48;5;255m");
        printf("[0] Exit                                                    \n");
        printf("[1] Calendar                                                \n");
        printf("[2] Age Calculation                                         \n");
        printf("[3] Date Conversion                                         \n");
        printf("\x1b[0m");
        printf("Enter Option: ");
        scanf("%d", &selected_option);
        system("clear");
        switch (selected_option)
        {
        case 0:
            printf("                    Thank you, Goodbye!                     \n");
            break;
        case 1:
            CalendarMenu();
            system("clear");
            break;
        case 2:
            AgeMenu();
            system("clear");
            break;
        case 3:
            ConversionMenu();
            system("clear");
            break;
        default:
            system("clear");
            printf("\x1b[38;5;196m");
            printf("                       Invalid Option                       \n");
            printf("\x1b[0m");
        }
    } while (selected_option != 0);
    return 0;
}
