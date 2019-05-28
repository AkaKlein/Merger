#pragma once

#include "Utils/algebra.h"
#include "model_interface.h"

/// @brief A model in which demands follow a quadratic function and costs are constant.
///
/// A model in which the demands vector can be written as
///
/// @f{equation}{
///     q = a + B' p + E' (p \odot p)  
/// @f}
///
/// where @f$ a @f$ is the income vector, @f$ p @f$ is the vector of prices
/// @f$ B @f$ is the elasticities' matrix, and @f$ E @f$ is the quadratic 
/// elasticities' matrix. Besides, it defines a @f$ c @f$ vector that is constant.
class QuadraticDemandsConstantCosts : public ModelInterface
{
public:
    /// Creates a model with no products. It should only be used to load the model
    /// from a file after calling it.
    QuadraticDemandsConstantCosts() = default;

    /// Creates a model with @p income being @f$ a @f$, @p costs being @f$ c @f$, @p elasticities
    /// being @f$ B @f$ and @p quad_elasticities being @f$ E @f$ in the model definition.
    ///
    /// @param income The income vector as defined in the model.
    /// @param costs The costs vector as defined in the model.
    /// @param elasticities The matrix of elasticities as defined in the model.
    /// @param quad_elasticities The matrix of quadratic elasticities defined in the model.
    QuadraticDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities, Matrix const& quad_elasticities);


    /*** Functions to get information about the model ***/

    /// Returns the type of the model.
    virtual ModelType GetType() const override final { return ModelType::QuadraticDemandsConstantCosts; }

    /// Returns the number of products.
    virtual int GetNumberOfProducts() const override final { return m_a.Size(); }

    /// Computes the equilibrium prices of the model.    
    virtual ColumnVector ComputePrices() const override final;
    
    /// Computes the equilibrium quantities of the model.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeQuantities(ColumnVector const& prices) const override final;

    /// Computes the costs of the model in equilibrium.
    ///
    /// @param quantities The equilibrium quantities.
    virtual ColumnVector ComputeCosts(ColumnVector const& quantities) const override final { (void)quantities; return m_c; }

    /// Computes the profits of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeProfits(ColumnVector const& prices) const override final;

    /// Computes the consumer welfare of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeConsumerWelfare(ColumnVector const& prices) const override final;


    /*** Functions to perform mergers ***/

    /// Sets the two given products to be produced by the same firm.
    ///
    /// @param i The index of the first product.
    /// @param j The index of the second product.
    virtual void Merge(int i, int j) override final;

    /// Returns true iff the two given products are produced by the same firm.
    ///
    /// @param i The index of the first product.
    /// @param j The index of the second product.
    virtual bool AreProducedBySameFirm(int i, int j) const override final;

    
    /*** Functions for serialization ***/

    /// Saves the current model values to the given file path.
    ///
    /// @param file_path The path of the file to where the model will be saved.
    virtual void SaveToFile(std::string const& file_path) const override final;

    /// Loads the model values from the given file path.
    ///
    /// @param file_path The path of the file from where the model has to read its values.
    virtual void LoadFromFile(std::string const& file_path) override final;


    /*** Function to clone ***/

    /// Returns a new model that is identical.
    virtual std::shared_ptr<ModelInterface> Clone() const;
    
    /// Returns a new model with the same properties but where every product is produced by a different firm.
    virtual std::shared_ptr<ModelInterface> CloneWithoutMergers() const override final;

private:
    /// Income vector.
    ColumnVector m_a;

    /// Costs vector.
    ColumnVector m_c;

    /// Elasticities' matrix.
    Matrix m_B;

    /// Quadratic Elasticities' matrix.
    Matrix m_E;

    /// Merger matrix.
    Matrix m_D;
};
