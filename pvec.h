/**
 *  @file pvec.h
 *  @version 0.0.0
 *  @date Thu Nov  1 09:58:31 CDT 2018
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _PVEC_H_
#define _PVEC_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "pvec"

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 *  @returns Returns 0 on success, 0 otherwise.
 */

int         pvec_check(unsigned len, double *pvec);

/**
 *  @brief Compute the maximal domain for convex combinations.
 *  @details The convex combination (1-alpha)*pvec1 + alpha*pvec2 can 
 *  remain a probability vector for alpha outside the usual inteval
 *  [0, 1]. This function computes the smallest and largest feasible
 *  values of alpha.
 *  @param len [in] Length of the pvecs.
 *  @param pvec1 [in] A pvec.
 *  @param pvec2 [in] A pvec.
 *  @param alpha_min [out] Smallest value of alpha for which
 *  (1-alpha)*pvec1 + alpha*pvec2 is a pvec.
 *  @param alpha_max [out] Largest value of alpha for which
 *  (1-alpha)*pvec1 + alpha*pvec2 is a pvec.
 */

void        pvec_convex_domain(unsigned len, double *pvec1, double *pvec2,
                               double *alpha_min, double *alpha_max);

void        pvec_convex_sum(unsigned len, double a, double *pvec1, double *pvec2,
                            double *pvec3);
double      pvec_entropy(unsigned len, double *pvec);
int         pvec_normalize(unsigned len, double *pvec);

/**
 *  @brief Simple pvec sparsification.
 *  @details Compute a simple sparsification of a pvec by setting
 *  to zero all values strictly less than 1 / len.
 *  @param len [in] Length of the pvec.
 *  @param pvec [in,out] A pvec, on return renormalized after
 *  sparsification.
 *  @returns Returns the number of changes made.
 */

unsigned    pvec_sparsify(unsigned len, double *pvec);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *pvec_version(void);

#endif
