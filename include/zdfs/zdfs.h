//! @file
//! @brief C99 API for the ZDFS library.

#pragma once

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

/// @see zdfs_fs_new
typedef struct zdfs_FileSys zdfs_FileSys;

/// @brief Destroys a filesystem instance.
void zdfs_fs_free(const zdfs_FileSys* const);

/// @returns A pointer to an empty filesystem instance allocated on the heap.
ZDFS_NODISCARD zdfs_FileSys* zdfs_fs_new(void);

#if defined(__cplusplus)
}
#endif
