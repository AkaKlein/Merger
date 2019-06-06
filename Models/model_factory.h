#pragma once

#include <memory>

//#include "hyperbolic_demands_constant_costs.h"
//#include "hyperbolic_demands_linear_costs.h"
#include "linear_demands_constant_costs.h"
#include "linear_demands_linear_costs.h"
#include "quadratic_demands_constant_costs.h"
#include "quadratic_demands_linear_costs.h"

class ModelFactory
{
public:
    static std::shared_ptr<ModelInterface> CreateModel(std::string const& file_name, ModelType model_type)
    {
        std::shared_ptr<ModelInterface> result;

        // Create an empty model.
        switch (model_type)
        {
            //case ModelType::HyperbolicDemandsConstantCosts:
                //result = std::make_shared<HyperbolicDemandsConstantCosts>();
                //break;
            //case ModelType::HyperbolicDemandsLinearCosts:
                //result = std::make_shared<HyperbolicDemandsLinearCosts>();
                //break;
            case ModelType::LinearDemandsConstantCosts:
                result = std::make_shared<LinearDemandsConstantCosts>();
                break;
            case ModelType::LinearDemandsLinearCosts:
                result = std::make_shared<LinearDemandsLinearCosts>();
                break;
            case ModelType::QuadraticDemandsConstantCosts:
                result = std::make_shared<QuadraticDemandsConstantCosts>();
                break;
            case ModelType::QuadraticDemandsLinearCosts:
                result = std::make_shared<QuadraticDemandsLinearCosts>();
                break;
            default:
                throw std::runtime_error("ModelFactory::CreateModel: should not happen");
        }

        // Load it from the file.
        result->LoadFromFile(file_name);
        
        return std::move(result);
    }
};