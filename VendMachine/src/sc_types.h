/** 
 * @file SC_TYPES.h
 * @brief Header file defining types used in statechart implementations.
 */

#ifndef SC_TYPES_H_
#define SC_TYPES_H_

#ifdef __STDC_VERSION__
	#if __STDC_VERSION__ >= 199901L 
		#define HAS_C99_BOOLS
	#endif
#else
	#ifdef __cplusplus
		#define HAS_C99_BOOLS
	#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif 

#include <stdint.h>
#ifdef HAS_C99_BOOLS
#include <stdbool.h>
#endif

/**
 * @def sc_string
 * @brief Defines a type alias for string.
 */
#define sc_string		char*
 
#ifdef HAS_C99_BOOLS
/**
 * @typedef sc_boolean
 * @brief Defines the boolean type using C99 bool if available, otherwise uint8_t.
 */
typedef bool			sc_boolean;
#else
typedef uint8_t			sc_boolean;
#endif

/**
 * @typedef sc_short
 * @brief Defines a signed short integer type.
 */
typedef int_fast16_t	sc_short;
/**
 * @typedef sc_ushort
 * @brief Defines an unsigned short integer type.
 */
typedef uint_fast16_t	sc_ushort;
/**
 * @typedef sc_integer
 * @brief Defines a signed integer type.
 */
typedef int32_t			sc_integer;
/**
 * @typedef sc_uinteger
 * @brief Defines an unsigned integer type.
 */
typedef uint32_t		sc_uinteger;

/**
 * @typedef sc_time
 * @brief Defines a type for representing time.
 */
typedef int32_t       sc_time;

/**
 * @typedef sc_real
 * @brief Defines a type for representing real numbers.
 */
typedef double			sc_real;

/**
 * @typedef sc_eventid
 * @brief Defines a type for representing event IDs.
 */
typedef void*			sc_eventid;

/**
 * @typedef sc_intptr_t
 * @brief Defines a signed integer type capable of holding a pointer.
 */
typedef intptr_t		sc_intptr_t;

#ifdef __cplusplus
}
#endif

#ifndef sc_null
	#ifdef __cplusplus
		#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
	  		#define sc_null nullptr
		#else
			#define sc_null 0
		#endif
	#else
		#define sc_null ((void *)0)
	#endif
#endif

#ifdef HAS_C99_BOOLS
#define bool_true true
#define bool_false false
#else
#define bool_true 1
#define bool_false 0
#endif

#endif /* SC_TYPES_H_ */

