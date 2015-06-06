#include <string>

#include "UtilsParser.h"
#include "DeclarationParser.h"
#include "Utils/Debug.h"

namespace minimoe
{
    using std::string;

    /***********************
    Parse
    **********************/
    TagDeclaration::Ptr TagDeclaration::Parse(LineIter & head, LineIter tail, CompileError::List & errors)
    {
        if (CheckEndOfFile(head, tail, errors))
            return nullptr;
        auto tokenIt = (*head)->tokens.begin();
        auto tokenEnd = (*head)->tokens.end();
        if (CheckReachTheEnd(tokenIt, tokenEnd, errors))
            return nullptr;
        if (!CheckSingleTokenType(tokenIt, tokenEnd, CodeTokenType::Tag, errors))
            return nullptr;
        string name = (*tokenIt)->value;
        if (!CheckSingleTokenType(tokenIt, tokenEnd, CodeTokenType::Identifier, errors))
            return nullptr;
        auto tag = std::make_shared<TagDeclaration>();
        tag->name = name;
        return tag;
    }

    /****************
    ToLog
    ****************/
    std::string TypeDeclaration::ToLog()
    {
        return "not implemented";
    }

    std::string TagDeclaration::ToLog()
    {
        return "Tag(" + name + ")";
    }

    std::string ArgumentDeclaration::ToLog()
    {
        return "not implemented";
    }

    std::string FunctionDeclaration::ToLog()
    {
        string name, argument;
        for (auto & fragment : fragments)
        {
            if (fragment->type == FunctionFragmentType::Name)
            {
                if (!name.empty()) name += "_";
                name += fragment->name;
            }
            else if (fragment->type == FunctionFragmentType::Argument)
            {
                if (!argument.empty()) argument += ", ";
                argument += fragment->name;
            }
            else ERRORMSG("invalid enum");
        }
        return name + "(" + argument + ")";
    }

    std::string VariableDeclaration::ToLog()
    {
        return "not implemented";
    }

    // FunctionDeclaration
    FunctionDeclaration::Ptr FunctionDeclaration::Make(FunctionType type)
    {
        auto func = std::make_shared<FunctionDeclaration>();
        func->type = type;
        return func;
    }

    FunctionDeclaration::Ptr FunctionDeclaration::name(std::string s)
    {
        auto fragment = std::make_shared<FunctionFragment>();
        fragment->type = FunctionFragmentType::Name;
        fragment->name = s;
        fragments.push_back(fragment);
        return std::dynamic_pointer_cast<FunctionDeclaration>(shared_from_this());
    }

    FunctionDeclaration::Ptr FunctionDeclaration::arg(FunctionArgumentType type, std::string s)
    {
        auto fragment = std::make_shared<FunctionFragment>();
        fragment->type = FunctionFragmentType::Argument;
        fragment->name = s;
        fragments.push_back(fragment);

        auto argument = std::make_shared<ArgumentDeclaration>();
        argument->type = type;
        arguments.push_back(argument);

        return std::dynamic_pointer_cast<FunctionDeclaration>(shared_from_this());
    }
}
