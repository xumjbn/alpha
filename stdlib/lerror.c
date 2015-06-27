
#include <stdio.h>  /* perror */
#include <string.h> /* strerror */
#include <stdbool.h>
#include <errno.h>  

#include "lstd.h"


/*
 * strerr = err.strerro(errno)
 */
static int lerr_strerror(lua_State *L)
{
    int err = luaL_checknumber(L, 1);
    char *strerr = strerror(err);     /* not reentrant */
    lua_pushstring(L, strerr);
    return 1;
}

/*
 * err.perror(msg)
 */
static int lerr_perror(lua_State *L)
{
    int err = luaL_checkint(L, 1);
    printf("%s\n", strerror(err));
    return 0;
}

/*
 *  true = err.seterrno(errno)
 */
static int lerr_seterrno(lua_State *L)
{
    errno = luaL_checknumber(L, 1);
    lua_pushboolean(L, true);
    return 1;
}

static void lerrno_register(lua_State *L)
{
    LERR_NUMS(EPERM);       			/* Operation not permitted */
    LERR_NUMS(ENOENT);      			/* No such file or directory */
    LERR_NUMS(ESRCH);       			/* No such process */
    LERR_NUMS(EINTR);       			/* Interrupted system call */
    LERR_NUMS(EIO);         			/* I/O error */
    LERR_NUMS(ENXIO);       			/* No such device or address */
    LERR_NUMS(E2BIG);       			/* Arg list too long */
    LERR_NUMS(ENOEXEC);     			/* Exec format error */
    LERR_NUMS(EBADF);       			/* Bad file number */
    LERR_NUMS(ECHILD);      			/* No child processes */
    LERR_NUMS(EAGAIN);      			/* Try again */
    LERR_NUMS(ENOMEM);      			/* Out of memory */
    LERR_NUMS(EACCES);      			/* Permission denied */
    LERR_NUMS(EFAULT);      			/* Bad address */
    LERR_NUMS(ENOTBLK);     			/* Block device required */
    LERR_NUMS(EBUSY);       			/* Device or resource busy */
    LERR_NUMS(EEXIST);      			/* File exists */
    LERR_NUMS(EXDEV);       			/* Cross-device link */
    LERR_NUMS(ENODEV);      			/* No such device */
    LERR_NUMS(ENOTDIR);     			/* Not a directory */
    LERR_NUMS(EISDIR);      			/* Is a directory */
    LERR_NUMS(EINVAL);      			/* Invalid argument */
    LERR_NUMS(ENFILE);      			/* File table overflow */
    LERR_NUMS(EMFILE);      			/* Too many open files */
    LERR_NUMS(ENOTTY);      			/* Not a typewriter */
    LERR_NUMS(ETXTBSY);     			/* Text file busy */
    LERR_NUMS(EFBIG);       			/* File too large */
    LERR_NUMS(ENOSPC);      			/* No space left on device */
    LERR_NUMS(ESPIPE);      			/* Illegal seek */
    LERR_NUMS(EROFS);       			/* Read-only file system */
    LERR_NUMS(EMLINK);      			/* Too many links */
    LERR_NUMS(EPIPE);       			/* Broken pipe */
    LERR_NUMS(EDOM);        			/* Math argument out of domain of func */
    LERR_NUMS(ERANGE);      			/* Math result not representable */
    LERR_NUMS(EDEADLK);     			/* Resource deadlock would occur */
    LERR_NUMS(ENAMETOOLONG);            /* File name too long */
    LERR_NUMS(ENOLCK);      			/* No record locks available */
    LERR_NUMS(ENOSYS);      			/* Function not implemented */
    LERR_NUMS(ENOTEMPTY);   			/* Directory not empty */
    LERR_NUMS(ELOOP);       			/* Too many symbolic links encountered */
    LERR_NUMS(EWOULDBLOCK); 			/* Operation would block */
    LERR_NUMS(ENOMSG);      			/* No message of desired type */
    LERR_NUMS(EIDRM);       			/* Identifier removed */
    LERR_NUMS(ECHRNG);      			/* Channel number out of range */
    LERR_NUMS(EL2NSYNC);    			/* Level 2 not synchronized */
    LERR_NUMS(EL3HLT);      			/* Level 3 halted */
    LERR_NUMS(EL3RST);      			/* Level 3 reset */
    LERR_NUMS(ELNRNG);      			/* Link number out of range */
    LERR_NUMS(EUNATCH);     			/* Protocol driver not attached */
    LERR_NUMS(ENOCSI);      			/* No CSI structure available */
    LERR_NUMS(EL2HLT);      			/* Level 2 halted */
    LERR_NUMS(EBADE);       			/* Invalid exchange */
    LERR_NUMS(EBADR);       			/* Invalid request descriptor */
    LERR_NUMS(EXFULL);      			/* Exchange full */
    LERR_NUMS(ENOANO);      			/* No anode */
    LERR_NUMS(EBADRQC);     			/* Invalid request code */
    LERR_NUMS(EBADSLT);     			/* Invalid slot */
    LERR_NUMS(EDEADLOCK);   			/* EDEADLK */
    LERR_NUMS(EBFONT);      			/* Bad font file format */
    LERR_NUMS(ENOSTR);      			/* Device not a stream */
    LERR_NUMS(ENODATA);     			/* No data available */
    LERR_NUMS(ETIME);       			/* Timer expired */
    LERR_NUMS(ENOSR);       			/* Out of streams resources */
    LERR_NUMS(ENONET);      			/* Machine is not on the network */
    LERR_NUMS(ENOPKG);      			/* Package not installed */
    LERR_NUMS(EREMOTE);     			/* Object is remote */
    LERR_NUMS(ENOLINK);     			/* Link has been severed */
    LERR_NUMS(EADV);        			/* Advertise error */
    LERR_NUMS(ESRMNT);      			/* Srmount error */
    LERR_NUMS(ECOMM);       			/* Communication error on send */
    LERR_NUMS(EPROTO);      			/* Protocol error */
    LERR_NUMS(EMULTIHOP);   			/* Multihop attempted */
    LERR_NUMS(EDOTDOT);     			/* RFS specific error */
    LERR_NUMS(EBADMSG);     			/* Not a data message */
    LERR_NUMS(EOVERFLOW);   			/* Value too large for defined data type */
    LERR_NUMS(ENOTUNIQ);    			/* Name not unique on network */
    LERR_NUMS(EBADFD);      			/* File descriptor in bad state */
    LERR_NUMS(EREMCHG);     			/* Remote address changed */
    LERR_NUMS(ELIBACC);     			/* Can not access a needed shared library */
    LERR_NUMS(ELIBBAD);     			/* Accessing a corrupted shared library */
    LERR_NUMS(ELIBSCN);                 /* .lib section in a.out corrupted */
    LERR_NUMS(ELIBMAX);                 /* Attempting to link in too many shared libraries */
    LERR_NUMS(ELIBEXEC);                /* Cannot exec a shared library directly */
    LERR_NUMS(EILSEQ);                  /* Illegal byte sequence */
    LERR_NUMS(ERESTART);                /* Interrupted system call should be restarted */
    LERR_NUMS(ESTRPIPE);                /* Streams pipe error */
    LERR_NUMS(EUSERS);                  /* Too many users */
    LERR_NUMS(ENOTSOCK);                /* Socket operation on non-socket */
    LERR_NUMS(EDESTADDRREQ);            /* Destination address required */
    LERR_NUMS(EMSGSIZE);                /* Message too long */
    LERR_NUMS(EPROTOTYPE);              /* Protocol wrong type for socket */
    LERR_NUMS(ENOPROTOOPT);             /* Protocol not available */
    LERR_NUMS(EPROTONOSUPPORT);         /* Protocol not supported */
    LERR_NUMS(ESOCKTNOSUPPORT);         /* Socket type not supported */
    LERR_NUMS(EOPNOTSUPP);              /* Operation not supported on transport endpoint */
    LERR_NUMS(EPFNOSUPPORT);            /* Protocol family not supported */
    LERR_NUMS(EAFNOSUPPORT);            /* Address family not supported by protocol */
    LERR_NUMS(EADDRINUSE);              /* Address already in use */
    LERR_NUMS(EADDRNOTAVAIL);           /* Cannot assign requested address */
    LERR_NUMS(ENETDOWN);                /* Network is down */
    LERR_NUMS(ENETUNREACH);             /* Network is unreachable */
    LERR_NUMS(ENETRESET);               /* Network dropped connection because of reset */
    LERR_NUMS(ECONNABORTED);            /* Software caused connection abort */
    LERR_NUMS(ECONNRESET);              /* Connection reset by peer */
    LERR_NUMS(ENOBUFS);                 /* No buffer space available */
    LERR_NUMS(EISCONN);                 /* Transport endpoint is already connected */
    LERR_NUMS(ENOTCONN);                /* Transport endpoint is not connected */
    LERR_NUMS(ESHUTDOWN);               /* Cannot send after transport endpoint shutdown */
    LERR_NUMS(ETOOMANYREFS);            /* Too many references: cannot splice */
    LERR_NUMS(ETIMEDOUT);               /* Connection timed out */
    LERR_NUMS(ECONNREFUSED);            /* Connection refused */
    LERR_NUMS(EHOSTDOWN);               /* Host is down */
    LERR_NUMS(EHOSTUNREACH);            /* No route to host */
    LERR_NUMS(EALREADY);                /* Operation already in progress */
    LERR_NUMS(EINPROGRESS);             /* Operation now in progress */
    LERR_NUMS(ESTALE);                  /* Stale NFS file handle */
    LERR_NUMS(EUCLEAN);                 /* Structure needs cleaning */
    LERR_NUMS(ENOTNAM);                 /* Not a XENIX named type file */
    LERR_NUMS(ENAVAIL);                 /* No XENIX semaphores available */
    LERR_NUMS(EISNAM);                  /* Is a named type file */
    LERR_NUMS(EREMOTEIO);               /* Remote I/O error */
    LERR_NUMS(EDQUOT);                  /* Quota exceeded */
    LERR_NUMS(ENOMEDIUM);               /* No medium found */
    LERR_NUMS(EMEDIUMTYPE);             /* Wrong medium type */
    LERR_NUMS(ECANCELED);               /* Operation Canceled */
    LERR_NUMS(ENOKEY);                  /* Required key not available */
    LERR_NUMS(EKEYEXPIRED);             /* Key has expired */
    LERR_NUMS(EKEYREVOKED);             /* Key has been revoked */
    LERR_NUMS(EKEYREJECTED);            /* Key was rejected by service */
    /* for robust mutexes */
    LERR_NUMS(EOWNERDEAD);              /* Owner died */
    LERR_NUMS(ENOTRECOVERABLE);         /* State not recoverable */
}

static const struct luaL_Reg err_funcs[] = {
    {"strerror",    lerr_strerror},
    {"perror",      lerr_perror},
    {"seterrno",    lerr_seterrno},
    {NULL,          NULL},
};

int lstd_openerr(lua_State *L)
{
    luaL_register(L, "errno", err_funcs);
    lerrno_register(L);
    return 0;
}
