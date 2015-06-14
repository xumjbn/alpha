
#include <stdio.h>  /* perror */
#include <string.h> /* strerror */
#include <stdbool.h>
#include <errno.h>  

#include "lstd.h"

static int lerr_strerror(lua_State *L)
{
    int err = luaL_checknumber(L, 1);
    char *strerr = strerror(err);     /* not reentrant */
    lua_pushstring(L, strerr);
    return 1;
}

static int lerr_perror(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    perror(msg);
    return 0;
}

static int lerr_seterrno(lua_State *L)
{
    errno = luaL_checknumber(L, 1);
    lua_pushboolean(L, true);
    return 1;
}

static void lerr_errnoreg(lua_State *L)
{
    LPOSIX_CONST(EPERM);       			/* Operation not permitted */
    LPOSIX_CONST(ENOENT);      			/* No such file or directory */
    LPOSIX_CONST(ESRCH);       			/* No such process */
    LPOSIX_CONST(EINTR);       			/* Interrupted system call */
    LPOSIX_CONST(EIO);         			/* I/O error */
    LPOSIX_CONST(ENXIO);       			/* No such device or address */
    LPOSIX_CONST(E2BIG);       			/* Arg list too long */
    LPOSIX_CONST(ENOEXEC);     			/* Exec format error */
    LPOSIX_CONST(EBADF);       			/* Bad file number */
    LPOSIX_CONST(ECHILD);      			/* No child processes */
    LPOSIX_CONST(EAGAIN);      			/* Try again */
    LPOSIX_CONST(ENOMEM);      			/* Out of memory */
    LPOSIX_CONST(EACCES);      			/* Permission denied */
    LPOSIX_CONST(EFAULT);      			/* Bad address */
    LPOSIX_CONST(ENOTBLK);     			/* Block device required */
    LPOSIX_CONST(EBUSY);       			/* Device or resource busy */
    LPOSIX_CONST(EEXIST);      			/* File exists */
    LPOSIX_CONST(EXDEV);       			/* Cross-device link */
    LPOSIX_CONST(ENODEV);      			/* No such device */
    LPOSIX_CONST(ENOTDIR);     			/* Not a directory */
    LPOSIX_CONST(EISDIR);      			/* Is a directory */
    LPOSIX_CONST(EINVAL);      			/* Invalid argument */
    LPOSIX_CONST(ENFILE);      			/* File table overflow */
    LPOSIX_CONST(EMFILE);      			/* Too many open files */
    LPOSIX_CONST(ENOTTY);      			/* Not a typewriter */
    LPOSIX_CONST(ETXTBSY);     			/* Text file busy */
    LPOSIX_CONST(EFBIG);       			/* File too large */
    LPOSIX_CONST(ENOSPC);      			/* No space left on device */
    LPOSIX_CONST(ESPIPE);      			/* Illegal seek */
    LPOSIX_CONST(EROFS);       			/* Read-only file system */
    LPOSIX_CONST(EMLINK);      			/* Too many links */
    LPOSIX_CONST(EPIPE);       			/* Broken pipe */
    LPOSIX_CONST(EDOM);        			/* Math argument out of domain of func */
    LPOSIX_CONST(ERANGE);      			/* Math result not representable */
    LPOSIX_CONST(EDEADLK);     			/* Resource deadlock would occur */
    LPOSIX_CONST(ENAMETOOLONG);         /* File name too long */
    LPOSIX_CONST(ENOLCK);      			/* No record locks available */
    LPOSIX_CONST(ENOSYS);      			/* Function not implemented */
    LPOSIX_CONST(ENOTEMPTY);   			/* Directory not empty */
    LPOSIX_CONST(ELOOP);       			/* Too many symbolic links encountered */
    LPOSIX_CONST(EWOULDBLOCK); 			/* Operation would block */
    LPOSIX_CONST(ENOMSG);      			/* No message of desired type */
    LPOSIX_CONST(EIDRM);       			/* Identifier removed */
    LPOSIX_CONST(ECHRNG);      			/* Channel number out of range */
    LPOSIX_CONST(EL2NSYNC);    			/* Level 2 not synchronized */
    LPOSIX_CONST(EL3HLT);      			/* Level 3 halted */
    LPOSIX_CONST(EL3RST);      			/* Level 3 reset */
    LPOSIX_CONST(ELNRNG);      			/* Link number out of range */
    LPOSIX_CONST(EUNATCH);     			/* Protocol driver not attached */
    LPOSIX_CONST(ENOCSI);      			/* No CSI structure available */
    LPOSIX_CONST(EL2HLT);      			/* Level 2 halted */
    LPOSIX_CONST(EBADE);       			/* Invalid exchange */
    LPOSIX_CONST(EBADR);       			/* Invalid request descriptor */
    LPOSIX_CONST(EXFULL);      			/* Exchange full */
    LPOSIX_CONST(ENOANO);      			/* No anode */
    LPOSIX_CONST(EBADRQC);     			/* Invalid request code */
    LPOSIX_CONST(EBADSLT);     			/* Invalid slot */
    LPOSIX_CONST(EDEADLOCK);   			/* EDEADLK */
    LPOSIX_CONST(EBFONT);      			/* Bad font file format */
    LPOSIX_CONST(ENOSTR);      			/* Device not a stream */
    LPOSIX_CONST(ENODATA);     			/* No data available */
    LPOSIX_CONST(ETIME);       			/* Timer expired */
    LPOSIX_CONST(ENOSR);       			/* Out of streams resources */
    LPOSIX_CONST(ENONET);      			/* Machine is not on the network */
    LPOSIX_CONST(ENOPKG);      			/* Package not installed */
    LPOSIX_CONST(EREMOTE);     			/* Object is remote */
    LPOSIX_CONST(ENOLINK);     			/* Link has been severed */
    LPOSIX_CONST(EADV);        			/* Advertise error */
    LPOSIX_CONST(ESRMNT);      			/* Srmount error */
    LPOSIX_CONST(ECOMM);       			/* Communication error on send */
    LPOSIX_CONST(EPROTO);      			/* Protocol error */
    LPOSIX_CONST(EMULTIHOP);   			/* Multihop attempted */
    LPOSIX_CONST(EDOTDOT);     			/* RFS specific error */
    LPOSIX_CONST(EBADMSG);     			/* Not a data message */
    LPOSIX_CONST(EOVERFLOW);   			/* Value too large for defined data type */
    LPOSIX_CONST(ENOTUNIQ);    			/* Name not unique on network */
    LPOSIX_CONST(EBADFD);      			/* File descriptor in bad state */
    LPOSIX_CONST(EREMCHG);     			/* Remote address changed */
    LPOSIX_CONST(ELIBACC);     			/* Can not access a needed shared library */
    LPOSIX_CONST(ELIBBAD);     			/* Accessing a corrupted shared library */
    LPOSIX_CONST(ELIBSCN);              /* .lib section in a.out corrupted */
    LPOSIX_CONST(ELIBMAX);              /* Attempting to link in too many shared libraries */
    LPOSIX_CONST(ELIBEXEC);             /* Cannot exec a shared library directly */
    LPOSIX_CONST(EILSEQ);               /* Illegal byte sequence */
    LPOSIX_CONST(ERESTART);             /* Interrupted system call should be restarted */
    LPOSIX_CONST(ESTRPIPE);             /* Streams pipe error */
    LPOSIX_CONST(EUSERS);               /* Too many users */
    LPOSIX_CONST(ENOTSOCK);             /* Socket operation on non-socket */
    LPOSIX_CONST(EDESTADDRREQ);         /* Destination address required */
    LPOSIX_CONST(EMSGSIZE);             /* Message too long */
    LPOSIX_CONST(EPROTOTYPE);           /* Protocol wrong type for socket */
    LPOSIX_CONST(ENOPROTOOPT);          /* Protocol not available */
    LPOSIX_CONST(EPROTONOSUPPORT);      /* Protocol not supported */
    LPOSIX_CONST(ESOCKTNOSUPPORT);      /* Socket type not supported */
    LPOSIX_CONST(EOPNOTSUPP);           /* Operation not supported on transport endpoint */
    LPOSIX_CONST(EPFNOSUPPORT);         /* Protocol family not supported */
    LPOSIX_CONST(EAFNOSUPPORT);         /* Address family not supported by protocol */
    LPOSIX_CONST(EADDRINUSE);           /* Address already in use */
    LPOSIX_CONST(EADDRNOTAVAIL);        /* Cannot assign requested address */
    LPOSIX_CONST(ENETDOWN);             /* Network is down */
    LPOSIX_CONST(ENETUNREACH);          /* Network is unreachable */
    LPOSIX_CONST(ENETRESET);            /* Network dropped connection because of reset */
    LPOSIX_CONST(ECONNABORTED);         /* Software caused connection abort */
    LPOSIX_CONST(ECONNRESET);           /* Connection reset by peer */
    LPOSIX_CONST(ENOBUFS);              /* No buffer space available */
    LPOSIX_CONST(EISCONN);              /* Transport endpoint is already connected */
    LPOSIX_CONST(ENOTCONN);             /* Transport endpoint is not connected */
    LPOSIX_CONST(ESHUTDOWN);            /* Cannot send after transport endpoint shutdown */
    LPOSIX_CONST(ETOOMANYREFS);         /* Too many references: cannot splice */
    LPOSIX_CONST(ETIMEDOUT);            /* Connection timed out */
    LPOSIX_CONST(ECONNREFUSED);         /* Connection refused */
    LPOSIX_CONST(EHOSTDOWN);            /* Host is down */
    LPOSIX_CONST(EHOSTUNREACH);         /* No route to host */
    LPOSIX_CONST(EALREADY);             /* Operation already in progress */
    LPOSIX_CONST(EINPROGRESS);          /* Operation now in progress */
    LPOSIX_CONST(ESTALE);               /* Stale NFS file handle */
    LPOSIX_CONST(EUCLEAN);              /* Structure needs cleaning */
    LPOSIX_CONST(ENOTNAM);              /* Not a XENIX named type file */
    LPOSIX_CONST(ENAVAIL);              /* No XENIX semaphores available */
    LPOSIX_CONST(EISNAM);               /* Is a named type file */
    LPOSIX_CONST(EREMOTEIO);            /* Remote I/O error */
    LPOSIX_CONST(EDQUOT);               /* Quota exceeded */
    LPOSIX_CONST(ENOMEDIUM);            /* No medium found */
    LPOSIX_CONST(EMEDIUMTYPE);          /* Wrong medium type */
    LPOSIX_CONST(ECANCELED);            /* Operation Canceled */
    LPOSIX_CONST(ENOKEY);               /* Required key not available */
    LPOSIX_CONST(EKEYEXPIRED);          /* Key has expired */
    LPOSIX_CONST(EKEYREVOKED);          /* Key has been revoked */
    LPOSIX_CONST(EKEYREJECTED);         /* Key was rejected by service */
    /* for robust mutexes */
    LPOSIX_CONST(EOWNERDEAD);           /* Owner died */
    LPOSIX_CONST(ENOTRECOVERABLE);      /* State not recoverable */
}

static const struct luaL_Reg os_funcs[] = {
    {"strerror",    lerr_strerror},
    {"perror",      lerr_perror},
    {"seterrno",    lerr_seterrno},
    {NULL,          NULL},
};

int lstd_openerr(lua_State *L)
{
    luaL_register(L, "err", os_funcs);
    lerr_errnoreg(L);
    return 0;
}
