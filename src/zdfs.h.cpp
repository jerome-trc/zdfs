//! @file
//! @brief Implements the interface in zdfs.h.

#include "zdfs/zdfs.h"

#include "zdfs/filesystem.hpp"

zdfs_FileSys* zdfs_fs_new(void) {
	return (zdfs_FileSys*)new zdfs::FileSystem();
}

void zdfs_fs_free(const zdfs_FileSys* const fs) {
	delete (zdfs::FileSystem*)fs;
}
