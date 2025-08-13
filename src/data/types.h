#ifndef TYPES_H
#define TYPES_H

#include <limits>

enum OperationType
{
    None,
    Add,
    Subtract,
    Multiply,
    Divide
};

struct CalculationBlock
{
    double first_value;
    double second_value;
    OperationType old_operation_type;
    OperationType new_operation_type;

};

const double NOT_SET = std::numeric_limits<double>::max();

#endif // TYPES_H
