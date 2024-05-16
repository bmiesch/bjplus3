#ifndef LLMCLIENT_H
#define LLMCLIENT_H

#include <string>

class LLMClient {
public:
    virtual ~LLMClient() {}
    virtual std::string getDecision(const std::string& gameState) = 0;
};

#endif // LLMCLIENT_H

