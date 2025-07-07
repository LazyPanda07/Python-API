#include "Context.h"

#include "FacerecService.h"
#include "DynamicTemplateIndex.h"

namespace face_sdk_3divi
{
    py::bytes Context::getBytesFromPtr(const Context& context, uint64_t size)
    {
        return context.getBytes(size);
    }

    pbio::Context Context::parsePythonBytes(const py::bytes& data)
    {
        py::gil_scoped_release release;

        std::string_view temp = static_cast<std::string_view>(data);

        return FacerecService::get()->createContextFromEncodedImage(reinterpret_cast<const uint8_t*>(temp.data()), temp.size());
    }

    pbio::Context Context::createContextFromFrame(uint8_t* data, int32_t width, int32_t height, Context::Format format, int32_t baseAngle)
    {
        py::gil_scoped_release release;

        return FacerecService::get()->createContextFromFrame(data, width, height, static_cast<pbio::Context::Format>(format), baseAngle);
    }

    pbio::Context Context::createContextFromJsonFile(const std::string& pathToJsonFile)
    {
        py::gil_scoped_release release;

        return FacerecService::get()->createContextFromJsonFile(pathToJsonFile);
    }

    Context::Context(pbio::Context::Ref* implementation) :
        implementation(std::shared_ptr<pbio::Context::Ref>(implementation))
    {

    }

    Context::Context() :
        implementation(std::make_shared<pbio::Context>(FacerecService::get()->createContext()))
    {

    }

    Context::Context(const py::dict& dict) :
        Context()
    {
        (*this) = dict;
    }

    Context::Context(const py::bytes& data) :
        implementation(std::make_shared<pbio::Context>(Context::parsePythonBytes(data)))
    {

    }

    Context::Context(uint8_t* data, int32_t width, int32_t height, Context::Format format, int32_t baseAngle) :
        implementation(std::make_shared<pbio::Context>(Context::createContextFromFrame(data, width, height, format, baseAngle)))
    {

    }

    Context::Context(const std::string& pathToJsonFile) :
        implementation(std::make_shared<pbio::Context>(Context::createContextFromJsonFile(pathToJsonFile)))
    {

    }

    Context::Context(const Context& other) :
        implementation(other.implementation)
    {

    }

    Context& Context::operator =(const Context& other)
    {
        (**this) = *other;

        return *this;
    }

    void Context::pushBack(const Context& value)
    {
        (**this).push_back(*value);
    }

    std::string Context::serializeToJson() const
    {
        return (**this).serializeToJson();
    }

    bool Context::contains(const std::string& key) const
    {
        return (**this).contains(key);
    }

    py::dict Context::toDict() const
    {
        if (!(**this).isObject())
        {
            throw std::runtime_error("Not an object");
        }

        py::object json = py::module::import("json");

        return json.attr("loads")(serializeToJson()).cast<py::dict>();
    }

    uint64_t Context::size() const
    {
        return (**this).size();
    }

    void Context::clear()
    {
        (**this).clear();
    }

    bool Context::isNone() const
    {
        return (**this).isNone();
    }

    bool Context::isLong() const
    {
        return (**this).isLong();
    }

    bool Context::isBool() const
    {
        return (**this).isBool();
    }

    bool Context::isString() const
    {
        return (**this).isString();
    }

    bool Context::isDouble() const
    {
        return (**this).isDouble();
    }

    bool Context::isDataPtr() const
    {
        return (**this).isDataPtr();
    }

    bool Context::isContextTemplate() const
    {
        return (**this).isContextTemplate();
    }

    bool Context::isDynamicTemplateIndex() const
    {
        return (**this).isDynamicTemplateIndex();
    }

    bool Context::isArray() const
    {
        return (**this).isArray();
    }

    bool Context::isObject() const
    {
        return (**this).isObject();
    }

    void Context::setLong(int64_t value)
    {
        (**this).setLong(value);
    }

    void Context::setBool(bool value)
    {
        (**this).setBool(value);
    }

    void Context::setString(const std::string& value)
    {
        (**this).setString(value);
    }

    void Context::setDouble(double value)
    {
        (**this).setDouble(value);
    }

    void Context::setDataPtr(const py::bytes& value)
    {
        std::string_view temp = static_cast<std::string_view>(value);

        (**this).setDataPtr(temp.data(), temp.size());
    }

    void Context::setContextTemplate(const ContextTemplate& value)
    {
        (**this).setContextTemplate(*value);
    }

    void Context::setDynamicTemplateIndex(const DynamicTemplateIndex& value)
    {
        (**this).setDynamicTemplateIndex(*value);
    }

    void Context::setValue(const py::handle& value)
    {
        if (py::isinstance<py::str>(value))
        {
            (*this) = value.cast<py::str>();
        }
        else if (py::isinstance<py::bool_>(value))
        {
            (*this) = value.cast<py::bool_>();
        }
        else if (py::isinstance<py::int_>(value)) // with bool returns true
        {
            (*this) = value.cast<py::int_>();
        }
        else if (py::isinstance<py::float_>(value))
        {
            (*this) = value.cast<py::float_>();
        }
        else if (py::isinstance<py::bytes>(value))
        {
            (*this) = value.cast<py::bytes>();
        }
        else if (py::isinstance<Context>(value))
        {
            (*this) = value.cast<Context>();
        }
        else if (py::isinstance<py::dict>(value))
        {
            (*this) = value.cast<py::dict>();
        }
        else if (py::isinstance<py::list>(value))
        {
            (*this) = value.cast<py::list>();
        }
        else if (py::isinstance<py::none>(value))
        {

        }
        else if (py::isinstance<DynamicTemplateIndex>(value))
        {
            (*this) = value.cast<DynamicTemplateIndex>();
        }
        else if (py::isinstance<ContextTemplate>(value))
        {
            (*this) = value.cast<ContextTemplate>();
        }
        else
        {
            throw std::runtime_error("Unknown type: " + py::str(value.get_type()).cast<std::string>());
        }
    }

    int64_t Context::getLong() const
    {
        return (**this).getLong();
    }

    bool Context::getBool() const
    {
        return (**this).getBool();
    }

    std::string Context::getString() const
    {
        return (**this).getString();
    }

    double Context::getDouble() const
    {
        return (**this).getDouble();
    }

    py::bytes Context::getBytes(uint64_t size) const
    {
        return py::bytes(reinterpret_cast<const char*>((**this).getDataPtr()), size);
    }

    ContextTemplate Context::getContextTemplate() const
    {
        return (**this).getContextTemplate();
    }

    DynamicTemplateIndex Context::getDynamicTemplateIndex() const
    {
        return (**this).getDynamicTemplateIndex();
    }

    std::variant<py::handle, py::float_, ContextTemplate, DynamicTemplateIndex> Context::getValue() const
    {
        std::function<std::variant<py::handle, py::float_, ContextTemplate, DynamicTemplateIndex>()> getter;
        const pbio::Context& value = **this;

        if (value.isString())
        {
            getter = [&value]() { return py::str(value.getString()); };
        }
        else if (value.isLong())
        {
            getter = [&value]() { return py::int_(value.getLong()); };
        }
        else if (value.isDouble())
        {
            getter = [&value]() { return py::float_(value.getDouble()); };
        }
        else if (value.isBool())
        {
            getter = [&value]() { return py::bool_(value.getBool()); };
        }
        else if (value.isNone())
        {
            getter = []() { return py::none(); };
        }
        else if (value.isDynamicTemplateIndex())
        {
            getter = [&value]() { return DynamicTemplateIndex(value.getDynamicTemplateIndex()); };
        }
        else if (value.isContextTemplate())
        {
            getter = [&value]() { return ContextTemplate(value.getContextTemplate()); };
        }

        py::gil_scoped_acquire acquire;

        return getter();
    }

    std::vector<std::string> Context::getKeys()
    {
        return (**this).getKeys();
    }

    Context Context::operator[](int64_t index)
    {
        return (**this)[index].getContextPtr();
    }

    Context Context::operator[](const std::string& key)
    {
        return (**this)[key].getContextPtr();
    }

    const Context Context::operator[](int64_t index) const
    {
        return (**this)[index].getContextPtr();
    }

    const Context Context::operator[](const std::string& key) const
    {
        return (**this)[key].getContextPtr();
    }

    void Context::operator =(const py::str& value)
    {
        (**this) = static_cast<std::string>(value);
    }

    void Context::operator =(const py::int_& value)
    {
        (**this) = static_cast<int64_t>(value);
    }

    void Context::operator =(const py::float_& value)
    {
        (**this) = static_cast<double>(value);
    }

    void Context::operator =(const py::bool_& value)
    {
        (**this) = static_cast<bool>(value);
    }

    void Context::operator =(const py::bytes& value)
    {
        std::string_view temp = static_cast<std::string_view>(value);

        (**this).setDataPtr(temp.data(), temp.size());
    }

    void Context::operator =(const ContextTemplate& value)
    {
        (**this).setContextTemplate(*value);
    }

    void Context::operator =(const DynamicTemplateIndex& value)
    {
        (**this).setDynamicTemplateIndex(*value);
    }

    void Context::operator =(const py::dict& dict)
    {
        for (const auto& [key, value] : dict)
        {
            Context temp = (*this)[key.cast<std::string>()];

            temp.setValue(value);
        }
    }

    void Context::operator =(const py::list& list)
    {
        for (const auto& value : list)
        {
            Context temp;

            temp.setValue(value);

            pushBack(temp);
        }
    }

    pbio::Context& Context::operator *()
    {
        return *implementation;
    }

    const pbio::Context& Context::operator *() const
    {
        return *implementation;
    }
}
