"use strict";

((window) => {
    const { primordials, ops } = window.__bootstrap;
    const { ObjectAssign } = primordials;

    const { FileUtils } = window.__bindings.ax;

    ObjectAssign(ops, {
        op_require_read_file(filename) {
            return FileUtils.getInstance().getStringFromFile(filename);
        },
        op_require_real_path(path) {
            return FileUtils.getInstance().fullPathForFilename(path);
        },
        op_require_stat(path) {
            const futils = FileUtils.getInstance();
            const isFile = futils.isFileExist(path);
            if (isFile) {
                return 0;
            }

            const isDir = futils.isDirectoryExist(path);
            if (isDir) {
                return 1;
            }

            return -1;
        },
        op_require_cwd() {
            return FileUtils.getInstance().getDefaultResourceRootPath();
        }
    });
})(globalThis);
