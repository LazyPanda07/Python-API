#include "DynamicTemplateIndex.h"

#include "FacerecService.h"

namespace face_sdk_3divi
{
    DynamicTemplateIndex::DynamicTemplateIndex(const Context& config) :
        implementation(FacerecService::get()->createDynamicTemplateIndex(*config))
    {

    }

    DynamicTemplateIndex::DynamicTemplateIndex(const py::dict& config) :
        DynamicTemplateIndex(Context(config))
    {

    }

    DynamicTemplateIndex::DynamicTemplateIndex(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids, const Context& config)
    {
        std::vector<pbio::ContextTemplate::Ptr> temp;

        temp.reserve(templates.size());

        std::transform
        (
            templates.begin(), templates.end(), std::back_inserter(temp),
            [](const ContextTemplate& contextTemplate) { return *contextTemplate; }
        );

        implementation = FacerecService::get()->createDynamicTemplateIndex(temp, uuids, *config);
    }

    DynamicTemplateIndex::DynamicTemplateIndex(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids, const py::dict& config) :
        DynamicTemplateIndex(templates, uuids, Context(config))
    {

    }

    DynamicTemplateIndex::DynamicTemplateIndex(pbio::DynamicTemplateIndex::Ptr implementation) :
        implementation(implementation)
    {

    }

    void DynamicTemplateIndex::add(const ContextTemplate& contextTemplate, const std::string& uuid)
    {
        implementation->add(*contextTemplate, uuid);
    }

    void DynamicTemplateIndex::add(const std::vector<ContextTemplate>& templates, const std::vector<std::string>& uuids)
    {
        std::vector<pbio::ContextTemplate::Ptr> temp;

        temp.reserve(templates.size());

        std::transform
        (
            templates.begin(), templates.end(), std::back_inserter(temp),
            [](const ContextTemplate& contextTemplate) { return *contextTemplate; }
        );

        implementation->add(temp, uuids);
    }

    size_t DynamicTemplateIndex::size() const
    {
        return implementation->size();
    }

    size_t DynamicTemplateIndex::capacity() const
    {
        return implementation->capacity();
    }

    void DynamicTemplateIndex::concat(const DynamicTemplateIndex& other)
    {
        implementation->concat(*other);
    }

    void DynamicTemplateIndex::remove(const std::string& uuid)
    {
        implementation->remove(uuid);
    }

    void DynamicTemplateIndex::remove(const std::vector<std::string>& uuids)
    {
        implementation->remove(uuids);
    }

    void DynamicTemplateIndex::clear()
    {
        implementation->clear();
    }

    ContextTemplate DynamicTemplateIndex::get(int64_t index)
    {
        return implementation->get(index);
    }

    ContextTemplate DynamicTemplateIndex::at(const std::string& uuid)
    {
        return implementation->at(uuid);
    }

    std::string DynamicTemplateIndex::getUUID(int64_t index)
    {
        return implementation->getUUID(index);
    }

    std::string DynamicTemplateIndex::getMethodName() const
    {
        return implementation->getMethodName();
    }

    pbio::DynamicTemplateIndex::Ptr& DynamicTemplateIndex::operator *()
    {
        return implementation;
    }

    const pbio::DynamicTemplateIndex::Ptr DynamicTemplateIndex::operator *() const
    {
        return implementation;
    }
}
