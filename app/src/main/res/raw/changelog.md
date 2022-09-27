# alpha更新日志

## Magisk (c97d1044-alpha)
- [App] 还原boot镜像后删除备份文件
- [App] 内置当前版本更新日志
- [General] 不再自动解锁设备块
- [App] 允许加载zygisk模块
- [General] 更新到官方NDK 25，移除rust


# 上游更新日志

## Magisk (f42c089b) (25102)

- [MagiskInit] Fix a potential issue when stub cpio is used
- [MagiskInit] Fix reboot to recovery when stub cpio is used
- [General] Better data encryption detection
- [General] Move the whole logging infrastructure into Rust

## Diffs to v25.1

- [MagiskInit] Fix a potential issue when stub cpio is used
- [MagiskInit] Fix reboot to recovery when stub cpio is used
- [General] Better data encryption detection
- [General] Move the whole logging infrastructure into Rust
