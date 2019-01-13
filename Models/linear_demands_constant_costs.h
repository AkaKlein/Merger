#pragma once

#include "Utils/algebra.h"
#include "model_interface.h"

/// Model in which demands follow a linear function and costs are constant.
class LinearDemandsConstantCosts : public ModelInterface
{
public:
    LinearDemandsConstantCosts() = default;
    LinearDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities);


    /*** Functions to get information about the model ***/

    /// Returns the name of the model.
    virtual std::string GetName() const { return "Linear Demands with Constant Costs"; }

    /// Returns the number of products.
    virtual int GetNumberOfProducts() const { return m_a.Size(); }


    /// Computes the equilibrium prices of the model.    
    virtual ColumnVector ComputePrices() const override final;
    
    /// Computes the equilibrium quantities of the model.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeQuantities(ColumnVector const& prices) const override final;

    /// Computes the costs of the model in equilibrium.
    ///
    /// @param quantities The equilibrium quantities.
    virtual ColumnVector ComputeCosts(ColumnVector const& /*quantities*/) const override final { return m_c; }

    /// Computes the profits of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeProfits(ColumnVector const& prices) const override final;

    /// Computes the consumer welfare of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeConsumerWelfare(ColumnVector const& prices) const override final;


    /*** Functions to perform mergers ***/

    /// Merges two different firms.
    ///
    /// @param i The index of the first firm to merge.
    /// @param j The index of the second firm to merge.
    virtual void Merge(int i, int j) override final;

    
    /*** Functions for serialization ***/

    /// Saves the current model values to the given file path.
    ///
    /// @param file_path The path of the file to where the model will be saved.
    virtual void SaveToFile(std::string const& file_path) const override final;

    /// Loads the model values from the given file path.
    ///
    /// @param file_path The path of the file from where the model has to read its values.
    virtual void LoadFromFile(std::string const& file_path) override final;

private:
    /// Income vector.
    ColumnVector m_a;

    /// Costs vector.
    ColumnVector m_c;

    /// Elasticities' matrix.
    Matrix m_B;

    /// Merger matrix.
    Matrix m_D;
};
