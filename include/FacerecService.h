#pragma once

#include <memory>
#include <string_view>

#include <pbio/FacerecService.h>

namespace face_sdk_3divi
{
    class FacerecService
    {
    private:
        pbio::FacerecService::Ptr service;

    private:
        FacerecService(const std::string& dllPath, const std::string& confDirectory, const std::string& licenseDirectory);

        ~FacerecService() = default;

    public:
        static pbio::FacerecService::Ptr& get();

        static void createService(const std::string& dllPath, const std::string& confDirectory, const std::string& licenseDirectory);

        friend struct std::default_delete<FacerecService>;
    };
}
