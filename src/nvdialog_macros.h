/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef __nvdialog_macros_h__
#define __nvdialog_macros_h__

#if defined(__clang__) || defined(__GNUC__)

#define NVD_FORCE_INLINE inline __attribute__((always_inline))

#ifndef NVD_BUFFER_SIZE
#define NVD_BUFFER_SIZE NVDIALOG_MAXBUF
#endif /* NVD_BUFFER_SIZE */

#define NVD_LIBRARY_FUNCTION  __attribute__((visibility("default")))
#define NVD_INTERNAL_FUNCTION __attribute__((visibility("hidden")))
#define NVD_DONT_INITIALIZE   __attribute__((noinit))
#define NVD_DEPRECATED(x)     __attribute__((deprecated(x)))
#define NVD_FN_IDENT          __PRETTY_FUNCTION__

#else

#define NVD_FORCE_INLINE  inline __forceinline
#define NVD_DEPRECATED(x) __declspec(deprecated(x))
#define NVD_DONT_INITIALIZE

#define NVD_LIBRARY_FUNCTION
#define NVD_INTERNAL_FUNCTION

#define NVD_FN_IDENT __func__

#ifndef NVD_BUFFER_SIZE
#define NVD_BUFFER_SIZE NVDIALOG_MAXBUF
#endif /* NVD_BUFFER_SIZE */
#endif /* __clang__ */

#endif /* __nvdialog_macros_h__ */