#include <stdio.h>

/* ref: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=46770  */
#ifdef INIT_FINI
static void init()
{
  printf ("init_array\n");
}

#if 1
__attribute__((section (".init_array"))) typeof(init) *myinit =  init;
#else
static void (*const init_array []) ()
  __attribute__ ((section (".init_array"), aligned (sizeof (void *)))) __attribute__ ((unused))
  = { init };
#endif

static void fini()
{
  printf ("fini_array\n");
}

#if 1
__attribute__((section (".fini_array"))) typeof(fini) *myfini =  fini;
#else
static void (*const fini_array []) ()
  __attribute__ ((section (".fini_array"), aligned (sizeof (void *)))) __attribute__ ((unused))
  = { fini };
#endif

#endif

#ifdef AT_EXIT
#include <stdlib.h>

static void
run_at_exit ()
{
  printf ("atexit\n");
}
#endif


int main(int argc, char *argv[])
{
#ifdef SEGFAULT_TEST
	int i = 0;

	printf("Please input a number: ");
	scanf("%d", i);
#endif
#ifdef AT_EXIT
	atexit(run_at_exit);
#endif
	printf("main\n");

	return 0;
}
