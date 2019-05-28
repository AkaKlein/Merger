#pragma once

#include <iostream>
#include <stdexcept>

enum class ModelType
{
    HyperbolicDemandsConstantCosts,
    HyperbolicDemandsLinearCosts,
    LinearDemandsConstantCosts,
    LinearDemandsLinearCosts,
    QuadraticDemandsConstantCosts, 
    QuadraticDemandsLinearCosts, 

    Count
};

inline std::string ModelTypeToCompactString(ModelType type)
{
    switch (type)
    {
        case ModelType::HyperbolicDemandsConstantCosts:
            return "HyperbolicDemandsConstantCosts";
        case ModelType::HyperbolicDemandsLinearCosts:
            return "HyperbolicDemandsLinearCosts";
        case ModelType::LinearDemandsConstantCosts:
            return "LinearDemandsConstantCosts";
        case ModelType::LinearDemandsLinearCosts:
            return "LinearDemandsLinearCosts";
        case ModelType::QuadraticDemandsConstantCosts:
            return "QuadraticDemandsConstantCosts";
        case ModelType::QuadraticDemandsLinearCosts:
            return "QuadraticDemandsLinearCosts";
        default:
            throw std::runtime_error("ModelTypeToCompactString: should not happen");
    }
}

inline std::string ModelTypeToExtendedString(ModelType type)
{
    switch (type)
    {
        case ModelType::HyperbolicDemandsConstantCosts:
            return "Hyperbolic Demands with Constant Costs";
        case ModelType::HyperbolicDemandsLinearCosts:
            return "Hyperbolic Demands with Linear Costs";
        case ModelType::LinearDemandsConstantCosts:
            return "Linear Demands with Constant Costs";
        case ModelType::LinearDemandsLinearCosts:
            return "Linear Demands with Linear Costs";
        case ModelType::QuadraticDemandsConstantCosts:
            return "Quadratic Demands with Constant Costs";
        case ModelType::QuadraticDemandsLinearCosts:
            return "Quadratic Demands with Linear Costs";
        default:
            throw std::runtime_error("ModelTypeToExtendedString: should not happen");
    }
}

inline std::ostream& operator<<(std::ostream& out, ModelType type)
{
    out << ModelTypeToCompactString(type);
    return out;
}