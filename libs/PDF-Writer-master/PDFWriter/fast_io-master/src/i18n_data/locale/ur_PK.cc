﻿#include"../localedef.h"

namespace fast_io_i18n
{
namespace
{

inline constexpr std::size_t numeric_grouping_storage[]{3};

inline constexpr lc_all lc_all_global{.identification={.name=tsc("ur_PK"),.encoding=tsc(FAST_IO_LOCALE_ENCODING),.title=tsc("Urdu Language Locale for Pakistan"),.source=tsc("fast_io"),.address=tsc("https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc("fast_io"),.email=tsc("bug-glibc-locales@gnu.org;euloanty@live.com"),.tel=tsc(""),.fax=tsc(""),.language=tsc("Urdu"),.territory=tsc("Pakistan"),.revision=tsc("0.3"),.date=tsc("2000-07-11")},.monetary={.int_curr_symbol=tsc("PKR "),.currency_symbol=tsc("Rs"),.mon_decimal_point=tsc("."),.mon_thousands_sep=tsc(","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(""),.negative_sign=tsc("-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=0,.p_sign_posn=2,.n_sign_posn=1},.numeric={.decimal_point=tsc("."),.thousands_sep=tsc(","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc("اتوار"),tsc("پير"),tsc("منگل"),tsc("بدھ"),tsc("جمعرات"),tsc("جمعه"),tsc("هفته")},.day={tsc("اتوار"),tsc("پير"),tsc("منگل"),tsc("بدھ"),tsc("جمعرات"),tsc("جمعه"),tsc("هفته")},.abmon={tsc("جنوری"),tsc("فروری"),tsc("مارچ"),tsc("اپریل"),tsc("مئی"),tsc("جون"),tsc("جولائی"),tsc("اگست"),tsc("ستمبر"),tsc("اکتوبر"),tsc("نومبر"),tsc("دسمبر")},.mon={tsc("جنوری"),tsc("فروری"),tsc("مارچ"),tsc("اپریل"),tsc("مئی"),tsc("جون"),tsc("جولائی"),tsc("اگست"),tsc("ستمبر"),tsc("اکتوبر"),tsc("نومبر"),tsc("دسمبر")},.d_t_fmt=tsc("و %H:%M:%S ت %d %B %Y"),.d_fmt=tsc("%d//%m//%Y"),.t_fmt=tsc("%H:%M:%S"),.t_fmt_ampm=tsc("%P %I:%M:%S"),.date_fmt=tsc("و %H:%M:%S %Z ت %d %B %Y"),.am_pm={tsc("ص"),tsc("ش")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc("^[+1yYهبf]"),.noexpr=tsc("^[-0nNنo]"),.yesstr=tsc("ہاں"),.nostr=tsc("نہیں")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc("+%c ;%a ;%l"),.int_select=tsc("00"),.int_prefix=tsc("92")},.name={.name_fmt=tsc("%d%t%g%t%m%t%f")},.address={.postal_fmt=tsc("%a%N%f%N%d%N%b%N%h %s %e %r%N%T %z%N%c%N"),.country_name=tsc("پاکستان"),.country_ab2=tsc("PK"),.country_ab3=tsc("PAK"),.country_num=586,.country_car=tsc("PK"),.lang_name=tsc("اردو"),.lang_ab=tsc("ur"),.lang_term=tsc("urd"),.lang_lib=tsc("urd")},.measurement={.measurement=1}};

inline constexpr wlc_all wlc_all_global{.identification={.name=tsc(L"ur_PK"),.encoding=tsc(FAST_IO_LOCALE_LENCODING),.title=tsc(L"Urdu Language Locale for Pakistan"),.source=tsc(L"fast_io"),.address=tsc(L"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(L"fast_io"),.email=tsc(L"bug-glibc-locales@gnu.org;euloanty@live.com"),.tel=tsc(L""),.fax=tsc(L""),.language=tsc(L"Urdu"),.territory=tsc(L"Pakistan"),.revision=tsc(L"0.3"),.date=tsc(L"2000-07-11")},.monetary={.int_curr_symbol=tsc(L"PKR "),.currency_symbol=tsc(L"Rs"),.mon_decimal_point=tsc(L"."),.mon_thousands_sep=tsc(L","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(L""),.negative_sign=tsc(L"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=0,.p_sign_posn=2,.n_sign_posn=1},.numeric={.decimal_point=tsc(L"."),.thousands_sep=tsc(L","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(L"اتوار"),tsc(L"پير"),tsc(L"منگل"),tsc(L"بدھ"),tsc(L"جمعرات"),tsc(L"جمعه"),tsc(L"هفته")},.day={tsc(L"اتوار"),tsc(L"پير"),tsc(L"منگل"),tsc(L"بدھ"),tsc(L"جمعرات"),tsc(L"جمعه"),tsc(L"هفته")},.abmon={tsc(L"جنوری"),tsc(L"فروری"),tsc(L"مارچ"),tsc(L"اپریل"),tsc(L"مئی"),tsc(L"جون"),tsc(L"جولائی"),tsc(L"اگست"),tsc(L"ستمبر"),tsc(L"اکتوبر"),tsc(L"نومبر"),tsc(L"دسمبر")},.mon={tsc(L"جنوری"),tsc(L"فروری"),tsc(L"مارچ"),tsc(L"اپریل"),tsc(L"مئی"),tsc(L"جون"),tsc(L"جولائی"),tsc(L"اگست"),tsc(L"ستمبر"),tsc(L"اکتوبر"),tsc(L"نومبر"),tsc(L"دسمبر")},.d_t_fmt=tsc(L"و %H:%M:%S ت %d %B %Y"),.d_fmt=tsc(L"%d//%m//%Y"),.t_fmt=tsc(L"%H:%M:%S"),.t_fmt_ampm=tsc(L"%P %I:%M:%S"),.date_fmt=tsc(L"و %H:%M:%S %Z ت %d %B %Y"),.am_pm={tsc(L"ص"),tsc(L"ش")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(L"^[+1yYهبf]"),.noexpr=tsc(L"^[-0nNنo]"),.yesstr=tsc(L"ہاں"),.nostr=tsc(L"نہیں")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(L"+%c ;%a ;%l"),.int_select=tsc(L"00"),.int_prefix=tsc(L"92")},.name={.name_fmt=tsc(L"%d%t%g%t%m%t%f")},.address={.postal_fmt=tsc(L"%a%N%f%N%d%N%b%N%h %s %e %r%N%T %z%N%c%N"),.country_name=tsc(L"پاکستان"),.country_ab2=tsc(L"PK"),.country_ab3=tsc(L"PAK"),.country_num=586,.country_car=tsc(L"PK"),.lang_name=tsc(L"اردو"),.lang_ab=tsc(L"ur"),.lang_term=tsc(L"urd"),.lang_lib=tsc(L"urd")},.measurement={.measurement=1}};

inline constexpr u8lc_all u8lc_all_global{.identification={.name=tsc(u8"ur_PK"),.encoding=tsc(FAST_IO_LOCALE_u8ENCODING),.title=tsc(u8"Urdu Language Locale for Pakistan"),.source=tsc(u8"fast_io"),.address=tsc(u8"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(u8"fast_io"),.email=tsc(u8"bug-glibc-locales@gnu.org;euloanty@live.com"),.tel=tsc(u8""),.fax=tsc(u8""),.language=tsc(u8"Urdu"),.territory=tsc(u8"Pakistan"),.revision=tsc(u8"0.3"),.date=tsc(u8"2000-07-11")},.monetary={.int_curr_symbol=tsc(u8"PKR "),.currency_symbol=tsc(u8"Rs"),.mon_decimal_point=tsc(u8"."),.mon_thousands_sep=tsc(u8","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u8""),.negative_sign=tsc(u8"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=0,.p_sign_posn=2,.n_sign_posn=1},.numeric={.decimal_point=tsc(u8"."),.thousands_sep=tsc(u8","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u8"اتوار"),tsc(u8"پير"),tsc(u8"منگل"),tsc(u8"بدھ"),tsc(u8"جمعرات"),tsc(u8"جمعه"),tsc(u8"هفته")},.day={tsc(u8"اتوار"),tsc(u8"پير"),tsc(u8"منگل"),tsc(u8"بدھ"),tsc(u8"جمعرات"),tsc(u8"جمعه"),tsc(u8"هفته")},.abmon={tsc(u8"جنوری"),tsc(u8"فروری"),tsc(u8"مارچ"),tsc(u8"اپریل"),tsc(u8"مئی"),tsc(u8"جون"),tsc(u8"جولائی"),tsc(u8"اگست"),tsc(u8"ستمبر"),tsc(u8"اکتوبر"),tsc(u8"نومبر"),tsc(u8"دسمبر")},.mon={tsc(u8"جنوری"),tsc(u8"فروری"),tsc(u8"مارچ"),tsc(u8"اپریل"),tsc(u8"مئی"),tsc(u8"جون"),tsc(u8"جولائی"),tsc(u8"اگست"),tsc(u8"ستمبر"),tsc(u8"اکتوبر"),tsc(u8"نومبر"),tsc(u8"دسمبر")},.d_t_fmt=tsc(u8"و %H:%M:%S ت %d %B %Y"),.d_fmt=tsc(u8"%d//%m//%Y"),.t_fmt=tsc(u8"%H:%M:%S"),.t_fmt_ampm=tsc(u8"%P %I:%M:%S"),.date_fmt=tsc(u8"و %H:%M:%S %Z ت %d %B %Y"),.am_pm={tsc(u8"ص"),tsc(u8"ش")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(u8"^[+1yYهبf]"),.noexpr=tsc(u8"^[-0nNنo]"),.yesstr=tsc(u8"ہاں"),.nostr=tsc(u8"نہیں")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(u8"+%c ;%a ;%l"),.int_select=tsc(u8"00"),.int_prefix=tsc(u8"92")},.name={.name_fmt=tsc(u8"%d%t%g%t%m%t%f")},.address={.postal_fmt=tsc(u8"%a%N%f%N%d%N%b%N%h %s %e %r%N%T %z%N%c%N"),.country_name=tsc(u8"پاکستان"),.country_ab2=tsc(u8"PK"),.country_ab3=tsc(u8"PAK"),.country_num=586,.country_car=tsc(u8"PK"),.lang_name=tsc(u8"اردو"),.lang_ab=tsc(u8"ur"),.lang_term=tsc(u8"urd"),.lang_lib=tsc(u8"urd")},.measurement={.measurement=1}};

inline constexpr u16lc_all u16lc_all_global{.identification={.name=tsc(u"ur_PK"),.encoding=tsc(FAST_IO_LOCALE_uENCODING),.title=tsc(u"Urdu Language Locale for Pakistan"),.source=tsc(u"fast_io"),.address=tsc(u"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(u"fast_io"),.email=tsc(u"bug-glibc-locales@gnu.org;euloanty@live.com"),.tel=tsc(u""),.fax=tsc(u""),.language=tsc(u"Urdu"),.territory=tsc(u"Pakistan"),.revision=tsc(u"0.3"),.date=tsc(u"2000-07-11")},.monetary={.int_curr_symbol=tsc(u"PKR "),.currency_symbol=tsc(u"Rs"),.mon_decimal_point=tsc(u"."),.mon_thousands_sep=tsc(u","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u""),.negative_sign=tsc(u"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=0,.p_sign_posn=2,.n_sign_posn=1},.numeric={.decimal_point=tsc(u"."),.thousands_sep=tsc(u","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u"اتوار"),tsc(u"پير"),tsc(u"منگل"),tsc(u"بدھ"),tsc(u"جمعرات"),tsc(u"جمعه"),tsc(u"هفته")},.day={tsc(u"اتوار"),tsc(u"پير"),tsc(u"منگل"),tsc(u"بدھ"),tsc(u"جمعرات"),tsc(u"جمعه"),tsc(u"هفته")},.abmon={tsc(u"جنوری"),tsc(u"فروری"),tsc(u"مارچ"),tsc(u"اپریل"),tsc(u"مئی"),tsc(u"جون"),tsc(u"جولائی"),tsc(u"اگست"),tsc(u"ستمبر"),tsc(u"اکتوبر"),tsc(u"نومبر"),tsc(u"دسمبر")},.mon={tsc(u"جنوری"),tsc(u"فروری"),tsc(u"مارچ"),tsc(u"اپریل"),tsc(u"مئی"),tsc(u"جون"),tsc(u"جولائی"),tsc(u"اگست"),tsc(u"ستمبر"),tsc(u"اکتوبر"),tsc(u"نومبر"),tsc(u"دسمبر")},.d_t_fmt=tsc(u"و %H:%M:%S ت %d %B %Y"),.d_fmt=tsc(u"%d//%m//%Y"),.t_fmt=tsc(u"%H:%M:%S"),.t_fmt_ampm=tsc(u"%P %I:%M:%S"),.date_fmt=tsc(u"و %H:%M:%S %Z ت %d %B %Y"),.am_pm={tsc(u"ص"),tsc(u"ش")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(u"^[+1yYهبf]"),.noexpr=tsc(u"^[-0nNنo]"),.yesstr=tsc(u"ہاں"),.nostr=tsc(u"نہیں")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(u"+%c ;%a ;%l"),.int_select=tsc(u"00"),.int_prefix=tsc(u"92")},.name={.name_fmt=tsc(u"%d%t%g%t%m%t%f")},.address={.postal_fmt=tsc(u"%a%N%f%N%d%N%b%N%h %s %e %r%N%T %z%N%c%N"),.country_name=tsc(u"پاکستان"),.country_ab2=tsc(u"PK"),.country_ab3=tsc(u"PAK"),.country_num=586,.country_car=tsc(u"PK"),.lang_name=tsc(u"اردو"),.lang_ab=tsc(u"ur"),.lang_term=tsc(u"urd"),.lang_lib=tsc(u"urd")},.measurement={.measurement=1}};

inline constexpr u32lc_all u32lc_all_global{.identification={.name=tsc(U"ur_PK"),.encoding=tsc(FAST_IO_LOCALE_UENCODING),.title=tsc(U"Urdu Language Locale for Pakistan"),.source=tsc(U"fast_io"),.address=tsc(U"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(U"fast_io"),.email=tsc(U"bug-glibc-locales@gnu.org;euloanty@live.com"),.tel=tsc(U""),.fax=tsc(U""),.language=tsc(U"Urdu"),.territory=tsc(U"Pakistan"),.revision=tsc(U"0.3"),.date=tsc(U"2000-07-11")},.monetary={.int_curr_symbol=tsc(U"PKR "),.currency_symbol=tsc(U"Rs"),.mon_decimal_point=tsc(U"."),.mon_thousands_sep=tsc(U","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(U""),.negative_sign=tsc(U"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=0,.p_sign_posn=2,.n_sign_posn=1},.numeric={.decimal_point=tsc(U"."),.thousands_sep=tsc(U","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(U"اتوار"),tsc(U"پير"),tsc(U"منگل"),tsc(U"بدھ"),tsc(U"جمعرات"),tsc(U"جمعه"),tsc(U"هفته")},.day={tsc(U"اتوار"),tsc(U"پير"),tsc(U"منگل"),tsc(U"بدھ"),tsc(U"جمعرات"),tsc(U"جمعه"),tsc(U"هفته")},.abmon={tsc(U"جنوری"),tsc(U"فروری"),tsc(U"مارچ"),tsc(U"اپریل"),tsc(U"مئی"),tsc(U"جون"),tsc(U"جولائی"),tsc(U"اگست"),tsc(U"ستمبر"),tsc(U"اکتوبر"),tsc(U"نومبر"),tsc(U"دسمبر")},.mon={tsc(U"جنوری"),tsc(U"فروری"),tsc(U"مارچ"),tsc(U"اپریل"),tsc(U"مئی"),tsc(U"جون"),tsc(U"جولائی"),tsc(U"اگست"),tsc(U"ستمبر"),tsc(U"اکتوبر"),tsc(U"نومبر"),tsc(U"دسمبر")},.d_t_fmt=tsc(U"و %H:%M:%S ت %d %B %Y"),.d_fmt=tsc(U"%d//%m//%Y"),.t_fmt=tsc(U"%H:%M:%S"),.t_fmt_ampm=tsc(U"%P %I:%M:%S"),.date_fmt=tsc(U"و %H:%M:%S %Z ت %d %B %Y"),.am_pm={tsc(U"ص"),tsc(U"ش")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(U"^[+1yYهبf]"),.noexpr=tsc(U"^[-0nNنo]"),.yesstr=tsc(U"ہاں"),.nostr=tsc(U"نہیں")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(U"+%c ;%a ;%l"),.int_select=tsc(U"00"),.int_prefix=tsc(U"92")},.name={.name_fmt=tsc(U"%d%t%g%t%m%t%f")},.address={.postal_fmt=tsc(U"%a%N%f%N%d%N%b%N%h %s %e %r%N%T %z%N%c%N"),.country_name=tsc(U"پاکستان"),.country_ab2=tsc(U"PK"),.country_ab3=tsc(U"PAK"),.country_num=586,.country_car=tsc(U"PK"),.lang_name=tsc(U"اردو"),.lang_ab=tsc(U"ur"),.lang_term=tsc(U"urd"),.lang_lib=tsc(U"urd")},.measurement={.measurement=1}};


}
}

#include"../main.h"