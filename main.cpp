#include <iostream>

//#include <QtWidgets>

//#include "GUI/main_window.h"
#include "Models/linear_demands_constant_costs.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();*/

    int n = 3;
    ColumnVector a(n);
    ColumnVector c(n);
    Matrix B(n, n);
    Matrix D(n, n);

    for (int i = 0; i < n; ++i)
    {
        a[i] = 1;
        c[i] = 2;
    }

    for (int i = 0; i < n; ++ i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                B[i][j] = -4;
            else
                B[i][j] = 1.9;
        }
    }

    LinearDemandsConstantCosts model1(a, c, B);

    ColumnVector prices = model1.ComputePrices();
    cout << "Prices " << prices << endl;
    cout << "Quantities " << model1.ComputeQuantities(prices) << endl;
    cout << "Profit " << model1.ComputeProfits(prices) << endl;
    cout << "Consumer Welfare " << model1.ComputeConsumerWelfare(prices) << endl;

    model1.Merge(1, 2);
    prices = model1.ComputePrices();
    cout << "Prices Post " << prices << endl;
    cout << "Quantities Post " << model1.ComputeQuantities(prices) << endl;
    cout << "Profit Post" << model1.ComputeProfits(prices) << endl;
    cout << "Consumer Welfare Post " << model1.ComputeConsumerWelfare(prices) << endl;
}
