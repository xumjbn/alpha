
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <dirent.h> /* oepndir */
#include <glob.h>	/* glob */
#include <stdint.h>
#include <errno.h>

#include "lstd.h"

#define CWD_SIZE	512


static void push_stattot(lua_State *L, struct stat *buf)
{
	lua_newtable(L);
	lstd_rawsetnumber(L, "mode", buf->st_mode);
	lstd_rawsetnumber(L, "inode", buf->st_ino);
	lstd_rawsetnumber(L, "dev", buf->st_dev);
	lstd_rawsetnumber(L, "rdev", buf->st_rdev);
	lstd_rawsetnumber(L, "nlink", buf->st_nlink);
	lstd_rawsetnumber(L, "uid", buf->st_uid);
	lstd_rawsetnumber(L, "gid", buf->st_gid);
	lstd_rawsetnumber(L, "size", buf->st_size);
	lstd_rawsetnumber(L, "atime", buf->st_atime);
	lstd_rawsetnumber(L, "mtime", buf->st_mtime);
	lstd_rawsetnumber(L, "ctime", buf->st_ctime);
	lstd_rawsetnumber(L, "blksize", buf->st_blksize);
	lstd_rawsetnumber(L, "blocks", buf->st_blocks);
}

/*
 *  {} or errno = fs.stat(pathname)
 */
static int lfs_stat(lua_State *L)
{
	struct stat statbuf;
	
	lstd_checknargs(L, 1);
	const char *s = luaL_checkstring(L, 1);
	int err = stat(s, &statbuf);
	if (err != -1) {
		push_stattot(L, &statbuf);
	} else {
		lua_pushnumber(L, errno);
	}
    return 1;
}

static int lfs_lstat(lua_State *L)
{
	struct stat statbuf;
	
	lstd_checknargs(L, 1);
	const char *s = luaL_checkstring(L, 1);
	int err = lstat(s, &statbuf);
	if (err != -1) {
		push_stattot(L, &statbuf);
	} else {
		lua_pushnil(L);
	}
    return 1;
}

/*
 * err = fs.access(path, mode)
 * @path path name 
 * @mode fs.R_OK fs.W_OK fs.X_OK fs.F_OK 
 */
static int lfs_access(lua_State *L)
{
	lstd_checknargs(L, 2);
	const char *s = luaL_checkstring(L, 1);
	int mode = luaL_checkint(L, 2);
	int err = access(s, mode);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}

/*
 * fs.umask(cmask)
 * @cmask fs.S_IRUSR | fs.S_IWUSR ...
 * return older mask 
 */
static int lfs_umask(lua_State *L)
{
	lstd_checknargs(L, 1);
	mode_t mask = luaL_checkint(L, 1);
	lua_pushnumber(L, umask(mask));
	return 1;
}

/*
 * err = fs.chmod(mode)
 */
static int lfs_chmod(lua_State *L)
{
	lstd_checknargs(L, 2);		
	const char *s = luaL_checkstring(L, 1);
	mode_t mode = luaL_checkint(L, 2);
	int err = chmod(s, mode);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}

/*
 * err = fs.chown(ptahname, owner, group)
 */
static int lfs_chown(lua_State *L)
{
	lstd_checknargs(L, 3);		
	const char *pathname = luaL_checkstring(L, 1);
	uid_t owner = luaL_checkint(L, 2);
	gid_t group = luaL_checkint(L, 3);
	int err = chown(pathname, owner, group);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}

/*
 * err = fs.lchown(pathname, owner, group)
 * change the symlink file own
 */
static int lfs_lchown(lua_State *L)
{
	lstd_checknargs(L, 3);		
	const char *pathname = luaL_checkstring(L, 1);
	uid_t owner = luaL_checkint(L, 2);
	gid_t group = luaL_checkint(L, 3);
	int err = lchown(pathname, owner, group);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}


/*
 * err = fs.truncate(pathname, length)
 */
static int lfs_truncate(lua_State *L)
{
	lstd_checknargs(L, 2);		
	const char *pathname = luaL_checkstring(L, 1);
	off_t len = luaL_checkint(L, 2);
	int err = truncate(pathname, len);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}

/* 
 * fs.link(existingpath, newpath)
 * return ture or false
 */
static int lfs_link(lua_State *L)
{
    lstd_checknargs(L, 2);
    const char *old = luaL_checkstring(L, 1);
    const char *new = luaL_checkstring(L, 2);
    int err = link(old, new);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/* 
 * err = fs.unlink(path)
 */
static int lfs_unlink(lua_State *L)
{
    lstd_checknargs(L, 1);
    const char *s = luaL_checkstring(L, 1);
    int err = unlink(s);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/* 
 * err = fs.remove(pathname)
 */
static int lfs_remove(lua_State *L)
{
    lstd_checknargs(L, 1);
    const char *s = luaL_checkstring(L, 1);
    int err = remove(s);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/* 
 * err = fs.rename(oldname, newname)
 */
static int lfs_rename(lua_State *L)
{
    lstd_checknargs(L, 2);
    const char *old = luaL_checkstring(L, 1);
    const char *new = luaL_checkstring(L, 2);
    int err = rename(old, new);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = fs.symlink(actualpath, sympath)
 */
static int lfs_symlink(lua_State *L)
{
	lstd_checknargs(L, 2);
    const char *actual = luaL_checkstring(L, 1);
    const char *sympath = luaL_checkstring(L, 2);
    int err = symlink(actual, sympath);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = fs.readlink(pathname)
 * return symlink filename on sucess, errno on err
 */
static int lfs_readlink(lua_State *L)
{
	char buf[CWD_SIZE];
	
	const char *pathname = luaL_checkstring(L, 1);
	if (readlink(pathname, buf, CWD_SIZE)) {
		lua_pushstring(L, buf);	
	} else {
		lua_pushnumber(L, errno);
	}
	return 1;
}

/*
 * err = fs.mkdir(pathname, mode)
 * return 0 on sucess, errno on err
 */
static int lfs_mkdir(lua_State *L)
{
    lstd_checknargs(L, 2);
    const char *pathname = luaL_checkstring(L, 1);
    mode_t mode = luaL_checkint(L, 2);
    int err = mkdir(pathname, mode);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = fs.rmdir(pathname)
 * return 0 on sucess, errno on err
 */
static int lfs_rmdir(lua_State *L)
{
    lstd_checknargs(L, 1);
    const char *pathname = luaL_checkstring(L, 1);
    int err = rmdir(pathname);
	lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * brief: set file modify time and access time
 * err = fs.utime(pathname, atime, mtime)
 * return 0 on sucess, errno on err
 */
static int lfs_utime(lua_State *L)
{
	struct utimbuf times;
	
	lstd_checknargs(L, 3);
    const char *pathname = luaL_checkstring(L, 1);
	times.actime = luaL_checkint(L, 2);
	times.modtime = luaL_checkint(L, 3);
    int err = utime(pathname, &times);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = fs.chdir(pathname)
 * return 0 on sucess, errno on err
 */
static int lfs_chdir(lua_State *L)
{
	lstd_checknargs(L, 1);
    const char *pathname = luaL_checkstring(L, 1);
    int err = chdir(pathname);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = fs.getcwd()
 * return 0 on sucess, errno on err
 */
static int lfs_getcwd(lua_State *L)
{
	char buf[CWD_SIZE];
	
    if (getcwd(buf, CWD_SIZE)) {
		lua_pushstring(L, buf);	
	} else {
		lua_pushnumber(L, errno);
	}
    return 1;
}

/*
 * err, dir = fs.dir(dirname)
 */
static int lfs_dir(lua_State *L)
{
	DIR *dp;
	
	lstd_checknargs(L, 1);
    const char *dirname = luaL_checkstring(L, 1);
	
	dp = opendir(dirname);
	if (!dp) {
		lua_pushnumber(L, errno);
		return 1;
	}
	
	lua_pushnumber(L, 0);
	int i = 1;
	struct dirent *entry;
	lua_newtable(L);
	while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 
                && strcmp(entry->d_name, "..") != 0) {
            lua_pushnumber(L, i++);
            lua_pushstring(L, entry->d_name);
            lua_rawset(L, -3);
        }
	}
	if (i == 1) {
		lua_pop(L, 1);
		lua_pushnil(L);
	}
	closedir(dp);
	return 2;
}

/*
 * err = fs.isfile(path)
 */
static int lfs_isfile(lua_State *L)
{
	struct stat statbuf;
	
	lstd_checknargs(L, 1);
    const char *path = luaL_checkstring(L, 1);
	int err = stat(path, &statbuf);
	if (err != -1) {
		lua_pushnumber(L, 0);
		lua_pushboolean(L, !0);
	} else {
		lua_pushnumber(L, errno);
		lua_pushboolean(L, S_ISDIR(statbuf.st_mode)? 0: !0);
	}
	return 2;
}

/*
 * err, stat = fs.isdir(path)
 */
static int lfs_isdir(lua_State *L)
{
	struct stat statbuf;
	
	lstd_checknargs(L, 1);
    const char *path = luaL_checkstring(L, 1);
	int err = stat(path, &statbuf);
	if (err != -1) {
		lua_pushnumber(L, 0);
		lua_pushboolean(L, !0);
	} else {
		lua_pushnumber(L, errno);
		lua_pushboolean(L, S_ISDIR(statbuf.st_mode)? !0: 0);
	}
	return 2;
}

/*
 * err, dir = fs.glob(pattern)
 * support sch brace expression lik "{foo{, cat, dog}, bar}"
 * then would return "foo/", "foo/cat/", "foo/dog", "bar"
 */
static int lfs_glob(lua_State *L)
{
	glob_t gb;
	uint32_t i = 0;
	
	lstd_checknargs(L, 1);
    const char *s = luaL_checkstring(L, 1);
	
	int res = glob(s, GLOB_BRACE | GLOB_TILDE, NULL, &gb);
	if (res == 0) {
		lua_pushnumber(L, 0);
		lua_newtable(L);
		for (i = 1; i <= gb.gl_pathc; i++) {
				lua_pushnumber(L, i);
				lua_pushstring(L, gb.gl_pathv[i]);
				lua_rawset(L, -3);
		}
		if (i == 1) {
			lua_pop(L, 1);
			lua_pushnil(L);
		}
	} else {
		lua_pushnumber(L, errno);
		lua_pushnil(L);
	}
	globfree(&gb);
	return 2;
}

static void lfs_const_register(lua_State *L)
{
	/* for acess */
	LENUMS(R_OK);
	LENUMS(W_OK);
	LENUMS(X_OK);
	LENUMS(F_OK);	/* file exist */
	
	/* for umask chmod .. */
	LENUMS(S_IRWXU);
	LENUMS(S_IRUSR);
	LENUMS(S_IWUSR);
	LENUMS(S_IXUSR);
	
	LENUMS(S_IRWXG);
	LENUMS(S_IRGRP);
	LENUMS(S_IWGRP);
	LENUMS(S_IXGRP);
	
	LENUMS(S_IRWXO);
	LENUMS(S_IROTH);
	LENUMS(S_IWOTH);
	LENUMS(S_IXOTH);
	
	LENUMS(S_ISUID);	/* set user-id on execution */
	LENUMS(S_ISGID);	/* set grop-id on execution */
	//LENUMS(S_ISVTX);	/* set sticky bit */
}

static const struct luaL_Reg fs_funcs[] = {
    {"stat",     lfs_stat},
    {"lstat",    lfs_lstat},
	{"access",   lfs_access},
	{"umask",    lfs_umask},
	{"chmod",    lfs_chmod},
	{"chown",    lfs_chown},
	{"lchown",   lfs_lchown},
	{"truncate", lfs_truncate},
    {"link",     lfs_link},
    {"unlink",   lfs_unlink},
    {"remove",   lfs_remove},
    {"rename",   lfs_rename},
    {"symlink",  lfs_symlink},
    {"readlink", lfs_readlink},
    {"mkdir",    lfs_mkdir},
    {"rmdir",    lfs_rmdir},
    {"utime",    lfs_utime},
    {"chdir",    lfs_chdir},
    {"getcwd",   lfs_getcwd},
	
	{"dir", 	 lfs_dir},
	{"isfile", 	 lfs_isfile},
	{"isdir", 	 lfs_isdir},
	{"glob", 	 lfs_glob},
    {NULL,       NULL},
};

int lstd_openfs(lua_State *L)
{
    luaL_register(L, "fs", fs_funcs);
	lfs_const_register(L);
    return 0;
}
