#pragma once

#include <vector>

#include <pbio/DynamicTemplateIndex.h>

#include "Context.h"
#include "ContextTemplate.h"

namespace face_sdk_3divi
{
    class DynamicTemplateIndex
    {
    private:
        pbio::DynamicTemplateIndex::Ptr implementation;

    public:
        DynamicTemplateIndex(const Context& config);

        DynamicTemplateIndex(const py::dict& config);

        DynamicTemplateIndex(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids, const Context& config);

        DynamicTemplateIndex(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids, const py::dict& config);

        DynamicTemplateIndex(pbio::DynamicTemplateIndex::Ptr implementation);

        void add(const ContextTemplate& contextTemplate, const std::string& uuid);

        void add(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids);

        size_t size() const;

        size_t capacity() const;

        void concat(const DynamicTemplateIndex& other);

        void remove(const std::string& uuid);

        void remove(const std::vector<std::string>& uuids);

        void clear();

        ContextTemplate get(int64_t index);

        ContextTemplate at(const std::string& uuid);

        std::string getUUID(int64_t index);

        std::string getMethodName() const;

        pbio::DynamicTemplateIndex::Ptr& operator *();

        const pbio::DynamicTemplateIndex::Ptr operator *() const;

        ~DynamicTemplateIndex() = default;
    };
}
