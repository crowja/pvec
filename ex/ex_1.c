#include <stdlib.h>
#include <stdio.h>
#include "pvec.h"

int
main(void)
{
   double x[] = {1, 2, 1, 3, 1, 1, 1};
   double y[] = {4, 1, 1, 4, 2, 2, 2};
   double z[] = {0, 0, 0, 0, 0, 0, 0};
   double alpha1, alpha2, alpha;

   pvec_normalize(7, x);
   pvec_normalize(7, y);
   pvec_convex_domain(7, x, y, &alpha1, &alpha2);

   pvec_convex_sum(7, alpha1, x, y, z);
   printf("Entropy at alpha1 (%f): %f\n", alpha1, pvec_entropy(7, z));
   pvec_convex_sum(7, 0, x, y, z);
   printf("Entropy at left (%f): %f\n", 0.0, pvec_entropy(7, z));
   pvec_convex_sum(7, 1, x, y, z);
   printf("Entropy at right (%f): %f\n", 1.0, pvec_entropy(7, z));
   pvec_convex_sum(7, alpha2, x, y, z);
   printf("Entropy at alpha2 (%f): %f\n", alpha2, pvec_entropy(7, z));
   pvec_convex_sum(7, 0.5, x, y, z);
   printf("Entropy at midpoint (%f): %f\n", 0.5, pvec_entropy(7, z));

   return 0;
}
