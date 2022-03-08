#ifndef PRO_TOOL_SOFTWARE_RELEASE_H
#define PRO_TOOL_SOFTWARE_RELEASE_H

#include "../pro_sample.h"
#include <extcpp/archive>

namespace pro::tools
{

class software_release : public pro::dialog_sample
{
    using paths_type = std::vector<ext::fs::path>;

public:
    software_release(pro::global& global);


protected:
    /*
     * error
    */
    std::error_code error_;
    /*
     * form archive
    */
    ext::ui::form form_archive_;
    /*
     * closing
    */
    std::atomic_bool closing_ = false;
    /*
     * thread
    */
    std::thread archive_thread_;
    /*
     * files
    */
    std::uint64_t total_size_archive_ = 0;
    /*
     * finished
    */
    std::uint64_t finished_size_archive_ = 0;
    /*
     * archive progress
    */
    ext::ui::progress* archive_progress_ = nullptr;


protected:
    /*
     * mime
    */
    ext::text mime(const ext::fs::path& path);


protected:
    /*
     * is windows file
    */
    bool is_windows_file(const ext::fs::path& path);
    /*
     * is linux file
    */
    bool is_linux_file(const ext::fs::path& path);
    /*
     * is ignore
    */
    bool is_ignore(const ext::fs::path& path,const std::vector<std::regex>& rules);


protected:
    /*
     * on archive done
    */
    void on_archive_done(bool success);
    /*
     * on zip progress
    */
    void on_zip_progress(const ext::archive::file_info_t& info,int64_t position);


protected:
    /*
     * create archive
    */
    void create_archive();
    /*
     * create archive
    */
    bool create_archive(const ext::text& name,const ext::fs::path& dir,const ext::fs::path& output_dir,const std::vector<std::regex>& ignores);
    /*
     * write archive
    */
    bool write_archive(ext::archive::zip& zip,const ext::fs::path& dir,paths_type& directories,paths_type& paths,paths_type& paths_common);


protected:
    /*
     * init actions
    */
    void init_actions();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
