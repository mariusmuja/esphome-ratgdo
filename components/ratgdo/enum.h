

#define PARENS ()

// Rescan macro tokens 256 times
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, type, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, type, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, type, a1, ...) \
    macro(type, a1)                           \
        __VA_OPT__(FOR_EACH_AGAIN PARENS(macro, type, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define ENUM_VARIANT0(name, val) name = val,
#define ENUM_VARIANT(type, tuple) ENUM_VARIANT0 tuple

#define TUPLE(x, y) x, y

#define LPAREN (

#define TO_STRING_CASE0(type, name, val) \
    case type::name:                     \
        return #name;
#define TO_STRING_CASE(type, tuple) TO_STRING_CASE0 LPAREN type, TUPLE tuple)

#define FROM_INT_CASE0(type, name, val) \
    case val:                           \
        return type::name;
#define FROM_INT_CASE(type, tuple) FROM_INT_CASE0 LPAREN type, TUPLE tuple)

#define ENUM(name, type, ...)                           \
    enum class name : type {                            \
        FOR_EACH(ENUM_VARIANT, name, __VA_ARGS__)       \
    };                                                  \
    constexpr inline const char*                        \
        name##_to_string(name _e)                       \
    {                                                   \
        switch (_e) {                                   \
            FOR_EACH(TO_STRING_CASE, name, __VA_ARGS__) \
        default:                                        \
            return "UNKNOWN";                           \
        }                                               \
    }                                                   \
    constexpr inline name                               \
        to_##name(type _t, name _missing)               \
    {                                                   \
        switch (_t) {                                   \
            FOR_EACH(FROM_INT_CASE, name, __VA_ARGS__)  \
        default:                                        \
            return _missing;                            \
        }                                               \
    }
