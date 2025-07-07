#include "ContextTemplate.h"

#include "FacerecService.h"

namespace face_sdk_3divi
{
    ContextTemplate::ContextTemplate(pbio::ContextTemplate::Ptr implementation) :
        implementation(implementation)
    {

    }

    ContextTemplate::ContextTemplate(const py::bytes& data)
    {
        std::istringstream is(data);

        implementation = FacerecService::get()->loadContextTemplate(is);
    }

    ContextTemplate::ContextTemplate(py::object& binaryReadStream)
    {
        if (!py::hasattr(binaryReadStream, "read") || !py::isinstance<py::function>(binaryReadStream.attr("read")))
        {
            throw std::runtime_error("Can't find read function in binary_read_stream object");
        }

        // TODO: read
        
        binaryReadStream.attr("read")();
    }

    int32_t ContextTemplate::size() const
    {
        return implementation->size();
    }

    void ContextTemplate::save(py::object& binaryWriteStream) const
    {
        if (!py::hasattr(binaryWriteStream, "write") || !py::isinstance<py::function>(binaryWriteStream.attr("write")))
        {
            throw std::runtime_error("Can't find write function in binary_write_stream object");
        }
        std::ostringstream temp;
        
        implementation->save(temp);

        std::string data = temp.str();

        binaryWriteStream.attr("write")(py::bytes(data));
    }

    std::string ContextTemplate::getMethodName() const
    {
        return implementation->getMethodName();
    }

    pbio::ContextTemplate::Ptr& ContextTemplate::operator *()
    {
        return implementation;
    }

    const pbio::ContextTemplate::Ptr ContextTemplate::operator *() const
    {
        return implementation;
    }
}
