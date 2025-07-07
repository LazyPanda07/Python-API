#pragma once

#include <pbio/ContextTemplate.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace face_sdk_3divi
{
    class ContextTemplate
    {
    private:
        pbio::ContextTemplate::Ptr implementation;

    public:
        ContextTemplate(pbio::ContextTemplate::Ptr implementation);

        ContextTemplate(const py::bytes& data);

        ContextTemplate(py::object& binaryReadStream);

        int32_t size() const;

        void save(py::object& binaryWriteStream) const;

        std::string getMethodName() const;

        pbio::ContextTemplate::Ptr& operator *();

        const pbio::ContextTemplate::Ptr operator *() const;

        ~ContextTemplate() = default;
    };
}
