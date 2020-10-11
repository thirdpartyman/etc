#pragma once

#include <stdio.h>
#include <curl/curl.h>
/* For older cURL versions you will also need
#include <curl/types.h>
#include <curl/easy.h>
*/
#include <string>
#include "EventHandler.hpp"
#include "progress.hpp"
#include <filesystem>
namespace fs = std::filesystem;

namespace curl
{
    class downloader
    {
        static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
            size_t written = fwrite(ptr, size, nmemb, stream);
            return written;
        }

        static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
        {
            auto data = static_cast<downloader::data*>(ptr);
            data->onload(data->url, data->filename, progress{ .all = TotalToDownload, .done = NowDownloaded });
            return 0;
        }

    public:     
        EventHandler<downloader, const std::string&, const fs::path&, const progress&> onload;
    private:
        struct data
        {
            const std::string& url;
            const fs::path& filename;
            std::add_lvalue_reference<decltype(downloader::onload)>::type onload;
        };
    public:
        void operator()(const std::string& url, const fs::path& filename) {
            CURL* curl;
            FILE* fp;
            CURLcode res;
#define url url.data()
#define outfilename filename.string().data()
            curl = curl_easy_init();
            if (curl) {
                fp = fopen(outfilename, "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

                // Internal CURL progressmeter must be disabled if we provide our own callback
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
                // Install the callback function
                curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);

                #undef url
                #undef outfilename
                auto data = downloader::data{ url, filename, onload };
                curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &data);

                res = curl_easy_perform(curl);

                curl_easy_cleanup(curl);
                fclose(fp);
            }
        }
    };
}
