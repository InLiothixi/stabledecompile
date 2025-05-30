/*
    Copyright 2010 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl-2.0.txt
*/

#ifdef i386

// x86 32bit calling conventions 0.1
// ---------------------------------
// the functions have been written in this "easy-to-use" way just
// for being used in any project other than QuickBMS for which were
// created and with the maximum compatibility in mind.
// everything done here is necessary to preserve the stack and
// allowing the correct assignment of the arguments to the registers.
// note that all these functions have not been tested at 100%, my
// only doubt is about the preserved registers at return in some
// of them (like syscall).

#define INIT_CALLCONV \
    va_list ap; \
    int     i, \
            ret, \
            argv[argc]; \
    \
    va_start(ap, argc); \
    for(i = 0; i < argc; i++) { \
        argv[i] = va_arg(ap, int); \
    } \
    va_end(ap);
#define MYASM   __asm__ __volatile__ 



int cdecl_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 0; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }

    MYASM("call *%0" :: "g"(func));
    MYASM("add %0, %%esp" :: "g"(argc * 4));
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int stdcall_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 0; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }

    MYASM("call *%0" :: "g"(func));
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int msfastcall_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 2; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }
    if(argc > 1) MYASM("movl %0, %%edx" :: "g"(argv[1]) : "%ecx"       );
    if(argc > 0) MYASM("movl %0, %%ecx" :: "g"(argv[0]) :        "%edx");

    MYASM("call *%0" :: "g"(func) : "%ecx","%edx");
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int borland_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = 3; i < argc; i++) { // left->right
        MYASM("push %0" :: "g"(argv[i]));
    }
    if(argc > 2) MYASM("movl %0, %%ecx" :: "g"(argv[2]) : "%eax","%edx"       );
    if(argc > 1) MYASM("movl %0, %%edx" :: "g"(argv[1]) : "%eax",       "%ecx");
    if(argc > 0) MYASM("movl %0, %%eax" :: "g"(argv[0]) :        "%edx","%ecx");

    MYASM("call *%0" :: "g"(func) : "%eax","%edx","%ecx");
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int pascal_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = 0; i < argc; i++) { // left->right
        MYASM("push %0" :: "g"(argv[i]));
    }

    MYASM("call *%0" :: "g"(func));
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int watcom_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 4; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }

    if(argc > 3) MYASM("movl %0, %%ecx" :: "g"(argv[3]) : "%eax","%edx","%ebx"       );
    if(argc > 2) MYASM("movl %0, %%ebx" :: "g"(argv[2]) : "%eax","%edx",       "%ecx");
    if(argc > 1) MYASM("movl %0, %%edx" :: "g"(argv[1]) : "%eax",       "%ebx","%ecx");
    if(argc > 0) MYASM("movl %0, %%eax" :: "g"(argv[0]) :        "%edx","%ebx","%ecx");

    MYASM("call *%0" :: "g"(func) : "%eax","%edx","%ebx","%ecx");
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int safecall_call(void *func, int argc, ...) {
    INIT_CALLCONV

    ret = 0;
    MYASM("push %0" :: "g"(&ret));

    for(i = argc - 1; i >= 0; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }

    MYASM("call *%0" :: "g"(func));
    // eax is 0 if all ok or another value in case of exceptions
    return(ret);
}



int syscall_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 0; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }

    MYASM("movl %0, %%eax" :: "g"(argc)); // from Wikipedia but it looks false
    MYASM("call *%0" :: "g"(func) : "%eax");  // note that is not clear the thing of
    MYASM("add %0, %%esp" :: "g"(argc * 4));
    MYASM("movl %%eax, %0" : "=g"(ret));      // preservation but should be ok like in cdecl
    return(ret);
}



int optilink_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = argc - 1; i >= 3; i--) {    // right->left
        MYASM("push %0" :: "g"(argv[i]));
    }
    if(argc > 2) MYASM("movl %0, %%ecx" :: "g"(argv[2]) : "%eax","%edx"       );
    if(argc > 1) MYASM("movl %0, %%edx" :: "g"(argv[1]) : "%eax",       "%ecx");
    if(argc > 0) MYASM("movl %0, %%eax" :: "g"(argv[0]) :        "%edx","%ecx");

    MYASM("call *%0" :: "g"(func) : "%eax","%edx","%ecx");
    MYASM("add %0, %%esp" :: "g"(argc * 4));
    MYASM("movl %%eax, %0" : "=g"(ret));
    return(ret);
}



int clarion_call(void *func, int argc, ...) {
    INIT_CALLCONV

    for(i = 4; i < argc; i++) { // left->right
        MYASM("push %0" :: "g"(argv[i]));
    }

    if(argc > 3) MYASM("movl %0, %%edx" :: "g"(argv[3]) : "%eax","%ebx","%ecx"       );
    if(argc > 2) MYASM("movl %0, %%ecx" :: "g"(argv[2]) : "%eax","%ebx",       "%edx");
    if(argc > 1) MYASM("movl %0, %%ebx" :: "g"(argv[1]) : "%eax",       "%ecx","%edx");
    if(argc > 0) MYASM("movl %0, %%eax" :: "g"(argv[0]) :        "%ebx","%ecx","%edx");

    MYASM("call *%0" :: "g"(func) : "%eax","%ebx","%ecx","%edx");
    MYASM("movl %%eax, %0" : "=g"(ret));
    //MYASM("movl %%edx, %0" : "=g"(ret));  // for pointers
    return(ret);
}

#endif

