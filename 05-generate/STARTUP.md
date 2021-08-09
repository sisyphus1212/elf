
# X86 App Starting up procedure

```
glibc: csu/libc-start.c: `___libc_start_main`: init+main+exit

_start            /* main, argc, argv*,         init,     fini,       rtld_fini, stack_end */

    __libc_start_main(main, %esi, %ecx, __libc_csu_init, __libc_csu_fini, %edx, %esp)

        ARCH_SETUP_IREL () -> apply_irel() -> elf_irel
        __libc_init_first (argc, argv, __environ);
        VDSO_SETUP (); -> __vdso_platform_setup -> _dl_vdso_vsym

        __libc_global_ctors ();                                                             /* csu/init-first.c */
            run_hooks (__CTOR_LIST__);                                                      /* elf/soinit.c, .ctors */

        __cxa_atexit ((void (*) (void *)) rtld_fini, NULL, NULL);                           /* register fini funcs for rtld */
        __cxa_atexit ((void (*) (void *)) fini, NULL, NULL);                                /* register fini funcs for itself */

      + (*init) (argc, argv, __environ MAIN_AUXVEC_PARAM);
            __libc_csu_init()                                                               /* csu/elf-init.c */
                (*__init_array_start [i]) (argc, argv, envp);                               /*.init_array*/
                _init                                                                       /* sysdep/i386/crti.S, crtn.S */
                    __gmon_start__                                                          /* csu/gmon-start.c, profiling start */

      + result = main (argc, argv, __environ MAIN_AUXVEC_PARAM);                            /* call main entry of hello.c here */

      + exit (result)                                                                       /* stdlib/exit.c */
            __run_exit_handlers()
                RUN_HOOK (__libc_atexit, ());
                    __libc_csu_fini()                                                       /* csu/elf-init.c, via atexit() */
                        (*__fini_array_start [i]) ();
                             __libc_fini                                                    /* .fini_array <= elf/soinit.c: __libc_fini */
                                 run_hooks (__DTOR_LIST);                                   /* elf/soinit.c, .dtors */
                        _fini                                                               /* sysdep/i386/crti.S, crtn.S */
                _exit (status);                                                             /* sysdeps/unix/sysv/linux/_exit.c */
                    INLINE_SYSCALL (exit, 1, status);                                       /* may exit_group */
```


## Recommendation

* [How main() is executed on Linux ](https://linuxgazette.net/84/hawk.html)
