#ifndef DATATYPE_H
#define DATATYPE_H

#include <iostream>

class DataType {
private:
    int data;
public:
    DataType(int d = 0);

    [[nodiscard]] int getData() const noexcept;

    void setData(int d) noexcept;

    DataType& operator=(const DataType& d) = default;
    bool operator==(const DataType& d) const noexcept;
    friend std::ostream& operator<<(std::ostream& os, const DataType& obj);

    bool operator<(const DataType& other) const noexcept;
};

#endif // DATATYPE_H
