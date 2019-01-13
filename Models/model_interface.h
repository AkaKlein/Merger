#pragma once

#include "Utils/algebra.h"

/// An interface for any model.
class ModelInterface
{
public:
    /*** Functions to get information about the model ***/

    /// Returns the name of the model.
    virtual std::string GetName() const = 0;

    /// Returns the number of products.
    virtual int GetNumberOfProducts() const = 0;


    /*** Functions to compute equilibrium values ***/

    /// Computes the equilibrium prices of the model.
    virtual ColumnVector ComputePrices() const = 0;

    /// Computes the equilibrium quantities of the model.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeQuantities(ColumnVector const& prices) const = 0;

    /// Computes the costs of the model in equilibrium.
    ///
    /// @param quantities The equilibrium quantities.
    virtual ColumnVector ComputeCosts(ColumnVector const& quantities) const = 0;

    /// Computes the profits of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeProfits(ColumnVector const& prices) const = 0;

    /// Computes the consumer welfare of the model in equilibrium.
    ///
    /// @param prices The equilibrium prices.
    virtual ColumnVector ComputeConsumerWelfare(ColumnVector const& prices) const = 0;


    /*** Functions to perform mergers ***/

    /// Merges two different firms.
    ///
    /// @param i The index of the first firm to merge.
    /// @param j The index of the second firm to merge.
    virtual void Merge(int i, int j) = 0;


    /*** Functions for serialization ***/

    /// Saves the current model values to the given file path.
    ///
    /// @param file_path The path of the file to where the model will be saved.
    virtual void SaveToFile(std::string const& file_path) const = 0;

    /// Loads the model values from the given file path.
    ///
    /// @param file_path The path of the file from where the model has to read its values.
    virtual void LoadFromFile(std::string const& file_path) = 0;
};