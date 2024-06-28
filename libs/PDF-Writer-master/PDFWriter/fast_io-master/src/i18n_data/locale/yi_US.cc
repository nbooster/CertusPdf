﻿#include"../localedef.h"

namespace fast_io_i18n
{
namespace
{

inline constexpr std::size_t numeric_grouping_storage[]{3};

inline constexpr lc_all lc_all_global{.identification={.name=tsc("yi_US"),.encoding=tsc(FAST_IO_LOCALE_ENCODING),.title=tsc("Yiddish Language locale for the USA"),.source=tsc("http:////www.uyip.org//\t\t;\t\tfast_io"),.address=tsc("https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc("Pablo Saratxaga\t\t;\t\tfast_io"),.email=tsc("pablo@mandrakesoft.com;euloanty@live.com"),.tel=tsc(""),.fax=tsc(""),.language=tsc("Yiddish"),.territory=tsc("United States"),.revision=tsc("0.4"),.date=tsc("2003-08-16")},.monetary={.int_curr_symbol=tsc("USD "),.currency_symbol=tsc("$"),.mon_decimal_point=tsc("."),.mon_thousands_sep=tsc(","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(""),.negative_sign=tsc("-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=2,.n_sign_posn=2},.numeric={.decimal_point=tsc("."),.thousands_sep=tsc(","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc("זונ'"),tsc("מאָנ'"),tsc("דינ'"),tsc("מיט'"),tsc("דאָנ'"),tsc("פֿרײַ'"),tsc("שבת")},.day={tsc("זונטיק"),tsc("מאָנטיק"),tsc("דינסטיק"),tsc("מיטװאָך"),tsc("דאָנערשטיק"),tsc("פֿרײַטיק"),tsc("שבת")},.abmon={tsc("יאַנ"),tsc("פֿעב"),tsc("מאַר"),tsc("אַפּר"),tsc("מײַ "),tsc("יונ"),tsc("יול"),tsc("אױג"),tsc("סעפּ"),tsc("אָקט"),tsc("נאָװ"),tsc("דעצ")},.mon={tsc("יאַנואַר"),tsc("פֿעברואַר"),tsc("מערץ"),tsc("אַפּריל"),tsc("מיי"),tsc("יוני"),tsc("יולי"),tsc("אויגוסט"),tsc("סעפּטעמבער"),tsc("אקטאבער"),tsc("נאוועמבער"),tsc("דעצעמבער")},.d_t_fmt=tsc("%H:%M:%S %Y %b %d %a"),.d_fmt=tsc("%d//%m//%y"),.t_fmt=tsc("%H:%M:%S"),.t_fmt_ampm=tsc("%I:%M:%S %P"),.date_fmt=tsc("%Z %H:%M:%S %Y %b %d %a"),.am_pm={tsc("AM"),tsc("PM")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc("^[+1yYי]"),.noexpr=tsc("^[-0nNנק]"),.yesstr=tsc("יאָ"),.nostr=tsc("קײן")},.paper={.width=216,.height=279},.telephone={.tel_int_fmt=tsc("+%c (%a) %l"),.tel_dom_fmt=tsc("(%a) %l"),.int_select=tsc("11"),.int_prefix=tsc("1")},.name={.name_fmt=tsc("%d%t%g%t%m%t%f"),.name_miss=tsc("Miss."),.name_mr=tsc("Mr."),.name_mrs=tsc("Mrs."),.name_ms=tsc("Ms.")},.address={.postal_fmt=tsc("%d%N%f%N%d%N%b%N%s %h 5e %r%N%C%z %T%N%c%N"),.country_name=tsc("פֿאַראייניגטע שטאַטן"),.country_post=tsc("USA"),.country_ab2=tsc("US"),.country_ab3=tsc("USA"),.country_num=840,.country_car=tsc("USA"),.country_isbn=tsc("0"),.lang_name=tsc("ייִדיש"),.lang_ab=tsc("yi"),.lang_term=tsc("yid"),.lang_lib=tsc("yid")},.measurement={.measurement=2}};

inline constexpr wlc_all wlc_all_global{.identification={.name=tsc(L"yi_US"),.encoding=tsc(FAST_IO_LOCALE_LENCODING),.title=tsc(L"Yiddish Language locale for the USA"),.source=tsc(L"http:////www.uyip.org//\t\t;\t\tfast_io"),.address=tsc(L"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(L"Pablo Saratxaga\t\t;\t\tfast_io"),.email=tsc(L"pablo@mandrakesoft.com;euloanty@live.com"),.tel=tsc(L""),.fax=tsc(L""),.language=tsc(L"Yiddish"),.territory=tsc(L"United States"),.revision=tsc(L"0.4"),.date=tsc(L"2003-08-16")},.monetary={.int_curr_symbol=tsc(L"USD "),.currency_symbol=tsc(L"$"),.mon_decimal_point=tsc(L"."),.mon_thousands_sep=tsc(L","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(L""),.negative_sign=tsc(L"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=2,.n_sign_posn=2},.numeric={.decimal_point=tsc(L"."),.thousands_sep=tsc(L","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(L"זונ'"),tsc(L"מאָנ'"),tsc(L"דינ'"),tsc(L"מיט'"),tsc(L"דאָנ'"),tsc(L"פֿרײַ'"),tsc(L"שבת")},.day={tsc(L"זונטיק"),tsc(L"מאָנטיק"),tsc(L"דינסטיק"),tsc(L"מיטװאָך"),tsc(L"דאָנערשטיק"),tsc(L"פֿרײַטיק"),tsc(L"שבת")},.abmon={tsc(L"יאַנ"),tsc(L"פֿעב"),tsc(L"מאַר"),tsc(L"אַפּר"),tsc(L"מײַ "),tsc(L"יונ"),tsc(L"יול"),tsc(L"אױג"),tsc(L"סעפּ"),tsc(L"אָקט"),tsc(L"נאָװ"),tsc(L"דעצ")},.mon={tsc(L"יאַנואַר"),tsc(L"פֿעברואַר"),tsc(L"מערץ"),tsc(L"אַפּריל"),tsc(L"מיי"),tsc(L"יוני"),tsc(L"יולי"),tsc(L"אויגוסט"),tsc(L"סעפּטעמבער"),tsc(L"אקטאבער"),tsc(L"נאוועמבער"),tsc(L"דעצעמבער")},.d_t_fmt=tsc(L"%H:%M:%S %Y %b %d %a"),.d_fmt=tsc(L"%d//%m//%y"),.t_fmt=tsc(L"%H:%M:%S"),.t_fmt_ampm=tsc(L"%I:%M:%S %P"),.date_fmt=tsc(L"%Z %H:%M:%S %Y %b %d %a"),.am_pm={tsc(L"AM"),tsc(L"PM")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(L"^[+1yYי]"),.noexpr=tsc(L"^[-0nNנק]"),.yesstr=tsc(L"יאָ"),.nostr=tsc(L"קײן")},.paper={.width=216,.height=279},.telephone={.tel_int_fmt=tsc(L"+%c (%a) %l"),.tel_dom_fmt=tsc(L"(%a) %l"),.int_select=tsc(L"11"),.int_prefix=tsc(L"1")},.name={.name_fmt=tsc(L"%d%t%g%t%m%t%f"),.name_miss=tsc(L"Miss."),.name_mr=tsc(L"Mr."),.name_mrs=tsc(L"Mrs."),.name_ms=tsc(L"Ms.")},.address={.postal_fmt=tsc(L"%d%N%f%N%d%N%b%N%s %h 5e %r%N%C%z %T%N%c%N"),.country_name=tsc(L"פֿאַראייניגטע שטאַטן"),.country_post=tsc(L"USA"),.country_ab2=tsc(L"US"),.country_ab3=tsc(L"USA"),.country_num=840,.country_car=tsc(L"USA"),.country_isbn=tsc(L"0"),.lang_name=tsc(L"ייִדיש"),.lang_ab=tsc(L"yi"),.lang_term=tsc(L"yid"),.lang_lib=tsc(L"yid")},.measurement={.measurement=2}};

inline constexpr u8lc_all u8lc_all_global{.identification={.name=tsc(u8"yi_US"),.encoding=tsc(FAST_IO_LOCALE_u8ENCODING),.title=tsc(u8"Yiddish Language locale for the USA"),.source=tsc(u8"http:////www.uyip.org//\t\t;\t\tfast_io"),.address=tsc(u8"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(u8"Pablo Saratxaga\t\t;\t\tfast_io"),.email=tsc(u8"pablo@mandrakesoft.com;euloanty@live.com"),.tel=tsc(u8""),.fax=tsc(u8""),.language=tsc(u8"Yiddish"),.territory=tsc(u8"United States"),.revision=tsc(u8"0.4"),.date=tsc(u8"2003-08-16")},.monetary={.int_curr_symbol=tsc(u8"USD "),.currency_symbol=tsc(u8"$"),.mon_decimal_point=tsc(u8"."),.mon_thousands_sep=tsc(u8","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u8""),.negative_sign=tsc(u8"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=2,.n_sign_posn=2},.numeric={.decimal_point=tsc(u8"."),.thousands_sep=tsc(u8","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u8"זונ'"),tsc(u8"מאָנ'"),tsc(u8"דינ'"),tsc(u8"מיט'"),tsc(u8"דאָנ'"),tsc(u8"פֿרײַ'"),tsc(u8"שבת")},.day={tsc(u8"זונטיק"),tsc(u8"מאָנטיק"),tsc(u8"דינסטיק"),tsc(u8"מיטװאָך"),tsc(u8"דאָנערשטיק"),tsc(u8"פֿרײַטיק"),tsc(u8"שבת")},.abmon={tsc(u8"יאַנ"),tsc(u8"פֿעב"),tsc(u8"מאַר"),tsc(u8"אַפּר"),tsc(u8"מײַ "),tsc(u8"יונ"),tsc(u8"יול"),tsc(u8"אױג"),tsc(u8"סעפּ"),tsc(u8"אָקט"),tsc(u8"נאָװ"),tsc(u8"דעצ")},.mon={tsc(u8"יאַנואַר"),tsc(u8"פֿעברואַר"),tsc(u8"מערץ"),tsc(u8"אַפּריל"),tsc(u8"מיי"),tsc(u8"יוני"),tsc(u8"יולי"),tsc(u8"אויגוסט"),tsc(u8"סעפּטעמבער"),tsc(u8"אקטאבער"),tsc(u8"נאוועמבער"),tsc(u8"דעצעמבער")},.d_t_fmt=tsc(u8"%H:%M:%S %Y %b %d %a"),.d_fmt=tsc(u8"%d//%m//%y"),.t_fmt=tsc(u8"%H:%M:%S"),.t_fmt_ampm=tsc(u8"%I:%M:%S %P"),.date_fmt=tsc(u8"%Z %H:%M:%S %Y %b %d %a"),.am_pm={tsc(u8"AM"),tsc(u8"PM")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(u8"^[+1yYי]"),.noexpr=tsc(u8"^[-0nNנק]"),.yesstr=tsc(u8"יאָ"),.nostr=tsc(u8"קײן")},.paper={.width=216,.height=279},.telephone={.tel_int_fmt=tsc(u8"+%c (%a) %l"),.tel_dom_fmt=tsc(u8"(%a) %l"),.int_select=tsc(u8"11"),.int_prefix=tsc(u8"1")},.name={.name_fmt=tsc(u8"%d%t%g%t%m%t%f"),.name_miss=tsc(u8"Miss."),.name_mr=tsc(u8"Mr."),.name_mrs=tsc(u8"Mrs."),.name_ms=tsc(u8"Ms.")},.address={.postal_fmt=tsc(u8"%d%N%f%N%d%N%b%N%s %h 5e %r%N%C%z %T%N%c%N"),.country_name=tsc(u8"פֿאַראייניגטע שטאַטן"),.country_post=tsc(u8"USA"),.country_ab2=tsc(u8"US"),.country_ab3=tsc(u8"USA"),.country_num=840,.country_car=tsc(u8"USA"),.country_isbn=tsc(u8"0"),.lang_name=tsc(u8"ייִדיש"),.lang_ab=tsc(u8"yi"),.lang_term=tsc(u8"yid"),.lang_lib=tsc(u8"yid")},.measurement={.measurement=2}};

inline constexpr u16lc_all u16lc_all_global{.identification={.name=tsc(u"yi_US"),.encoding=tsc(FAST_IO_LOCALE_uENCODING),.title=tsc(u"Yiddish Language locale for the USA"),.source=tsc(u"http:////www.uyip.org//\t\t;\t\tfast_io"),.address=tsc(u"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(u"Pablo Saratxaga\t\t;\t\tfast_io"),.email=tsc(u"pablo@mandrakesoft.com;euloanty@live.com"),.tel=tsc(u""),.fax=tsc(u""),.language=tsc(u"Yiddish"),.territory=tsc(u"United States"),.revision=tsc(u"0.4"),.date=tsc(u"2003-08-16")},.monetary={.int_curr_symbol=tsc(u"USD "),.currency_symbol=tsc(u"$"),.mon_decimal_point=tsc(u"."),.mon_thousands_sep=tsc(u","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u""),.negative_sign=tsc(u"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=2,.n_sign_posn=2},.numeric={.decimal_point=tsc(u"."),.thousands_sep=tsc(u","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u"זונ'"),tsc(u"מאָנ'"),tsc(u"דינ'"),tsc(u"מיט'"),tsc(u"דאָנ'"),tsc(u"פֿרײַ'"),tsc(u"שבת")},.day={tsc(u"זונטיק"),tsc(u"מאָנטיק"),tsc(u"דינסטיק"),tsc(u"מיטװאָך"),tsc(u"דאָנערשטיק"),tsc(u"פֿרײַטיק"),tsc(u"שבת")},.abmon={tsc(u"יאַנ"),tsc(u"פֿעב"),tsc(u"מאַר"),tsc(u"אַפּר"),tsc(u"מײַ "),tsc(u"יונ"),tsc(u"יול"),tsc(u"אױג"),tsc(u"סעפּ"),tsc(u"אָקט"),tsc(u"נאָװ"),tsc(u"דעצ")},.mon={tsc(u"יאַנואַר"),tsc(u"פֿעברואַר"),tsc(u"מערץ"),tsc(u"אַפּריל"),tsc(u"מיי"),tsc(u"יוני"),tsc(u"יולי"),tsc(u"אויגוסט"),tsc(u"סעפּטעמבער"),tsc(u"אקטאבער"),tsc(u"נאוועמבער"),tsc(u"דעצעמבער")},.d_t_fmt=tsc(u"%H:%M:%S %Y %b %d %a"),.d_fmt=tsc(u"%d//%m//%y"),.t_fmt=tsc(u"%H:%M:%S"),.t_fmt_ampm=tsc(u"%I:%M:%S %P"),.date_fmt=tsc(u"%Z %H:%M:%S %Y %b %d %a"),.am_pm={tsc(u"AM"),tsc(u"PM")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(u"^[+1yYי]"),.noexpr=tsc(u"^[-0nNנק]"),.yesstr=tsc(u"יאָ"),.nostr=tsc(u"קײן")},.paper={.width=216,.height=279},.telephone={.tel_int_fmt=tsc(u"+%c (%a) %l"),.tel_dom_fmt=tsc(u"(%a) %l"),.int_select=tsc(u"11"),.int_prefix=tsc(u"1")},.name={.name_fmt=tsc(u"%d%t%g%t%m%t%f"),.name_miss=tsc(u"Miss."),.name_mr=tsc(u"Mr."),.name_mrs=tsc(u"Mrs."),.name_ms=tsc(u"Ms.")},.address={.postal_fmt=tsc(u"%d%N%f%N%d%N%b%N%s %h 5e %r%N%C%z %T%N%c%N"),.country_name=tsc(u"פֿאַראייניגטע שטאַטן"),.country_post=tsc(u"USA"),.country_ab2=tsc(u"US"),.country_ab3=tsc(u"USA"),.country_num=840,.country_car=tsc(u"USA"),.country_isbn=tsc(u"0"),.lang_name=tsc(u"ייִדיש"),.lang_ab=tsc(u"yi"),.lang_term=tsc(u"yid"),.lang_lib=tsc(u"yid")},.measurement={.measurement=2}};

inline constexpr u32lc_all u32lc_all_global{.identification={.name=tsc(U"yi_US"),.encoding=tsc(FAST_IO_LOCALE_UENCODING),.title=tsc(U"Yiddish Language locale for the USA"),.source=tsc(U"http:////www.uyip.org//\t\t;\t\tfast_io"),.address=tsc(U"https://gitee.com/qabeowjbtkwb/fast_io\t\t;\t\thttps://github.com/cppfastio/fast_io"),.contact=tsc(U"Pablo Saratxaga\t\t;\t\tfast_io"),.email=tsc(U"pablo@mandrakesoft.com;euloanty@live.com"),.tel=tsc(U""),.fax=tsc(U""),.language=tsc(U"Yiddish"),.territory=tsc(U"United States"),.revision=tsc(U"0.4"),.date=tsc(U"2003-08-16")},.monetary={.int_curr_symbol=tsc(U"USD "),.currency_symbol=tsc(U"$"),.mon_decimal_point=tsc(U"."),.mon_thousands_sep=tsc(U","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(U""),.negative_sign=tsc(U"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=2,.n_sign_posn=2},.numeric={.decimal_point=tsc(U"."),.thousands_sep=tsc(U","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(U"זונ'"),tsc(U"מאָנ'"),tsc(U"דינ'"),tsc(U"מיט'"),tsc(U"דאָנ'"),tsc(U"פֿרײַ'"),tsc(U"שבת")},.day={tsc(U"זונטיק"),tsc(U"מאָנטיק"),tsc(U"דינסטיק"),tsc(U"מיטװאָך"),tsc(U"דאָנערשטיק"),tsc(U"פֿרײַטיק"),tsc(U"שבת")},.abmon={tsc(U"יאַנ"),tsc(U"פֿעב"),tsc(U"מאַר"),tsc(U"אַפּר"),tsc(U"מײַ "),tsc(U"יונ"),tsc(U"יול"),tsc(U"אױג"),tsc(U"סעפּ"),tsc(U"אָקט"),tsc(U"נאָװ"),tsc(U"דעצ")},.mon={tsc(U"יאַנואַר"),tsc(U"פֿעברואַר"),tsc(U"מערץ"),tsc(U"אַפּריל"),tsc(U"מיי"),tsc(U"יוני"),tsc(U"יולי"),tsc(U"אויגוסט"),tsc(U"סעפּטעמבער"),tsc(U"אקטאבער"),tsc(U"נאוועמבער"),tsc(U"דעצעמבער")},.d_t_fmt=tsc(U"%H:%M:%S %Y %b %d %a"),.d_fmt=tsc(U"%d//%m//%y"),.t_fmt=tsc(U"%H:%M:%S"),.t_fmt_ampm=tsc(U"%I:%M:%S %P"),.date_fmt=tsc(U"%Z %H:%M:%S %Y %b %d %a"),.am_pm={tsc(U"AM"),tsc(U"PM")},.week={7,19971130,1},.cal_direction=3},.messages={.yesexpr=tsc(U"^[+1yYי]"),.noexpr=tsc(U"^[-0nNנק]"),.yesstr=tsc(U"יאָ"),.nostr=tsc(U"קײן")},.paper={.width=216,.height=279},.telephone={.tel_int_fmt=tsc(U"+%c (%a) %l"),.tel_dom_fmt=tsc(U"(%a) %l"),.int_select=tsc(U"11"),.int_prefix=tsc(U"1")},.name={.name_fmt=tsc(U"%d%t%g%t%m%t%f"),.name_miss=tsc(U"Miss."),.name_mr=tsc(U"Mr."),.name_mrs=tsc(U"Mrs."),.name_ms=tsc(U"Ms.")},.address={.postal_fmt=tsc(U"%d%N%f%N%d%N%b%N%s %h 5e %r%N%C%z %T%N%c%N"),.country_name=tsc(U"פֿאַראייניגטע שטאַטן"),.country_post=tsc(U"USA"),.country_ab2=tsc(U"US"),.country_ab3=tsc(U"USA"),.country_num=840,.country_car=tsc(U"USA"),.country_isbn=tsc(U"0"),.lang_name=tsc(U"ייִדיש"),.lang_ab=tsc(U"yi"),.lang_term=tsc(U"yid"),.lang_lib=tsc(U"yid")},.measurement={.measurement=2}};


}
}

#include"../main.h"