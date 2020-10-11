#pragma once

#include <curl/curl.h>
/* For older cURL versions you will also need
#include <curl/types.h>
#include <curl/easy.h>
*/
#include <string>


namespace curl {
    size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        return size * nmemb;
    }

    auto get_file_size(const std::string& url)
    {
        curl_off_t cl;

        CURL* curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.data());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            //Set CURLOPT_FOLLOWLOCATION to TRUE so that our
            //cURL request follows any redirects.
            //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

            //Set CURLOPT_HEADER to TRUE so that cURL returns
            //the header information.
            curl_easy_setopt(curl, CURLOPT_HEADER, true);

            //Set CURLOPT_NOBODY to TRUE to send a HEAD request.
            //This stops cURL from downloading the entire body
            //of the content.
            curl_easy_setopt(curl, CURLOPT_NOBODY, true);

            res = curl_easy_perform(curl);

            //Retrieve the size of the remote file in bytes.

            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &cl);

            /* always cleanup */
            curl_easy_cleanup(curl);
        }

        return cl;
    }
}