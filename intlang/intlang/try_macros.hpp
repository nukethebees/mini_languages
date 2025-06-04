#define TRY_ASSIGN(MAC_VAR_NAME, MAC_EXPR_TO_TEST)                   \
    auto MAC_VAR_NAME{MAC_EXPR_TO_TEST};                             \
    do {                                                             \
        if (!MAC_VAR_NAME) {                                         \
            return std::unexpected(std::move(MAC_VAR_NAME.error())); \
        }                                                            \
    } while (0)

// Only checking for errors
#define TRY(MAC_EXPR_TO_TEST)                                        \
    do {                                                             \
        auto MAC_ERR_NAME{MAC_EXPR_TO_TEST};                         \
        if (!MAC_ERR_NAME) {                                         \
            return std::unexpected(std::move(MAC_ERR_NAME.error())); \
        }                                                            \
    } while (0)
