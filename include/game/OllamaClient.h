#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include "LLMClient.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class OllamaClient : public LLMClient {
public:
    OllamaClient() {}

    ~OllamaClient() override = default;
    
    std::string getDecision(const std::string& prompt) override {
        CURL* curl = curl_easy_init();
        if (curl) {
            std::string response;
            std::string jsonData = "{\"model\": \"" + model + "\", \"prompt\": \"" + prompt + "\", \"stream\": false}";

            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, serverURL.c_str());
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);

            nlohmann::json jsonResponse;
            try {
                jsonResponse = nlohmann::json::parse(response);
                return jsonResponse["response"].get<std::string>();
            } catch (const nlohmann::json::parse_error& e) {
                return "Failed to parse response: " + std::string(e.what());
            }
        }
        return "";
    }

private:
    std::string serverURL = "http://localhost:11434/api/generate";
    std::string model = "phi3";

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};


#endif // OLLAMACLIENT_H