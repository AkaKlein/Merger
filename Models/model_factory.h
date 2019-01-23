#pragma once

#include <memory>

#include "linear_demands_constant_costs.h"

class ModelFactory
{
public:
    static std::unique_ptr<ModelInterface> CreateModel(std::string const& file_name, ModelType model_type)
    {
        std::unique_ptr<ModelInterface> result;

        // Create an empty model.
        switch (model_type)
        {
            case ModelType::LinearDemandsConstantCosts:
                result = std::make_unique<LinearDemandsConstantCosts>();
                break;
            default:
                throw std::runtime_error("ModelFactory::CreateModel: should not happen");
        }

        // Load it from the file.
        result->LoadFromFile(file_name);
        
        return std::move(result);
    }
};