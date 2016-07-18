#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([audio_coding_module], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([codecs/audio_encoder.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h memory.h stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor memmove memset pow sqrt strchr])

AM_INIT_AUTOMAKE(audio_coding_module,1.0)
AC_CONFIG_FILES([Makefile])
AC_CONFIG_SUBDIRS([main neteq codecs])
RANLIB
AC_OUTPUT
