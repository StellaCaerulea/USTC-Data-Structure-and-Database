#ifndef _ABBR_H_
#define _ABBR_H_

#include <stdbool.h>
#include <math.h>

#ifndef choose_expr
#define choose_expr __builtin_choose_expr
#endif

#ifndef types_compatible
#define types_compatible __builtin_types_compatible_p
#endif

#ifndef likely
#define likely(x) __builtin_expect((x),true)
#endif

#ifndef unlikely
#define unlikely(x) __builtin_expect((x),false)
#endif

#define _equal(x_1, x_2)									\
choose_expr(											\
	types_compatible(__typeof__(x_1), double) &&	\
	types_compatible(__typeof__(x_2), double),				\
		_dbl_equal(x_1, x_2),							\
choose_expr(										\
	types_compatible(__typeof__(x_1),  float) &&			\
	types_compatible(__typeof__(x_2),  float),			\
		_flt_equal(x_1, x_2),						\
choose_expr(												\
	types_compatible(__typeof__(x_1), long double) &&	\
	types_compatible(__typeof__(x_2), long double),	\
		_ldbl_equal(x_1, x_2),								\
(void)0)))

bool _dbl_equal(double x_1, double x_2);
bool _flt_equal(float x_1, float x_2);
bool _ldbl_equal(long double x_1, long double x_2);

inline bool _dbl_equal(double x_1, double x_2)
{
	return (fabs(x_1 - x_2) < __DBL_EPSILON__ * fabs(x_1 + x_2));
}

inline bool _flt_equal(float x_1, float x_2)
{
	return (fabsf(x_1 - x_2) < __FLT_EPSILON__ * fabsf(x_1 + x_2));
}

inline bool _ldbl_equal(long double x_1, long double x_2)
{
	return (fabsl(x_1 - x_2) < __LDBL_EPSILON__ * fabsl(x_1 + x_2));
}

#endif /* _ABBR_H_ */
