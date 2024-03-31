/* xwstdio.h internal header */
#ifndef _XWSTDIO
#define _XWSTDIO
#include <xstdio.h>
#include <xwchar.h>
_C_STD_BEGIN
		/* macros for _WScanf and friends */
#define WGET(px)	\
	(++(px)->nchar, (*(px)->pfn)((px)->arg, 0, 1))
#define WGETN(px)	(wint_t)(0 <= --(px)->nget ? WGET(px) \
	: (++(px)->nchar, WEOF))
#define WUNGET(px, ch)	\
	(--(px)->nchar, (*(px)->pfn)((px)->arg, ch, 0))
#define WUNGETN(px, ch)	do if ((int)(ch) != WEOF) WUNGET(px, ch); \
	else --(px)->nchar; while (0)

		/* type definitions */
typedef struct
	{	/* print formatting information */
	union
		{	/* long or long double value */
		_Longlong li;
		_ULonglong uli;
		long double ld;
		} v;
	void *(*pfn)(void *, const wchar_t *, size_t);
	void *arg;
	wchar_t *s;
	int n0, nz0, n1, nz1, n2, nz2;
	int argno, prec, nchar, width;
	unsigned short flags;
	wchar_t qual;
	char secure;	/* added for _HAS_LIB_EXT1 */
	wchar_t sep;	/* added for _HAS_FIXED_POINT %v */
	} _WPft;

typedef struct
	{	/* scan formatting information */
	wint_t (*pfn)(void *, wint_t, int);
	void *arg;
	va_list ap;
	const wchar_t *s;
	int nchar, nget, width;
	size_t prec;
	wchar_t qual;
	char noconv, stored;
	char secure;	/* added for _HAS_LIB_EXT1 */
	wchar_t sep;	/* added for _HAS_FIXED_POINT %v */
	} _WSft;

		/* declarations */
_C_LIB_DECL
_CRTIMP2 int _CDECL _WFrprep(FILE *);
_CRTIMP2 int _CDECL _WFwprep(FILE *);
_CRTIMP2 void _CDECL _WGenld(_WPft *, wchar_t, wchar_t *, short, short);
_CRTIMP2 int _CDECL _WGetfld(_WSft *);
_CRTIMP2 int _CDECL _WGetfloat(_WSft *, void *);
_CRTIMP2 int _CDECL _WGetint(_WSft *, void *);
_CRTIMP2 int _CDECL _WGetstr(_WSft *, int);
_CRTIMP2 void _CDECL _WLdtob(_WPft *, wchar_t);
_CRTIMP2 void _CDECL _WLitob(_WPft *, wchar_t);
_CRTIMP2 int _CDECL _WPrintf(void *(*)(void *, const wchar_t *, size_t),
	void *, const wchar_t *, va_list, int);
_CRTIMP2 int _CDECL _WPutstr(_WPft *, const char *);
_CRTIMP2 int _CDECL _WPutfld(_WPft *, va_list *, wchar_t, wchar_t *);
_CRTIMP2 int _CDECL _WPuttxt(_WPft *, const wchar_t *);
_CRTIMP2 int _CDECL _WScanf(wint_t (*)(void *, wint_t, int),
	void *, const wchar_t *, va_list, int);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XWSTDIO */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.40:1611 */
