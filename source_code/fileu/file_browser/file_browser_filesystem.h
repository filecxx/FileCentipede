#ifndef PRO_FILE_BROWSER_FILESYSTEM_H
#define PRO_FILE_BROWSER_FILESYSTEM_H

#include "../dialogs/dialog_ask_pass.h"
#include "file_browser_alert.h"
#include "file_browser_super_cache.h"
#include "file_browser_clone.h"

namespace pro::file_browser
{

class hosts;
class filesystem : public std::enable_shared_from_this<filesystem>,public pro::sample<pro::file_browser::global>
{
    friend class main;
    friend class filesystems;
    friend class tasks;

    struct copy_item_type
    {
        ext::fs::file_type file_type;
        ext::value         values;
    };


public:
    filesystem(pro::file_browser::global& global,pro::file_browser::hosts* hosts,ext::ui::tab* tabs,ext::ui::statusbar* statusbar);


public:
    ~filesystem();


protected:
    /*
     * host id
    */
    std::int64_t hid_ = 0;
    /*
     * session id
    */
    std::int64_t sid_ = 0;
    /*
     * session type
    */
    std::uint16_t type_ = 0;
    /*
     * port
    */
    std::uint16_t port_ = 0;
    /*
     * protocol
    */
    ext::text protocol_ = "";
    /*
     * host
    */
    ext::text host_ = "";
    /*
     * current path
    */
    ext::text path_ = "";


protected:
    /*
     * oid (increased)
    */
    std::int64_t oid_ = 0;
    /*
     * operations
    */
    std::unordered_map<int64_t,operation_t> operations_;
    /*
     * history
    */
    std::deque<std::pair<int64_t,operation_t>> history_;
    /*
     * cuts
    */
    std::unordered_map<ext::text,copy_item_type> cuts_;
    /*
     * copies
    */
    std::unordered_map<ext::text,copy_item_type> copies_;
    /*
     * pasting
    */
    std::unordered_map<std::int64_t,copy_item_type> pasting_;


protected:
    /*
     * timer loading
    */
    std::int64_t timer_loading_ = 0;
    /*
     * directories count
    */
    std::uint32_t directories_count_ = 0;
    /*
     * files count
    */
    std::uint32_t files_count_ = 0;


protected:
    /*
     * hosts
    */
    pro::file_browser::hosts* hosts_ = nullptr;
    /*
     * tab
    */
    ext::ui::tab* tabs_ = nullptr;
    /*
     * statusbar
    */
    ext::ui::statusbar* statusbar_ = nullptr;
    /*
     * nfs protocols
    */
    ext::ui::combobox* protocols_ = nullptr;
    /*
     * addresses
    */
    ext::ui::addressbar* addresses_ = nullptr;
    /*
     * grid
    */
    ext::ui::filesystem* grid_ = nullptr;
    /*
     * widget
    */
    ext::ui::widget* widget_ = nullptr;
    /*
     * loading
    */
    ext::ui::widget* loading_ = nullptr;
    /*
     * loading img
    */
    ext::ui::img* loading_img_ = nullptr;
    /*
     * filter rule
    */
    ext::ui::combobox* filter_rule_ = nullptr;
    /*
     * filter types
    */
    ext::ui::combobox* filter_types_ = nullptr;
    /*
     * filter text
    */
    ext::ui::line_edit* filter_text_ = nullptr;


protected:
    /*
     * filter value rule regex
    */
    std::vector<std::regex> filter_value_rule_regex_;
    /*
     * filter value text
    */
    ext::text filter_value_text_;
    /*
     * filter types
    */
    std::uint16_t filter_value_type_;
    /*
     * filter enabled
    */
    ext::boolean_t filter_enabled_ = false;


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init view
    */
    void init_view();
    /*
     * init addresses
    */
    void init_addresses();
    /*
     * init shortcut
    */
    void init_shortcut();
    /*
     * init filters
    */
    void init_filters();
    /*
     * init grid
    */
    void init_grid();
    /*
     * init
    */
    void init(std::int64_t id,std::int64_t sid,std::int64_t tid,std::uint16_t type);


protected:
    /*
     * on address change
    */
    bool on_address_change(const ext::uri::address& address);
    /*
     * on context menu
    */
    void on_context_menu();
    /*
     * on double click
    */
    void on_double_click();
    /*
     * on filter
    */
    void on_filter();


protected:
    /*
     * on status
    */
    void on_status(std::uint16_t state,std::int64_t oid,ext::value& values);
    /*
     * on done
    */
    void on_done(std::int64_t oid,operation_t& operation,ext::value& values);
    /*
     * on ask pass
    */
    void on_ask_pass(ext::value& values);
    /*
     * on file
    */
    void on_file(ext::value& values);
    /*
     * on list
    */
    void on_list(ext::value& values);
    /*
     * on rename
    */
    void on_rename(ext::value& values);
    /*
     * on move
    */
    void on_move(std::int64_t oid,ext::value& values);
    /*
     * on copy
    */
    void on_copy(std::int64_t oid,ext::value& values);
    /*
     * on remove
    */
    void on_remove(ext::value& values);
    /*
     * on attribute
    */
    void on_attribute(ext::value& values);
    /*
     * on chmod
    */
    void on_chmod(ext::value& values);
    /*
     * on create file
    */
    void on_create_file(ext::value& values);
    /*
     * on create dir
    */
    void on_create_dir(ext::value& values);
    /*
     * on upload
    */
    void on_upload(operation_t& operation,ext::value& values);
    /*
     * on download
    */
    void on_download(operation_t& operation,ext::value& values);


protected:
    /*
     * view icon
    */
    void view_icon();
    /*
     * view grid
    */
    void view_grid();


protected:
    /*
     * show loading
    */
    void show_loading();
    /*
     * hide loading
    */
    void hide_loading();
    /*
     * clear files
    */
    void clear_files();
    /*
     * erase operation
    */
    void erase_operation(decltype(operations_)::iterator& iter);
    /*
     * erase clipboard (not system clipboard)
    */
    void erase_clipboard(const ext::text& path,ext::fs::file_type type);
    /*
     * matches filter
    */
    bool matches_filter(ext::fs::file_type file_type,ext::text_view text);


protected:
    /*
     * update actions
    */
    void update_actions();
    /*
     * update protocol
    */
    void update_protocol(ext::text_view protocol);
    /*
     * update statusbar
    */
    void update_statusbar();
    /*
     * update path
    */
    void update_path(const ext::text& path);
    /*
     * update title
    */
    void update_title(ext::text_view title);
    /*
     * update files
    */
    void update_files(ext::value& files);
    /*
     * update file
    */
    auto update_file(ext::value& file) -> ext::ui::filesystem::node_type*;
    /*
     * send operation
    */
    auto send_operation(std::uint16_t method,const ext::json::list_t& list = {},const ext::text& path_remote = {},const ext::text& path_local = {},const ext::value& parameter = "") -> int64_t;


public:
    /*
     * clipboard empty
    */
    bool clipboard_empty();


public:
    /*
     * make address
    */
    ext::text make_address(const ext::text& path);
    /*
     * make path
    */
    ext::text make_path(ext::text_view name,bool trailing_separator = false);


public:
    /*
     * refresh
    */
    void refresh();
    /*
     * upload
    */
    void upload(bool directory);
    /*
     * upload
    */
    void upload(ext::text_view text);
    /*
     * download
    */
    void download();
    /*
     * remove
    */
    void remove();
    /*
     * create directory
    */
    void create_directory();
    /*
     * create file
    */
    void create_file();
    /*
     * open
    */
    void open(std::uint16_t operation = ext::fs::Open);
    /*
     * open new tab
    */
    void open_new_tab();
    /*
     * rename
    */
    void rename();
    /*
     * move
    */
    void move();
    /*
     * move
    */
    auto move(const ext::text& from,const ext::text& to,ext::fs::file_type type) -> int64_t;
    /*
     * copy
    */
    auto copy(const ext::text& from,const ext::text& to,ext::fs::file_type type) -> int64_t;
    /*
     * copy path
    */
    void copy_path(bool cut);
    /*
     * paste
    */
    void paste();
    /*
     * attribute
    */
    void attribute();
    /*
     * search
    */
    void search();
    /*
     * super_cache
    */
    void super_cache();
    /*
     * clone
    */
    void clone();
    /*
     * list
    */
    void list(ext::text_view path);


};

}



#endif
