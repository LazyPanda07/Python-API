#include "FacerecService.h"

static std::unique_ptr<face_sdk_3divi::FacerecService> instance;

namespace face_sdk_3divi
{
    FacerecService::FacerecService(const std::string& dllPath, const std::string& confDirectory, const std::string& licenseDirectory) :
        service(pbio::FacerecService::createService(dllPath, confDirectory, licenseDirectory))
    {

    }

    pbio::FacerecService::Ptr& FacerecService::get()
    {
        if (!instance)
        {
            throw std::runtime_error("Call face_sdk_3divi.create_service");
        }

        return instance->service;
    }

    void FacerecService::createService(const std::string& dllPath, const std::string& confDirectory, const std::string& licenseDirectory)
    {
        if (!instance)
        {
            instance = std::unique_ptr<FacerecService>(new FacerecService(dllPath, confDirectory, licenseDirectory));
        }
    }
}
