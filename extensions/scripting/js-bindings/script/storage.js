const {
    op_get_session_storage,
    op_create_local_storage,
} = require("internal/ops");

Object.assign(window, {
    sys: {
        sessionStorage: op_get_session_storage(),
        localStorage: op_create_local_storage("jsb"),
    },
});
