#pragma once

#include <variant>
#include <pybind11/stl.h>

#include <pybind11/pybind11.h>

#include <pbio/Context.h>

#include "ContextTemplate.h"

namespace py = pybind11;

namespace face_sdk_3divi
{
    class DynamicTemplateIndex;

    class Context
    {
    public:
        enum class Format
        {
            FORMAT_BGR = 0,
            FORMAT_RGB = 1,
            FORMAT_BGRA8888 = 2,
            FORMAT_YUV420 = 3,
            FORMAT_YUV_NV12 = 4,
            FORMAT_NV21 = 5,
        };

    public:
        static py::bytes getBytesFromPtr(const Context& context, uint64_t size);

    private:
        std::shared_ptr<pbio::Context> implementation;

    private:
        static pbio::Context parsePythonBytes(const py::bytes& data);

        static pbio::Context createContextFromFrame(uint8_t* data, int32_t width, int32_t height, Context::Format format, int32_t baseAngle);

        static pbio::Context createContextFromJsonFile(const std::string& pathToJsonFile);

    private:
        Context(pbio::Context::Ref* implementation);

    public:
        Context();

        Context(const py::dict& dict);

        Context(const py::bytes& data);

        Context(uint8_t* data, int32_t width, int32_t height, Context::Format format = Context::Format::FORMAT_BGR, int32_t baseAngle = 0);

        Context(const std::string& pathToJsonFile);

        Context(const Context& other);

        Context& operator =(const Context& other);

        void pushBack(const Context& value);

        std::string serializeToJson() const;

        bool contains(const std::string& key) const;

        py::dict toDict() const;

        uint64_t size() const;

        void clear();

        bool isNone() const;

        bool isLong() const;

        bool isBool() const;

        bool isString() const;

        bool isDouble() const;

        bool isDataPtr() const;

        bool isContextTemplate() const;

        bool isDynamicTemplateIndex() const;

        bool isArray() const;

        bool isObject() const;

        void setLong(int64_t value);

        void setBool(bool value);

        void setString(const std::string& value);

        void setDouble(double value);

        void setDataPtr(const py::bytes& value);

        void setContextTemplate(const ContextTemplate& value);

        void setDynamicTemplateIndex(const DynamicTemplateIndex& value);

        void setValue(const py::handle& value);
        
        int64_t getLong() const;

        bool getBool() const;

        std::string getString() const;

        double getDouble() const;

        py::bytes getBytes(uint64_t size) const;

        ContextTemplate getContextTemplate() const;

        DynamicTemplateIndex getDynamicTemplateIndex() const;

        std::variant<py::handle, py::float_, ContextTemplate, DynamicTemplateIndex> getValue() const;

        std::vector<std::string> getKeys();

        Context operator[](int64_t index);

        Context operator[](const std::string& key);

        const Context operator[](int64_t index) const;

        const Context operator[](const std::string& key) const;

        void operator =(const py::str& value);

        void operator =(const py::int_& value);

        void operator =(const py::float_& value);

        void operator =(const py::bool_& value);

        void operator =(const py::bytes& value);

        void operator =(const ContextTemplate& value);

        void operator =(const DynamicTemplateIndex& value);

        void operator =(const py::dict& dict);

        void operator =(const py::list& list);

        pbio::Context& operator *();

        const pbio::Context& operator *() const;

        ~Context() = default;
    };
}
