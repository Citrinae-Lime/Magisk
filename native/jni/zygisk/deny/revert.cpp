#include <sys/mount.h>

#include <magisk.hpp>
#include <base.hpp>

#include "deny.hpp"

using namespace std;

static void lazy_unmount(const char* mountpoint) {
    if (umount2(mountpoint, MNT_DETACH) != -1)
        LOGD("denylist: Unmounted (%s)\n", mountpoint);
}

void revert_daemon(int pid) {
    if (fork_dont_care() == 0) {
        revert_unmount(pid);
        // Send resume signal
        kill(pid, SIGCONT);
        _exit(0);
    }
}

#define TMPFS_MNT(dir) (mentry->mnt_type == "tmpfs"sv && str_starts(mentry->mnt_dir, "/" #dir))

void revert_unmount(int pid) {
    if (pid > 0) {
        if (switch_mnt_ns(pid))
            return;
        LOGD("denylist: handling PID=[%d]\n", pid);
    }

    vector<string> targets;

    // Unmount dummy skeletons and MAGISKTMP
    targets.push_back(MAGISKTMP);
    parse_mnt("/proc/self/mounts", [&](mntent *mentry) {
        if (TMPFS_MNT(system) || TMPFS_MNT(vendor) || TMPFS_MNT(product) || TMPFS_MNT(system_ext))
            targets.emplace_back(mentry->mnt_dir);
        return true;
    });

    for (auto &s : reversed(targets))
        lazy_unmount(s.data());
    targets.clear();

    // Unmount all Magisk created mounts
    parse_mnt("/proc/self/mounts", [&](mntent *mentry) {
        if (str_contains(mentry->mnt_fsname, BLOCKDIR))
            targets.emplace_back(mentry->mnt_dir);
        return true;
    });

    for (auto &s : reversed(targets))
        lazy_unmount(s.data());
}
