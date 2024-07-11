//! @file
//! @brief Implements the interface in zdfs.h.

#include "zdfs/zdfs.h"

#include "zdfs/filesystem.hpp"
#include "zdfs/resourcefile.hpp"

static_assert(
	sizeof(int) == sizeof(int32_t), "ZDFS is untested on platforms where `int` is not 32 bits"
);
static_assert(
	sizeof(unsigned) == sizeof(uint32_t),
	"ZDFS is untested on platforms where `unsigned` is not 32 bits"
);

zdfs_FileSys* zdfs_fs_new(zdfs_MsgFunc msg_cb) {
	auto m = reinterpret_cast<zdfs::FileSystemMessageFunc>(msg_cb);
	return (zdfs_FileSys*)new zdfs::FileSystem(m);
}

void zdfs_fs_free(const zdfs_FileSys* const fs) {
	delete (zdfs::FileSystem*)fs;
}
