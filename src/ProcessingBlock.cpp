#include "ProcessingBlock.h"

#include "FacerecService.h"

namespace face_sdk_3divi
{
    ProcessingBlock::ProcessingBlock(const Context& config) :
        implementation(FacerecService::get()->createProcessingBlock(*config))
    {
        
    }

    ProcessingBlock::ProcessingBlock(const py::dict& dict) :
        ProcessingBlock(Context(dict))
    {

    }

    void ProcessingBlock::operator ()(Context& config)
    {
        implementation(*config);
    }
}
