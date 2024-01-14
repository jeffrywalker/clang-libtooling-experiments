#pragma once

#include "Config.h"
#include <memory>
#include <string>

namespace data_registration
{
    class Context;
    class RegisterRequest;

    /// represents object that is to be registered
    class DataRegister
    {
            public:
        virtual ~DataRegister()
        {
        }

        /// unique ID for this entity
        virtual std::string id() const = 0;

        /// generates the registration code for this entity
        // virtual void generateRegistration(Context& context, const RegisterRequest& request) = 0;
        virtual void generateRegistration(Context& context,
                                          const std::string& classItem) = 0;  //, const RegisterRequest& request) = 0;
    };

    typedef std::shared_ptr<DataRegister> spDataRegister;
}  // namespace data_registration