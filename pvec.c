/**
 *  @file pvec.c
 *  @version 0.2.0-dev0
 *  @date Sun Feb 16, 2020 08:22:42 PM CST
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <math.h>
#include <float.h>
#include "pvec.h"

#ifdef  IS_NULL
#undef  IS_NULL
#endif
#define IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  MAX2
#undef  MAX2
#endif
#define MAX2(a, b)   ((a) > (b) ? (a) : (b))

#ifdef  MIN2
#undef  MIN2
#endif
#define MIN2(a, b)   ((a) < (b) ? (a) : (b))

int
pvec_check(unsigned len, double *pvec)
{
   unsigned    i;
   unsigned    okay = 0;

   for (i = 0; i < len; i++) {
      if (pvec[i] < 0)
         return 0;
      if (pvec[i] > 0)
         okay = 1;                               /* have at least one positive value */
   }

   return okay;
}

void
pvec_convex_domain(unsigned len, double *pvec1, double *pvec2, double *alpha_min,
                   double *alpha_max)
{
   unsigned    i;
   double      del;

   *alpha_min = -DBL_MAX;
   *alpha_max = DBL_MAX;

   for (i = 0; i < len; i++) {
      del = pvec2[i] - pvec1[i];
      if (del > 0) {
         *alpha_max = MIN2(*alpha_max, (1 - pvec1[i]) / del);
         *alpha_min = MAX2(*alpha_min, -pvec1[i] / del);
      }
      else if (del < 0) {
         *alpha_max = MIN2(*alpha_max, -pvec1[i] / del);
         *alpha_min = MAX2(*alpha_min, (1 - pvec1[i]) / del);
      }
      else {                                     /* no-op */
      }
   }
}

void
pvec_convex_sum(unsigned len, double a, double *pvec1, double *pvec2, double *pvec3)
{
   unsigned    i;

   for (i = 0; i < len; i++)
      pvec3[i] = (1 - a) * pvec1[i] + a * pvec2[i];
}

double
pvec_entropy(unsigned len, double *pvec)
{
   unsigned    i;
   double      sum = 0;

   for (i = 0; i < len; i++)
      if (pvec[i] > 0)
         sum -= pvec[i] * log(pvec[i]);

   return sum > 0 ? sum : 0.0;
}

int
pvec_normalize(unsigned len, double *pvec)
{
   unsigned    i;
   double      sum = 0;

   for (i = 0; i < len; i++) {
      if (pvec[i] < 0)
         return 1;
      sum += pvec[i] < 0 ? 0 : pvec[i];
   }

   if (sum <= 0)
      return 1;

   for (i = 0; i < len; i++)
      pvec[i] /= sum;

   return 0;
}

unsigned
pvec_sparsify(unsigned len, double *pvec)
{
   unsigned    i;
   unsigned    changed = 0;

   for (i = 0; i < len; i++) {
      if (pvec[i] < 1.0 / len) {
         if (pvec[i] > 0)
            changed += 1;
         pvec[i] = 0;
      }
   }

   pvec_normalize(len, pvec);

   return changed;
}

const char *
pvec_version(void)
{
   return "0.2.0-dev0";
}

#undef IS_NULL
#undef MAX2
#undef MIN2
