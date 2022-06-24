#ifndef PRO_FILE_BROWSER_ALERT_H
#define PRO_FILE_BROWSER_ALERT_H

#include "../pro_global.h"

namespace pro::file_browser
{

struct operation_t
{
    std::uint16_t method;
    std::uint16_t state;
    std::uint16_t state2;
    std::uint16_t state3;
    std::int64_t  time_start;
    ext::text     path_remote;
    ext::text     path_local;
    ext::value    parameter;
};

enum alert_types : uint16_t
{
    Alert_Operation_Add,
    Alert_Operation_State,
    Alert_Operation_Error,
    Alert_Operation_Done,

    Alert_Operations_Clear
};

struct alert_type
{
    uint16_t type;
};

struct alert_operation_type : alert_type
{
    int64_t hid;
    int64_t sid;
};

struct alert_operation_error_type : alert_operation_type
{
    int64_t oid;
};

struct alert_operation_done_type : alert_operation_type
{
    int64_t  oid;
    uint16_t state;
};

struct alert_operation_state_type : alert_operation_type
{
    int64_t  oid;
    uint16_t state;
    uint16_t state2;
    uint16_t state3;
};

struct alert_operation_add_type : alert_operation_type
{
    int64_t      oid;
    operation_t& operation;
};

struct alert_operations_clear_type : alert_operation_type
{

};

}
#endif
