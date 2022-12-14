#include "munit.h"
#include "dlist.h"
#include <assert.h>
#include <string.h>

static MunitResult
test_init(const MunitParameter params[], void* data) {
  (void) params;

  KnotStorage st;
  int maxnum = 4;
  knot_storage_init(&st, maxnum);

  munit_assert(st.knots[0].next_allocated == NULL);
  munit_assert(st.knots[0].prev_allocated == NULL);

  munit_assert(st.knots[1].next_allocated == NULL);
  munit_assert(st.knots[1].prev_allocated == NULL);

  munit_assert(st.knots[2].next_allocated == NULL);
  munit_assert(st.knots[2].prev_allocated == NULL);

  munit_assert(st.knots[3].next_allocated == NULL);
  munit_assert(st.knots[3].prev_allocated == NULL);

  munit_assert(st.knots[0].next_free == &st.knots[1]);
  munit_assert(st.knots[1].next_free == &st.knots[2]);
  munit_assert(st.knots[2].next_free == &st.knots[3]);
  munit_assert(st.knots[3].next_free == NULL);

  munit_assert(st.knots[0].prev_free == NULL);
  munit_assert(st.knots[1].prev_free == &st.knots[0]);
  munit_assert(st.knots[2].prev_free == &st.knots[1]);
  munit_assert(st.knots[3].prev_free == &st.knots[2]);

  printf("allocated         %p\n", st.knots_allocated);
  /*printf("allocated->next   %p\n", st.knots_allocated->next_allocated);*/
  /*printf("allocated->prev   %p\n", st.knots_allocated->prev_allocated);*/
  printf("free              %p\n", st.knots_free);
  printf("free->next        %p\n", st.knots_free->next_free);
  printf("free->prev        %p\n", st.knots_free->prev_free);
  printf("---------------------------------------\n");

  for(int i = 0; i < maxnum; i++) {
      Knot *kn = &st.knots[i];
      printf("i = %.2d            %p\n", i, kn);
      printf("next_allocated    %p\n", kn->next_allocated);
      printf("prev_allocated    %p\n", kn->prev_allocated);
      printf("next_free         %p\n", kn->next_free);
      printf("prev_free         %p\n", kn->prev_free);
  }

  knot_storage_free(&st);

  return MUNIT_OK;
}

static MunitResult
test_alloc(const MunitParameter params[], void* data) {
  (void) params;

  KnotStorage st;
  int maxnum = 4;
  knot_storage_init(&st, maxnum);

  munit_assert(st.knots[0].next_allocated == NULL);
  munit_assert(st.knots[0].prev_allocated == NULL);

  munit_assert(st.knots[1].next_allocated == NULL);
  munit_assert(st.knots[1].prev_allocated == NULL);

  munit_assert(st.knots[2].next_allocated == NULL);
  munit_assert(st.knots[2].prev_allocated == NULL);

  munit_assert(st.knots[3].next_allocated == NULL);
  munit_assert(st.knots[3].prev_allocated == NULL);

  munit_assert(st.knots_free == &st.knots[0]);
  munit_assert(st.knots_free->next_free != NULL);
  munit_assert(st.knots[0].next_free == &st.knots[1]);
  munit_assert(st.knots[1].next_free == &st.knots[2]);
  munit_assert(st.knots[2].next_free == &st.knots[3]);
  munit_assert(st.knots[3].next_free == NULL);

  munit_assert(st.knots[0].prev_free == NULL);
  munit_assert(st.knots[1].prev_free == &st.knots[0]);
  munit_assert(st.knots[2].prev_free == &st.knots[1]);
  munit_assert(st.knots[3].prev_free == &st.knots[2]);

  munit_assert(st.knots_free != NULL);

  Knot *kn1 = knot_alloc(&st);
  munit_assert(kn1 != NULL);
  printf("kn1\n");

  Knot *kn2 = knot_alloc(&st);
  munit_assert(kn2 != NULL);
  printf("kn2\n");

  Knot *kn3 = knot_alloc(&st);
  munit_assert(kn3 != NULL);
  printf("kn3\n");

  Knot *kn4 = knot_alloc(&st);
  munit_assert(kn4 != NULL);
  printf("kn4\n");

  munit_assert(kn1 != kn2);
  munit_assert(kn2 != kn3);
  munit_assert(kn3 != kn4);
  munit_assert(kn4 != kn1);

  munit_assert(st.knots_allocated != NULL);
  munit_assert(st.knots_allocated->prev_allocated == NULL);

  knot_storage_free(&st);

  return MUNIT_OK;
}

bool iter_check_id(Knot *kn, void *data) {
    return kn->id == (int)data;
}

bool iter_test(Knot *kn, void *data) {
    assert(kn);
    printf("kn->id = %d\n", kn->id);
    return false;
}

static MunitResult
test_alloc_free(const MunitParameter params[], void* data) {
  (void) params;

  KnotStorage st;
  int maxnum = 4;
  knot_storage_init(&st, maxnum);

  munit_assert(st.knots[0].next_allocated == NULL);
  munit_assert(st.knots[0].prev_allocated == NULL);

  munit_assert(st.knots[1].next_allocated == NULL);
  munit_assert(st.knots[1].prev_allocated == NULL);

  munit_assert(st.knots[2].next_allocated == NULL);
  munit_assert(st.knots[2].prev_allocated == NULL);

  munit_assert(st.knots[3].next_allocated == NULL);
  munit_assert(st.knots[3].prev_allocated == NULL);

  munit_assert(st.knots_free == &st.knots[0]);
  munit_assert(st.knots_free->next_free != NULL);
  munit_assert(st.knots[0].next_free == &st.knots[1]);
  munit_assert(st.knots[1].next_free == &st.knots[2]);
  munit_assert(st.knots[2].next_free == &st.knots[3]);
  munit_assert(st.knots[3].next_free == NULL);

  munit_assert(st.knots[0].prev_free == NULL);
  munit_assert(st.knots[1].prev_free == &st.knots[0]);
  munit_assert(st.knots[2].prev_free == &st.knots[1]);
  munit_assert(st.knots[3].prev_free == &st.knots[2]);

  munit_assert(st.knots_free != NULL);

  printf("\n");

  Knot *kn1 = knot_alloc(&st);
  printf("id %d\n", kn1->id);
  Knot *kn2 = knot_alloc(&st);
  printf("id %d\n", kn2->id);
  Knot *kn3 = knot_alloc(&st);
  printf("id %d\n", kn3->id);

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  /*printf("---------------------------------------\n");*/
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");

  knot_free(&st, kn1);
  knot_free(&st, kn2);
  knot_free(&st, kn3);

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  /*printf("---------------------------------------\n");*/
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");

  return MUNIT_OK;
}

static MunitResult
test_alloc_free_alloc(const MunitParameter params[], void* data) {
  (void) params;

  KnotStorage st;
  int maxnum = 4;
  knot_storage_init(&st, maxnum);

  printf("\n");

  Knot *kn1, *kn2, *kn3, *kn4;

  kn1 = knot_alloc(&st);
  munit_assert_int(kn1->id, ==, 0);
  kn2 = knot_alloc(&st);
  munit_assert_int(kn2->id, ==, 1);
  kn3 = knot_alloc(&st);
  munit_assert_int(kn3->id, ==, 2);
  kn4 = knot_alloc(&st);
  munit_assert_int(kn4->id, ==, 3);

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  /*printf("---------------------------------------\n");*/
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");

  knot_free(&st, kn1);
  knot_free(&st, kn2);
  knot_free(&st, kn3);
  knot_free(&st, kn4);

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");
  
  kn1 = knot_alloc(&st);
  munit_assert_int(kn1->id, ==, 4);
  kn2 = knot_alloc(&st);
  munit_assert_int(kn2->id, ==, 5);
  kn3 = knot_alloc(&st);
  munit_assert_int(kn3->id, ==, 6);
  kn4 = knot_alloc(&st);
  munit_assert_int(kn4->id, ==, 7);

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  /*printf("---------------------------------------\n");*/
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");

  return MUNIT_OK;
}

static MunitResult
test_alloc_free_alloc2(const MunitParameter params[], void* data) {
  (void) params;

  KnotStorage st;
  int maxnum = 4;
  knot_storage_init(&st, maxnum);

  printf("\n");

  Knot *kn1, *kn2, *kn3, *kn4;
  int saved_id = -1;

  kn1 = knot_alloc(&st);
  munit_assert_int(kn1->id, ==, 0);
  kn2 = knot_alloc(&st);
  munit_assert_int(kn2->id, ==, 1);
  kn3 = knot_alloc(&st);
  munit_assert_int(kn3->id, ==, 2);
  kn4 = knot_alloc(&st);
  munit_assert_int(kn4->id, ==, 3);

  knot_free(&st, kn1);
  knot_free(&st, kn2);
  saved_id = kn3->id;
  knot_free(&st, kn3);
  knot_free(&st, kn4);

  munit_assert_false(knot_foreach_allocated(&st, iter_check_id, saved_id));
  munit_assert_true(knot_foreach_free(&st, iter_check_id, saved_id));

  kn1 = knot_alloc(&st);
  munit_assert_int(kn1->id, ==, 4);
  kn2 = knot_alloc(&st);
  munit_assert_int(kn2->id, ==, 5);
  kn3 = knot_alloc(&st);
  munit_assert_int(kn3->id, ==, 6);
  kn4 = knot_alloc(&st);
  munit_assert_int(kn4->id, ==, 7);

  saved_id = kn2->id;
  knot_free(&st, kn2);
  knot_free(&st, kn1);
  knot_free(&st, kn3);

  munit_assert_false(knot_foreach_allocated(&st, iter_check_id, saved_id));
  munit_assert_true(knot_foreach_free(&st, iter_check_id, saved_id));

  printf("allocated nodes\n");
  knot_foreach_allocated(&st, iter_test, NULL);
  /*printf("---------------------------------------\n");*/
  printf("free nodes\n");
  knot_foreach_free(&st, iter_test, NULL);
  printf("---------------------------------------\n");

  return MUNIT_OK;
}

/* Tests are functions that return void, and take a single void*
 * parameter.  We'll get to what that parameter is later. */
static MunitResult
test_compare(const MunitParameter params[], void* data) {
  /* We'll use these later */
  const unsigned char val_uchar = 'b';
  const short val_short = 1729;
  double pi = 3.141592654;
  char* stewardesses = "stewardesses";
  char* most_fun_word_to_type;

  /* These are just to silence compiler warnings about the parameters
   * being unused. */
  (void) params;
  (void) data;

  /* Let's start with the basics. */
  munit_assert(0 != 1);

  /* There is also the more verbose, though slightly more descriptive
     munit_assert_true/false: */
  munit_assert_false(0);

  /* You can also call munit_error and munit_errorf yourself.  We
   * won't do it is used to indicate a failure, but here is what it
   * would look like: */
  /* munit_error("FAIL"); */
  /* munit_errorf("Goodbye, cruel %s", "world"); */

  /* There are macros for comparing lots of types. */
  munit_assert_char('a', ==, 'a');

  /* Sure, you could just assert('a' == 'a'), but if you did that, a
   * failed assertion would just say something like "assertion failed:
   * val_uchar == 'b'".  ??nit will tell you the actual values, so a
   * failure here would result in something like "assertion failed:
   * val_uchar == 'b' ('X' == 'b')." */
  munit_assert_uchar(val_uchar, ==, 'b');

  /* Obviously we can handle values larger than 'char' and 'uchar'.
   * There are versions for char, short, int, long, long long,
   * int8/16/32/64_t, as well as the unsigned versions of them all. */
  munit_assert_short(42, <, val_short);

  /* There is also support for size_t.
   *
   * The longest word in English without repeating any letters is
   * "uncopyrightables", which has uncopyrightable (and
   * dermatoglyphics, which is the study of fingerprints) beat by a
   * character */
  munit_assert_size(strlen("uncopyrightables"), >, strlen("dermatoglyphics"));

  /* Of course there is also support for doubles and floats. */
  munit_assert_double(pi, ==, 3.141592654);

  /* If you want to compare two doubles for equality, you might want
   * to consider using munit_assert_double_equal.  It compares two
   * doubles for equality within a precison of 1.0 x 10^-(precision).
   * Note that precision (the third argument to the macro) needs to be
   * fully evaluated to an integer by the preprocessor so ??nit doesn't
   * have to depend pow, which is often in libm not libc. */
  munit_assert_double_equal(3.141592654, 3.141592653589793, 9);

  /* And if you want to check strings for equality (or inequality),
   * there is munit_assert_string_equal/not_equal.
   *
   * "stewardesses" is the longest word you can type on a QWERTY
   * keyboard with only one hand, which makes it loads of fun to type.
   * If I'm going to have to type a string repeatedly, let's make it a
   * good one! */
  munit_assert_string_equal(stewardesses, "stewardesses");

  /* A personal favorite macro which is fantastic if you're working
   * with binary data, is the one which na??vely checks two blobs of
   * memory for equality.  If this fails it will tell you the offset
   * of the first differing byte. */
  munit_assert_memory_equal(7, stewardesses, "steward");

  /* You can also make sure that two blobs differ *somewhere*: */
  munit_assert_memory_not_equal(8, stewardesses, "steward");

  /* There are equal/not_equal macros for pointers, too: */
  most_fun_word_to_type = stewardesses;
  munit_assert_ptr_equal(most_fun_word_to_type, stewardesses);

  /* And null/not_null */
  munit_assert_null(NULL);
  munit_assert_not_null(most_fun_word_to_type);

  /* Lets verify that the data parameter is what we expected.  We'll
   * see where this comes from in a bit.
   *
   * Note that the casting isn't usually required; if you give this
   * function a real pointer (instead of a number like 0xdeadbeef) it
   * would work as expected. */
  munit_assert_ptr_equal(data, (void*)(uintptr_t)0xdeadbeef);

  return MUNIT_OK;
}

static MunitResult
test_rand(const MunitParameter params[], void* user_data) {
  int random_int;
  double random_dbl;
  munit_uint8_t data[5];

  (void) params;
  (void) user_data;

  /* One thing missing from a lot of unit testing frameworks is a
   * random number generator.  You can't just use srand/rand because
   * the implementation varies across different platforms, and it's
   * important to be able to look at the seed used in a failing test
   * to see if you can reproduce it.  Some randomness is a fantastic
   * thing to have in your tests, I don't know why more people don't
   * do it...
   *
   * ??nit's PRNG is re-seeded with the same value for each iteration
   * of each test.  The seed is retrieved from the MUNIT_SEED
   * envirnment variable or, if none is provided, one will be
   * (pseudo-)randomly generated. */

  /* If you need an integer in a given range */
  random_int = munit_rand_int_range(128, 4096);
  munit_assert_int(random_int, >=, 128);
  munit_assert_int(random_int, <=, 4096);

  /* Or maybe you want a double, between 0 and 1: */
  random_dbl = munit_rand_double();
  munit_assert_double(random_dbl, >=, 0.0);
  munit_assert_double(random_dbl, <=, 1.0);

  /* Of course, you want to be able to reproduce bugs discovered
   * during testing, so every time the tests are run they print the
   * random seed used.  When you want to reproduce a result, just put
   * that random seed in the MUNIT_SEED environment variable; it even
   * works on different platforms.
   *
   * If you want this to pass, use 0xdeadbeef as the random seed and
   * uncomment the next line of code.  Note that the PRNG is not
   * re-seeded between iterations of the same test, so this will only
   * work on the first iteration. */
  /* munit_assert_uint32(munit_rand_uint32(), ==, 1306447409); */

  /* You can also get blobs of random memory: */
  munit_rand_memory(sizeof(data), data);

  return MUNIT_OK;
}

/* This test case shows how to accept parameters.  We'll see how to
 * specify them soon.
 *
 * By default, every possible variation of a parameterized test is
 * run, but you can specify parameters manually if you want to only
 * run specific test(s), or you can pass the --single argument to the
 * CLI to have the harness simply choose one variation at random
 * instead of running them all. */
static MunitResult
test_parameters(const MunitParameter params[], void* user_data) {
  const char* foo;
  const char* bar;

  (void) user_data;

  /* The "foo" parameter is specified as one of the following values:
   * "one", "two", or "three". */
  foo = munit_parameters_get(params, "foo");
  /* Similarly, "bar" is one of "four", "five", or "six". */
  bar = munit_parameters_get(params, "bar");
  /* "baz" is a bit more complicated.  We don't actually specify a
   * list of valid values, so by default NULL is passed.  However, the
   * CLI will accept any value.  This is a good way to have a value
   * that is usually selected randomly by the test, but can be
   * overridden on the command line if desired. */
  /* const char* baz = munit_parameters_get(params, "baz"); */

  /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */

  if (strcmp(foo, "one") != 0 &&
      strcmp(foo, "two") != 0 &&
      strcmp(foo, "three") != 0)
    return MUNIT_FAIL;

  if (strcmp(bar, "red") != 0 &&
      strcmp(bar, "green") != 0 &&
      strcmp(bar, "blue") != 0)
    return MUNIT_FAIL;

  return MUNIT_OK;
}

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */
static void*
test_compare_setup(const MunitParameter params[], void* user_data) {
  (void) params;

  munit_assert_string_equal(user_data, "??nit");
  return (void*) (uintptr_t) 0xdeadbeef;
}

/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void
test_compare_tear_down(void* fixture) {
  munit_assert_ptr_equal(fixture, (void*)(uintptr_t)0xdeadbeef);
}

static char* foo_params[] = {
  (char*) "one", (char*) "two", (char*) "three", NULL
};

static char* bar_params[] = {
  (char*) "red", (char*) "green", (char*) "blue", NULL
};

static MunitParameterEnum test_params[] = {
  { (char*) "foo", foo_params },
  { (char*) "bar", bar_params },
  { (char*) "baz", NULL },
  { NULL, NULL },
};

static MunitTest dlist_tests[] = {
  { (char*) "/dlist/init", test_init, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/dlist/alloc", test_alloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/dlist/alloc_free", test_alloc_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/dlist/alloc_free_alloc", test_alloc_free_alloc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/dlist/alloc_free_alloc2", test_alloc_free_alloc2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

  /*{ (char*) "/CIRC_BUF/push", test_push, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },*/
  /*{ (char*) "/CIRC_BUF/pop", test_pop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },*/
  /*{ (char*) "/CIRC_BUF/push_pop_1size", test_push_pop_1size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },*/

};

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  /* Usually this is written in a much more compact format; all these
   * comments kind of ruin that, though.  Here is how you'll usually
   * see entries written: */
  { (char*) "/example/rand", test_rand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  /* To tell the test runner when the array is over, just add a NULL
   * entry at the end. */
  /*{ (char*) "/example/parameters", test_parameters, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },*/
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/??nit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "",
  /* The first parameter is the array of test suites. */
  /*test_suite_tests,*/
  dlist_tests,
  /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
  NULL,
  /* An interesting feature of ??nit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
  1,
  /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
  MUNIT_SUITE_OPTION_NONE
};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about ??nit requires it. */
#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void*) "??nit", argc, argv);
}
