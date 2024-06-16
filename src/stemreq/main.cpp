#include <iostream>
#include <curl/curl.h>
#include <cstring>

// Callback function to handle data received from the GET request body
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Callback function to handle data received from the GET request headers
size_t HeaderCallback(char* buffer, size_t size, size_t nitems, std::string* userp)
{
    userp->append(buffer, size * nitems);
    return size * nitems;
}

int main(int argc, char** argv)
{

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <flags>" << std::endl;
        return 1;
    }

    bool pHeader = false;
    bool pBody = false;

    if (std::strcmp(argv[2], "hb") == 0) {
        pHeader = true;
        pBody = true;
    } else if (std::strcmp(argv[2], "h") == 0) {
        pHeader = true;
    } else if (std::strcmp(argv[2], "b") == 0) {
        pBody = true;
    }

    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string headerBuffer;

    // Initialize libcurl
    std::cout << "HTTP REQUEST GENERATOR: STEM UTILITIES [Copyright 2024-present Raphtik@GHG]; USING CURL" << std::endl;
    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

        // Set the callback function to handle the response body
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the callback function to handle the response headers
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);

        // Perform the GET request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Print the headers
            std::cout << "Headers:\n" << headerBuffer << "\n\n";

            // Print the HTML body
            std::cout << "Body:\n" << readBuffer << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}
