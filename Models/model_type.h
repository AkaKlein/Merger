#pragma once

enum class ModelType
{
    LinearDemandsConstantCosts,
    LinearDemandsLinearCosts,

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
        default:
            throw std::runtime_error("ModelTypeToExtendedString: should not happen");
    }
}