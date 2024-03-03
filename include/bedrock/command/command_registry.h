// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "bedrock/bedrock.h"
#include "bedrock/command/command_origin.h"
#include "bedrock/command/command_version.h"
#include "bedrock/type_id.h"

struct CommandFlag {
    uint16_t value;
};

enum class CommandPermissionLevel : std::uint8_t {
    Any = 0,
    GameDirectors = 1,
    Admin = 2,
    Host = 3,
    Owner = 4,
    Internal = 5
};

class Command;
class CommandParameterData;

class CommandRegistry {
public:
    struct Overload {
        Overload(const CommandVersion &version, std::unique_ptr<Command> (*factory)())
            : version(version), factory(factory)
        {
        }

        CommandVersion version;                    // +0
        std::unique_ptr<Command> (*factory)();     // +8
        std::vector<CommandParameterData> params;  // +16
        uint8_t unknown1 = 0;                      // +40
        uint16_t unknown2 = -1;
        uint64_t unknown3 = 0;
        uint64_t unknown4 = 0;
        uint64_t unknown5 = 0;
    };

    struct Symbol {
        int value = -1;
    };

    struct Signature {
        std::string name;                                  // +0
        std::string description;                           // +32
        std::vector<CommandRegistry::Overload> overloads;  // +64
        char pad1[24];                                     // +88
        CommandPermissionLevel permission_level;           // +112
        CommandRegistry::Symbol symbol;                    // +116
        int32_t unknown2;                                  // +120
        CommandFlag command_flag;                          // +124
        int32_t unknown3;                                  // +128
        int32_t unknown4;                                  // +132
        int32_t unknown5;                                  // +136
        char unknown6;                                     // +140
        int64_t unknown7;                                  // +144
    };

    struct ParseToken {
        std::unique_ptr<ParseToken> child;  // +0
        std::unique_ptr<ParseToken> next;   // +8
        ParseToken *parent;                 // +16
        char const *data;                   // +24
        uint32_t size;                      // +32
        Symbol symbol;                      // +36

        friend std::ostream &operator<<(std::ostream &os, const ParseToken &token);
    };
    static_assert(sizeof(CommandRegistry::ParseToken) == 40);

    using ParseRule = bool (CommandRegistry::*)(void *, const CommandRegistry::ParseToken &, const CommandOrigin &, int,
                                                std::string &, std::vector<std::string> &);

    template <typename CommandType>
    static std::unique_ptr<Command> allocateCommand()
    {
        return std::move(std::make_unique<CommandType>());
    }

    template <typename CommandType, typename... Params>
    const CommandRegistry::Overload *registerOverload(const char *name, CommandVersion version, const Params &...params)
    {
        // TODO: can we get rid of const_cast?
        auto *signature = const_cast<CommandRegistry::Signature *>(findCommand(name));

        if (!signature) {
            return nullptr;
        }

        auto overload = CommandRegistry::Overload(version, CommandRegistry::allocateCommand<CommandType>);
        overload.params = {params...};

        signature->overloads.push_back(overload);
        registerOverloadInternal(*signature, overload);
        return &signature->overloads.back();
    }

    BEDROCK_API void registerCommand(const std::string &name, char const *description, CommandPermissionLevel level,
                                     CommandFlag flag1, CommandFlag flag2);

private:
    [[nodiscard]] BEDROCK_API const CommandRegistry::Signature *findCommand(const std::string &name) const;
    [[nodiscard]] BEDROCK_API std::unique_ptr<Command> CommandRegistry::createCommand(
        const CommandRegistry::ParseToken &parse_token, const CommandOrigin &origin, int version,
        std::string &error_message, std::vector<std::string> &error_params) const;
    [[nodiscard]] BEDROCK_API std::string describe(CommandParameterData const &) const;
    BEDROCK_API void registerOverloadInternal(CommandRegistry::Signature &signature,
                                              CommandRegistry::Overload &overload);
};

enum CommandParameterDataType : int;
enum CommandParameterOption : char;

struct CommandParameterData {

    CommandParameterData(const Bedrock::typeid_t<CommandRegistry> &type_id, CommandRegistry::ParseRule parse_rule,
                         const char *name, CommandParameterDataType type, const char *enum_name,
                         const char *postfix_name, int offset_value, bool optional, int offset_has_value)
        : type_id(type_id), parse_rule(parse_rule), name(name), type(type), enum_name(enum_name),
          postfix_name(postfix_name), offset_value(offset_value), optional(optional), offset_has_value(offset_has_value)
    {
    }

    Bedrock::typeid_t<CommandRegistry> type_id;  // +0
    CommandRegistry::ParseRule parse_rule;       // +8
    std::string name;                            // +16
    const char *enum_name;                       // +48
    CommandRegistry::Symbol enum_symbol;         // +56
    const char *postfix_name;                    // +64
    CommandRegistry::Symbol postfix_symbol;      // +72
    CommandParameterDataType type;               // +76
    int offset_value;                            // +80
    int offset_has_value;                        // +84
    bool optional;                               // +88
    CommandParameterOption option;               // +89
};
