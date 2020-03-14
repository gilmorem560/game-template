/*
 * macros - useful macros
 */
#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* decimal - create decimal a.b */
#define decimal(a,b) ((double) a + ((double) b / 10.0))

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MACROS_H__ */
