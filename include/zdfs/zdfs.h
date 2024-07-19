//! @file
//! @brief C99 API for the ZDFS library.

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if __STDC_VERSION__ >= 202000L || (defined(__cplusplus) && __cplusplus >= 201703L)
#define ZDFS_NODISCARD [[nodiscard]]
#else
#define ZDFS_NODISCARD
#endif

typedef int32_t zdfs_WadNum;
typedef int32_t zdfs_LumpNum;
typedef uint32_t zdfs_ULumpNum;

enum {
	zdfs_msglevel_error = 1,
	zdfs_msglevel_warning = 2,
	zdfs_msglevel_attention = 3,
	zdfs_msglevel_message = 4,
	zdfs_msglevel_debugwarn = 5,
	zdfs_msglevel_debugnotify = 6,
}; typedef int zdfs_MessageLevel;

/// @see zdfs_fs_new
typedef struct zdfs_FileSys zdfs_FileSys;
typedef struct zdfs_StringVector zdfs_StringVector;

typedef union zdfs_ShortName {
	char string[9];
	/// For accessing the first 4 or 8 chars of `string` as a unit
	/// without breaking strict aliasing rules.
	uint32_t dword;
	/// For accessing the first 4 or 8 chars of `string` as a unit
	/// without breaking strict aliasing rules.
	uint64_t qword;
} zdfs_ShortName;

typedef struct zdfs_FolderEntry {
	const char* name;
	zdfs_ULumpNum num;
} zdfs_FolderEntry;

typedef int32_t(*zdfs_MsgFunc)(zdfs_MessageLevel, const char* fmt, ...);

void zdfs_set_main_thread(void);

/// @brief Destroys a filesystem instance.
void zdfs_fs_free(const zdfs_FileSys*);

/// @returns A pointer to an empty filesystem instance allocated on the heap.
ZDFS_NODISCARD zdfs_FileSys* zdfs_fs_new(zdfs_MsgFunc);

bool zdfs_fs_mount(zdfs_FileSys*, const char* path);

/// This consumes `paths`; the caller should not access or free it afterwards,
/// regardless of whether this returns `true` (success) or `false` (failure).
bool zdfs_fs_mount_multi(
	zdfs_FileSys*,
	zdfs_StringVector* paths,
	bool allow_duplicates
);

zdfs_StringVector* zdfs_strvec_new(size_t capacity);
void zdfs_strvec_push(zdfs_StringVector*, const char*);
void zdfs_strvec_free(zdfs_StringVector*);

#if defined(__cplusplus)
}
#endif
