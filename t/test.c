#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "pvec.h"
#include "tinytest.h"
#include "tinyhelp.h"

static void
test_check(void)
{
   double    x[] = { 0.5, 0.2, 0.3 };
   double    y[] = { -0.3, 0.3, 0.4 };
   double    z[] = { 0.3, 0.3, -0.4 };

   fprintf_test_info(stdout, "test_check", "pvec_check");
   ASSERT_EQUALS(1, pvec_check(3, x));
   ASSERT_EQUALS(0, pvec_check(3, y));
   ASSERT_EQUALS(0, pvec_check(3, z));
}

static void
test_convex_domain_1(void)
{
   double    x[] = { 0.5, 0.2, 0.3 };
   double    y[] = { 0.3, 0.3, 0.4 };
   double    alpha_min, alpha_max;
   unsigned  len = sizeof(x) / sizeof(double);

   fprintf_test_info(stdout, "test_convex_domain_1", "pvec_convex_domain");
   pvec_convex_domain(len, x, y, &alpha_min, &alpha_max);
   ASSERT_DOUBLE_EQUALS(-2.0, alpha_min);
   ASSERT_DOUBLE_EQUALS(2.5, alpha_max);
}

static void
test_convex_domain_2(void)
{
   double    x[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   double    y[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
   double    alpha_min, alpha_max;
   unsigned  len = sizeof(x) / sizeof(double);

   fprintf_test_info(stdout, "test_convex_domain_2",
                     "pvec_normalize, pvec_convex_domain");
   pvec_normalize(len, x);
   pvec_normalize(len, y);
   pvec_convex_domain(3, x, y, &alpha_min, &alpha_max);
   ASSERT_DOUBLE_EQUALS(0.0, alpha_min);
   ASSERT_DOUBLE_EQUALS(5.0, alpha_max);
}

static void
test_convex_sum(void)
{
   double    x[] = { 0.5, 0.4, 0.1 };
   double    y[] = { 0.1, 0.4, 0.5 };
   double    z[] = { 0, 0, 0 };                  /* overwritten below */
   double    a = 0.4;
   double    check0 = x[0] + (y[0] - x[0]) * a;
   double    check1 = x[1] + (y[1] - x[1]) * a;
   double    check2 = x[2] + (y[2] - x[2]) * a;

   fprintf_test_info(stderr, "test_convex_sum", "pvec_convex_sum");
   pvec_convex_sum(3, 0.4, x, y, z);
   ASSERT_DOUBLE_EQUALS(check0, z[0]);
   ASSERT_DOUBLE_EQUALS(check1, z[1]);
   ASSERT_DOUBLE_EQUALS(check2, z[2]);
}

static void
test_entropy(void)
{
   double    x[] = { 0.5, 0.4, 0.1, 0.0 };
   double    entropy = pvec_entropy(4, x);
   double    entropy0 = 0.94334839232903924917e-00;

   fprintf_test_info(stderr, "test_entropy", "pvec_entropy");
   ASSERT_DOUBLE_EQUALS(entropy0, entropy);
}

static void
test_normalize(void)
{
   double    x[3] = { 1, 2, 3 };
   double    y[3] = { 1, 2, -3 };
   double    z[3] = { 0, 0, 0 };

   fprintf_test_info(stdout, "test_normalize", "pvec_normalize");
   ASSERT_EQUALS(0, pvec_normalize(3, x));
   ASSERT_EQUALS(1, pvec_normalize(3, y));
   ASSERT_EQUALS(1, pvec_normalize(3, z));
}

static void
test_sparsify(void)
{
   double    x[] = { 0.5, 0.4, 0.1 };
   unsigned  changed;

   fprintf_test_info(stdout, "test_sparsify", "pvec_sparsify");
   changed = pvec_sparsify(3, x);
   ASSERT_EQUALS(1, changed);
   ASSERT_DOUBLE_EQUALS(x[0], 0.5 / 0.9);
   ASSERT_DOUBLE_EQUALS(x[1], 0.4 / 0.9);
   ASSERT_DOUBLE_EQUALS(x[2], 0.0 / 0.9);
   changed = pvec_sparsify(3, x);
   ASSERT_EQUALS(0, changed);
}

#if 0                                            /* 6 yy */
static void
test_stub(void)
{
   fprintf_test_info(stdout, "test_stub()", NULL);
   ASSERT_EQUALS(0, 0);
}
#endif

int
main(void)
{
   printf("%s\n", pvec_version());

   RUN(test_check);
   RUN(test_convex_domain_1);
   RUN(test_convex_domain_2);
   RUN(test_convex_sum);
   RUN(test_entropy);
   RUN(test_normalize);
   RUN(test_sparsify);

   return TEST_REPORT();
}
