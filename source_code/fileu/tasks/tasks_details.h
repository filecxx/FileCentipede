#ifndef PRO_TASKS_DETAILS_H
#define PRO_TASKS_DETAILS_H

#include "../pro_sample.h"

namespace pro::tasks
{

class details
{
    friend class main;

    using mapped_items_t     = std::unordered_map<ext::text,ext::ui::standard_item*>;
    using mapped_int_items_t = std::unordered_map<std::uint32_t,ext::ui::standard_item*>;

    struct details_t
    {
        ext::ui::sample*    sample    = nullptr;
        ext::ui::detailbar* detailbar = nullptr;
        ext::ui::form       form;
    };


public:
    details(pro::global& global);


public:
    ~details();


protected:
    /*
     * global
    */
    pro::global& zzz;


protected:
    /*
     * type
    */
    std::uint16_t type_ = protocol::Task_Types_Size;
    /*
     * id
    */
    std::int64_t id_ = 0;
    /*
     * timepoint query
    */
    ext::steady_time_t timepoint_query_;
    /*
     * detail subset
    */
    ext::text_view subset_;
    /*
     * tasks splitter
    */
    ext::ui::splitter* tasks_splitter_ = nullptr;
    /*
     * detailbars
    */
    ext::ui::widget* detailbars_ = nullptr;
    /*
     * current
    */
    details_t* current_ = nullptr;
    /*
     * details
    */
    std::array<details_t,protocol::Task_Types_Size> details_ = {};
    /*
     * sizes
    */
    QList<int> sizes_;


protected:
    /*
     * mapped trackers (url -> item)
    */
    mapped_items_t mapped_trackers_temp_;
    /*
     * mapped web seeds (url -> item)
    */
    mapped_items_t mapped_web_seeds_temp_;
    /*
     * mapped peers (url -> item)
    */
    mapped_items_t mapped_peers_temp_;
    /*
     * mapped trackers (text -> item)
    */
    mapped_items_t mapped_trackers_;
    /*
     * mapped web seeds (url -> item)
    */
    mapped_items_t mapped_web_seeds_;
    /*
     * mapped peers (ip:port -> item)
    */
    mapped_items_t mapped_peers_;


protected:
    /*
     * type to filename
    */
    ext::text type_to_filename(uint16_t type);


protected:
    /*
     * init details
    */
    void init_details(ext::ui::splitter* splitter,ext::ui::widget* detailbars);
    /*
     * init detailbar
    */
    void init_detailbar(ext::ui::detailbar*,std::uint16_t type);
    /*
     * init torrent tracker actions
    */
    void init_torrent_tracker_actions(ext::ui::model& ui);
    /*
     * init torrent peers actions
    */
    void init_torrent_peers_actions(ext::ui::model& ui);
    /*
     * init torrent web seeds actions
    */
    void init_torrent_web_seeds_actions(ext::ui::model& ui);
    /*
     * init torrent details
    */
    void init_torrent_details();


protected:
    /*
     * clear mapped
    */
    void clear_mapped(ext::ui::table* table,mapped_items_t& mapped,mapped_items_t& mapped_temp);
    /*
     * update trackers
    */
    void update_trackers(ext::ui::table* table,ext::value&& values,bool clear);
    /*
     * update web seeds
    */
    void update_web_seeds(ext::ui::table* table,ext::value&& values,bool clear);
    /*
     * update peers
    */
    void update_peers(ext::ui::table* table,ext::value&& values,bool clear);


public:
    /*
     * expanded
    */
    bool expanded() const
    {
        return current_ && current_->detailbar && current_->detailbar->expanded();
    }


public:
    /*
     * query detail
    */
    void query_detail(bool try_status = false,bool immediately = false);


public:
    /*
     * minimize
    */
    void minimize();
    /*
     * display
    */
    void display(uint16_t type,int64_t id,ext::value& values);
    /*
     * hide
    */
    void hide();
    /*
     * update
    */
    void update(uint16_t type,ext::value& values,bool clear = false);


};

}


#endif
