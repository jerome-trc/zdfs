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
	return reinterpret_cast<zdfs_FileSys*>(new zdfs::FileSystem(m));
}

void zdfs_fs_free(const zdfs_FileSys* const fs) {
	delete reinterpret_cast<const zdfs::FileSystem*>(fs);
}

bool zdfs_fs_mount(zdfs_FileSys* fs_c, const char* path) {
	auto fs = reinterpret_cast<zdfs::FileSystem*>(fs_c);
	return fs->init_single_file(path);
}

bool zdfs_fs_mount_multi(
	zdfs_FileSys* fs_c,
	zdfs_StringVector* vec_c,
	bool allow_duplicates
) {
	auto fs = reinterpret_cast<zdfs::FileSystem*>(fs_c);
	auto vec = reinterpret_cast<std::vector<std::string>*>(vec_c);
	return fs->init_multiple_files(*vec);
}

zdfs_StringVector* zdfs_strvec_new(size_t capacity) {
	return reinterpret_cast<zdfs_StringVector*>(new std::vector<std::string>());
}

void zdfs_strvec_push(zdfs_StringVector* vec_c, const char* str) {
	auto vec = reinterpret_cast<std::vector<std::string>*>(vec_c);
	vec->emplace_back(str);
}

void zdfs_strvec_free(zdfs_StringVector* v) {
	delete reinterpret_cast<std::vector<std::string>*>(v);
}
