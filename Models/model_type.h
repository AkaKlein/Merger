#pragma once

#include <iostream>
#include <stdexcept>

enum class ModelType
{
    LinearDemandsConstantCosts,
    LinearDemandsLinearCosts,
    QuadraticDemandsConstantCosts, 

    Count
};

inline std::string ModelTypeToCompactString(ModelType type)
{
    switch (type)
    {
        case ModelType::LinearDemandsConstantCosts:
            return "LinearDemandsConstantCosts";
        case ModelType::LinearDemandsLinearCosts:
            return "LinearDemandsLinearCosts";
        case ModelType::QuadraticDemandsConstantCosts:
            return "QuadraticDemandsConstantCosts";
        default:
            throw std::runtime_error("ModelTypeToCompactString: should not happen");
    }
}

inline std::string ModelTypeToExtendedString(ModelType type)
{
    switch (type)
    {
        case ModelType::LinearDemandsConstantCosts:
            return "Linear Demands with Constant Costs";
        case ModelType::LinearDemandsLinearCosts:
            return "Linear Demands with Linear Costs";
        case ModelType::QuadraticDemandsConstantCosts:
            return "Quadratic Demands with Constant Costs";
        default:
            throw std::runtime_error("ModelTypeToExtendedString: should not happen");
    }
}

inline std::ostream& operator<<(std::ostream& out, ModelType type)
{
    out << ModelTypeToCompactString(type);
    return out;
}