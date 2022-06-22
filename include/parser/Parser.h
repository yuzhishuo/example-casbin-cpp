//
// Created by yuzhi on 5/19/22.
//

#ifndef LEDGERDB_PARSER_H
#define LEDGERDB_PARSER_H

#include <stdio.h>
#include <stdlib.h> // for malloc, exit
#include <string.h> // for std::string
#include <memory> // for std::shared_ptr
#include <parser/GrammarCommandFactory.h>

#include <utility/VaStack.h>
#include <config/IConfigurable.hpp> // for interface IConfigurable
#include <config/Config.h>

namespace yuzhi::grammar {

    class Parser : public IConfigurable {
    public:
        static std::shared_ptr<Parser> Instance()
        {
            static std::shared_ptr<Parser> parser = std::make_shared<Parser>();
            return parser;
        }
    public:
        Parser();
        ~Parser();
    public:
        void handle(const std::string& type, utility::VaStack& vaStack)
        {
            spdlog::info("parser::handle type is {}", type);

            auto& config = Config::Instance();
            auto cli_config = config.get<std::string>(this, "cli");
            GrammarCommandFactory::Instance().get(type)(vaStack);
        }

    public:
        const char *Field() const override;
        Parser& load(std::string_view view);
        int handle(const std::string& sentence);
        int yy () const;
    private:
        FILE* fp_;
    };

} // namespace yuzhi::parser

#endif // LEDGERDB_PARSER_H
