#include <pybind11/pybind11.h>

#include "FacerecService.h"
#include "Context.h"
#include "ProcessingBlock.h"
#include "ContextTemplate.h"
#include "DynamicTemplateIndex.h"

namespace py = pybind11;

PYBIND11_MODULE(face_sdk_3divi, m, py::mod_gil_not_used())
{
    using namespace py::literals;

    m.doc() = "face_sdk_3divi plugin";

    py::class_<face_sdk_3divi::FacerecService>(m, "FacerecService")
        .def_static("create_service", &face_sdk_3divi::FacerecService::createService, "dll_path"_a, "facerec_conf_dir"_a, "license_dir"_a, py::call_guard<py::gil_scoped_release>());

    py::class_<face_sdk_3divi::ContextTemplate> contextTemplate(m, "ContextTemplate");
    py::class_<face_sdk_3divi::DynamicTemplateIndex> dynamicTemplateIndex(m, "DynamicTemplateIndex");
    py::class_<face_sdk_3divi::Context> context(m, "Context");
    py::class_<face_sdk_3divi::ProcessingBlock> processingBlock(m, "ProcessingBlock");

    py::enum_<face_sdk_3divi::Context::Format>(context, "Format")
        .value("FORMAT_BGR", face_sdk_3divi::Context::Format::FORMAT_BGR)
        .value("FORMAT_RGB", face_sdk_3divi::Context::Format::FORMAT_RGB)
        .value("FORMAT_BGRA8888", face_sdk_3divi::Context::Format::FORMAT_BGRA8888)
        .value("FORMAT_YUV420", face_sdk_3divi::Context::Format::FORMAT_YUV420)
        .value("FORMAT_YUV_NV12", face_sdk_3divi::Context::Format::FORMAT_YUV_NV12)
        .value("FORMAT_NV21", face_sdk_3divi::Context::Format::FORMAT_NV21)
        .export_values();

    context
        .def(py::init())
        .def(py::init<const py::dict&>(), "ctx"_a)
        .def(py::init<const py::bytes&>(), "image_data"_a)
        .def(py::init<uint8_t*, int32_t, int32_t, face_sdk_3divi::Context::Format, int32_t>(), "frame_data"_a, "width"_a, "height"_a, "format"_a, "base_angle"_a)
        .def(py::init<const std::string&>(), "path_to_json_file"_a)
        .def("serialize_to_json", &face_sdk_3divi::Context::serializeToJson, py::call_guard<py::gil_scoped_release>())
        .def("contains", &face_sdk_3divi::Context::contains, py::call_guard<py::gil_scoped_release>(), "key"_a)
        .def("to_dict", &face_sdk_3divi::Context::toDict)
        .def("clear", &face_sdk_3divi::Context::clear, py::call_guard<py::gil_scoped_release>())
        .def("keys", &face_sdk_3divi::Context::getKeys, py::call_guard<py::gil_scoped_release>())
        .def("is_none", &face_sdk_3divi::Context::isNone, py::call_guard<py::gil_scoped_release>())
        .def("is_long", &face_sdk_3divi::Context::isLong, py::call_guard<py::gil_scoped_release>())
        .def("is_bool", &face_sdk_3divi::Context::isBool, py::call_guard<py::gil_scoped_release>())
        .def("is_string", &face_sdk_3divi::Context::isString, py::call_guard<py::gil_scoped_release>())
        .def("is_double", &face_sdk_3divi::Context::isDouble, py::call_guard<py::gil_scoped_release>())
        .def("is_data_ptr", &face_sdk_3divi::Context::isDataPtr, py::call_guard<py::gil_scoped_release>())
        .def("is_context_template", &face_sdk_3divi::Context::isContextTemplate, py::call_guard<py::gil_scoped_release>())
        .def("is_dynamic_template_index", &face_sdk_3divi::Context::isDynamicTemplateIndex, py::call_guard<py::gil_scoped_release>())
        .def("is_array", &face_sdk_3divi::Context::isArray, py::call_guard<py::gil_scoped_release>())
        .def("is_object", &face_sdk_3divi::Context::isObject, py::call_guard<py::gil_scoped_release>())
        .def("set_long", &face_sdk_3divi::Context::setLong, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_bool", &face_sdk_3divi::Context::setBool, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_string", &face_sdk_3divi::Context::setString, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_double", &face_sdk_3divi::Context::setDouble, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_bytes", &face_sdk_3divi::Context::setDataPtr, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_context_template", &face_sdk_3divi::Context::setContextTemplate, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("set_dynamic_template_index", &face_sdk_3divi::Context::setDynamicTemplateIndex, "value"_a, py::call_guard<py::gil_scoped_release>())
        .def("get_long", &face_sdk_3divi::Context::getLong, py::call_guard<py::gil_scoped_release>())
        .def("get_bool", &face_sdk_3divi::Context::getBool, py::call_guard<py::gil_scoped_release>())
        .def("get_string", &face_sdk_3divi::Context::getString, py::call_guard<py::gil_scoped_release>())
        .def("get_double", &face_sdk_3divi::Context::getDouble, py::call_guard<py::gil_scoped_release>())
        .def("get_context_template", &face_sdk_3divi::Context::getContextTemplate, py::call_guard<py::gil_scoped_release>())
        .def("get_dynamic_template_index", &face_sdk_3divi::Context::getDynamicTemplateIndex, py::call_guard<py::gil_scoped_release>())
        .def("get_value", &face_sdk_3divi::Context::getValue, py::call_guard<py::gil_scoped_release>())
        .def("get_bytes", &face_sdk_3divi::Context::getBytes, "size"_a)
        .def_static("get_bytes_from_ptr", &face_sdk_3divi::Context::getBytesFromPtr, "context"_a, "size"_a)
        .def("__len__", &face_sdk_3divi::Context::size)
        .def("__setitem__", [](face_sdk_3divi::Context& context, int64_t index, const py::handle& value) { context[index].setValue(value); })
        .def("__setitem__", [](face_sdk_3divi::Context& context, const std::string& key, const py::handle& value) { context[key].setValue(value); })
        .def("__getitem__", [](face_sdk_3divi::Context& context, int64_t index) { return context[index]; }, "index"_a)
        .def("__getitem__", [](face_sdk_3divi::Context& context, const std::string& key) { return context[key]; }, "key"_a)
        .def("__contains__", [](face_sdk_3divi::Context& context, const std::string& key) { return context.contains(key); }, "key"_a);

    contextTemplate
        .def(py::init<const face_sdk_3divi::ContextTemplate&>(), "context_template"_a)
        .def(py::init<const py::bytes&>(), "data"_a)
        .def(py::init<py::object&>(), "binary_read_stream"_a)
        .def("save", &face_sdk_3divi::ContextTemplate::save, "binary_write_stream"_a)
        .def("size", &face_sdk_3divi::ContextTemplate::size, py::call_guard<py::gil_scoped_release>())
        .def("get_method_name", &face_sdk_3divi::ContextTemplate::getMethodName, py::call_guard<py::gil_scoped_release>());

    dynamicTemplateIndex
        .def(py::init<const face_sdk_3divi::Context&>(), "config"_a)
        .def(py::init<const py::dict&>(), "config"_a)
        .def(py::init<const std::vector<face_sdk_3divi::ContextTemplate>&, const std::vector<std::string>&, const face_sdk_3divi::Context&>(), "templates"_a, "uuids"_a, "config"_a)
        .def(py::init<const std::vector<face_sdk_3divi::ContextTemplate>&, const std::vector<std::string>&, const py::dict&>(), "templates"_a, "uuids"_a, "config"_a)
        .def("add", py::overload_cast<const face_sdk_3divi::ContextTemplate&, const std::string&>(&face_sdk_3divi::DynamicTemplateIndex::add), "context_template"_a, "uuid"_a)
        .def("add", py::overload_cast<const std::vector<face_sdk_3divi::ContextTemplate>&, const std::vector<std::string>&>(&face_sdk_3divi::DynamicTemplateIndex::add), "templates"_a, "uuids"_a)
        .def("size", &face_sdk_3divi::DynamicTemplateIndex::size)
        .def("capacity", &face_sdk_3divi::DynamicTemplateIndex::capacity)
        .def("concat", &face_sdk_3divi::DynamicTemplateIndex::concat, "other"_a)
        .def("remove", py::overload_cast<const std::string&>(&face_sdk_3divi::DynamicTemplateIndex::remove))
        .def("remove", py::overload_cast<const std::vector<std::string>&>(&face_sdk_3divi::DynamicTemplateIndex::remove))
        .def("clear", &face_sdk_3divi::DynamicTemplateIndex::clear)
        .def("get", &face_sdk_3divi::DynamicTemplateIndex::get, "index"_a)
        .def("at", &face_sdk_3divi::DynamicTemplateIndex::get, "uuid"_a)
        .def("get_uuid", &face_sdk_3divi::DynamicTemplateIndex::get, "index"_a)
        .def("get_method_name", &face_sdk_3divi::DynamicTemplateIndex::getMethodName);

    processingBlock
        .def(py::init<const face_sdk_3divi::Context&>(), "config"_a, py::call_guard<py::gil_scoped_release>())
        .def(py::init<const py::dict&>(), "config"_a)
        .def("__call__", &face_sdk_3divi::ProcessingBlock::operator (), "io_data"_a, py::call_guard<py::gil_scoped_release>());

    py::class_<pbio::Error>(m, "_ErrorImplementation")
        .def("__str__", [](const pbio::Error& error) { return py::str("0x{:x}: {}").format(error.code(), error.what()); });

    py::register_exception<pbio::Error>(m, "Error");

    py::register_exception_translator
    (
        [](std::exception_ptr p)
        {
            try
            {
                if (p)
                {
                    std::rethrow_exception(p);
                }
            }
            catch (const pbio::Error& e)
            {
                auto errorClass = py::module_::import("face_sdk_3divi").attr("Error");

                py::set_error(errorClass, py::cast(e).ptr());
            }
        }
    );
}
