#ifndef PRO_TOOL_FILEC_LINK_H
#define PRO_TOOL_FILEC_LINK_H

#include "../pro_sample.h"

namespace pro::tools
{

class create_address : public pro::dialog_sample
{
public:
    create_address(pro::global& global);


public:
    ~create_address();


protected:
    /*
     * timer
    */
    std::int64_t timer_ = 0;
    /*
     * type
    */
    std::uint16_t type_ = protocol::Task_Types_Size;
    /*
     * form config
    */
    ext::ui::form form_config_;
    /*
     * tab
    */
    ext::ui::tab* tab_ = nullptr;
    /*
     * addresses
    */
    ext::ui::text_edit* addresses_ = nullptr;
    /*
     * dialog result
    */
    ext::ui::dialog* dialog_result_ = nullptr;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * analyze addresses
    */
    void analyze_addresses();
    /*
     * create
    */
    void create();


public:
    /*
     * exec
    */
    void exec();


};

}



#endif
