#ifndef PRO_TOOL_CHECKSUM_H
#define PRO_TOOL_CHECKSUM_H

#include "../pro_sample.h"

namespace pro::tools
{

class checksum : public pro::dialog_sample<pro::global>
{
public:
    checksum(pro::global& global);


public:
    ~checksum();


protected:
    /*
     * state
    */
    std::atomic_uint16_t state_ = ext::state::Stopped;
    /*
     * refcount
    */
    std::atomic_uint32_t refcount_ = 0;
    /*
     * total size
    */
    std::atomic_size_t total_size_ = 0;
    /*
     * form text
    */
    ext::ui::form form_text_;
    /*
     * form file
    */
    ext::ui::form form_file_;
    /*
     * button start
    */
    ext::ui::button* button_start_;
    /*
     * button stop
    */
    ext::ui::button* button_stop_;
    /*
     * button save
    */
    ext::ui::button* button_save_;
    /*
     * file path
    */
    ext::ui::line_edit* file_path_;
    /*
     * thread
    */
    std::array<std::jthread,4> threads_;
    /*
     * temp key
    */
    ext::text temp_key_;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * post file result
    */
    void post_file_result(const ext::text& name,const std::string& result);
    /*
     * post file progress
    */
    void post_file_progress(const ext::text& name,size_t file_size,size_t offset,size_t size);
    /*
     * calc text
    */
    void calc_text(ext::text_view text);
    /*
     * calc file
    */
    void calc_file(const ext::fs::path& path);


public:
    /*
     * stopping
    */
    bool stopping() const
    {
        return state_ != ext::state::Running;
    }


public:
    /*
     * start
    */
    void start();
    /*
     * stop
    */
    void stop();
    /*
     * join
    */
    void join();
    /*
     * save
    */
    void save();
    /*
     * exec
    */
    void exec(const ext::text& path = {});
    /*
     * exec
    */
    void exec(int argc,char** argv);

};

}


#endif
